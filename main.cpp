#include <QApplication>
#include <QGraphicsView>
#include "GraphScene.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsView view;
    GraphScene scene;
    
    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(0, 0, 800, 600);
    view.show();

    return app.exec();
}
