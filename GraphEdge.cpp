#include "GraphEdge.hpp"

GraphEdge::GraphEdge(GraphNode* sourceNode, GraphNode* targetNode)
    : source(sourceNode), target(targetNode) {
    assert(sourceNode&&targetNode&&targetNode!=sourceNode);
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePosition();
    
}

GraphEdge::~GraphEdge() {
    if (target) target->removeEdge(this);
    if (source) source->removeEdge(this);
}

void GraphEdge::updatePosition() {
    if (source && target) {
        setLine(QLineF(source->pos(), target->pos()));
    }
}

void GraphEdge::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        scene()->removeItem(this);
        delete this;
    }
}

/**
 * @brief Computes the shortest distance from a point to a line segment.
 *
 * @param point The point in question.
 * @param lineStart The start of the line segment.
 * @param lineEnd The end of the line segment.
 * @return The perpendicular distance from `point` to the segment.
 */
static qreal distanceToSegment(const QPointF& point, const QPointF& lineStart, const QPointF& lineEnd) {
    QLineF line(lineStart, lineEnd);
    
    if (line.length() == 0.0) {
        return QLineF(point, lineStart).length(); // If the segment is a single point
    }

    // Compute the projection factor `t` (normalized position on segment)
    QPointF lineVec = lineEnd - lineStart;
    QPointF pointVec = point - lineStart;

    qreal t = QPointF::dotProduct(pointVec, lineVec) / QPointF::dotProduct(lineVec, lineVec);

    // Clamp `t` to stay within the segment
    t = std::max(0.0, std::min(1.0, t));

    // Compute the closest point on the segment
    QPointF closestPoint = lineStart + t * lineVec;

    // Return the distance from the point to the closest point on the segment
    return QLineF(point, closestPoint).length();
}

bool GraphEdge::contains(const QPointF &point) const {    
    qreal distance = distanceToSegment(point,source->pos(), target->pos());
    
    return distance < 10.0;  //If near enough, consider it selected
}
