#include "GraphEdge.hpp"


GraphEdge::GraphEdge(GraphNode* sourceNode, GraphNode* targetNode)
    : source(sourceNode), target(targetNode) {
    setPen(QPen(Qt::black, 2));
    updatePosition();
}

GraphEdge::~GraphEdge() {
    if (source) source->removeEdge(this);
    if (target) target->removeEdge(this);
}

void GraphEdge::updatePosition() {
    if (source && target) {
        setLine(QLineF(source->pos(), target->pos()));  // ✅ Update edge position when nodes move
    }
}

void GraphEdge::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        scene()->removeItem(this);
        delete this;
    }
}
