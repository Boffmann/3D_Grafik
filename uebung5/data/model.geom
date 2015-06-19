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
// Matr.-Nr: 775014
// Matr.-Nr: 775165
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

        vec4 u = gl_in[1].gl_Position - gl_in[0].gl_Position;
        vec4 v = gl_in[2].gl_Position - gl_in[0].gl_Position;
        vec3 norm = vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), (u.x * v.y) - (u.z * v.x));
        norm = normalize(norm);

        float angle = radians(360) * animationFrame;
        float c = cos(angle);
        float s = sin(angle);

        vec4 rot_c1 = vec4((1.0-c) * norm.x * norm.x + c, (1.0-c) * norm.x * norm.y + norm.z * s, (1.0-c) * norm.x * norm.z - norm.y * s, 0.0);
        vec4 rot_c2 = vec4((1.0-c) * norm.x * norm.y - norm.z * s, (1.0-c) * norm.y * norm.y + c, (1.0-c) * norm.y * norm.z + norm.x * s, 0.0);
        vec4 rot_c3 = vec4((1.0-c) * norm.x * norm.z + norm.y * s, (1.0-c) * norm.y * norm.z - norm.x * s, (1.0-c) * norm.z * norm.z + c, 0.0);

        // vec4 rot_c1 = vec4((1.0-c) * normal.x * normal.x + c, (1.0-c) * normal.x * normal.y + normal.z * s, (1.0-c) * normal.x * normal.z - normal.y * s, 0.0);
        // vec4 rot_c2 = vec4((1.0-c) * normal.x * normal.y - normal.z * s, (1.0-c) * normal.y * normal.y + c, (1.0-c) * normal.y * normal.z + normal.x * s, 0.0);
        // vec4 rot_c3 = vec4((1.0-c) * normal.x * normal.z + normal.y * s, (1.0-c) * normal.y * normal.z - normal.x * s, (1.0-c) * normal.z * normal.z + c, 0.0);
        vec4 rot_c4 = vec4(0.0, 0.0, 0.0, 1.0);
        mat4 rot = mat4(rot_c1, rot_c2, rot_c3, rot_c4);

        vec3 scal = animationFrame * -0.5 * norm;
        vec4 trans_c1 = vec4(1.0, 0.0, 0.0, 0.0);
        vec4 trans_c2 = vec4(0.0, 1.0, 0.0, 0.0);
        vec4 trans_c3 = vec4(0.0, 0.0, 1.0, 0.0);
        vec4 trans_c4 = vec4(scal, 1.0);
        mat4 trans = mat4(trans_c1, trans_c2, trans_c3, trans_c4);

        vertex = vertex * rot;
        //vertex = vertex * trans * rot;
        gl_Position = viewprojection * vertex;

        EmitVertex();
    }

    EndPrimitive();
}
