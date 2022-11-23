#ifndef SCREEN_H
#define SCREEN_H

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
    explicit screen(QWidget* parent = nullptr);
    virtual ~screen();

  signals:
  private:
    void init();
    QVBoxLayout* layV = new QVBoxLayout(this);
    QHBoxLayout* layH = new QHBoxLayout(this);
    QPixmap* scene;
    QPixmap* butLeft;
    QPixmap* butCenter;
    QPixmap* butRight;
    QPushButton* labLeft = new QPushButton(this);
    QPushButton* labRight = new QPushButton(this);
    QPushButton* labCenter = new QPushButton(this);
    QLabel* labScene = new QLabel(this);
};

#endif // SCREEN_H
