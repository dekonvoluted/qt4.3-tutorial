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
    void setForce( int );

    signals:
    void angleChanged( int );
    void forceChanged( int );

    protected:
    void paintEvent( QPaintEvent* );

    private:
    QRect cannonRect() const;

    int currentAngle;
    int currentForce;
};

#endif

