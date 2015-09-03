#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>

class QSlider;

class LCDRange : public QWidget
{
    Q_OBJECT

    public:
    LCDRange( QWidget* = 0 );

    public slots:
    void setValue( int );

    signals:
    void valueChanged( int );

    private:
    QSlider* slider;
};

#endif

