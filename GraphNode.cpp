#include "GraphNode.hpp"
#include "GraphEdge.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>

#include "GraphScene.hpp"

GraphNode::GraphNode(QGraphicsItem* parent) 
    : QGraphicsEllipseItem(-10, -10, 20, 20, parent) {
    setBrush(QBrush(Qt::blue));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphNode::~GraphNode() {
    //deselect me
    GraphScene* graphScene = dynamic_cast<GraphScene*>(scene());
    if (graphScene && graphScene->selectedNode == this) {
        graphScene->selectedNode = nullptr;
    }

    //Remove all edges safely
    while (!edges.empty()) {
        GraphEdge* edge = edges.back();
        edges.pop_back();

        if (edge->getSourceNode() == this) {
            if (edge->getTargetNode()) {
                edge->getTargetNode()->removeEdge(edge);
            }
        } else {
            if (edge->getSourceNode()) {
                edge->getSourceNode()->removeEdge(edge);
            }
        }

        delete edge;
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

/// mouse handeling

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setBrush(QBrush(Qt::yellow));  // ✅ Highlight when clicked
    QGraphicsEllipseItem::mousePressEvent(event);
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    notifyEdges();  // ✅ Ensure edges update
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    setBrush(QBrush(Qt::blue));  // ✅ Reset color when released
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}


void GraphNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
    QMenu menu;
    QAction* deleteAction = menu.addAction("Delete Node");
    // QAction* connectAction = menu.addAction("Connect Edge");

    QAction* selectedAction = menu.exec(event->screenPos());
    
    if (selectedAction == deleteAction) {
        scene()->removeItem(this);
        delete this;
    } 
    // else if (selectedAction == connectAction) {
    //     scene()->addItem(new GraphEdge(this, nullptr));  // Start edge connection
    // }
}
