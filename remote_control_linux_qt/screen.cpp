#include "screen.h"

screen::screen(QWidget* parent) : QDialog(parent) { init(); }

screen::~screen() {
    delete scene;
    delete pixLeft;
    delete pixRight;
    delete pixCenter;
    delete pixCenterStarted;
    delete pixRightStarted;
    delete pixLeftStarted;
    delete scene;
    delete pixD1; delete pixD2; delete pixD3;
}

void screen::timeoutFPS()
{
    if(counterExit >100) close();
    if(w > 200) {
        labScene->setGeometry(w++,0,300,400);
        labScene->setPixmap(*pixD1);
    } else {
        labScene->setGeometry(w++,0,300,400);
        labScene->setPixmap(*pixD2);
    }

    switch(currentState) {
    case States::STOP:
        currentState = States::STOPPED;
        break;
    case States::STOPPED:
        butLeft->setIcon(*pixLeft);
        butRight->setIcon(*pixRight);
        butCenter->setIcon(*pixCenter);
        currentState = States::START;


        break;
    case States::START:
        static bool toggle;
        if(!toggle) {
            toggle = true;
            currentState = States::STARTED_LEFT;
        } else {
            toggle = false;
            currentState = States::STARTED_RIGHT;
        }
        break;
    case States::STARTED_LEFT:
        butLeft->setIcon(*pixLeftStarted);
        butRight->setIcon(*pixRight);
        butCenter->setIcon(*pixCenterStarted);
        currentState = States::STOP;
        break;
    case States::STARTED_RIGHT:
        butLeft->setIcon(*pixLeft);
        butRight->setIcon(*pixRightStarted);
        butCenter->setIcon(*pixCenterStarted);
        currentState = States::STOP;
        counterExit++;
        break;
    }
}

void screen::init() {
    setFixedSize(1024, 768);
    pixLeft = new QPixmap(":/pictures/play_left.png");
    pixRight = new QPixmap(":/pictures/play_right.png");
    pixCenter = new QPixmap(":/pictures/stop200.png");
    pixLeftStarted = new QPixmap(":/pictures/forward_left.png");
    pixRightStarted = new QPixmap(":/pictures/forward_right.png");
    pixCenterStarted = new QPixmap(":/pictures/pause.png");
    scene = new QPixmap();
    labScene->setPixmap(*scene);
    labScene->setFixedSize(300,400);
    butLeft->setFixedSize(340, 200);
    butCenter->setFixedSize(340, 200);
    butRight->setFixedSize(340, 200);
    butLeft->setIcon(*pixLeft);
    butRight->setIcon(*pixRight);
    butCenter->setIcon(*pixCenter);
    butLeft->setIconSize(QSize(340, 200));
    butRight->setIconSize(QSize(340, 200));
    butCenter->setIconSize(QSize(340, 200));
    layH->addWidget(butLeft);
    layH->addWidget(butCenter);
    layH->addWidget(butRight);
    layV->addWidget(labScene);
    layV->addLayout(layH);
    setLayout(layV);

    //-------------------- timer ----------------------
    timFPS = new QTimer(this);
    connect(timFPS, &QTimer::timeout, this, &screen::timeoutFPS);
    timFPS->start(1); //30fps

    //-------------------- photo ----------------------
    pixD1 = new QPixmap(":/d1.png");
    pixD2 = new QPixmap(":/d2.png");


}
