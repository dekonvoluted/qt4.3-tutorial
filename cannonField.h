#ifndef CANNONFIELD_H
#define CANNONFIELD_H

#include <QWidget>

class CannonField : public QWidget
{
    Q_OBJECT

    public:
    CannonField( QWidget* = 0 );

    public slots:
    void setAngle( int );

    signals:
    void angleChanged( int );

    protected:
    void paintEvent( QPaintEvent* );

    private:
    int currentAngle;
};

#endif

