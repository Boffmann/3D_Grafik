// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 6
//                     - Aufgabe 19
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775014
// Matr.-Nr: 775165
//
// ======================================

#include "exercise19.h"

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <glm/common.hpp>

#include "util/camera.h"
#include "util/polygonaldrawable.h"


#include <iostream>
#include <QtGlobal>
#include <QMouseEvent>
#include <QWindow>
#include <QMatrix4x4>


namespace
{
    // global state FTW

    std::vector<Vertex> g_combinedVertices; // new vertices from tesselation (see combineCallback)
    std::vector<Vertex> g_vertices; // vertices for the current primitive

    GLenum g_primitive; // Current primitive type
}

void errorCallback(GLenum errorCode)
{
    qWarning() << "Tessellation Error: " << gluErrorString(errorCode);
}

void beginCallback(GLenum prim)
{
    //TODO
    g_primitive = prim;
}

void vertexCallback(void * vdata)
{
    //TODO
    g_vertices.push_back(*((Vertex *) vdata));
}

void combineCallback(double coords[3], double vertex_data[4], float weight[4], double **dataOut)
{
    Vertex vertex(coords[0], coords[1], coords[2]);
    g_combinedVertices.push_back(vertex);
    Vertex &v = g_combinedVertices.back();
    *dataOut = &v.x;
}

void endCallback(void)
{
    //TODO
    glBegin(g_primitive);
    double contour_color[3] = {0.0, 0.5, 0.0};
    glColor3dv(contour_color);

    for(auto i = g_vertices.begin(); i != g_vertices.end(); ++i) {
      double data[3] = {i->x, i->y, i->z};
      glVertex3dv(data);
    }

    glEnd();

    glBegin(GL_LINE_LOOP);
    double line_color[3] = {1.0, 1.0, 1.0};
    glColor3dv(line_color);

    for(auto i = g_combinedVertices.begin(); i != g_combinedVertices.end(); ++i) {
      double data[3] = {i->x, i->y, i->z};
      glVertex3dv(data);
    }

    glEnd();
    g_vertices.clear();
}


Exercise19::Exercise19()
:   AbstractExercise()
{
}

Exercise19::~Exercise19()
{
}

void Exercise19::render()
{
    glViewport(0, 0, m_viewport[0], m_viewport[1]);


    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    //TODO use these
    //drawContours();
    //tessellatePolygons();

    drawContours();
    tessellatePolygons();

    glPopMatrix();
}

bool Exercise19::initialize()
{
    initializeOpenGLFunctions();

    m_contours.push_back(Contour());

    glClearColor(0.5, 0.5, 0.5, 1.0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glPointSize(2.f);

    return true;
}

const QString Exercise19::hints() const
{
    return "Left click to add point to current contour. Right click to close current contour.";
}

const QString Exercise19::description() const
{
    return "Tessellation";
}

void Exercise19::drawContours()
{
    static const GLenum mode[] = { GL_POINTS, GL_LINES, GL_POLYGON };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (unsigned int i = 0; i < m_contours.size(); ++i)
    {
        const Contour contour = m_contours[i];

        const QColor color((Qt::GlobalColor)(i % 13 + 6));
        glColor3f(color.redF(), color.greenF(), color.blueF());

        if (contour.size() > 0)
        {
            int modeIndex = glm::min(static_cast<unsigned int>(contour.size()-1), 2u);
            glBegin(mode[modeIndex]);

            for (Contour::const_iterator it = contour.begin(); it != contour.end(); ++it)
            {
                //qDebug() << it->x << ", " << it->y;
                glVertex3f(it->x, it->y, it->z);
            }
            glEnd();
        }
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Exercise19::tessellatePolygons()
{
    //TODO
    GLUtesselator* tess = gluNewTess();
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (*) ()) &beginCallback);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (*) ()) &vertexCallback);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (*) ()) &combineCallback);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (*) ()) &errorCallback);
    gluTessCallback(tess, GLU_TESS_END, (void (*) ()) &endCallback);

#if 0
    for(auto i = m_contours.begin(); i != m_contours.end(); ++i) {
      gluTessBeginPolygon(tess, NULL);
      gluTessBeginContour(tess);
      for(auto j = i->begin(); j != i->end(); ++j) {
        GLdouble data[3];
        data[0] = j->x;
        data[1] = j->y;
        data[2] = j->z;
        gluTessVertex(tess, data, data);
      }
      gluTessEndContour(tess);
      gluTessEndPolygon(tess);
    }
    gluDeleteTess(tess);
#endif
      glShadeModel(GL_FLAT);
      gluTessBeginPolygon(tess, NULL);

      for(Contour &contour:m_contours) {
        gluTessBeginContour(tess);

        for (Vertex &vertex:contour) {
          gluTessVertex(tess, (GLdouble *) &vertex, &vertex);
         }

         gluTessEndContour(tess);
      }

      gluTessEndPolygon(tess);
      gluDeleteTess(tess);

}

bool Exercise19::onMouseReleased(QMouseEvent * mouseEvent)
{
    bool changed = false;

    if (mouseEvent->button() == Qt::LeftButton)
    {
        // Add vertex to contour
        float ratio = 1.0;// TODO use pixel device ratio;
        int x = mouseEvent->pos().x()*ratio;
        int y = mouseEvent->pos().y()*ratio;

        Vertex v(static_cast<float>(x), static_cast<float>(y), 0.f);
        m_contours[m_contours.size() - 1].push_back(v);

        changed = true;
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        // Finish current contour and go to the next one
        Contour & current = m_contours[m_contours.size() - 1];

        if (current.size() >= 3)
        {
            // The last contour has 3 or more vertices, so it's valid and we create a new one
            Contour contour;
            m_contours.push_back(contour);
        }
        else
        {
            // The last contour did not have 3 or more vertices, so we clear it and start again
            current.clear();
        }

        changed = true;
    }

    return changed || AbstractExercise::onMouseReleased(mouseEvent);
}

bool Exercise19::onKeyPressed(QKeyEvent * event)
{
    bool changed = false;

    switch(event->key())
    {
    case Qt::Key_R:

        m_contours.clear();

        m_contours.push_back(Contour());

        changed = true;

        break;
    }

    return changed || AbstractExercise::onKeyPressed(event);
}

void Exercise19::resize(int width, int height)
{
    AbstractExercise::resize(width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
