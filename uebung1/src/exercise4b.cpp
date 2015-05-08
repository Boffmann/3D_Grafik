// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 1
//                     - Aufgabe 4b
//
//
//
// ======================================

#include "exercise4b.h"
#include "stable.h"

//
// std
//
#include <math.h>

//
// Qt
//
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>

using namespace Qt;

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
const float maxAbsSquare = 4.0f;
const int maxIterations  = 100;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
namespace exercise4b
{

int computeIterations(float cx, float cy)
{
    float absSquare = 0;
    int iterationCount = 0;
    float x = 0, y = 0;
    //////////////////////////////////////////////////////////////////////////
    // TODO: copy from implemented computeIterations() at Exercise4a
    //////////////////////////////////////////////////////////////////////////
    while(iterationCount <= maxIterations && absSquare <= maxAbsSquare) {
      float x_old = x;
      x = x * x - y * y + cx;
      y = 2 * x_old * y + cy;
      absSquare = x * x + y * y;
      iterationCount++;
    }
    return iterationCount;
}


QColor chooseColor(int value, int maxValue)
{
	float p = (float)value/maxValue;
	int i = (int)(299 * std::min(std::max(p, 0.0f), 1.0f));
	int k = i / 60;
	float m = 1.0f * (i % 60) / 59.0f;
	switch (k)
	{
        case 0: return QColor(255, m*255, 0);
        case 1: return QColor((1-m)*255, 255, 0);
        case 2: return QColor(0, 255, m);
        case 3: return QColor(m*255, (1-m)*255, 255);
        case 4: return QColor((1-m)*255, 0, 255);
	}

	return QColor(0, 0, 0);
}

}

using namespace exercise4b;

Exercise4b::Exercise4b(QWidget *parent) :
    ImageView(parent),
    m_currentLevel(0),
    m_currentDir(1),
    m_timer(NULL)
{
    // Render mandelbrot set (initially)
    renderMandelbrot();

    //////////////////////////////////////////////////////////////////////////////
    // TODO: 4(b) Create a QTimer here and connect it to the slot onTimer()
    //            (in it, update m_currentLevel to count from 0 to 12 and back)
    //////////////////////////////////////////////////////////////////////////////

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(500);
    renderMandelbrot();
}

Exercise4b::~Exercise4b()
{
    // Destroy timer
    delete m_timer;
}

void Exercise4b::renderMandelbrot()
{
    // Create image
    int width = 800, height = 600;
    QPixmap mandelbrot(width, height);
    QPainter painter(&mandelbrot);

    // Draw image using a quadtree
    drawRecursive(painter, 0, 0, width, height, m_currentLevel);

    // Update image
    this->setImage(mandelbrot.toImage());
}

/**
*  @brief
*    Draw function recursively by using a quadtree-method
*/
void Exercise4b::drawRecursive(QPainter &painter, int x, int y, int w, int h, int level)
{
    //////////////////////////////////////////////////////////////////////////
    // TODO: Render Mandelbrot recursively for current level m_level
    //////////////////////////////////////////////////////////////////////////
    if(level <= 0) {
      QPoint origin(600, 250);
      float scaleX = 3.0f, scaleY = 3.0f;
      int width = 800, height = 600;
      float cx = ((float)((x + w/2) - origin.x()) / width)  * scaleX;
      float cy = ((float)((y + h/2) - origin.y()) / height) * scaleY;
      painter.fillRect(x, y, x+(w-1), y+(h-1), chooseColor(computeIterations(cx, cy), maxIterations));
    } else {
      drawRecursive(painter, x, y, w/2+1, h/2+1, level-1);
      drawRecursive(painter, x+w/2, y, w/2+1, h/2+1, level-1);
      drawRecursive(painter, x, y+h/2, w/2+1, h/2+1, level-1);
      drawRecursive(painter, x+w/2,y+h/2, w/2+1, h/2+1, level-1);
     }
}

void Exercise4b::onTimer()
{
    //////////////////////////////////////////////////////////////////////////
    // TODO: count level from 0 to 12 and back (ping-pong loop)
    //////////////////////////////////////////////////////////////////////////
    if(m_currentLevel == 0) m_currentDir = 1;
    if(m_currentLevel == 12) m_currentDir = -1;
    m_currentLevel += m_currentDir;

    // Render mandelbrot with current level
    renderMandelbrot();
}
