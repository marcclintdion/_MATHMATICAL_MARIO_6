varying vec4 position;

float distance;  
float attenuation;

vec4 finalcolor;
vec4 specularcolor;
vec4 diffuse = vec4(2.0,2.0,2.0,1.0);

vec3 normal;
vec3 lightDir;

vec3  halfV;
float NdotL;
float NdotHV;

varying vec3 halfVector;

uniform sampler2D Texture1;			    
		

void main( void )
{

	lightDir = normalize(vec3(gl_LightSource[0].position - position));
	distance = length(vec3(gl_LightSource[0].position - position));
	
   
    attenuation = 1.00 / (gl_LightSource[0].constantAttenuation +
				  gl_LightSource[0].linearAttenuation * distance +
				  gl_LightSource[0].quadraticAttenuation * distance * distance);

    
    finalcolor    = texture2D(Texture1,gl_TexCoord[0].xy);  
    finalcolor   *= attenuation *diffuse; 
    
    gl_FragColor = finalcolor;
}
