#ifndef PLOT_H
#define PLOT_H

#include "../qcustomplot.h"
#include <QWidget>

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = 0);
    ~Plot();

private:
    Ui::Plot *ui;
    void setupQuadraticDemo(QCustomPlot *customPlot);
    void generatePlot(double (*f)(double));
};

#endif // PLOT_H
