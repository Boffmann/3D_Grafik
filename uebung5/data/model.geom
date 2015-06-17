#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 16
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 viewprojection;
uniform float animationFrame;

in vec3 geom_normal[];

out vec4 vertex;
out vec3 normal;

/////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: Aufgabe 16
// Note: In GLSL matrices are defined in column-major order.
// Take into account the animationFrame parameter:
//      0.0f: No transformation at all
//      1.0f: Maximum rotation of 360° and maximum translation
/////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
    for (int i=0; i < 3; ++i) {
        normal = normalize(geom_normal[i]);
        vertex = gl_in[i].gl_Position;
        gl_Position = viewprojection * vertex;

        float angle = radians(360) * animationFrame;
        float c = cos(angle);
        float s = sin(angle);
        float x = ((1-c) * normal.x * normal.x + c) * vertex.x + ((1-c) * normal.x * normal.y - normal.z * s) * vertex.y + ((1-c) * normal.x * normal.z + normal.y * s) * vertex.z;
        float y = ((1-c) * normal.x * normal.x + c) * vertex.x + ((1-c) * normal.x * normal.y - normal.z * s) * vertex.y + ((1-c) * normal.x * normal.z + normal.y * s) * vertex.z;
        float z = ((1-c) * normal.x * normal.x + c) * vertex.x + ((1-c) * normal.x * normal.y - normal.z * s) * vertex.y + ((1-c) * normal.x * normal.z + normal.y * s) * vertex.z;
        // mat4 rot = mat4((1-c) * normal.x * normal.x + c), (1-c) * normal.x * normal.x + c), (1-c) * normal.x * normal.x + c), 0.0, (1-c) * normal.x * normal.y - normal.z * s), (1-c) * normal.x * normal.y - normal.z * s), (1-c) * normal.x * normal.y - normal.z * s), 0.0, (1-c) * normal.x * normal.z + normal.y * s), (1-c) * normal.x * normal.z + normal.y * s), (1-c) * normal.x * normal.z + normal.y * s), 0.0, 0.0, 0.0, 0.0, 1.0)
        x += animationFrame * normal.x;
        y += animationFrame * normal.y;
        z += animationFrame * normal.z;
        vertex = vec4(x, y, z, 1.0);
        EmitVertex();
    }

    EndPrimitive();
}
