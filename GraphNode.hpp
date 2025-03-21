#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <vector>
#include <QPen>
#include <QGraphicsScene>
#include <cmath>


class GraphEdge;
class GraphScene;

class GraphNode : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    GraphNode(QGraphicsItem* parent = nullptr);
    ~GraphNode();

    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);
    void notifyEdges();  // Updates edges when the node moves

    void setSelected(bool b);
    GraphEdge* getEdgeTo(GraphNode* other) const;
    
signals:
    void requestConnection(GraphNode* node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;  // Right-click menu

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    std::unordered_map<GraphNode*, GraphEdge*> connections;
};

#endif
