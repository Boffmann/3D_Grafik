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
    if(interpolationMode == 1) colorValue = colorValue1;
    if(interpolationMode == 2) colorValue = colorValue2;
    if(interpolationMode == 3) colorValue = colorValue3;
    
    //////////////////////////////////////////////////
    // TODO: Aufgabe 6c) - Farbe berechnen
    //////////////////////////////////////////////////
  
	// 4 verschiedene Farben zuweisen  
	vec4 color0 = vec4(0x34, 0x87, 0x00, 0xFF);
	vec4 color1 = vec4(0x38, 0x2C, 0x0A, 0xFF);
	vec4 color2 = vec4(0x80, 0x80, 0x80, 0xFF);
	vec4 color3 = vec4(0xE9, 0xE9, 0xE9, 0xFF);

	// interpolieren
    if(colorValue < 0.1) {
    	color = color0/255.0;
    } else if(colorValue < 1.0/3.0) {
        color = mix(color0/255.0, color1/255.0, colorValue);
    } else if(colorValue < 2.0/3.0) {
        color = mix(color1/255.0, color2/255.0, colorValue);
    } else if(colorValue < 0.9) {
    	color = mix(color2/255.0, color3/255.0, colorValue);
    } else {
    	color = color3/255.0;
    }
}