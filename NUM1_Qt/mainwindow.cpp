#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateOutput()
{
    ui->output->setText(text);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    text+="Raz\nDwa\nTrzy";
    updateOutput();
    connect(ui->command, SIGNAL(returnPressed()), this, SLOT( ReadLine() ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadLine()
{
    text+=ui->command->text();
    text+='\n';
    updateOutput();
    ui->command->clear();
}


