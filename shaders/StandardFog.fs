#version 130

varying vec2 vTextureCoord;
varying float fogFactor;
varying vec3 vNormal;
varying vec4 shadowPos;
varying vec4 shadow2Pos;

uniform float textureEnabled;
uniform vec4 shapeColor;
uniform float isAlpha;
uniform float alphaTest;
uniform vec4 skyColor;
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform vec3 lightDirection;
uniform sampler2D uSampler;
uniform sampler2D uSampler2;
uniform sampler2DShadow shadow1;
uniform sampler2DShadow shadow2;
uniform float secondTexEnabled;
uniform mat4 uMVMatrix;
uniform mat4 uMSMatrix;
uniform float enableNormals;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

float insideBox(vec2 v, vec2 bottomLeft, vec2 topRight) {
    vec2 s = step(bottomLeft, v) - step(topRight, v);
    return s.x * s.y;   
}

void main() {
        //gl_FragColor  =vec4(1.0,0.0,0.0,1.0);
        if(textureEnabled == 0) {
            gl_FragColor = shapeColor;
        } else {
            gl_FragColor = texture(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
            gl_FragColor.a = max(gl_FragColor.a, isAlpha);  

            if(gl_FragColor.a < alphaTest)
                discard;    
                
            float bias = 0.0025;
            if(enableNormals > 0.0){
                vec3 normal = normalize(mat3(uMVMatrix) * mat3(uMSMatrix) * vNormal);
                vec3 lights = normalize(lightDirection);
                float cosTheta = dot( normal, lights );
                cosTheta = clamp(cosTheta, 0, 1);
                vec4 color = diffuseColor;
                color.xyz *= cosTheta;
                color += ambientColor;
                gl_FragColor *= color;
                bias = bias*tan(acos(cosTheta));
                bias = clamp(bias, 0, 0.005);
            }
            vec4 shadowPos2 = shadowPos*0.5+0.5;
            vec4 shadow2Pos2 = shadow2Pos*0.5+0.5;
            float t = insideBox(shadowPos2.xy, vec2(0, 0), vec2(1, 1));
            float t2 = insideBox(shadow2Pos2.xy, vec2(0, 0), vec2(1, 1));
            float visibility = 1.0;
            for (int i=0;i<4;i++){
		int index = i;
		visibility -= t*0.15*(1.0-texture( shadow1, vec3(shadowPos2.xy + poissonDisk[index]/2000.0, (shadowPos2.z-bias)) ));
                visibility -= (1.0-t)*t2*0.15*(1.0-texture( shadow2, vec3(shadow2Pos2.xy + poissonDisk[index]/4000.0, (shadow2Pos2.z-0.002)) ));
            }
            gl_FragColor.xyz *= visibility;

            gl_FragColor = mix(gl_FragColor, skyColor, fogFactor);
        }
}