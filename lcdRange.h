#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>

class QLabel;
class QSlider;

class LCDRange : public QWidget
{
    Q_OBJECT

    public:
    LCDRange( const QLabel&, QWidget* = 0 );

    public slots:
    void setValue( int );
    void setRange( int, int );

    signals:
    void valueChanged( int );

    private:
    QSlider* slider;
    QLabel* label;
};

#endif

