#include <cstdio>
#include <algorithm>
#include "Path2dView.hpp"

#define DEFAULT_WIDGET_WIDTH    1024
#define DEFAULT_WIDGET_HEIGHT    1024

bool compare_waypoint_position_x(base::Waypoint i, base::Waypoint j) {
    return i.position[0] < j.position[0];
}

bool compare_waypoint_position_y(base::Waypoint i, base::Waypoint j) {
    return i.position[1] < j.position[1];
}

Path2dView::Path2dView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene_ = new QGraphicsScene();
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setScene(scene_);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollChanged(int)));


    scene_scale_ = computeSceneScale(DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT);
    resize(DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT);
    show();
}

Path2dView::~Path2dView()
{
}

void Path2dView::setData(const std::vector<base::Waypoint> wps)
{
    waypoints_ = wps;
    drawWaypoint(fitToScreen());
}

std::vector<QPointF> Path2dView::fitToScreen() {
    return fitToScreen(waypoints_);
}

std::vector<QPointF> Path2dView::fitToScreen(const std::vector<base::Waypoint> wps) {

    scene_scale_ = computeSceneScale(
            viewport()->width(),
            viewport()->height(),
            (*std::min_element(wps.begin(), wps.end(), compare_waypoint_position_x)).position[0],
            (*std::max_element(wps.begin(), wps.end(), compare_waypoint_position_x)).position[0],
            (*std::min_element(wps.begin(), wps.end(), compare_waypoint_position_y)).position[1],
            (*std::max_element(wps.begin(), wps.end(), compare_waypoint_position_y)).position[1],
            25
    );

    return generatePoints(wps, scene_scale_);
}

std::vector<QPointF> Path2dView::generatePoints(qreal scale) {
    return generatePoints(waypoints_, scale);
}

std::vector<QPointF> Path2dView::generatePoints(const std::vector<base::Waypoint> wps, qreal scale) {
    std::vector<QPointF> norm_points;
    norm_points.resize(wps.size());

    for (size_t i = 0; i < wps.size(); i++) {
        norm_points[i] = QPointF(wps[i].position[0] * scene_scale_,  wps[i].position[1] * scene_scale_);
    }

    return norm_points;
}

void Path2dView::drawWaypoint(std::vector<QPointF> points) {

    const qreal line_width = 7;
    const qreal circle_radius_out = line_width;
    const qreal circle_radius_in = circle_radius_out - (circle_radius_out/4);

    if (points.size() > 0) {

        scene_->clear();

        QPen in_pen(Qt::yellow);
        QPen out_pen(Qt::black);

        out_pen.setWidth(line_width);
        in_pen.setWidth(line_width/2);

        QGraphicsPathItem *out_path = scene_->addPath(QPainterPath(), out_pen);

        QPainterPath path;
        path.moveTo(points[0]);

        QPointF pt = points[0];

        scene_->addEllipse(pt.x()-circle_radius_out, pt.y()-circle_radius_out, circle_radius_out*2, circle_radius_out*2, QPen(Qt::black), QBrush(Qt::black));
        scene_->addEllipse(pt.x()-circle_radius_in, pt.y()-circle_radius_in, circle_radius_in*2, circle_radius_in*2, QPen(Qt::yellow), QBrush(Qt::yellow));

        for (size_t i = 1; i < points.size(); i++) {
            pt = points[i];
            path.lineTo(pt);

            scene_->addEllipse(pt.x()-circle_radius_out, pt.y()-circle_radius_out, circle_radius_out*2, circle_radius_out*2, QPen(Qt::black), QBrush(Qt::black));
            scene_->addEllipse(pt.x()-circle_radius_in, pt.y()-circle_radius_in, circle_radius_in*2, circle_radius_in*2, QPen(Qt::yellow), QBrush(Qt::yellow));
        }

        out_path->setPath(path);

        QGraphicsPathItem *in_path = scene_->addPath(QPainterPath(), in_pen);
        in_path->setPath(path);
    }
}

qreal Path2dView::computeSceneScale(
    qreal screen_width, qreal screen_height,
    qreal min_x, qreal max_x,
    qreal min_y, qreal max_y,
    quint32 margin ){

    qreal scale_x = (screen_width - margin) / (max_x - min_x);
    qreal scale_y = (screen_height - margin) / (max_y - min_y);

    return std::min(scale_x, scale_y);
}

void Path2dView::wheelEvent(QWheelEvent *event) {

    if (event->modifiers() & Qt::ControlModifier) {

        QPoint mouse_pos = event->pos();

        QRectF before_scale_rect = scene_->itemsBoundingRect();

        QPointF viewport_pos = mapToScene(QPoint(viewport()->x(), viewport()->y()));

        scene_scale_ *= (static_cast<QWheelEvent*>(event)->delta() >= 0) ? 1.1 : 0.9;
        QPointF before_scale_pos = mapToScene(mouse_pos);

        drawWaypoint(generatePoints(scene_scale_));

        QRectF after_scale_rect = scene_->itemsBoundingRect();

        setSceneRect(after_scale_rect);

        QPointF after_scale_pos = mapToScene(mouse_pos);

        printf("Viewport: x: %d y: %d w: %d h: %d\n", viewport()->x(), viewport()->y(), viewport()->width(), viewport()->height());

        printf("before_scale_rect: x: %f y: %f w: %f h: %f\n", before_scale_rect.x(),
                                                               before_scale_rect.y(),
                                                               before_scale_rect.width(),
                                                               before_scale_rect.height());

        printf("after_scale_rect: x: %f y: %f w: %f h: %f\n", after_scale_rect.x(),
                                                              after_scale_rect.y(),
                                                              after_scale_rect.width(),
                                                              after_scale_rect.height());


        printf("before_scale_pos: %f y: %f\n", before_scale_pos.x(), before_scale_pos.y());
        printf("after_scale_pos: %f y: %f\n", after_scale_pos.x(), after_scale_pos.y());
        printf("mouse_pos: %d y: %d\n", mouse_pos.x(), mouse_pos.y());
        printf("viewport_pos: %f y: %f\n", viewport_pos.x(), viewport_pos.y());

        QScrollBar *horiz_scroll = horizontalScrollBar();

        printf("horiz_scroll - minimum: %d maximum: %d total_range: %d value: %d\n", horiz_scroll->minimum(),
                                                                                     horiz_scroll->maximum(),
                                                                                     horiz_scroll->maximum() - horiz_scroll->minimum(),
                                                                                     horiz_scroll->value());

//        QScrollBar *vert_scroll = verticalScrollBar();
//
//        horiz_scroll->setValue(-viewport_pos.x());
//        vert_scroll->setValue(vert_scroll->value() - before_scale_pos.y());
//        centerOn(before_scale_pos.x(), before_scale_pos.y());


        return;
    }

    QGraphicsView::wheelEvent(event);
}

void Path2dView::horizontalScrollChanged(int value) {
    printf("horizontalScrollChanged: %d\n", value);
}
