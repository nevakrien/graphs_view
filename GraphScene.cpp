#include "GraphScene.hpp"


GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent), selectedNode(nullptr) {}

GraphScene::~GraphScene() {}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

    if (event->button() == Qt::LeftButton) {
        if (!item) {
            auto* node = new GraphNode();
            node->setPos(event->scenePos());
            addItem(node);
            connect(node, &GraphNode::requestConnection, this, &GraphScene::handleConnection);
        } 
        else if (auto* node = dynamic_cast<GraphNode*>(item)) {
            if (!selectedNode) {
                selectedNode = node;  // ✅ First node selected
            } else {
                // ✅ Second node clicked, create edge
                auto* edge = new GraphEdge(selectedNode, node);
                addItem(edge);
                selectedNode->addEdge(edge);
                node->addEdge(edge);
                selectedNode = nullptr;  // ✅ Reset selection
            }
        }
    } 
    else if (event->button() == Qt::RightButton) {
        if (auto* edge = dynamic_cast<GraphEdge*>(item)) {
            removeItem(edge);
            delete edge;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}


void GraphScene::handleConnection(GraphNode* node) {
    if (!selectedNode) {
        selectedNode = node;
    } else {
        // ✅ Create an edge only if explicitly requested
        auto* edge = new GraphEdge(selectedNode, node);
        addItem(edge);
        selectedNode->addEdge(edge);
        node->addEdge(edge);
        selectedNode = nullptr;
    }
}
