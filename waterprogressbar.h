#ifndef WATERPROGRESSBAR_H
#define WATERPROGRESSBAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

class WaterProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int radius READ getRadius WRITE setRadius)
    Q_PROPERTY(QColor waterColor READ getWaterColor WRITE setWaterColor)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
public:
    explicit WaterProgressBar(QWidget *parent = nullptr);

    double getValue() const;
    int getRadius() const;
    QColor getWaterColor() const;
    QColor getBgColor() const;
    void start();
    void stop();

signals:

public Q_SLOTS:
    void setValue(int m_Value);
    void setRadius(int m_Radius);
    void setWaterColor(QColor m_WaterColor);
    void setBgColor(QColor m_BgColor);

protected:
    virtual void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void drawWater(QPainter *);
    void drawText(QPainter *);
    void drawBg(QPainter *);

private:
    double value;
    int radius;
    int offset;
    QColor waterColor;
    QColor bgColor;
    QTimer *timer;
};

#endif // WATERPROGRESSBAR_H
