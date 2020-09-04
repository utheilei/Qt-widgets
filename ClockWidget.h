#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QTimer>

class ClockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClockWidget(QWidget *parent = nullptr);
    ~ClockWidget() Q_DECL_OVERRIDE;

    void setRadius(int radius);

    void startTime();

    void stopTime();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void drawScale(QPainter *painter);  //绘制表盘刻度
    void drawScaleNum(QPainter *painter);  //绘制表盘刻度值
    void drawPointer(QPainter *painter);   //绘制表盘指针

signals:

public slots:

private:
    int m_radius = 100;
    QTimer *m_time = Q_NULLPTR;
};

#endif // CLOCKWIDGET_H
