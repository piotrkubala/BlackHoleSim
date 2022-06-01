#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.141592653589793
#define ONE_2PI 0.15915494309189535
#define ONE_PI 0.3183098861837907

uniform vec2 u_resolution;

uniform sampler2D u_background;

uniform float u_angle;

uniform float u_time;

vec3 wektorKierunkuSwiatla(vec2 polozenie)
{
    float tangens = 1.0 / tan(u_angle * PI / 180.0);
    vec3 v = vec3(polozenie, 0.0) - vec3(0.0, 0.0, -tangens);

    return v / length(v);
}

vec2 znajdzPunktTekstury(vec3 kierunek)
{
    //return vec2(atan(kierunek.z, kierunek.x) * ONE_2PI + 0.5, kierunek.y * 0.5 + 0.5);

    float dlugosc = atan2(kierunek.z, kierunek.x) * ONE_2PI + 0.5;
    float szerokosc = (asin(kierunek.y / length(kierunek)) * ONE_PI  + 0.5);

    return vec2(dlugosc, szerokosc);
}

vec3 obrotZ(float x, vec3 v)
{
    float c = cos(x), s = sin(x);
    return vec3(c * v.x + s * v.y, -s * v.x + c * v.y, v.z);
}

vec3 obrotY(float x, vec3 v)
{
    float c = cos(x), s = sin(x);
    return vec3(c * v.x + s * v.z, v.y, -s * v.x + c * v.z);
}

vec3 obrotX(float x, vec3 v)
{
    float c = cos(x), s = sin(x);
    return vec3(v.x, c * v.y + s * v.z, -s * v.y + c * v.z);
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution.xy;

    float wspolczynnik = u_resolution.x / u_resolution.y;
    
    st -= 0.5;
    st.x *= wspolczynnik;

    vec3 color = texture(u_background, znajdzPunktTekstury(obrotY(u_time * 1.4213 * 0.1, obrotX(u_time * 0.1, wektorKierunkuSwiatla(st)))));

    gl_FragColor = vec4(color,1.0);
}