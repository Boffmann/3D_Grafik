#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 17
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

uniform mat4 transform;
uniform mat4 viewprojection;
uniform vec3 overallObjectDimensions;
uniform float animationFrame;
uniform int globalDeformationMode;

in vec3 in_vertex;
in vec3 in_normal;

out vec3 normal;
out vec4 vertex;

vec3 mold(vec3 v, float moldPlateau)
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 17, part 1
    // Apply a mold deformation to the given vertex v.
    // Take into account the moldPlateau parameter
    //      1.0f: No deformation at all
    //      0.0f: Maximum deformation
    // Tip: Use overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////
    float z = v.z;
    float deform_fac = 1.0 - moldPlateau;
    float a = atan(v.x, v.z) / radians(180);
    a = abs(a);
    if (v.z > 0)  {
      z *= (1.0 - deform_fac * a);
    } else {
      // richtige deformation, faengt aber bei z = 0, daher + ...
      //z = (deform_fac * a * z) + ((1.0 - deform_fac) * z);

      // umgeformt
      z *= deform_fac * (a - 1.0) + 1.0;
    }
    return vec3(v.x, v.y, z);
}

vec3 pinch(vec3 v, float pinchPlateau)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 17, part 2
    // Apply a pinch deformation to the given vertex v.
    // Take into account the pinchPlateau parameter
    //      1.0f: No deformation at all
    //      0.0f: Maximum deformation
    // Tip: Use overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////
    float offset = overallObjectDimensions.y / 2;
    float a = (v.y + offset) / overallObjectDimensions.y;
    float deform_fac = 1.0 - pinchPlateau;

    float x = (1.0 - a * deform_fac) * v.x;
    return vec3(x, v.y, v.z);
}

vec3 twist(vec3 v, float maxAngle)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 17, part 3
    // Apply a twist deformation to the given vertex v.
    // Take into account the maxAngle parameter, that defines the maximum rotation angle
    // Tip: Use overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // interpolation factor (height)
    float offset = overallObjectDimensions.y / 2;
    float a = (v.y + offset) / overallObjectDimensions.y;

    // rotation angle
    float angle = maxAngle * a;

    // multiply vector with rotation matrix
    float x = v.x * cos(angle) - v.z * sin(angle);
    float z = v.x * sin(angle) + v.z * cos(angle);

    return vec3(x, v.y, z);
}

vec3 bend(vec3 v, float maxAngle)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 17, part 4
    // Apply a bend deformation to the given vertex v.
    // Take into account the maxAngle parameter, that defines the maximum rotation angle
    // Tip: Use overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    float offset = overallObjectDimensions.y / 2;
    float a = (v.y + offset) / overallObjectDimensions.y;
    float angle = maxAngle * a;

    float y = v.y * cos(angle) - v.x * sin(angle);
    float x = v.y * sin(angle) + v.x * cos(angle);

    return vec3(x, y, v.z);
}

void main()
{
    vec3 transV;

    if(globalDeformationMode == 1)
        transV = mold(in_vertex, 1.0f - animationFrame);
    else if(globalDeformationMode == 2)
        transV = pinch(in_vertex, 1.0f - animationFrame);
    else if(globalDeformationMode == 3)
        transV = twist(in_vertex, radians(animationFrame * 360.0f));
    else if(globalDeformationMode == 4)
        transV = bend(in_vertex, radians(animationFrame * 90.0f));
    else
        transV = in_vertex;

    gl_Position = viewprojection * transform * vec4(transV, 1.0);
    vertex = transform * vec4(transV, 1.0);
    normal = in_normal;
}
