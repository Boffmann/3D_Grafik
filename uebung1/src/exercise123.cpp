// ======================================
// 3D-Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 1
//                     - Aufgabe 1,2,3
// Matrikelnummern: 775014, 775165
//
//
// ======================================

#include "exercise123.h"
//
// std
//
#include <math.h>
//
// Qt
//
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QDebug>

using namespace Qt;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
// Get pixel at position
QColor Exercise123::getPixel(const QImage &image, int x, int y)
{
    return QColor(image.pixel(qBound(0, x, image.width()-1), qBound(0, y, image.height() - 1)));
}

// clamp color components to [0.0, 1.0]
void Exercise123::clampColor(float &r, float &g, float &b)
{
    r = qBound(0.0f, r, 1.0f);
    g = qBound(0.0f, g, 1.0f);
    b = qBound(0.0f, b, 1.0f);
}

// return grayscale
float Exercise123::getGrayColor(const QColor &color)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (grayscale)
    //////////////////////////////////////////////////
    float gray = 0.0f;

    //TODO: Implement grayscale function
    gray = 0.299 * color.redF() + 0.587 * color.greenF() + 0.114 * color.blueF();

    return gray;
}

// return grayscale
QColor Exercise123::getInvertColor(const QColor &color)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (invert color)
    //////////////////////////////////////////////////
    QColor invert;

    //TODO: Implement invert color function

    invert.setRgb(255-color.red(),255-color.green(),255-color.blue());

    return invert;
}

//[-------------------------------------------------------]
//[ Filter functions                                      ]
//[-------------------------------------------------------]

QColor Exercise123::getSharpenColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
  //////////////////////////////////////////////////
  /// \brief r
  ///
    float r = 0;
    float g = 0;
    float b = 0;

    ///	...	 ... ... ... ...
    ///	...	|_1_|_2_|_3_|...
    ///	...	|_4_|_5_|_6_|...	<- 3x3 filter components
    ///	...	|_7_|_8_|_9_|...
    ///	...	 ... ... ... ...

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Laplace-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2a
    //////////////////////////////////////////////////
    // Apply kernel
    for (int yy=-1; yy<=1; yy++) {
        for (int xx=-1; xx<=1; xx++) {
            QColor pixel = getPixel(image,x + xx,y + yy);
            r += kernel[xx+1+3*(yy+1)] * pixel.redF();
            g += kernel[xx+1+3*(yy+1)] * pixel.greenF();
            b += kernel[xx+1+3*(yy+1)] * pixel.blueF();
        }
    }
    clampColor(r, g, b);
    return QColor::fromRgbF(r, g, b);
}

QColor Exercise123::getGaussColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Gauss-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

    // Apply kernel
    //////////////////////////////////////////////////
    // TODO: Aufgabe 2b
    //////////////////////////////////////////////////
    int weight = 0;
    for (int yy=-1; yy<=1; yy++) {
        for (int xx=-1; xx<=1; xx++) {
            QColor pixel = getPixel(image,x + xx,y + yy);
            r += kernel[xx+1+3*(yy+1)] * pixel.redF();
            g += kernel[xx+1+3*(yy+1)] * pixel.greenF();
            b += kernel[xx+1+3*(yy+1)] * pixel.blueF();
            weight += kernel[xx+1+3*(yy+1)];
        }
    }
    r /= weight;
    g /= weight;
    b /= weight;
    clampColor(r, g, b);
    return QColor::fromRgbF(r, g, b);
}

QColor Exercise123::getSobelColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernels as Sobel Operators for both directions
    //////////////////////////////////////////////////////////////////////////
    int kernelX[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int kernelY[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2c
    //////////////////////////////////////////////////

    // apply kernel, use grayColor()!

    float c = 0.0f;
    float tmpx = 0.0f;
    float tmpy = 0.0f;
    for (int yy=-1; yy<=1; yy++) {
        for (int xx=-1; xx<=1; xx++) {
          tmpx += kernelX[xx+1+3*(yy+1)] * getGrayColor(getPixel(image,x + xx,y + yy));
          tmpy += kernelY[xx+1+3*(yy+1)] * getGrayColor(getPixel(image,x + xx,y + yy));
        }
    }
    if(tmpx < 0.0) tmpx *= -1.0;
    if(tmpy < 0.0) tmpy *= -1.0;
    c = tmpx + tmpy;
    c /= 2;
    c = qBound(0.0f, c, 1.0f);
    return QColor::fromRgbF(c, c, c);
}

QColor Exercise123::getMeanColorDynamicSize(const QImage &image, int x, int y, int kernelSize)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2d
    //////////////////////////////////////////////////

    // Apply kernel

    // TODO: normalize
    float sum = 0.0;
    for (int yy=-(int)kernelSize; yy<=(int)kernelSize; yy++) {
        for (int xx=-(int)kernelSize; xx<=(int)kernelSize; xx++) {
          QColor pixel = getPixel(image,x + xx,y + yy);
          r += pixel.redF();
          g += pixel.greenF();
          b += pixel.blueF();
          sum += 1;
        }
    }
    r /= sum;
    g /= sum;
    b /= sum;
    clampColor(r, g, b);
    return QColor::fromRgbF(r, g, b);
}
QRgb ditheringhelp(QColor color, float diff) {
  float r = color.redF() + diff;
  float g = color.greenF() + diff;
  float b = color.blueF() + diff;
  r = qBound(0.0f, r, 1.0f);
  g = qBound(0.0f, g, 1.0f);
  b = qBound(0.0f, b, 1.0f);
  return QColor::fromRgbF(r, g, b).rgb();
}


//getDitheringColor can work directly on image - use it
QColor Exercise123::getDitheringColor(QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 3
    //////////////////////////////////////////////////

    float oldpixel = 0.0f;
    float newpixel = 0.0f;

    //TODO: quantize oldpixel to a gray color palette with 4 entries (0.0f, 0.33f, 0.66f, 1.0f)
    //TODO: dithering by floyd-steinberg
    oldpixel = getGrayColor(getPixel(image,x,y));
    if(oldpixel < (1.0/6)){
      newpixel = 0.0f;
    } else if(oldpixel < (0.5)) {
      newpixel = 1.0/3; // looks prettier than 0.33
      //newpixel = 0.33f;
    } else if(oldpixel < (5.0/6)) {
      newpixel = 2.0/3; // looks prettier than 0.66
      //newpixel = 0.66f;
    } else newpixel = 1.0f;

    image.setPixel(x, y ,newpixel);
    float diff = oldpixel - newpixel;
    if(y < image.height() - 1) {
      image.setPixel(x, y+1 ,ditheringhelp(getPixel(image, x, y+1), (diff * 5.0/16)));
    } if(x < image.width() - 1 && y < image.height() - 1) {
        image.setPixel(x+1, y+1, ditheringhelp(getPixel(image, x+1, y+1), (diff/16)));
    } if(x > 0 && y < image.height() - 1) {
        image.setPixel(x-1, y+1, ditheringhelp(getPixel(image, x-1, y+1), (diff * 3.0/16)));
    } if(x < image.width() - 1) {
      image.setPixel(x+1, y, ditheringhelp(getPixel(image, x+1, y), (diff * 7.0/16)));
    }

    newpixel = qBound(0.0f, newpixel, 1.0f);
    return QColor::fromRgbF(newpixel, newpixel, newpixel);
}

Exercise123::Exercise123(Filter_Type type, QWidget *parent) :
    ImageView(parent),
    m_type(type)
{
    // load image
    const QImage image("image1.png");
    QImage filterImage(image);

    if(type == ORIGINAL)
    {
        this->setImage(image);
    }
    else
    {
        // filter image
        for (int y=0; y<image.height(); y++)
        {
            for (int x=0; x<image.width(); x++)
            {
                QColor filteredColor;

                // choose filter
                if(type == LAPLACE)
                {
                    filteredColor = getSharpenColor(image, x, y);
                }
                else if(type == GAUSS)
                {
                    filteredColor = getGaussColor(image, x, y);
                }
                else if(type == SOBEL)
                {
                    filteredColor = getSobelColor(image, x, y);
                }
                else if(type == MEANFILTER)
                {
                    filteredColor = getMeanColorDynamicSize(image, x, y, 5);
                }
                else if(type == GRAYSCALE)
                {
                    float luminance = getGrayColor(getPixel(image, x, y));
                    filteredColor = QColor::fromRgbF(luminance, luminance, luminance);
                }
                else if(type == INVERT)
                {
                    filteredColor = getInvertColor(getPixel(image, x, y));
                }
                else if(type == DITHERED)
                {
                    filteredColor = getDitheringColor(filterImage, x, y);
                }
                else
                {
                    // ORIGINAL -> do nothing
                }

                // draw pixel
                filterImage.setPixel(x,y,filteredColor.rgb());
            }
        }

        this->setImage(filterImage);
        this->zoomOut();
    }
}

Exercise123::~Exercise123()
{
}
