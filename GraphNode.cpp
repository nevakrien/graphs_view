#include "GraphNode.hpp"
#include "GraphEdge.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>

GraphNode::GraphNode(QGraphicsItem* parent) 
    : QGraphicsEllipseItem(-10, -10, 20, 20, parent) {
    setBrush(QBrush(Qt::blue));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphNode::~GraphNode() {
    for (auto* edge : edges) {
        delete edge;  // Delete edges when the node is deleted
    }
}

void GraphNode::addEdge(GraphEdge* edge) {
    edges.push_back(edge);
}

void GraphNode::removeEdge(GraphEdge* edge) {
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

void GraphNode::notifyEdges() {
    for (auto* edge : edges) {
        edge->updatePosition();
    }
}

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setBrush(QBrush(Qt::yellow));  // Highlight when selected
    QGraphicsEllipseItem::mousePressEvent(event);
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    setBrush(QBrush(Qt::blue));
    notifyEdges();  // ✅ Update edges when moved
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void GraphNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
    QMenu menu;
    QAction* deleteAction = menu.addAction("Delete Node");
    QAction* connectAction = menu.addAction("Connect Edge");

    QAction* selectedAction = menu.exec(event->screenPos());
    
    if (selectedAction == deleteAction) {
        scene()->removeItem(this);
        delete this;
    } 
    else if (selectedAction == connectAction) {
        scene()->addItem(new GraphEdge(this, nullptr));  // Start edge connection
    }
}
