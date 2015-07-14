#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 7
//                     - Aufgabe 22 (Toon)
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

in vec3 normal;

out vec4 out_color;

uniform vec4 light_pos;



void main()
{   
    float intensity;
	vec4 baseColor = vec4(0.8, 0.1, 0.1, 1.0);
	vec4 color = baseColor;
	
	vec3 normN = normalize(normal);
	vec4 normL = normalize(light_pos);
    
    ///////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 22
    // Implement toon shading. Take the intensity and baseColor into account
    ///////////////////////////////////////////////////////////////////

    intensity = (normN.x * normL.x + normN.y * normL.y + normN.z * normL.z);

    if(intensity < 0.01) {
        color = vec4(0.0 * color.xyz, color.w);
    } else if(intensity <= 0.33) {
        color = vec4(0.33 * color.xyz, color.w);
    } else if(intensity <= 0.66) {
        color = vec4(0.66 * color.xyz, color.w);
    } else if(intensity <= 0.99) {
        color = vec4(0.99 * color.xyz, color.w);
    } else if(intensity > 0.99) {
        color = vec4(1.0, 1.0, 1.0, color.w);
    }

    out_color = color;
}
