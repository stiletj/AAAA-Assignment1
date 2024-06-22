#shader vertex
#version 330 core
 
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord; 

out vec2 v_TexCoord; 
out vec3 Normal0;
out vec3 LocalPos0;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord; 
    Normal0 = normal;
    LocalPos0.x = position.x;
    LocalPos0.y = position.y;
    LocalPos0.z = position.z;
};
 
#shader fragment
#version 330 core

const int MAX_POINT_LIGHTS = 2;

layout(location = 0) out vec4 color;

in vec2 v_TexCoord; 
in vec3 Normal0;
in vec3 LocalPos0;

uniform sampler2D u_Texture; 
uniform int u_HasTexture; 

uniform float u_AmbientIntensity;
uniform vec4 u_LightColour;
uniform vec4 u_AmbientColour;

uniform vec3 u_Direction;
uniform float u_DiffuseIntensity;
uniform vec4 u_DiffuseColour;

uniform vec4 u_SpecularColour;
uniform float u_SpecularExponent;
uniform vec3 u_LocalCamPos;

uniform vec3 u_PointPositions[MAX_POINT_LIGHTS];
uniform vec4 u_PointColours[MAX_POINT_LIGHTS];
uniform float u_PointAmbientIntensities[MAX_POINT_LIGHTS];
uniform float u_PointDiffuseIntensities[MAX_POINT_LIGHTS];
uniform float u_PointConstants[MAX_POINT_LIGHTS];
uniform float u_PointLinears[MAX_POINT_LIGHTS];
uniform float u_PointExps[MAX_POINT_LIGHTS];
uniform int u_NumOfPoints;

uniform int u_IsLight;

vec4 CalcLightInternal(float ambientIntensity, float diffuseIntensity, vec4 lightColour, vec3 direction, vec3 Normal)
{
    vec4 AmbientColour = lightColour * ambientIntensity * u_AmbientColour;

    float DiffuseFactor = dot(normalize(Normal), -direction);

    vec4 DiffuseColour = vec4(0, 0, 0, 0);
    vec4 SpecularColour = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0)
    {
	DiffuseColour = lightColour * diffuseIntensity * u_DiffuseColour * DiffuseFactor;

	vec3 PixelToCamera = normalize(u_LocalCamPos - LocalPos0);
	vec3 LightReflect = normalize(reflect(direction, Normal));
	float SpecularFactor = dot(PixelToCamera, LightReflect);

	if (SpecularFactor > 0)
	{
	    SpecularFactor = pow(SpecularFactor, u_SpecularExponent);
	    SpecularColour = lightColour * u_SpecularColour * SpecularFactor;
	}
    }

    return (AmbientColour + DiffuseColour + SpecularColour);
}

vec4 CalcDirectionalLight(vec3 Normal)
{
    return CalcLightInternal(u_AmbientIntensity, u_DiffuseIntensity, u_LightColour, u_Direction, Normal);
}

vec4 CalcPointLight(int Index, vec3 Normal)
{
    vec3 LightDirection = LocalPos0 - u_PointPositions[Index];
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 Colour = CalcLightInternal(u_PointAmbientIntensities[Index], u_PointDiffuseIntensities[Index], u_PointColours[Index], LightDirection, Normal);
    float Attenuation = u_PointConstants[Index] + u_PointLinears[Index] * Distance + u_PointExps[Index] * Distance * Distance;

    return Colour / Attenuation;
}

void main()
{
    vec4 TotalLight = vec4(0.f, 0.f, 0.f, 0.f);

    vec3 Normal = normalize(Normal0);

    if (u_IsLight == 1)
    {
    	TotalLight += CalcDirectionalLight(Normal);
    }
    else
    {
	TotalLight = u_LightColour * u_AmbientIntensity * u_AmbientColour;
    }

    for (int i = 0; i < u_NumOfPoints; i++)
    {
        TotalLight += CalcPointLight(i, Normal);
    }

    if (u_HasTexture == 1)
    {
    	vec4 texColor = texture(u_Texture, v_TexCoord);
    	color = texColor * TotalLight; 
    }
    else
    {
	color = TotalLight;
    }
};