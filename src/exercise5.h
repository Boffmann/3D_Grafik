#pragma once

//
// Qt
//
#include <QGraphicsView>

class Exercise5 : public QGraphicsView
{
    Q_OBJECT

	public:
        Exercise5(QWidget *parent = NULL);
        ~Exercise5();

	protected:
		/**
		*  @brief
		*    Called when widget is resized
		*
		*  @param event
		*    Resize event
		*/
        virtual void resizeEvent(QResizeEvent *event);

		/**
		*  @brief
		*    Called when mouse button is released
		*
		*  @param event
		*    Mouse event
		*/
        virtual void mouseReleaseEvent(QMouseEvent *event);

		/**
		*  @brief
		*    Render metaballs
		*/
	    void renderMetaballs();

	protected:
        QGraphicsScene       m_scene;       /**< Graphics scene */
        QGraphicsPixmapItem* m_imageItem;   /**< Graphics image item */
        QVector<QPoint>      m_metaballs;   /**< List of metaballs */
};
