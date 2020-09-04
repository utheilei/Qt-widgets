#include "gaugespeed.h"
#include <QtMath>
#include <QDebug>
#include <QLCDNumber>
#include <QVBoxLayout>

GaugeSpeed::GaugeSpeed(QWidget *parent) : QWidget(parent)
{
//    QVBoxLayout *vboxLayout = new QVBoxLayout;
//    this->setLayout(vboxLayout);
//    QLCDNumber *lcdNumber = new QLCDNumber(this);
//    lcdNumber->setFixedSize(100,50);
//    vboxLayout->addWidget(lcdNumber);
//    vboxLayout->setAlignment(lcdNumber,Qt::AlignCenter);
//    vboxLayout->setContentsMargins(0,100,0,0);
//    int x =  (this->width()-lcdNumber->width())/2;
//    int y =  (this->height()-lcdNumber->height())/2;
//    lcdNumber->move(x,y);
//    qDebug()<<this->width()<<this->height()<<x<<y;
}

int GaugeSpeed::getRadius()
{
    return m_radius;
}

double GaugeSpeed::getValue()
{
    return m_value;
}

void GaugeSpeed::paintEvent(QPaintEvent *e)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    //painter.scale(side / 200.0, side / 200.0);

    drawRing(&painter);
    drawScale(&painter);
    drawScaleNum(&painter);
    drawPointer(&painter);
    drawValue(&painter);

    QWidget::paintEvent(e);
}

void GaugeSpeed::drawRing(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(20);
    QRect rect(-m_radius,-m_radius,2*m_radius,2*m_radius);

    //绘制第一圆环
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawArc(rect, 150 * 16, 60 * 16);

    //绘制第二圆环
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawArc(rect, 30 * 16, 120 * 16);

    //绘制第三圆环
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawArc(rect, -30 * 16, 60 * 16);
    painter->restore();
}

void GaugeSpeed::drawScale(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(1.5);
    painter->rotate(30);
    for (int i=0;i<9;i++) {
        if(i<3)
        {
            ringColor = Qt::green;
        }
        else if (i>5) {
            ringColor = Qt::red;
        }
        else {
            ringColor = Qt::blue;
        }
        painter->rotate(rotateAngle);
        pen.setColor(ringColor);
        painter->setPen(pen);
        painter->drawLine(0, m_radius-25, 0, m_radius-1);
    }
    painter->restore();
}

void GaugeSpeed::drawScaleNum(QPainter *painter)
{
    int starAngle = -30;
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(1.5);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    for (int i=0;i<9;i++) {
        starAngle -= 30;
        qreal x = (m_radius*2/3)*qSin(M_PI*starAngle/180);
        qreal y = (m_radius*2/3)*qCos(M_PI*starAngle/180);
        QString strValue = QString("%1M").arg(i*12.5);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int pointX = x - textWidth / 2;
        int pointY = y + textHeight / 4;
        painter->drawText(pointX,pointY,strValue);
    }
    painter->restore();
}

void GaugeSpeed::drawPointer(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::darkBlue);

    QPolygon polygon;
    polygon.setPoints(4, -5, 0, 0, -8, 5, 0, 0, m_radius/2);

    painter->rotate(60);
    double angle = (m_value/100)*(300-60);
    painter->rotate(angle);
    painter->drawConvexPolygon(polygon);
    painter->restore();
}

void GaugeSpeed::drawValue(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(true);
    font.setPointSize(30);
    painter->setFont(font);

    int textWidth = fontMetrics().width(QString::number(m_value));
    painter->drawText(-(textWidth/2+15),m_radius*2/5,QString::number(m_value));
    painter->restore();
}

void GaugeSpeed::setRadius(int radius)
{
    m_radius = radius;
    repaint();
}

void GaugeSpeed::setValue(int value)
{
    m_value = value;
    repaint();
}
