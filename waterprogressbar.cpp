#include "waterprogressbar.h"
#include <QtMath>
#include <QDebug>

WaterProgressBar::WaterProgressBar(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(800);
    offset = 50;
    connect(timer,&QTimer::timeout,[=](){
        offset += 10;
        if(offset==100)
        {
            offset = 50;
        }
        update();
    });
}

double WaterProgressBar::getValue() const
{
    return value;
}

int WaterProgressBar::getRadius() const
{
    return radius;
}

QColor WaterProgressBar::getWaterColor() const
{
    return waterColor;
}

QColor WaterProgressBar::getBgColor() const
{
    return bgColor;
}

void WaterProgressBar::start()
{
    timer->start();
}

void WaterProgressBar::stop()
{
    timer->stop();
}

void WaterProgressBar::setValue(int m_Value)
{
    value = m_Value;
    repaint();
}

void WaterProgressBar::setRadius(int m_Radius)
{
    radius = m_Radius;
    repaint();
}

void WaterProgressBar::setWaterColor(QColor m_WaterColor)
{
    waterColor = m_WaterColor;
    repaint();
}

void WaterProgressBar::setBgColor(QColor m_BgColor)
{
    bgColor = m_BgColor;
    repaint();
}

void WaterProgressBar::paintEvent(QPaintEvent *event)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    drawBg(&painter);
    drawWater(&painter);
    drawText(&painter);
    QWidget::paintEvent(event);
}

void WaterProgressBar::drawWater(QPainter* painter){
    double sinA = 2.5;
    double sinAlph = 0.1;
    QRect rect(-radius,-radius,2*radius,2*radius);
    int startX = -radius;
    int startY = -radius;
    int endX = radius;
    int endY = radius;
    float height = radius-((value*radius)/50);

    QPainterPath waterPath1;
    waterPath1.moveTo(startX,endY);
    QPainterPath waterPath2;
    waterPath2.moveTo(startX,endY);

    for(int i = startX;i<=endX;i++){
        float y1,y2;

        y1 = sinA*qSin(sinAlph*i+offset)+height;    // y = A * sin(ωx + φ) + k
        y2 = sinA*qSin(sinAlph*i+60+offset)+height;

        if(value == 0){
            y1 = y2 = endY;
        }
        if(value == 100){
            y1 = y2 = -endY;
        }
        waterPath1.lineTo(i,y1);
        waterPath2.lineTo(i,y2);
    }
    waterPath1.lineTo(endX,endY);
    waterPath2.lineTo(endX,endY);

    QPainterPath bigPath;
    bigPath.addEllipse(rect);
    waterPath1 = bigPath.intersected(waterPath1);
    waterPath2 = bigPath.intersected(waterPath2);
    painter->save();
    painter->setPen(Qt::NoPen);
    waterColor.setAlpha(180);
    painter->setBrush(waterColor);
    painter->drawPath(waterPath2);
    waterColor.setAlpha(100);
    painter->setBrush(waterColor);
    painter->drawPath(waterPath1);
    painter->restore();
}

void WaterProgressBar::drawText(QPainter* painter){
    painter->save();
    QString text = QString("%1%").arg(value);
    QFont font = painter->font();
    font.setPixelSize(30);
    painter->setFont(font);
    QPen pen = painter->pen();
    pen.setColor(Qt::white);
    pen.setWidth(4);
    painter->setPen(pen);
    QRect rect(-radius,-radius,radius*2,radius*2);
    painter->drawText(rect,Qt::AlignCenter,text);
    painter->restore();
}

void WaterProgressBar::drawBg(QPainter* painter){
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(bgColor));
    QRect rect(-radius,-radius,radius*2,radius*2);
    painter->drawEllipse(rect);
    painter->restore();
}
