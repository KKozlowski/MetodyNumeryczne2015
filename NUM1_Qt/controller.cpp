#include "controller.h"
#include "ui_controller.h"
#include <iostream>
#include <iostream>
#include <cmath>
#include <list>

//list<double> rozwiazania;
double miejsceZerowe;
double iterationLimit;
template<class F>void bisekcja(double start, double end, F funk, double epsilon){
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        double centerValue = funk(center);
        if(abs(centerValue) < epsilon){
            miejsceZerowe = center;
        } else {
            bisekcja(start, center, funk, epsilon);
            bisekcja(center, end, funk, epsilon);
        }
    }
}

template<class F>void bisekcjaITL(double start, double end, F funk, double it){
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        //double centerValue = funk(center);
        if(it == iterationLimit){
            miejsceZerowe = center;
        } else {
            bisekcja(start, center, funk, ++it);
            bisekcja(center, end, funk, ++it);
        }
    }
}



Controller::Controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controller)
{
    ui->setupUi(this);
    connect(ui->Sinus, SIGNAL(pressed()), this, SLOT( ComputeSinus()));
}

Controller::~Controller()
{
    delete ui;
}

void Controller::GetValues()
{
    one = ui->One->text();
    two = ui->Two->text();
    startNum = one.toDouble();
    endNum = two.toDouble();

}

void Controller::ComputeSinus()
{
    ui->MiejsceZerowe->setText(QString("Hue"));
    GetValues();
    bisekcja(startNum,endNum,sinus,0.1);
    ui->MiejsceZerowe->setText(QString::number(miejsceZerowe));
    Plot *p = new Plot();
    p->show();
    plots.push_back(p);
}
