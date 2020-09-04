#ifndef GAUGESPEED_H
#define GAUGESPEED_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class GaugeSpeed : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius WRITE setRadius)
    Q_PROPERTY(double value READ getValue WRITE setValue)

public:
    explicit GaugeSpeed(QWidget *parent = nullptr);
    int getRadius();
    double getValue();

protected:
    void paintEvent(QPaintEvent *);
    void drawRing(QPainter *painter);   //绘制表盘圆环
    void drawScale(QPainter *painter);  //绘制表盘刻度
    void drawScaleNum(QPainter *painter);  //绘制表盘刻度值
    void drawPointer(QPainter *painter);   //绘制表盘指针
    void drawValue(QPainter *painter);     //绘制表盘显示值
signals:

public slots:
    void setRadius(int radius);   //设置表盘大小
    void setValue(int value);     //设置表盘显示值

private:
    QColor ringColor;
    int rotateAngle = 30;
    int m_radius;
    double m_value;
};

#endif // GAUGESPEED_H
