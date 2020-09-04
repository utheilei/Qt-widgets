#include "mainwindow.h"
#include "waterprogressbar.h"
#include "gaugespeed.h"
#include "ClockWidget.h"
#include <QSlider>
#include <QBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,300,800,600);
    QWidget *centerWidget = new QWidget;
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    centerWidget->setLayout(vLayout);

    WaterProgressBar *probar = new WaterProgressBar(this);
    probar->setValue(30);
    probar->setRadius(50);
    probar->setBgColor(Qt::black);
    probar->setWaterColor(Qt::yellow);
    probar->start();

    ClockWidget *clockWidget = new ClockWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(clockWidget);
    vlayout->addWidget(probar);

    GaugeSpeed *gauge = new GaugeSpeed(this);
    gauge->setValue(60);
    gauge->setRadius(150);

    hLayout->addLayout(vlayout);
    hLayout->addWidget(gauge);

    QSlider *slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(0);
    slider->setMaximum(100);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(slider);
    this->setCentralWidget(centerWidget);

    connect(slider,&QSlider::valueChanged,[probar,gauge](int value){
        probar->setValue(value);
        gauge->setValue(value);
    });
}

MainWindow::~MainWindow()
{

}
