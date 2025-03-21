#ifndef GRAPHEDGE_HPP
#define GRAPHEDGE_HPP

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QGraphicsScene>
#include <cmath>

#include "GraphNode.hpp"

class GraphEdge : public QGraphicsLineItem {
public:
    GraphEdge(GraphNode* sourceNode, GraphNode* targetNode);
    ~GraphEdge();

    void updatePosition();  // Called when nodes move
    GraphNode* getSourceNode() const { return source; }
    GraphNode* getTargetNode() const { return target; }

     bool contains(const QPointF& point) const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    GraphNode* source;
    GraphNode* target;
};

#endif
