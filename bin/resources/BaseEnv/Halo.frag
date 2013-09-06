varying vec3 normal;
varying vec3 vertex;

void main()
{
	// origin color
	
	vec3 vToEye = normalize(-vertex);
	vec4 airColor = vec4(0.5, 0.5, 1, 0.7);
	float dotVal = max(dot(normal, vToEye), 0.0);
	float term = 0;
	const float threshold = 0.2;
	if (dotVal > threshold)
	{
		term = (1 - dotVal) / (1 - threshold);
		term *= term;
	}
	else if (dotVal >= 0)
	{
		term = dotVal / threshold;
	}

	
	vec4 Idiff = airColor * term;
	
	
	// consider the sun
	
	vec3 sunPos = gl_LightSource[0].position.xyz;
	float sunTerm = 1.0 * (dot(normal, normalize(sunPos-vertex)) + 1.0);
	
	
	// consider eye position
	float eyeTerm = 0;
	float dist = -vertex.z;
	if (dist > 300.0)
	{
		eyeTerm = 1;
	}
	else if (dist > 0.0)
	{
		eyeTerm = dist / 300.0;
	}
	
	
	gl_FragColor =  Idiff * sunTerm * eyeTerm;
}

