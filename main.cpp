#include <QApplication>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include "GraphScene.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // ✅ Setup Scene and View
    QGraphicsView* view = new QGraphicsView();
    GraphScene* scene = new GraphScene();
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSceneRect(0, 0, 800, 600);

    // ✅ Create "Erase Node" Button
    QPushButton* eraseButton = new QPushButton("Erase Node");
    QObject::connect(eraseButton, &QPushButton::clicked, [scene]() {
        scene->setEraseMode(true);
    });

    // ✅ Setup Layout
    QWidget window;
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(view);
    layout->addWidget(eraseButton);
    window.setLayout(layout);
    window.show();

    return app.exec();
}
