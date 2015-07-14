#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 7
//                     - Aufgabe 22 (Phong)
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

in vec3 normal;
in vec4 vertex;

out vec4 out_color;

uniform vec4 light_pos;
uniform vec4 light_iAmbient;
uniform vec4 light_iDiffuse;
uniform vec4 light_iSpecular;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform vec4 material_emission;
uniform float material_shininess;

void main()
{
    ///////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 22
    // Implement phong shading.
    ///////////////////////////////////////////////////////////////////
    vec3 normN = normalize(normal);
    vec4 normV = normalize(vertex);
    vec4 normL = normalize(light_pos);

    
    // write Total Color:
    //vec4 resultColor = vec4(0.0, 0.0, 0.0, 1.0); // only placeholder color
    float dotNL = (normN.x * normL.x + normN.y * normL.y + normN.z * normL.z);
    
	float angle = acos(dotNL);
	float x = normN.x;
	float y = normN.y;
	float z = normN.z;
	float s = sin(angle*2);
	float c = cos(angle*2);
	float d = 1-c;
	mat4 rotation = mat4(1.0);
	rotation[0] = vec4(d * x * x + c,      d * x * y + z * s,  d * x * z - y * s,  0.0); 
    rotation[1] = vec4(d * x * y - z * s,  d * y * y + c,      d * y * z + x * s,  0.0);
    rotation[2] = vec4(d * x * z + y * s,  d * y * z - x * s,  d * z * z + c,      0.0);
    mat4 trans1 = mat4(1.0);
    trans1[3] = (-normN.x/2, -normN.y/2, -normN.z/2, 1.0);

    vec4 normR = normL;
    normR -= (normR/2);
    normR *= rotation * trans1;

    mat4 trans2 = mat4(1.0);
    trans2[3] = (normR.x/2, normR.y/2, normR.z/2, 1.0); 
    normR *= trans2;

    float dotRV = (normR.x * normV.x + normR.y * normV.y + normR.z * normV.z)

    float intensity = light_iAmbient * material_ambient + light_iDiffuse * material_diffuse * dotNL + light_iSpecular * material_specular * pow(dotRV,material_shininess);

    vec4 resultColor = vec4(intensity * vec3(1.0, 1.0, 0.0), 1.0);
    out_color = clamp(resultColor,0.0,1.0);
}
