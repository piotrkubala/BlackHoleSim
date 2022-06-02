#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.141592653589793
#define ONE_2PI 0.15915494309189535
#define ONE_PI 0.3183098861837907

#define MAX_IT 100000

uniform vec2 u_resolution;

uniform sampler2D u_background;

uniform float u_angle;
uniform float u_maxDfi;
uniform float u_alfaParam;

uniform vec3 u_polozeniePocz;

uniform vec3 u_baseX;
uniform vec3 u_baseY;
uniform vec3 u_baseZ;

uniform float u_time;

vec3 wektorKierunkuSwiatla(vec2 polozenie)
{
    float tangens = 1.0 / tan(u_angle * PI / 180.0);
    vec3 v = vec3(polozenie, 0.0) - vec3(0.0, 0.0, tangens);

    v = v.x * u_baseX + v.y * u_baseY + v.z * u_baseZ;

    return v / length(v);
}

vec2 znajdzPunktTekstury(vec3 kierunek)
{
    float dlugosc = atan(kierunek.z, kierunek.x) * ONE_2PI + 0.5;
    float szerokosc = (asin(kierunek.y) * ONE_PI  + 0.5);

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

// os musi miec dlugosc 1
vec3 obrotWokolWekt(float angle, vec3 os, vec3 v)
{
    vec3 rownolegly = dot(os, v) * os;
    vec3 prost1 = v - rownolegly;

    float dlugoscProst = length(prost1);

    if(dlugoscProst == 0.0)
        return v;

    prost1 /= dlugoscProst;
    vec3 prost2 = cross(os, prost1);

    return rownolegly + (prost1 * cos(angle) + prost2 * sin(angle)) * dlugoscProst;
}

float dro_dfi(vec3 polozenie, vec3 kier, float odl)
{
    vec3 bazaR = -polozenie / odl;
    float rown = dot(kier, bazaR);
    float prost = length(kier - rown * bazaR);

    return -rown / (odl * prost);
}

float policzDobreDfi(float ro)
{
    return u_maxDfi * (1.0 - 0.5 / (1.0 + ro * ro));
}

vec3 znajdzWektorKierWNiesk(vec3 polozenie, vec3 kier)
{
    float r = length(polozenie);
    vec3 bazaX = polozenie / r, bazaY;
    bazaY = kier - dot(bazaX, kier) * bazaX;

    float dlBazaY = length(bazaY);

    if(dlBazaY == 0.0)
    {
        if(dot(polozenie, kier) <= 0.0)
            return vec3(0.0);
        else
            return kier;
    }

    float ro = 1.0 / r, fi = 0.0, pochRo = dro_dfi(polozenie, kier, r), dfi;

    for(int i = 0; i < MAX_IT; i++)
    {
        float d2ro_dfi2 = (u_alfaParam * ro - 1.0) * ro;

        dfi = policzDobreDfi(ro);

        float dro = (pochRo + 0.5 * d2ro_dfi2 * dfi) * dfi;

        if(ro + dro <= 1.0e-4)
            break;

        if((ro + dro) * ro < 0.0)
            break;

        pochRo += d2ro_dfi2 * dfi;
        ro += dro;
        fi += dfi;

        if(1.0 <= 2.0 * u_alfaParam / 3.0 * ro && 1.0 < ro * r)
            return vec3(0.0);

        if(1.0 >= 1.0e6 * ro)
            break;
    }

    if(1.0 <= 2.0 * u_alfaParam / 3.0 * ro && 1.0 < ro * r)
        return vec3(0.0);

    dfi = u_maxDfi;
    float r_nowe = 1.0 / ro;
    float pochR = -r_nowe * r_nowe * pochRo;

    if(pochR == 0.0)
        return vec3(0.0);
    
    vec3 polNowe1 = (bazaX * cos(fi) + bazaY * sin(fi)) * r_nowe, polNowe2 = (bazaX * cos(fi + dfi) + bazaY * sin(fi + dfi)) * (r_nowe + pochR * dfi);
    vec3 kierNowy = polNowe2 - polNowe1;

    return kierNowy / length(kierNowy);
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution.xy;

    float wspolczynnik = u_resolution.x / u_resolution.y;
    
    st -= 0.5;
    st.x *= wspolczynnik;

    vec3 kierSwiatla = wektorKierunkuSwiatla(st);

    kierSwiatla = znajdzWektorKierWNiesk(u_polozeniePocz, kierSwiatla);

    vec4 color = vec4(0.0);
    
    if(kierSwiatla != vec3(0.0))
        color = texture2D(u_background, znajdzPunktTekstury(kierSwiatla));

    gl_FragColor = color;
}