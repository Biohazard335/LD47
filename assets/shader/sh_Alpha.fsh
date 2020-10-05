//
// Simple passthrough fragment shader with a uniform for changing the alpha
//
uniform sampler2D BaseTexture;
uniform float alpha;

void main(void)
{
    vec4 Color;
    Color = vec4(texture(BaseTexture, gl_TexCoord[0].xy).rgb, alpha);
    gl_FragColor =  Color;
}