//
// Shader that only shows part of sprite based on ratio
// Y-aligned, depletes from top to bottom
//
uniform sampler2D BaseTexture;
uniform float percentage;
uniform vec2 v_bounds; // Top, then bottom v bounds of sprite on uv map

void main(void)
{
	vec4 color;

	float threshold = v_bounds[0] + ((v_bounds[1] - v_bounds[0]) * (1.0 - percentage));

	if (gl_TexCoord[0].y < threshold)
		color = vec4( texture2D(BaseTexture,gl_TexCoord[0].xy).rgb, 0.0 );
	else
		color = vec4( texture2D(BaseTexture,gl_TexCoord[0].xy).rgba );

    gl_FragColor = color;
}