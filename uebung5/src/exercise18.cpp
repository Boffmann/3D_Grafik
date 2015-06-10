// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 18
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

#include "exercise18.h"

#include <cassert>
#include <QKeyEvent>
#include <QMatrix4x4>

#include "util/camera.h"
#include "util/polygonaldrawable.h"
#include "util/objio.h"

Exercise18::Exercise18(float animationFrame)
    :   AbstractExercise(animationFrame)
    , m_drawable(nullptr)
{
    m_drawable = ObjIO::fromObjFile("data/suzanne.obj"); // not centered
}

Exercise18::~Exercise18()
{
}

const QString Exercise18::hints() const
{
    return QString("");
}

bool Exercise18::initialize()
{
    AbstractExercise::initialize();

    m_program.reset(createBasicShaderProgram("data/haloedlines.vert", "data/haloedlines.geom", "data/haloedlines.frag"));
    m_program->bind();

    m_drawable->setMode(GL_TRIANGLES);
    m_drawable->createVAO(m_program.data());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 18, part 1
    // Setup appropriate depth test to draw the given geometry as haloed lines.
    // Tip: Activate depth test as well as use glDepthFunc().
    /////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

void Exercise18::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue("color", QVector4D(1.0, 1.0, 1.0, 1.0));
    m_program->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program->setUniformValue("animationFrame", m_animationFrame);

    m_program->setUniformValue("viewprojection", camera()->viewProjection());
    m_program->setUniformValue("normalMatrix", camera()->viewProjection().normalMatrix());

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 18, part 2
    // Draw the given geometry as haloed lines.
    // Use a line width of 8.0f*animationFrame for the first and a line width of 3.0f*animationFrame for the second pass.
    // Tip: Use glColorMask(), glLineWidth(), m_drawable->draw(*this)
    /////////////////////////////////////////////////////////////////////////////////////////////////


    // pass 1
    //glLineWidth(...);

    //m_drawable->draw(*this);

    // pass 2
    //glLineWidth(...);

    //m_drawable->draw(*this);
}
