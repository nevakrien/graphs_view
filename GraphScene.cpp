#include "GraphScene.hpp"

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent) {}

GraphScene::~GraphScene() {}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (!item) {
            auto* node = new GraphNode();
            node->setPos(event->scenePos());
            addItem(node);
        } 
        else if (auto* node = dynamic_cast<GraphNode*>(item)) {
            if (!selectedNode) {
                selectedNode = node;
            } else {
                auto* edge = new GraphEdge(selectedNode, node);
                addItem(edge);
                selectedNode->addEdge(edge);
                node->addEdge(edge);
                selectedNode = nullptr;
            }
        }
    } 
    else if (event->button() == Qt::RightButton) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (auto* edge = dynamic_cast<GraphEdge*>(item)) {
            removeItem(edge);
            delete edge;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
