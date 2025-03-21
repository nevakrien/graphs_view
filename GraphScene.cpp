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
            } else if(node!=selectedNode && !node->getEdgeTo(selectedNode)){
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

//serilizing
void GraphScene::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_S) {
            saveToJson("graph_save.json");
        } else if (event->key() == Qt::Key_O) {
            loadFromJson("graph_save.json");
        }
    }
    QGraphicsScene::keyPressEvent(event);  // Pass to base class
}


void GraphScene::saveToJson(const QString& filename) {
    QJsonArray nodeArray;
    QMap<GraphNode*, int> nodeToId;
    int nodeId = 0;

    for (QGraphicsItem* item : items()) {
        if (GraphNode* node = dynamic_cast<GraphNode*>(item)) {
            QJsonObject obj;
            obj["id"] = nodeId;
            obj["x"] = node->pos().x();
            obj["y"] = node->pos().y();
            nodeArray.append(obj);
            nodeToId[node] = nodeId;
            nodeId++;
        }
    }

    QJsonArray edgeArray;
    for (QGraphicsItem* item : items()) {
        if (GraphEdge* edge = dynamic_cast<GraphEdge*>(item)) {
            GraphNode* src = edge->getSourceNode();
            GraphNode* tgt = edge->getTargetNode();
            if (nodeToId.contains(src) && nodeToId.contains(tgt)) {
                QJsonObject obj;
                obj["source"] = nodeToId[src];
                obj["target"] = nodeToId[tgt];
                edgeArray.append(obj);
            }
        }
    }

    QJsonObject root;
    root["nodes"] = nodeArray;
    root["edges"] = edgeArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void GraphScene::loadFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;

    clear();

    QMap<int, GraphNode*> idToNode;
    QJsonArray nodeArray = doc["nodes"].toArray();
    for (const QJsonValue& val : nodeArray) {
        QJsonObject obj = val.toObject();
        int id = obj["id"].toInt();
        qreal x = obj["x"].toDouble();
        qreal y = obj["y"].toDouble();

        GraphNode* node = new GraphNode();
        addItem(node);
        node->setPos(x, y);
        idToNode[id] = node;
    }

    QJsonArray edgeArray = doc["edges"].toArray();
    for (const QJsonValue& val : edgeArray) {
        QJsonObject obj = val.toObject();
        int srcId = obj["source"].toInt();
        int tgtId = obj["target"].toInt();

        if (idToNode.contains(srcId) && idToNode.contains(tgtId)) {
            GraphEdge* edge = new GraphEdge(idToNode[srcId], idToNode[tgtId]);
            addItem(edge);
            edge->updatePosition();
            idToNode[srcId]->addEdge(edge);
            idToNode[tgtId]->addEdge(edge);
        }
    }
}
