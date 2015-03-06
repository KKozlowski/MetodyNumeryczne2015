#include "plot.h"
#include "ui_plot.h"
#include <cmath>

Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    setupQuadraticDemo(ui->customPlot);
}

Plot::~Plot()
{
    delete ui;
}

void Plot::setupQuadraticDemo(QCustomPlot *customPlot)
{
  // generate some data:
    customPlot->clearGraphs();
    customPlot->clearPlottables();
  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = sin(x[i]);  // let's plot a quadratic function
  }
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(-1, 1);
}


void Plot::generatePlot(double (*f)(double))
{

}
