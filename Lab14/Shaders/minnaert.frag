#version 330 core
varying	vec3 l;
varying	vec3 h;
varying vec3 v;
varying vec3 n;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    float specular;
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 attenuation;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerAngle;
    float outerAngle;
  
    vec3 attenuation;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform float k = 0.8;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform PointLight pointLight2;
uniform PointLight pointLight3;
uniform PointLight pointLight4;
uniform PointLight pointLight5;
uniform SpotLight spotLight;
uniform vec3 viewPos;

// Directional light
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    vec3 diffuse = light.diffuse  * vec3(texture(material.diffuse, TexCoord));
    float d1 = pow ( max ( dot ( normal, lightDir ), 0.0 ), 1.0 + k );
    float d2 = pow ( 1.0 - dot ( normal, viewDir ), 1.0 - k );

    return (diffuse * d1 * d2) + ambient;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoord));
    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * (dist * dist));
    float d1 = pow ( max ( dot ( normal, lightDir ), 0.0 ), 1.0 + k );
    float d2 = pow ( 1.0 - dot ( normal, viewDir ), 1.0 - k );
    return (diffuse * d1 * d2 + ambient)* attenuation ;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * (dist * dist));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerAngle - light.outerAngle;
    float intensity = clamp((theta - light.outerAngle) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse = light.diffuse  * vec3(texture(material.diffuse, TexCoord));
    float d1 = pow ( max ( dot ( normal, lightDir ), 0.0 ), 1.0 + k );
    float d2 = pow ( 1.0 - dot ( normal, viewDir ), 1.0 - k );

    return (diffuse * d1 * d2+ ambient) * attenuation*intensity ;
}

void main()
{


    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos);
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    result += CalculateDirectionalLight(directionalLight, norm, viewDir);
    result += CalculatePointLight(pointLight, norm, FragPos, viewDir);
    result += CalculatePointLight(pointLight2, norm, FragPos, viewDir);   
    result += CalculatePointLight(pointLight3, norm, FragPos, viewDir);   
    result += CalculatePointLight(pointLight4, norm, FragPos, viewDir);   
    result += CalculatePointLight(pointLight5, norm, FragPos, viewDir);   
    result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}