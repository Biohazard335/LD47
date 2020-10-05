//
// Simple passthrough fragment shader
//
uniform sampler2D BaseTexture;
uniform vec2 pos;
const int Quality = 16;

void main(void)
{
    vec4 Color;
    float v;
    for( float i=0.0;i<1.0;i+=1.0/float(Quality) )
    {
            v = 0.9+i*0.1;//convert "i" to the 0.9 to 1 range
            Color += texture(BaseTexture, gl_TexCoord[0].xy*v+(pos)*(1.0-v)).rgba;
    }
    Color /= float(Quality);
    gl_FragColor =  Color *  gl_Color;
}