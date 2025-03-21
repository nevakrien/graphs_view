#include "GraphScene.hpp"


GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent), selectedNode(nullptr) {}

GraphScene::~GraphScene() {}

void GraphScene::selectNode(GraphNode* node){
    if(selectedNode) selectedNode->setSelected(false);
    if(node) node->setSelected(true);

    selectedNode = node;
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

    if (event->button() == Qt::LeftButton) {
        if (!item) {
            auto* node = new GraphNode();
            node->setPos(event->scenePos());
            addItem(node);
            selectNode(node);

            // connect(node, &GraphNode::requestConnection, this, &GraphScene::handleConnection);
        } 
        else if (auto* node = dynamic_cast<GraphNode*>(item)) {
            if (!selectedNode) {
                selectNode(node);
            } else {
                //Second node clicked, create edge
                auto* edge = new GraphEdge(selectedNode, node);
                addItem(edge);
                selectedNode->addEdge(edge);
                node->addEdge(edge);
                selectNode(nullptr);
            }
        }
    } 
    else if (event->button() == Qt::RightButton) {
        selectNode(nullptr);

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
        auto* edge = new GraphEdge(selectedNode, node);
        addItem(edge);
        selectedNode->addEdge(edge);
        node->addEdge(edge);
        selectNode(nullptr);
    }
}
