#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 2
//                     - Aufgabe 6
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

//////////////////////////////////////////////////
// TODO: Aufgabe 6d) - Interpolationsmodi anpassen
//
// Hinweis: Die Interpolationsmodi koennen vom laufenden Programm mittels der Tasten <1>, <2> und <3> gewechselt werden.
//////////////////////////////////////////////////

in float colorValue1;
in float colorValue2;
in float colorValue3;

out vec4 color;

uniform int interpolationMode;

void main()
{
    // TODO: Farbwert auslesen (vom Modus abhaengig)
    float colorValue = 0.0;
    if(interpolationMode == 0) colorValue = colorValue1;
    if(interpolationMode == 1) colorValue = colorValue2;
    if(interpolationMode == 2) colorValue = gl_FragCoord.w*colorValue3;

    
    //////////////////////////////////////////////////
    // TODO: Aufgabe 6c) - Farbe berechnen
    //////////////////////////////////////////////////
    
	vec4 color0;
	color0[0] = 0x34;
	color0[1] = 0x87;
	color0[2] = 0x00;
	color0[3] = 0xFF;
	vec4 color1;
	color1[0] = 0x38;
	color1[1] = 0x2C;
	color1[2] = 0x0A;
	color1[3] = 0xFF;
	vec4 color2;
	color2[0] = 0x80;
	color2[1] = 0x80;
	color2[2] = 0x80;
	color2[3] = 0xFF;
	vec4 color3;
	color3[0] = 0xE9;
	color3[1] = 0xE9;
	color3[2] = 0xE9;
	color3[3] = 0xFF;
	

    if(colorValue < 0.1) {
        color = color0;
    }else if(colorValue < 1.0/3.0) {
        color = mix(color0, color1, (colorValue-0.1)/(1.0/3.0-0.1));
    }else if(colorValue < 2.0/3.0) {
        color = mix(color1, color2, (colorValue-1.0/3.0)/(2.0/3.0-1.0/3.0));
    }else if(colorValue < 0.9) {
        color = mix(color2, color3, (colorValue-2.0/3.0)/(0.9-2.0/3.0));
    }else{
        color = color3;
    }


    // Als Graustufenwert interpretieren

    // TODO: Interpoliert
}
