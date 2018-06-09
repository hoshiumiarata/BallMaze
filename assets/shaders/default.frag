#version 150
out vec4 color;
uniform mat4 viewMatrix;

in vec3 viewPosition;
in vec3 viewNormal;

struct LightSource
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct Material
{
	bool hasTexture;
	sampler2D texture;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

const int MaxLightSourceNum = 8;

uniform Material material;
uniform LightSource lights[MaxLightSourceNum];

in vec2 pixelTexCoord;

vec4 calculateLight(int i)
{
	vec4 result = vec4(0.0, 0.0, 0.0, 1.0);
	bool isPoint = lights[i].position.w > 0.0;
	vec4 lightPosition = viewMatrix * lights[i].position;
	vec3 lightDirection;

	result += material.ambient * lights[i].ambient;

	if (isPoint)
		lightDirection = normalize(viewPosition - lightPosition.xyz);
	else
		lightDirection = normalize(lightPosition.xyz);

	result += material.diffuse * lights[i].diffuse * clamp(-dot(lightDirection, viewNormal), 0.0, 1.0);

	vec3 reflectedLight = reflect(lightDirection, viewNormal);
	vec3 cameraDirection = normalize(viewPosition);
	result += material.specular * lights[i].specular * clamp(pow(-dot(reflectedLight, cameraDirection), material.shininess), 0.0, 1.0);

	if (isPoint)
	{
		float d = distance(viewPosition, lightPosition.xyz);
		result /= lights[i].constantAttenuation + lights[i].linearAttenuation * d + lights[i].quadraticAttenuation * d * d;
	}

	return result;
}

void main()
{
	color = vec4(0.0, 0.0, 0.0, 0.0);

	for (int i = 0; i < MaxLightSourceNum; i++)
		color += calculateLight(i);

	color += material.emission;

	if (material.hasTexture)
		color = clamp(color, 0.0, 1.0) * texture(material.texture, pixelTexCoord);
}