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

        vec3 norm = normalize(cross(gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz));
        float angle = radians(360) * animationFrame;
        float c = cos(angle);
        float s = sin(angle);

        float x = normalize(norm).x;
        float y = normalize(norm).y;
        float z = normalize(norm).z;
        float d = 1.0 - c;
        mat4 rot = mat4(1.0);
        rot[0] = vec4(d * x * x + c,      d * x * y + z * s,  d * x * z - y * s,  0.0);
        rot[1] = vec4(d * x * y - z * s,  d * y * y + c,      d * y * z + x * s,  0.0);
        rot[2] = vec4(d * x * z + y * s,  d * y * z - x * s,  d * z * z + c,      0.0);

        mat4 trans = mat4(1.0);
        trans[3] = vec4(animationFrame * -norm, 1.0);

        vec4 transl = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0;
        mat4 trans_to = mat4(1.0);
        trans_to[3] = vec4(-transl.xyz, 1.0);
        mat4 trans_back = mat4(1.0);
        trans_back[3] = transl;

        mat4 transform = trans * trans_back * rot * trans_to;
        vertex = transform * vertex;

        gl_Position = viewprojection * vertex;

        EmitVertex();
    }

    EndPrimitive();
}
