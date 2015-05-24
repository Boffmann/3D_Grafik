// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 4
//                     - Aufgabe 12
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QOpenGLShaderProgram>

#include "util/camera.h"
#include <math.h>
#include <iomanip>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include "exercise12.h"

Exercise12::Exercise12()
{
    m_cubeTransform.scale(0.5f);
}

Exercise12::~Exercise12()
{
}

QMatrix4x4 Exercise12::rotateClockwise(int frame)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 12
    // Apply correct transformations (rotate, translate, scale) with respect to the current frame
    /////////////////////////////////////////////////////////////////////////////////////////////////

    QMatrix4x4 transform;

    int degree = (frame/3) % 720;
    float x;
    float y;
    int deg_tmp = degree % 90;
    float tmp = sin(deg_tmp * (M_PI/180.0));
    transform.setToIdentity();

    if (degree < 90) {
      x = deg_tmp / 90.0;
      y = tmp + (1.0 - (deg_tmp/90.0));
      transform.translate(x, y, 0.0);
    } else if(degree < 180) {
      y = 1.0 - (deg_tmp / 90.0);
      x = tmp + (1.0 - (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 270) {
      y = (deg_tmp / -90.0);
      x = tmp + (1.0 - (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 360) {
      x = 1.0 - (deg_tmp / 90.0);
      y = -tmp + (-1.0 + (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 450) {
      x = -(deg_tmp / 90.0);
      y = -tmp + (-1.0 + (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 540) {
      y = -1.0 + (deg_tmp / 90.0);
      x = -tmp + (-1.0 + (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 630) {
      y = (deg_tmp / 90.0);
      x = -tmp + (-1.0 + (deg_tmp/90.0));
      transform.translate(x, y, 0.0);

    } else if(degree < 720) {
      x = -1.0 + (deg_tmp / 90.0);
      y = tmp + (1.0 - (deg_tmp/90.0));
      transform.translate(x, y, 0.0);
    }
    transform.rotate(-degree, QVector3D::QVector3D(0.0, 0.0, 1.0));
    return transform;
}

const QString Exercise12::hints() const
{
	return QString("Press [SPACE] to pause or resume animation.");
}

bool Exercise12::initialize()
{
    AbstractExercise::initialize();

    m_program.reset(createBasicShaderProgram("data/cube12.vert", "data/cube12.frag"));
    m_program->bind();

    m_cube.initialize(*m_program);

    glClearColor(0.6, 0.6, 0.6, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	return true;
}

void Exercise12::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    m_program->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program->setUniformValue("viewprojection", camera()->viewProjection());

    m_program->setUniformValue("transform", m_cubeTransform);
    m_program->setUniformValue("normalMatrix", (camera()->view() * m_cubeTransform).normalMatrix());
    m_program->setUniformValue("color", QVector4D(1.0, 0.0, 0.0, 1.0));

    m_cube.draw(*this);

    m_program->setUniformValue("transform", rotateClockwise(m_frame) * m_cubeTransform);
    m_program->setUniformValue("normalMatrix", (camera()->view() * rotateClockwise(m_frame) * m_cubeTransform).normalMatrix());
    m_program->setUniformValue("color", QVector4D(1.0, 1.0, 0.0, 1.0));

    m_cube.draw(*this);
}
