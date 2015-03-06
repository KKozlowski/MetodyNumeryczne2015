#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QString>
#include <list>
#include "plot.h"
#include "funk.h"

namespace Ui {
class Controller;
}

class Controller : public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();
    void GetValues();

public slots:
    void ComputeSinus();

private:
    Ui::Controller *ui;
    QString one;
    QString two;
    QString three;
    QString four;

    std::list<Plot*> plots;

    double startNum;
    double endNum;
};

#endif // CONTROLLER_H
