//
// Shader that only shows part of sprite based on ratio
// Radially based, 100% is to the left
//
uniform sampler2D BaseTexture;
uniform vec2 uv_topLeft;
uniform vec2 uv_botRight;
uniform float percentage;

const float PI            = 3.1415926;
const float PI_AND_A_HALF = 4.7123889;
const float TWO_PI        = 6.2831852;

float angleBetween(vec2 v1, vec2 v2)
{
	float angle = atan(v2.y, v2.x) - atan(v1.y, v1.x);

	if (angle < 0) { angle += TWO_PI; };

    return atan( v1.x - v2.x, v1.y - v2.y ) + PI;
}

bool shouldDrawFragment(vec2 fragCoord)
{
    float targetAngle = percentage * PI_AND_A_HALF;

    vec2 center = vec2((uv_topLeft.x + uv_botRight.x) / 2.0, (uv_topLeft.y + uv_botRight.y) / 2.0);
	//vec2 full  = vec2(uv_topLeft.x, (uv_topLeft.y + uv_botRight.y) / 2.0);
	//vec2 empty = vec2((uv_topLeft.x + uv_botRight.x) / 2.0, uv_botRight.y);

    float a = angleBetween(center, fragCoord);

    return a <= targetAngle;
}

void main(void)
{
    vec4 Color;

    if (shouldDrawFragment(gl_TexCoord[0].xy))
    	Color = texture(BaseTexture, gl_TexCoord[0].xy).rgba;
	else
		Color = vec4( 0.0, 0.0, 0.0, 0.0 );

    gl_FragColor =  Color;
}