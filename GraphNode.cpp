#include "GraphNode.hpp"
#include "GraphEdge.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>

#include "GraphScene.hpp"

GraphNode::GraphNode(QGraphicsItem* parent) 
    : QGraphicsEllipseItem(-10, -10, 20, 20, parent) {
    setBrush(QBrush(Qt::blue));
    setFlag(QGraphicsItem::ItemIsMovable);
    // setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphNode::~GraphNode() {
    //deselect me
    GraphScene* graphScene = dynamic_cast<GraphScene*>(scene());
    if (graphScene && graphScene->selectedNode == this) {
        graphScene->selectedNode = nullptr;
    }

    //copy so we dont get weird stuff with destructors
    std::vector<GraphEdge*> toDelete;
    for (auto& pair : connections) {
        toDelete.push_back(pair.second);
    }

    for (GraphEdge* edge : toDelete) {
        GraphNode* other = (edge->getSourceNode() == this) ? edge->getTargetNode() : edge->getSourceNode();
        if (other) {
            other->removeEdge(edge);
        }
        delete edge;
    }

    connections.clear();
}


void GraphNode::addEdge(GraphEdge* edge) {
    GraphNode* other = (edge->getSourceNode() == this) ? edge->getTargetNode() : edge->getSourceNode();
    if (other) {
        connections[other] = edge;
    }
}

void GraphNode::removeEdge(GraphEdge* edge) {
    GraphNode* other = (edge->getSourceNode() == this) ? edge->getTargetNode() : edge->getSourceNode();
    if (other) {
        auto it = connections.find(other);
        if (it != connections.end() && it->second == edge) {
            connections.erase(it);
        }
    }
}


GraphEdge* GraphNode::getEdgeTo(GraphNode* other) const {
    auto it = connections.find(other);
    return (it != connections.end()) ? it->second : nullptr;
}

void GraphNode::notifyEdges() {
    for (const auto& [otherNode, edge] : connections) {
        if (edge) {
            edge->updatePosition();
        }
    }
}

void GraphNode::setSelected(bool b){
    if(b){
        setBrush(QBrush(Qt::yellow));
    } else {
        setBrush(QBrush(Qt::blue));
    }

    update();
}

void GraphNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);

    // // Change color based on selection state
    // if (selected) {
    //     painter->setBrush(Qt::yellow);
    // } else {
    //     painter->setBrush(Qt::blue);
    // }

    painter->setBrush(brush());
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(rect());
}


/// mouse handeling

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // setBrush(QBrush(Qt::yellow));  //Highlight when clicked
    QGraphicsEllipseItem::mousePressEvent(event);
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsEllipseItem::mouseMoveEvent(event);
    notifyEdges();  //Ensure edges update

}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // setBrush(QBrush(Qt::blue));  //Reset color when released
    // setSelected(false);
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
