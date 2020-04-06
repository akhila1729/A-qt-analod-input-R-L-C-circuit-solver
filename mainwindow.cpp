#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <cmath>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/ASUS/Desktop/xcircuit figures/rlc_circuit");
    ui->label_pic->setPixmap(pix);
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(onclicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onclicked()
{
    circuit_solver();
}
void MainWindow::circuit_solver()
{
    double h=1/(100000.0);
    double Vmax=ui->lineEdit->text().toDouble();
    double R=ui->lineEdit_2->text().toDouble();
    double C=ui->lineEdit_3->text().toDouble();
    double L=ui->lineEdit_4->text().toDouble();
    double phi=ui->lineEdit_5->text().toDouble();//sin(wt) is taken as reference
    double w=ui->lineEdit_6->text().toDouble();
    int N=100000*10*2*3.14/w;
    QVector<double> t(N),i(N);
    t[0]=0;
    i[0]=Vmax*sin(phi);
    double Xc=1/(C*w);
    double Xl=L*w;
    double X=Xl-Xc;
    double Xt;
    double theta;//the angle by which current leads or lags voltage

    Xt=sqrt(X*X+R*R);
    double imax=Vmax/Xt;
    theta=atan(X/R);
    for(int n=1;n<(100000*10*2*3.14/w);n++)
    {
        t[n]=n*h;
        i[n]=imax*sin(w*t[n]+phi*3.14/180+theta);
    }
    double imin=-1.5*imax;
    double xmax=10*2*3.14/w;



    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(t,i);
    ui->customPlot->xAxis->setLabel("t(s)");
    ui->customPlot->yAxis->setLabel("current(A)");
    ui->customPlot->xAxis->setRange(0,xmax);
    ui->customPlot->yAxis->setRange(imin,1.5*imax);
    ui->customPlot->replot();

}






