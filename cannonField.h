#ifndef CANNONFIELD_H
#define CANNONFIELD_H

#include <QWidget>

class QTimer;

class CannonField : public QWidget
{
    Q_OBJECT

    public:
    CannonField( QWidget* = 0 );

    public slots:
    void setAngle( int );
    void setForce( int );
    void shoot();
    void newTarget();

    private slots:
    void moveShot();

    signals:
    void hit();
    void missed();
    void angleChanged( int );
    void forceChanged( int );

    protected:
    void paintEvent( QPaintEvent* );

    private:
    void paintShot( QPainter& );
    void paintTarget( QPainter& );
    void paintCannon( QPainter& );
    QRect cannonRect() const;
    QRect shotRect() const;
    QRect targetRect() const;

    int currentAngle;
    int currentForce;

    int timerCount;
    QTimer* autoShootTimer;
    float shotAngle;
    float shotForce;

    QPoint target;
};

#endif

