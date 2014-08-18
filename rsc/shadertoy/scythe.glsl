// by Otavio Good: https://www.shadertoy.com/view/Ms2GDV
// Set this to 1.0 for crazy morphing animation.
#define crazyAnim 0.0

float PI=3.14159265;
vec3 sunCol = vec3(258.0, 208.0, 100.0) / 255.0;
vec3 environmentSphereColor = vec3(0.3001, 0.501, 0.901);

float distFromSphere;
vec3 normal;
vec3 texBlurry;

vec3 saturate(vec3 a)
{
	return clamp(a, 0.0, 1.0);
}
vec2 saturate(vec2 a)
{
	return clamp(a, 0.0, 1.0);
}
float saturate(float a)
{
	return clamp(a, 0.0, 1.0);
}

vec3 RotateX(vec3 v, float rad)
{
	float cos = cos(rad);
	float sin = sin(rad);
	//if (RIGHT_HANDED_COORD)
	return vec3(v.x, cos * v.y + sin * v.z, -sin * v.y + cos * v.z);
	//else return new float3(x, cos * y - sin * z, sin * y + cos * z);
}
vec3 RotateY(vec3 v, float rad)
{
	float cos = cos(rad);
	float sin = sin(rad);
	//if (RIGHT_HANDED_COORD)
	return vec3(cos * v.x - sin * v.z, v.y, sin * v.x + cos * v.z);
	//else return new float3(cos * x + sin * z, y, -sin * x + cos * z);
}
vec3 RotateZ(vec3 v, float rad)
{
	float cos = cos(rad);
	float sin = sin(rad);
	//if (RIGHT_HANDED_COORD)
	return vec3(cos * v.x + sin * v.y, -sin * v.x + cos * v.y, v.z);
}

	
// polynomial smooth min (k = 0.1);
float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}
// exponential smooth min (k = 32);
/*float smin( float a, float b, float k )
{
    float res = exp( -k*a ) + exp( -k*b );
    return -log( res )/k;
}*/

// This function basically is a procedural environment map that makes the sun and sky.
// (I deleted the sky to make it more gloomy)
vec3 GetSunColorReflection(vec3 rayDir, vec3 sunDir)
{
	vec3 localRay = normalize(rayDir);
	float sunIntensity = 1.0 - (dot(localRay, sunDir) * 0.5 + 0.5);
	//sunIntensity = (float)Math.Pow(sunIntensity, 14.0);
	sunIntensity = 0.1 / sunIntensity;
	sunIntensity = min(sunIntensity, 40000.0);
	return environmentSphereColor * 0.01 + sunCol * sunIntensity;
}

float IntersectSphereAndRay(vec3 pos, float radius, vec3 posA, vec3 posB, out vec3 intersectA2, out vec3 intersectB2)
{
	// Use dot product along line to find closest point on line
	vec3 eyeVec2 = normalize(posB-posA);
	float dp = dot(eyeVec2, pos - posA);
	vec3 pointOnLine = eyeVec2 * dp + posA;
	// Clamp that point to line end points if outside
	//if ((dp - radius) < 0) pointOnLine = posA;
	//if ((dp + radius) > (posB-posA).Length()) pointOnLine = posB;
	// Distance formula from that point to sphere center, compare with radius.
	float distance = length(pointOnLine - pos);
	float ac = radius*radius - distance*distance;
	float rightLen = 0.0;
	if (ac >= 0.0) rightLen = sqrt(ac);
	intersectA2 = pointOnLine - eyeVec2 * rightLen;
	intersectB2 = pointOnLine + eyeVec2 * rightLen;
	distFromSphere = distance - radius;
	if (distance <= radius) return 1.0;
	return 0.0;
}

float dSphere(vec3 p, float rad)
{
	//vec3 center = vec3(0, 0, 0.0);
	//p -= center;
	//rad += sin(p.y * 32.0 - iGlobalTime * 8.0) * 0.01;
	// This makes a basic sphere.
	return length(p) - rad;
}
float dSphereWave(vec3 p, float rad)
{
	//vec3 center = vec3(0, 0, 0.0);
	//p -= center;
	rad -= 0.05;
	rad += sin(p.y * 8.0 - iGlobalTime * 2.0) * 0.03;
	return length(p) - rad;
}

float dBox(vec3 pos)
{
	float b = 0.8;
	vec3 center = vec3(0, 0, 0.0);
	return length(max(abs(pos - center)-(b*(cos(pos.y))),0.0));
}

float dBoxSigned(vec3 p)
{
	// This makes a twisted box that is cut off.
	float b = 0.8;
	//vec3 center = vec3(0, 0, 0.0);
	p = RotateY(p, (p.y * cos(iGlobalTime*crazyAnim)-0.24)*PI);
	vec3 d = abs(p /*- center*/) - b*abs(cos(p.y + 0.5));
	return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

float dFloor(vec3 p)
{
	return p.y + 2.0;
}

float sdCylinder( vec3 p, vec3 c )
{
  return length(p.xz-c.xy)-c.z + abs(p.y)*0.05;
}

float dJank(vec3 p)
{
	//p += vec3(0.0, -1.54, 0.0);
	p += vec3(0.0, -1.62, 0.0);
	// This makes the janky blade object. It's really just a sphere subtracted from a cube,
	// but twisted and cut off.
	return max(dBoxSigned(p), -dSphere(p, 1.0));
}

float dSquareJank(vec3 p)
{
	// This copies 5 rotations of the basic janky blade object. The 5 rotations make most of a cube.
	// I use smin() function to smoothly blend between the 5 objects.
	float final = dJank(p);
	//const float blend = 7.0;// 0.41;
	const float blend = 0.41;
	vec3 p2 = p.xzy * vec3(1.0, 1.0, -1.0);// RotateX(p, PI/2.0);
	//vec3 p2 = RotateX(p, PI/2.0);
	final = smin(final, dJank(p2), blend);
	p2 = p.xzy * vec3(1.0, -1.0, 1.0);//  RotateX(p, -PI/2.0);
	//p2 = RotateX(p, -PI/2.0);
	final = smin(final, dJank(p2), blend);
	p2 = p.yxz * vec3(1.0, -1.0, 1.0);// RotateZ(p, PI/2.0);
	//p2 = RotateZ(p, PI/2.0);
	final = smin(final, dJank(p2), blend);
	p2 = p.yxz * vec3(-1.0, 1.0, 1.0);// RotateZ(p, -PI/2.0);
	//p2 = RotateZ(p, -PI/2.0);
	final = smin(final, dJank(p2), blend);
	p2 = p.xyz * vec3(1.0, -1.0, -1.0);
	//final = smin(final, dJank(p2), blend);
	return final;
}

float DistanceToObject(vec3 p)
{
	//vec3 c = vec3(1.0, 1.0, 1.0)* 1.0;
	//vec3 q = mod(p,c)-0.5*c;
	//p = q;

	// This makes the janky-looking blade object.
	float final = dSquareJank(p);
	// This makes the wavy sphere on the inside.
	final = min(final, dSphereWave(p, 0.1 + sin(iGlobalTime*0.0) * 0.015 + 0.87));
	//final = smin(final, sdCylinder(p, vec3(0.0, 0.0, 0.001) ), 0.5);
	//final = min(final, dFloor(p));
	return final;
	//return clamp((distance(pos, vec3(0, 0, 1.0)) - 1.0), 0.0, 1.0);
	//return dSphere(pos);
}

void main(void)
{
	// ---------------- First, set up the camera rays for ray marching ----------------
	vec2 uv = gl_FragCoord.xy/iResolution.xy * 2.0 - 1.0;// - 0.5;

	// Camera up vector.
	vec3 camUp=vec3(0,1,0); // vuv

	// Camera lookat.
	vec3 camLookat=vec3(0,0.0,0);	// vrp

	float mx=iMouse.x/iResolution.x*PI*2.0 + iGlobalTime * 0.1;
	float my=-iMouse.y/iResolution.y*10.0 + sin(iGlobalTime * 0.3)*0.2+0.2;//*PI/2.01;
	vec3 camPos=vec3(cos(my)*cos(mx),sin(my),cos(my)*sin(mx))*(2.6); 	// prp

	// Camera setup.
	vec3 camVec=normalize(camLookat - camPos);//vpn
	vec3 sideNorm=normalize(cross(camUp, camVec));	// u
	vec3 upNorm=cross(camVec, sideNorm);//v
	vec3 worldFacing=(camPos + camVec);//vcv
	vec3 worldPix = worldFacing + uv.x * sideNorm * (iResolution.x/iResolution.y) + uv.y * upNorm;//scrCoord
	vec3 relVec = normalize(worldPix - camPos);//scp

	// --------------------------------------------------------------------------------
	// I put a bounding sphere around the whole object. If the ray is outside
	// of the bounding sphere, I don't bother ray marching. It's just an optimization.
	vec3 iA, iB;
	float hit = IntersectSphereAndRay(vec3(0,0,0), 1.9, camPos, camPos+relVec,
									  iA, iB);

	// --------------------------------------------------------------------------------
	float dist = 0.02;
	float t = 0.5;
	float inc = 0.02;
	float maxDepth = 6.0;
	vec3 pos = vec3(0,0,0);
	// ray marching time
	if (hit > 0.5)	// check if inside bounding sphere before wasting time ray marching.
	{
		for (int i = 0; i < 180; i++)	// This is the count of how many times the ray actually marches.
		{
			if ((t > maxDepth) || (abs(dist) < 0.001)) continue;	// break DOESN'T WORK!!! ARRRGGG!
			pos = camPos + relVec * t;
			// *******************************************************
			// This is _the_ function that defines the "distance field".
			// It's really what makes the scene geometry.
			// *******************************************************
			dist = DistanceToObject(pos);
			inc = dist;
			t += inc * 0.45;	// because deformations mess up distance function.
			
	//		if ((t > maxDepth) || (abs(dist) < 0.001)) break;
		}
	}
	else
	{
		t = maxDepth + 1.0;
	}

	// --------------------------------------------------------------------------------
	// Now that we have done our ray marching, let's put some color on this geometry.

	vec3 sunDir = normalize(vec3(1.0, 1.0, 0.0));
	// This sun color value will only be used as a backup in case no ray hits the object.
	vec3 finalColor = GetSunColorReflection(relVec, sunDir) + vec3(0.1, 0.1, 0.1);

	// calculate the normal from the distance field. The distance field is a volume, so if you
	// sample the current point and neighboring points, you can use the difference to get
	// the normal.
	vec3 smallVec = vec3(0.02, 0, 0);
	vec3 normal = vec3(dist - DistanceToObject(pos - smallVec.xyy),
					   dist - DistanceToObject(pos - smallVec.yxy),
					   dist - DistanceToObject(pos - smallVec.yyx));
	normal = normalize(normal);

	// calculate the reflection vector for highlights
	vec3 ref = reflect(relVec, normal);
	
	// This is the rainbow coloring for the inside wavy sphere.
	vec3 spinner = abs(RotateY(normal * normal, iGlobalTime* 2.0)) * vec3(1.0, 1.0, 1.0);
	vec3 inner = abs(RotateY((-normal) * (-normal), iGlobalTime* 2.0)) * vec3(1.0, 1.0, 1.0);
	// get some texture on that inner wavy rainbow sphere.
	//vec4 texX = texture2D(iChannel0, normal.yz);// * vec2(0.925, 0.0) + vec2(iGlobalTime*1.0, 0.0));
	//vec4 texZ = texture2D(iChannel0, normal.xy);// * vec2(0.0, 0.925) + vec2(0.0, iGlobalTime*1.0));
	vec4 texX = white; // need to add iChannel0
	vec4 texZ = black; // need to add iChannel0
	vec4 noise = mix(texX, texZ, abs(normal.z));

	// If a ray actually hit the object, let's light it.
	if (t <= maxDepth)
	{
		finalColor = GetSunColorReflection(ref, sunDir)*0.68;// sunCol * max(0.0, dot(normal, -sunDir));
		// make a darker stripe in the middle, redder towards the top and bottom
		finalColor *= vec3(0.3 + abs(pos.y*pos.y), 0.35, 0.3);
		// we need the glowy rainbow sphere to illuminate the blade object from the inside.
		vec3 innerLight = inner * 2.0 * max(0.0,dot(pos, -normal)) + vec3(1.0,1.0,1.0)*0.3;
		innerLight *= (1.45 - length(pos));
		finalColor += max(vec3(0,0,0),innerLight);
		finalColor += vec3(0.02, 0.050, 0.09);
		//finalColor = sunCol * max(0.0, dot(normal, sunDir));

		// If we are inside a certain radius, call it the inner sphere and make it rainbow colors.
		if ((length(pos) < 1.0) || (length(pos.xz) < 0.5))
		{
			finalColor = spinner*2.0 + vec3(1.0,1.0,1.0)*0.25;
			finalColor += noise.xyz*0.15;
		}
	}
	//finalColor += hit*0.1;

	// output the final color with sqrt for "gamma correction"
	gl_FragColor = vec4(sqrt(clamp(finalColor, 0.0, 1.0)),1.0);
}
