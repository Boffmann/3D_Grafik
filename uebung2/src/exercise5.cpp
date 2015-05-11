// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 2
//                     - Aufgabe 5
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 775165
// Matr.-Nr: 775014
//
// ======================================

#include "exercise5.h"

//
// Qt
//
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <iostream>

using namespace Qt;

Exercise5::Exercise5(QWidget *parent) :
    QGraphicsView(parent)
{
    // Create some metaballs

    m_metaballs.push_back(QPoint(10, 10));
    m_metaballs.push_back(QPoint(100, 30));
    m_metaballs.push_back(QPoint(50, 70));
    m_metaballs.push_back(QPoint(80, 40));

    // Set graphics scene
    setScene(&m_scene);

    // Add image item
    QPixmap image;
    m_imageItem = m_scene.addPixmap(image);

    // Render metaballs
    renderMetaballs();
}

Exercise5::~Exercise5()
{
}

/**
*  @brief
*    Called when widget is resized
*/
void Exercise5::resizeEvent(QResizeEvent *event)
{
    // Resize graphics scene according to widget size
    m_scene.setSceneRect(contentsRect());

    // Update metaballs
    renderMetaballs();

    // Call base implementation
    QWidget::resizeEvent(event);
}

/**
*  @brief
*    Called when mouse button is released
*/
void Exercise5::mouseReleaseEvent(QMouseEvent *event)
{
    //////////////////////////////////////////////////
    // TODO: Aufgabe 5
    //////////////////////////////////////////////////

    // Left mouse button
    if (event->button() == Qt::LeftButton) {
        //////////////////////////////////////////////////////////////////////////
        // TODO: Add new metaball
        //////////////////////////////////////////////////////////////////////////
        m_metaballs.push_back(QPoint(event->x(), event->y()));
    }

    // Right mouse button
    else if (event->button() == Qt::RightButton) {
        //////////////////////////////////////////////////////////////////////////
        // TODO: remove all metaballs
        //////////////////////////////////////////////////////////////////////////
        m_metaballs.clear();
    }

    // Update metaballs
    renderMetaballs();
}

/**
*  @brief
*    Render metaballs
*/
void Exercise5::renderMetaballs()
{
    //[-------------------------------------------------------]
    //[ Definitions                                           ]
    //[-------------------------------------------------------]
    static const float s = 1.0f;
    static const float e = 3.5f;
    static const QColor outerColor = QColor(0, 0, 0);
    static const QColor innerColor = QColor(255, 255, 255);
    static const QColor middleColor = QColor(255,0 ,0);

    //////////////////////////////////////////////////
    // TODO: Aufgabe 5
    //////////////////////////////////////////////////

    // Get image size
    int w = contentsRect().width();
    int h = contentsRect().height();

    // Create temporary map
    std::vector<float> map = std::vector<float>(w*h, 0.0f);

    // Draw image
    QPixmap image(w, h);
    QPainter painter(&image);
    for (int y=0; y<h; y++)
    {
        for (int x=0; x<w; x++)
        {
            // Iterate over list of metaballs
            for (int i=0; i<m_metaballs.size(); i++)
            {
                //////////////////////////////////////////////////////////////////////////
                // TODO: Compute density of metaball i for position (x,y) with a given mass
                //////////////////////////////////////////////////////////////////////////
				float mass = 1000.0f;
                float density = mass/ ( ( (x-m_metaballs[i].x()) * (x-m_metaballs[i].x()) ) + ( (y-m_metaballs[i].y()) * (y-m_metaballs[i].y()) ));

                //////////////////////////////////////////////////////////////////////////
                // TODO: Add computed density (inverse distance weighting) to the current pixel value
                //////////////////////////////////////////////////////////////////////////
                map[y*w+x] += density;

                //////////////////////////////////////////////////////////////////////////
                // TODO: Use the added weights, s and e to interpolate between start, mid, and end color
                //////////////////////////////////////////////////////////////////////////
                float r, g, b;
                r = g = b = 0.0f;
                float factor = map[x+y*w];
                if(factor < s) {
                    factor = qBound(0.0f, factor, 1.0f);
                    r = (1-factor) * outerColor.red()/255 + factor * middleColor.red()/255;
                    g = (1-factor) * outerColor.green()/255 + factor * middleColor.green()/255;
                    b = (1-factor) * outerColor.blue()/255 + factor * middleColor.blue()/255;
                    painter.setPen(QColor(r * 255, g * 255, b * 255));
                }
				else {
					factor = qBound(0.0f, factor, 1.0f);
                    r = (1-factor) * middleColor.red()/255 + factor * innerColor.red()/255;
                    g = (1-factor) * middleColor.green()/255 + factor * innerColor.green()/255;
                    b = (1-factor) * middleColor.blue()/255 + factor * innerColor.blue()/255;
                    painter.setPen(QColor(r * 255, g * 255, b * 255));
                }
            }
            // Draw pixel
            painter.drawPoint(QPoint(x, y));
        }
    }

    // Update image
    m_imageItem->setPixmap(image);
}
