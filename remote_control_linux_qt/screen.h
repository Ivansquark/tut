#ifndef SCREEN_H
#define SCREEN_H

#include <qrandom.h>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

class screen : public QDialog {
    Q_OBJECT
  public:
    enum States : uint8_t {
        STOP,
        STOPPED,
        START,
        STARTED_LEFT,
        STARTED_RIGHT
    };
    explicit screen(QWidget* parent = nullptr);
    virtual ~screen();

  signals:
private slots:
    void timeoutFPS();
  private:
    void init();
    QVBoxLayout* layV = new QVBoxLayout(this);
    QHBoxLayout* layH = new QHBoxLayout(this);
    QPixmap* scene;
    QPixmap* pixLeft;
    QPixmap* pixCenter;
    QPixmap* pixRight;
    QPixmap* pixLeftStarted;
    QPixmap* pixCenterStarted;
    QPixmap* pixRightStarted;
    QPixmap* pixD1;
    QPixmap* pixD2;
    QPixmap* pixD3;
    QPushButton* butLeft = new QPushButton(this);
    QPushButton* butRight = new QPushButton(this);
    QPushButton* butCenter = new QPushButton(this);
    QLabel* labScene = new QLabel(this);
    //-------------- timer ---------------
    QTimer* timFPS;
    //-------------- states --------------
    States currentState = States::STOPPED;
    uint16_t counterExit = 0;
    //-------------- photo pos -----------
    uint16_t w = 0;
};

#endif // SCREEN_H
