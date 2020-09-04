#include "ClockWidget.h"

#include <QPainter>
#include <QTime>
#include <QtMath>

ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent)
{
    m_time = new QTimer(this);

    connect(m_time,&QTimer::timeout,[=](){
        this->update();
    });

    m_time->start(1000);
}

ClockWidget::~ClockWidget()
{
    stopTime();

    if (m_time) {
        delete m_time;
        m_time = Q_NULLPTR;
    }
}

void ClockWidget::setRadius(int radius)
{
    if (m_radius != radius) {
        m_radius = radius;
        update();
    }
}

void ClockWidget::startTime()
{
    if (!m_time->isActive())
        m_time->start(1000);
}

void ClockWidget::stopTime()
{
    if (m_time->isActive())
        m_time->stop();
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPointF pos = QPointF(width() / 2.0, height() / 2.0);
    painter.translate(pos);

    QPainterPath path;
    path.addEllipse(QPoint(0,0),m_radius,m_radius);
    painter.fillPath(path,palette().brush(QPalette::Button));

    painter.save();
    painter.drawEllipse(QPoint(0,0),m_radius,m_radius);
    painter.drawEllipse(QPoint(0,0),m_radius-5,m_radius-5);
    painter.restore();

    drawScale(&painter);
    drawScaleNum(&painter);
    drawPointer(&painter);
}

void ClockWidget::drawScale(QPainter *painter)
{
    painter->save();
    for (int i=1;i<13;i++) {
        QPen pen;
        pen.setWidthF(2);
        painter->setPen(pen);
        painter->drawLine(QPoint(0,-(m_radius-10)),QPoint(0,-(m_radius-20)));
        painter->rotate(30);
    }
    painter->restore();

    painter->save();
    for (int i=1;i<61;i++) {
        painter->drawLine(QPoint(0,-(m_radius-10)),QPoint(0,-(m_radius-16)));
        painter->rotate(6);
    }
    painter->restore();
}

void ClockWidget::drawScaleNum(QPainter *painter)
{
    int starAngle = 30;
    painter->save();
    for (int i=1;i<13;i++) {
        qreal x = (m_radius-30)*qSin(M_PI*starAngle/180);
        qreal y = -(m_radius-30)*qCos(M_PI*starAngle/180);
        qreal textWidth = fontMetrics().width(QString::number(i));
        qreal textHeight = fontMetrics().height();
        int pointX = int(x - textWidth/2);
        int pointY = int(y + textHeight/4);
        painter->drawText(pointX,pointY,QString::number(i));
        starAngle += 30;
    }
    painter->restore();
}

void ClockWidget::drawPointer(QPainter *painter)
{
    QTime time = QTime::currentTime();
    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();
    if (hour > 12)
        hour = hour - 12;

    painter->save();
    painter->setBrush(Qt::black);
    QPolygon hPolygon;
    hPolygon << QPoint(0,0) << QPoint(5,-8) << QPoint(0,-(m_radius/3*2)) << QPoint(-5,-8);
    int angle = hour*30;
    int pAngle = minute/2;
    painter->rotate(angle + pAngle);
    painter->drawConvexPolygon(hPolygon);
    painter->restore();

    painter->save();
    painter->setBrush(Qt::black);
    QPolygon mPolygon;
    mPolygon << QPoint(0,0) << QPoint(5,-8) << QPoint(0,-(m_radius/4*3)) << QPoint(-5,-8);
    int mAngle = minute*6;
    painter->rotate(mAngle);
    painter->drawConvexPolygon(mPolygon);
    painter->restore();

    painter->save();
    painter->setBrush(Qt::red);
    QPolygon sPolygon;
    sPolygon << QPoint(0,0) << QPoint(5,-8) << QPoint(0,-(m_radius-10)) << QPoint(-5,-8);
    int sAngle = second*6;
    painter->rotate(sAngle);
    painter->drawConvexPolygon(sPolygon);
    painter->restore();
}
