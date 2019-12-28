#version 440

out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

struct Material 
{
	sampler2D m_Diffuse;
	sampler2D m_Normal;
	sampler2D m_Metallic;
	sampler2D m_Roughness;
    sampler2D m_AO;
	float m_Shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float intensity;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float distance;
};

// num lights
uniform int numPointLights = 32;

// material parameters
uniform Material mat;

uniform DirLight dirLight;
uniform PointLight pointLights[32];

uniform vec3 viewPosition;

const float PI = 3.14159265359;

// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.

vec3 getNormalFromMap()
{
    vec3 tangentNormal =texture(mat.m_Normal, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------
// infinite distance needs fixed
vec3 calculatePointLight(vec3 albedo, vec3 N, vec3 F0, vec3 V, float roughness, float metallic, PointLight pl)
{
    // calculate per-light radiance
    vec3 L = normalize(pl.position - WorldPos);
    vec3 H = normalize(V + L);

    float distance = length(pl.position - WorldPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = pl.diffuse * (attenuation * pl.distance);

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3 specular = nominator / denominator;
    
    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallic;	  

    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0);        
    vec3 diffuse = NdotL * albedo; 
    // add to outgoing radiance Lo
    return (kD * diffuse / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
}


vec3 calculateDirectionalLight(vec3 albedo, vec3 N, vec3 F0, vec3 V, float roughness, float metallic)
{
    vec3 L = normalize(-dirLight.direction);
    vec3 H = normalize(V + L);

    vec3 radiance = dirLight.diffuse;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3 specular = nominator / denominator;
    
    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallic;	  

    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0); 
    vec3 diffuse = NdotL * albedo;       

    // add to outgoing radiance Lo
    return (kD * diffuse / PI + specular) * radiance * NdotL;
}

void main()
{
    vec4 rawTex = texture(mat.m_Diffuse, TexCoords);
    if(rawTex.a < 0.1)
        discard;		
    vec3 albedo     = pow(rawTex.rgb, vec3(2.2));
    float metallic  = texture(mat.m_Metallic, TexCoords).r;
    float roughness = texture(mat.m_Roughness, TexCoords).r;
    float ao        = texture(mat.m_AO, TexCoords).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(viewPosition - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);

    Lo += calculateDirectionalLight(albedo, N, F0, V, roughness, metallic);

    for(int i = 0; i < numPointLights; i++) 
    {
         Lo += calculatePointLight(albedo, N, F0, V, roughness, metallic, pointLights[i]);  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }   
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = dirLight.ambient * albedo * ao;
    
    // float edgeDetection = (dot(V, N) > 0.1) ? 1 : 0;

    // vec3 color = edgeDetection * (ambient + Lo);
    vec3 color = ambient + Lo;
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    // FragColor = vec4(color, 1.0);
    FragColor = vec4(color, 1.0);
}