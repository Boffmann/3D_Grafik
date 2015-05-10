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
// Matr.-Nr: 775165
// Matr.-Nr: 775014
//
// ======================================

//////////////////////////////////////////////////
// TODO: Aufgabe 6d) - Interpolationsmodi anpassen
//
// Hinweis: Die Interpolationsmodi koennen vom laufenden Programm mittels der Tasten <1>, <2> und <3> gewechselt werden.
//////////////////////////////////////////////////

flat in float colorValue1;
smooth in float colorValue2;
noperspective in float colorValue3;

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
    
    // vec4 color_0(0.20392156862,	0.5294117647,	0.0,			1.0);	//34 87 00	FF348700
    // vec4 color_1(0.21960784313,	0.1725490196,	0.03921568627,	1.0);	//38 2C 0A	F382C0A
    // vec4 color_2(0.50196078431,	0.50196078431,	0.50196078431,	1.0);	//80 80 80	FF808080
    // vec4 color_3(0.91372549019,	0.91372549019,	0.91372549019,	1.0);	//E9 E9 E9	FFE9E9E9

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
    } else if(colorValue < 1.0/3.0) {
        color[0] = color0[0] + colorValue * (color1[0] - color0[0]);
       	color[1] = color0[1] + colorValue * (color1[1] - color0[1]);
       	color[2] = color0[2] + colorValue * (color1[2] - color0[2]);
    } else if(colorValue < 2.0/3.0) {
        color[0] = color1[0] + colorValue * (color2[0] - color1[0]);
       	color[1] = color1[1] + colorValue * (color2[1] - color1[1]);
       	color[2] = color1[2] + colorValue * (color2[2] - color1[2]);
    } else if(colorValue < 0.9) {
		color[0] = color2[0] + colorValue * (color3[0] - color2[0]);
       	color[1] = color2[1] + colorValue * (color3[1] - color2[1]);
       	color[2] = color2[2] + colorValue * (color3[2] - color2[2]);
    } else {
        color = color3;
    }

    // if(colorValue < 0.1) {
    // 	color = color0;
    // } else if(colorValue < 1.0/3.0) {
    //     color = mix(color0, color1, (colorValue-0.1)/(1.0/3.0-0.1));
    // } else if(colorValue < 2.0/3.0) {
    //     color = mix(color1, color2, (colorValue-1.0/3.0)/(2.0/3.0-1.0/3.0));
    // } else if(colorValue < 0.9) {
    //     color = mix(color2, color3, (colorValue-2.0/3.0)/(0.9-2.0/3.0));
    // } else {
    //     color = color3;
    // }




    // Als Graustufenwert interpretieren

    // TODO: Interpoliert
}
