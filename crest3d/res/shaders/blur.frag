
#version 330 core

out vec4 FragColor;
/////////////////////////////////////////////////
// 7x1 gaussian blur fragment shader
/////////////////////////////////////////////////

in vec2 vTexCoords;

uniform vec2 scale;
uniform sampler2D screenTexture;

vec2 gaussFilter[7] = vec2[](

	vec2(-3.0,	0.015625),
	vec2(-2.0,	0.09375),
	vec2(-1.0,	0.234375),
	vec2(0.0,	0.3125),
	vec2(1.0,	0.234375),
	vec2(2.0,	0.09375),
	vec2(3.0,	0.015625)
);

void main()
{
	vec4 color = vec4(0.0);
	for( int i = 0; i < 15; i++ )
	{
		color += texture2D( screenTexture, vec2( vTexCoords.x+gaussFilter[i].x*scale.x, vTexCoords.y+gaussFilter[i].x*scale.y ) )*gaussFilter[i].y;
	}

	if(color.r < 0.3)
	{
		color = vec4(0.0);
	}
	FragColor = color / 15;
}
