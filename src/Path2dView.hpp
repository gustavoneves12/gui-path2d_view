#ifndef PATH2DVIEW_HPP
#define PATH2DVIEW_HPP

#include <QtGui>
#include <base/Waypoint.hpp>

class Path2dView : public QGraphicsView
{
    Q_OBJECT
public:
    Path2dView(QWidget *parent = 0);
    virtual ~Path2dView();

public slots:
    void setData(const std::vector<base::Waypoint> waypoints);
    void horizontalScrollChanged(int value);

protected:
    virtual void wheelEvent(QWheelEvent *event);

private:

    void drawWaypoint(std::vector<QPointF> points);

    std::vector<QPointF> fitToScreen();
    std::vector<QPointF> fitToScreen(const std::vector<base::Waypoint> waypoints);

    std::vector<QPointF> generatePoints(qreal scale = 1.0);
    std::vector<QPointF> generatePoints(const std::vector<base::Waypoint> waypoints, qreal scale = 1.0);


    qreal computeSceneScale(qreal screen_width, qreal screen_height,
                            qreal min_x = 0, qreal max_x = 1.0,
                            qreal min_y = 0, qreal max_y = 1.0,
                            quint32 margin = 9);

    QGraphicsScene *scene_;

    std::vector<base::Waypoint> waypoints_;

    qreal scene_scale_;
};

#endif /* PATH2DVIEW_HPP */
