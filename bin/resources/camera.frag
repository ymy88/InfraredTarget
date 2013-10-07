uniform sampler2D   tex; 
const vec2        pixelSize = vec2(1.0/512.0, 1.0/512.0);
const float       Gaussian_a = 1.0;
const float       Gaussian_c = 1.5;
const float       RANGE = 1.0;
  
const float e = 2.71828183;  
  
float Gaussian(float x)   
{  
    return Gaussian_a * pow(e, -x*x/(Gaussian_c*Gaussian_c) );  
}  
  
void main()  
{  
    vec2 halfPixelSize = pixelSize.xy / 2.0;  
    vec4 cOut = vec4(0.0, 0.0, 0.0, 1.0);      
    vec2 texCoordSample = gl_TexCoord[0].st;  
  
    float gaussTotal = 0.0;  
    float x,y;  
    float temp;  
  
    for (y=-RANGE; y<=RANGE; y+=1.0)  
    {  
        for (x=-RANGE; x<=RANGE; x+=1.0)  
        {  
            temp = Gaussian( sqrt( x*x + y*y ) );  
            gaussTotal += temp;  
            cOut += temp * texture2D(tex, texCoordSample + vec2(x,y) * pixelSize);  
        }  
    }  
  
    cOut /= gaussTotal; 
    gl_FragColor = cOut;  
}  
