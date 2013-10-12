varying vec3 normal;
varying vec3 vertex;

void main()
{
	// origin color
	
	vec3 vToEye = normalize(-vertex);
	vec4 airColor = vec4(0.6, 0.6, 1.0, 0.4);
	float dotVal = max(dot(normal, vToEye), 0.0);
	float term = 0.0;
	const float threshold = 0.25;
	if (dotVal > threshold)
	{
		term = (1.0 - dotVal) / (1.0 - threshold);
		term *= term;
	}
	else if (dotVal >= 0.0)
	{
		term = dotVal / threshold;
	}

	
	vec4 diffColor = airColor * term;
	
	
	// consider the sun
	
	vec3 sunPos = normalize(gl_LightSource[0].position.xyz);
	sunPos *= 100000.0;
	float sunTerm = max( (dot(normal, normalize(sunPos-vertex))), 0.0 ) + 0.6;

	
	// consider eye position
	float eyeTerm = 0.0;
	float dist = -vertex.z;
	if (dist > 300.0)
	{
		eyeTerm = 1.0;
	}
	else if (dist > 50.0)
	{
		eyeTerm = (dist - 50.0) / 250.0;
	}
	
	
	gl_FragColor =  diffColor * sunTerm * eyeTerm;
}

