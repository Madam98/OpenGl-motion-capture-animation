#version 330

struct Light{
	vec3 position;
	//vec3 direction;
	//float cutOff;
	//float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 4

uniform sampler2D tex;
uniform Light light[NR_POINT_LIGHTS];
uniform vec3 viewPos;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in float i_nl;
in vec2 i_tc;
in vec3 FragPos;
in vec3 Normals;

//prototyp funkcji
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos);

void main(void) {
	vec3 norm = normalize(Normals);
	vec3 result;
	for(int i = 0; i<NR_POINT_LIGHTS; i++){
		result += CalcLight(light[i],norm,FragPos);
	}
    //vec4 color=texture(tex,i_tc);
	//pixelColor=vec4(color.rgb*i_nl,color.a);
	pixelColor = vec4(result,1.0);
}

vec3 CalcLight(Light light, vec3 normal, vec3 fragPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 viewDir = normalize(light.position - FragPos);
	vec3 reflectionDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectionDir),0.0),1);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*(distance*distance));
	//float theta = dot(lightDir, normalize(-light.direction));
	//float epsilon = light.cutOff - light.outerCutOff;
	//float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);
	vec3 ambient = light.ambient * texture(tex,i_tc).rgb;
	vec3 diffuse = light.diffuse * diff * texture(tex,i_tc).rgb;
	vec3 specular = light.specular * spec * texture(tex,i_tc).rgb;
	//ambient *= attenuation * intensity;
	//diffuse *= attenuation * intensity;
	//specular *= attenuation * intensity;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}