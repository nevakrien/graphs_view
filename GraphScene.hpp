#ifndef GRAPHSCENE_HPP
#define GRAPHSCENE_HPP

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMessageBox>

#include "GraphNode.hpp"
#include "GraphEdge.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);
    virtual ~GraphScene() override;

    GraphNode* selectedNode = nullptr;
    
    void handleConnection(GraphNode* node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

};

#endif
