// by iq:  https://www.shadertoy.com/view/MdX3zr
// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

float distanceToSegment( vec2 a, vec2 b, vec2 p )
{
	vec2 pa = p - a;
	vec2 ba = b - a;
	float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	return length( pa - ba*h );
}

void main( void )
{
	vec2 p = gl_FragCoord.xy / iResolution.xx;
    vec4 m = iMouse / iResolution.xxxx;
	
	vec3 col = vec3(0.0);

	if( m.z>0.0 )
	{
		float d = distanceToSegment( m.xy, m.zw, p );
        col = mix( col, vec3(1.0,1.0,0.0), 1.0-smoothstep(.005,0.006, d) );
	}

	col = mix( col, vec3(1.0,0.0,0.0), 1.0-smoothstep(.03,0.04, length(p-m.xy)) );
    col = mix( col, vec3(0.0,0.0,1.0), 1.0-smoothstep(.03,0.04, length(p-abs(m.zw))) );

	gl_FragColor = vec4( col, 1.0 );
}
