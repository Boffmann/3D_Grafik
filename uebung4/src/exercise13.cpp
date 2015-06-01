// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 4
//                     - Aufgabe 13
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

#include <QDebug>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include <math.h>

#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "util/camera.h"

#include "exercise13.h"

namespace 
{
    const QString TEXTURE_FILENAME = "data/luxo.png";
}

Exercise13::Exercise13()
: m_textureID(-1)
, m_sphere(3)
{
    m_sphereScale.scale(0.3);
}

Exercise13::~Exercise13()
{
	if (m_textureID != -1)
        glDeleteTextures(1, &m_textureID);
}

QMatrix4x4 Exercise13::applyBallTransformation(const int frame)
{
    static const float fX = 0.05f;
    static const int numFramesPerAnimation = static_cast<int>(4.0f / fX);

    static const float r = 0.3f;
    static const float d = 0.3f * r;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 13
    // - Calculate correct translation, scaling and rotation matrices with respect to the current frame
    // - The sphere's environment is defined as follows:
    //              start at    x = -2.0 and y = 0.8
    //              left  cliff x = -0.9
    //              bottom at   y = -1.05;
    //              right cliff x = +0.9 and y = 0.4
    //              end at      x = +2.0
    // - Apply matrices in the correct order, using matrix multiplication
    /////////////////////////////////////////////////////////////////////////////////////////////////
    float x = -2.0;
    float y = 0.8;
    int length = 1600 * (0.01/fX);
    float distance = (float)(frame%length)/numFramesPerAnimation;
    float radians = -((360 * distance)/(2.0 * r * M_PI)) * (M_PI/180.0);  // - so it turns the right way
    float cosine = cos(radians);
    float sine = sin(radians);
    float lambda1 = 1.0;
    float lambda2 = 1.0;
    float lambda3 = 1.0;
    float fac;
    float transformvalue;
    transformvalue = d/(2.0*r);
    //transformvalue = 0.5;
    //transformvalue = 1.0 - (d/(2.0*r));
    // keine Ahnung ob um d stauchen heisst auf d oder 1-d skalieren

    x += distance;
    if(x >= 0.10 && !(x > 0.15)) {
      // stauchung von 0.10 bis 0.15
      fac = (x - 0.1) / 0.05;
      lambda2 = (1.0-fac) + fac * transformvalue;
      x = 0.1;
    } else if(x >= 0.15 && !(x > 0.20)) {
      // anti stauchung von 0.15 bis 0.2
      fac = (x - 0.15) / 0.05;
      lambda2 = (1.0-fac) * transformvalue + fac;
    }

    if(x >= 0.15) x-= 0.05;

    if(x >= -0.9 && x < 0.1) {  // -0.9 leftcliff / 0.1 behind bottom x
      y = -(27.0/16.0) * x * x - (16.0/5.0) * x - (1141.0/1600.0);
      // (-0.9,0.8) > (-0.7,0.7) > (0.1,-1.05)
    }
    if (x == 0.1) {
      y = -1.05;
    }
    if(x > 0.1 && x < 0.9) { // 0.1 behind bottom x / right cliff x
      y = -(35.0/16.0) * x * x + 4 * x - (457.0/320.0);
      // (0.1,-1.05) > (0.7,0.3) > (0.9,0.4)
    }
    if(x > 0.9 && x < 2.0) {  // rightcliff x / end x
      y = 0.4;  // right cliff y
    }

    y -= (1.0 - lambda2) * r;
    // den skalierten radius abziehen

    const QMatrix4x4 rotate(cosine, -sine, 0.0, 0.0,   sine, cosine, 0.0, 0.0,    0.0, 0.0, 1.0, 0.0,   0.0, 0.0, 0.0, 1.0);
    const QMatrix4x4 scale(lambda1, 0.0, 0.0, 0.0,   0.0, lambda2, 0.0, 0.0,   0.0, 0.0, lambda3, 0.0,   0.0, 0.0, 0.0, 1.0);
    const QMatrix4x4 translate(1.0, 0.0, 0.0, x,   0.0, 1.0, 0.0, y + r,   0.0, 0.0, 1.0, 0.0,   0.0, 0.0, 0.0, 1.0);

    return translate * scale * rotate;
}

void Exercise13::drawEnvironment()
{
    m_program0->bind();
    m_program0->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program0->setUniformValue("viewprojection", camera()->viewProjection());

    // Draw big cubes

    m_program0->setUniformValue("color", QVector4D(0.8, 0.8, 0.8, 1.0));

    QMatrix4x4 transform;
    transform.translate(-4.9f, -1.201f, 0.0f);
    transform.scale(4.f, 2.0f,  4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(4.9f, -1.401f, 0.0f);
    transform.scale(4.f, 1.8f, 4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(0.0f, -3.0501f, 0.0f);
    transform.scale(1.0f, 2.0f,  4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    // Draw trail

    m_program0->setUniformValue("color", QVector4D(0.9, 0.9, 0.9, 1.0));

    transform.setToIdentity();
    transform.translate(-4.9f, 0.8f, 0.0f);
    transform.scale(4.f, 0.0f, 0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(4.9f, 0.4f, 0.0f);
    transform.scale(4.f, 0.0f, 0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);

    transform.setToIdentity();
    transform.translate(0.0f, -1.05f, 0.0f);
    transform.scale(1.0f, 0.0f,  0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);
}

void Exercise13::render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    drawEnvironment();

	glBindTexture(GL_TEXTURE_2D, m_textureID);
    glActiveTexture(GL_TEXTURE0);

    QMatrix4x4 transform = applyBallTransformation(m_frame) * m_sphereScale;

    m_program1->bind();
    m_program1->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program1->setUniformValue("viewprojection", camera()->viewProjection());

    m_program1->setUniformValue("transform", transform);
    m_program1->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());
    m_program1->setUniformValue("diffuse", 0);

    m_sphere.draw(*this);
}

bool Exercise13::initialize()
{
    AbstractExercise::initialize();

    m_textureID = getOrCreateTexture(TEXTURE_FILENAME);


    m_program0.reset(createBasicShaderProgram("data/cube13.vert", "data/cube13.frag"));

    m_cube.initialize(*m_program0);

    m_program1.reset(createBasicShaderProgram("data/sphere.vert", "data/sphere.frag"));

    m_sphere.initialize(*m_program1);

    glClearColor(0.6, 0.6, 0.6, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    return true;
}

const QString Exercise13::hints() const
{
    return QString("Press [SPACE] to pause or resume animation.");
}
