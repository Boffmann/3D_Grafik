// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 15
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

#include "exercise16.h"

#include <cassert>
#include <QKeyEvent>
#include <QMatrix4x4>

#include "util/camera.h"
#include "util/polygonaldrawable.h"
#include "util/objio.h"

Exercise16::Exercise16(const float animationFrame)
    :   AbstractExercise(animationFrame)
    , m_drawable(nullptr)
    , m_viewIndex(-1)
{
    m_drawable = ObjIO::fromObjFile("data/suzanne.obj"); // not centered

    setupViews();
}

Exercise16::~Exercise16()
{
}

void Exercise16::setupViews()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 15
    // Define different views (via the lookAt()-method) for the orthogonal projection
    // Use [1] to [7] to switch cameras (1: perspective, 2-7: orthogonal).
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // eye, center, up
    // +x, -x, +y, -y, +z, -z
    QVector3D center(0.0, 0.0, 0.0);
    QVector3D up_y(0.0, 1.0, 0.0);
    m_views[2].lookAt(QVector3D(1.0, 0.0, 0.0),   center, up_y);
    m_views[3].lookAt(QVector3D(-1.0, 0.0, 0.0),  center, up_y);
    m_views[4].lookAt(QVector3D(0.0, 1.0, 0.0),   center, up_y);
    m_views[5].lookAt(QVector3D(0.0, 1.0, 0.0),   center, up_y);
    m_views[6].lookAt(QVector3D(0.0, 0.0, 1.0),   center, up_y);
    m_views[7].lookAt(QVector3D(0.0, 0.0, -1.0),  center, up_y);
}

void Exercise16::resize(int width, int height)
{
    AbstractExercise::resize(width, height);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 15
    // Setup a correct orthogonal projection via the ortho()-method of QMatrix4x4.
    // Find appropriate values for near and farplane. Keep the aspect ratio in mind.
    /////////////////////////////////////////////////////////////////////////////////////////////////

    float left = width/(-2.0);
    float right = width/(2.0);
    float bottom = height/(-2.0);
    float top = height/(2.0);
    float nearPlane = 0.0;
    float farPlane = 0.0;
    m_orthoProjection.ortho(left, right, bottom, top, nearPlane, farPlane);

}

const QString Exercise16::hints() const
{
    return QString("Use [1] to [7] to switch cameras (1: perspective, 2-7: orthogonal).");
}

bool Exercise16::initialize()
{
    AbstractExercise::initialize();

    m_program.reset(createBasicShaderProgram("data/model.vert", "data/model.geom", "data/model.frag"));
    m_program->bind();

    m_drawable->createVAO(m_program.data());

    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	return true;
}

void Exercise16::setProjectionMode(int index)
{
    assert(index >= -1);
    assert(index <= 5);

    m_viewIndex = index;
}

void Exercise16::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue("color", QVector4D(1.0, 0.0, 0.0, 1.0));
    m_program->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program->setUniformValue("animationFrame", m_animationFrame);

    if (m_viewIndex < 0)
    {
        m_program->setUniformValue("viewprojection", camera()->viewProjection());
        m_program->setUniformValue("normalMatrix", camera()->viewProjection().normalMatrix());
    }
    else
    {
        m_program->setUniformValue("viewprojection", m_orthoProjection * m_views[m_viewIndex]);
        m_program->setUniformValue("normalMatrix", m_views[m_viewIndex].normalMatrix());
    }

    m_drawable->draw(*this);
}

bool Exercise16::onKeyPressed(QKeyEvent * keyEvent)
{
    bool changed = false;

    if(keyEvent->key() >= 49 && keyEvent->key() <= 55)
    {
        setProjectionMode(keyEvent->key() - 49 - 1); // -1 to 5

        changed = true;
    }

    return changed || AbstractExercise::onKeyPressed(keyEvent);
}
