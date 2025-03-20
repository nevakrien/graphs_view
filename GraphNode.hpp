#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <vector>

class GraphEdge;

class GraphNode : public QGraphicsEllipseItem {
public:
    GraphNode(QGraphicsItem* parent = nullptr);
    ~GraphNode();

    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);
    void notifyEdges();  // Updates edges when the node moves

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;  // Right-click menu

private:
    std::vector<GraphEdge*> edges;
};

#endif
