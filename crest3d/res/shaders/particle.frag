#version 440

struct Material 
{
	sampler2D m_Diffuse;
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

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position;
in vec4 particlecolor;

// Ouput data
out vec4 color;

uniform Material mat;

uniform PointLight pointLights[32];
uniform DirLight dirLight;

uniform int NOPL;
uniform sampler2D m_Diffuse;
uniform vec3 viewPosition;


vec3 calcDirLight(DirLight dirLight, vec3 normal, vec3 fragPosition, vec3 viewDir)
{
	//vec3 lightDir = normalize(-dirLight.direction);
	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(normal, lightDir), 0.25);
	// vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(normal, lightDir), 0.0), 0.0);

	vec3 ambient;
	vec3 specular;


	ambient = dirLight.diffuse * diff * vec3(texture(mat.m_Diffuse, UV));
	specular = dirLight.specular * spec * vec3(0.0);

	return (ambient  + specular);

}

vec3 calcPointLight(PointLight pointLight, vec3 normal, vec3 fragPosition, vec3 viewDir)
{
	vec3 lightDir = normalize(pointLight.position - fragPosition);
	//vec3 lightDir = normalize(pointLight.direction - fragPosition);
	vec3 reflectDir = reflect(-lightDir,normal);	
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float diff = max(dot(normal, lightDir), 1.0);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 1.0);

	float attenuation = 1.0 / pointLight.distance;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	


	ambient = pointLight.ambient * vec3(texture(mat.m_Diffuse, UV));
	diffuse = pointLight.diffuse * diff * vec3(texture(mat.m_Diffuse, UV));
	specular = pointLight.specular * spec * vec3(0.0);

	ambient *= pointLight.intensity * attenuation;
	diffuse *= pointLight.intensity * attenuation;
	specular *= pointLight.intensity * attenuation;


	return (ambient + diffuse  + specular);
}

bool CloseToBlack(vec3 col)
{
	bool r = false;
	bool g = false;
	bool b = false;

	if(col.x >= 0.0 && col.x <= 0.05)
		r = true;
	if(col.y >= 0.0 && col.y <= 0.05)
		g = true;
	if(col.z >= 0.0 && col.z <= 0.05)
		b = true;

	if(r == true && g == true)
	{
		if(b == true)
		{
			return true;
		}
	}

	return false;
}

void main(){
	// Output color = color of the texture at the specified UV
	vec4 tex = texture( mat.m_Diffuse, UV ) * particlecolor;
	if(tex.a < 0.1)
		discard;

	if(CloseToBlack(tex.xyz) == true)
		discard;

	vec3 norm = normalize(Position);
	vec3 viewDirection = normalize(viewPosition -Position);

	

	vec3 result = vec3(tex.x * 0.01, tex.y * 0.01, tex.z * 0.01);
	
	result += calcDirLight(dirLight, norm, Position, viewDirection);

	for(int i = 0; i < NOPL; i++)
	{
		result += calcPointLight(pointLights[i], norm, Position, viewDirection);
	}
	
	color = vec4(result, 0.0);
}