#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>

class QLabel;
class QSlider;
class QString;

class LCDRange : public QWidget
{
    Q_OBJECT

    public:
    LCDRange( const QString&, QWidget* = 0 );

    public slots:
    void setValue( int );
    void setRange( int, int );

    signals:
    void valueChanged( int );

    private:
    QLabel* label;
    QSlider* slider;
};

#endif

