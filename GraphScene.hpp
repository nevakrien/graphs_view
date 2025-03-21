#ifndef GRAPHSCENE_HPP
#define GRAPHSCENE_HPP

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>
#include <QKeyEvent>

#include "GraphNode.hpp"
#include "GraphEdge.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);
    virtual ~GraphScene() override;

    GraphNode* selectedNode = nullptr;
    

    void selectNode(GraphNode* node);

    void saveToJson(const QString& filename);
    void loadFromJson(const QString& filename);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif
