#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "GraphScene.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsView* view = new QGraphicsView();
    GraphScene* scene = new GraphScene();
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSceneRect(0, 0, 800, 600);

    // ✅ Connect GraphNode signal to GraphScene slot
    QObject::connect(scene, &GraphScene::handleConnection, scene, &GraphScene::handleConnection);

    QWidget window;
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(view);
    window.setLayout(layout);
    window.show();

    return app.exec();
}
