#include "GraphScene.hpp"


GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent), eraseMode(false) {}

GraphScene::~GraphScene() {}

void GraphScene::setEraseMode(bool enabled) {
    eraseMode = enabled;
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

    if (eraseMode) {
        // ✅ If erasing, remove the clicked node (if it's a GraphNode)
        if (auto* node = dynamic_cast<GraphNode*>(item)) {
            removeItem(node);
            delete node;
        }
        eraseMode = false;  // Exit erase mode after one deletion
        return;  // 🚨 Prevent other actions in erase mode
    }

    if (event->button() == Qt::LeftButton) {
        if (!item) {
            // ✅ Left-click empty space → Create a new node
            auto* node = new GraphNode();
            node->setPos(event->scenePos());
            addItem(node);
        } 
        else if (auto* node = dynamic_cast<GraphNode*>(item)) {
            if (!selectedNode) {
                selectedNode = node;
            } else {
                // ✅ Left-click on two nodes → Create an edge
                auto* edge = new GraphEdge(selectedNode, node);
                addItem(edge);
                selectedNode->addEdge(edge);
                node->addEdge(edge);
                selectedNode = nullptr;
            }
        }
    } 
    else if (event->button() == Qt::RightButton) {
        // ✅ Right-click on an edge → Delete it
        if (auto* edge = dynamic_cast<GraphEdge*>(item)) {
            removeItem(edge);
            delete edge;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
