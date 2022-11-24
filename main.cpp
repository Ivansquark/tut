#include "screen.h"
#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    screen w;
//    w.show();

    //---------------------------------------------------------
    //slow rotation
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();
    view->setGeometry(w.geometry());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->addWidget(&w);
    view->setScene(scene);
    view->show();
    view->rotate(270);

    return a.exec();
}
