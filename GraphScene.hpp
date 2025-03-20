#ifndef GRAPHSCENE_HPP
#define GRAPHSCENE_HPP

#include <QGraphicsScene>
#include <QObject>
#include "GraphNode.hpp"
#include "GraphEdge.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);
    virtual ~GraphScene() override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    GraphNode* selectedNode = nullptr;
};

#endif
