#include "screen.h"

screen::screen(QWidget* parent) : QDialog(parent) { init(); }

screen::~screen() {
    delete scene;
    delete butLeft;
    delete butRight;
    delete butCenter;
}

void screen::init() {
    setFixedSize(600, 1024);
    butLeft = new QPixmap(":/pictures/play_left.png");
    butRight = new QPixmap(":/pictures/play_right.png");
    butCenter = new QPixmap(":/pictures/stop200.png");
    scene = new QPixmap();
    labScene->setPixmap(*scene);
    labLeft->setFixedSize(200, 200);
    labCenter->setFixedSize(200, 200);
    labRight->setFixedSize(200, 200);
    labLeft->setIcon(*butLeft);
    labRight->setIcon(*butRight);
    labCenter->setIcon(*butCenter);
    labLeft->setIconSize(QSize(200, 200));
    labRight->setIconSize(QSize(200, 200));
    labCenter->setIconSize(QSize(200, 200));
    layH->addWidget(labLeft);
    layH->addWidget(labCenter);
    layH->addWidget(labRight);
    layV->addWidget(labScene);
    layV->addLayout(layH);
    setLayout(layV);
}
