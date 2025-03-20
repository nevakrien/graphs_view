#ifndef GRAPHSCENE_HPP
#define GRAPHSCENE_HPP

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMessageBox>

#include "GraphNode.hpp"
#include "GraphEdge.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);
    virtual ~GraphScene() override;

    void setEraseMode(bool enabled);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    bool eraseMode = false;
    GraphNode* selectedNode = nullptr;
};

#endif
