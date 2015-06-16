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
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
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
    float deform_fac = 1.0 - moldPlateau;
    float a = atan(v.z, v.x) / radians(180);

    float x = (1.0 - a) * v.x + a * deform_fac;
    float z = (1.0 - a) * v.z + a * deform_fac;

    return vec3(x, v.y, z);
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

    float a = v.y / overallObjectDimensions.y;
    float deform_fac = 1.0 - pinchPlateau;

    float x = v.x * (1.0 - deform_fac * a);
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
    float a = v.y / overallObjectDimensions.y;

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

    float a = v.y / overallObjectDimensions.y;
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