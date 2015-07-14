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

    //intensity = sin(acos(normN.x * normL.x + normN.y * normL.y + normN.z * normL.z + 1 * normL.w));
    float angle = acos(normN.x * normL.x + normN.y * normL.y + normN.z * normL.z + 1 * normL.w);
    float int1 = sin(angle);
    float int2 = angle/90.0;

    if(int1 < 0.01)
    	color *= 0.0;
    else if(int1 <= 0.33)
    	color *= 1.0/6.0;
    else if(int1 <= (0.66)
    	color *= 3.0/6.0;
    else if(int1 <= 0.99)
    	color *= 5.0/6.0;
    //else
    //	color *= 1.0;



        
	out_color = color;
}
