#ifndef CANNONFIELD_H
#define CANNONFIELD_H

#include <QWidget>

class QTimer;

class CannonField : public QWidget
{
    Q_OBJECT

    public:
    CannonField( QWidget* = 0 );

    bool gameOver() const;
    bool isShooting() const;
    QSize sizeHint() const;

    public slots:
    void setAngle( int );
    void setForce( int );
    void shoot();
    void newTarget();
    void setGameOver();
    void restartGame();

    private slots:
    void moveShot();

    signals:
    void hit();
    void missed();
    void angleChanged( int );
    void forceChanged( int );
    void canShoot( bool );

    protected:
    void paintEvent( QPaintEvent* );
    void mousePressEvent( QMouseEvent* );
    void mouseMoveEvent( QMouseEvent* );
    void mouseReleaseEvent( QMouseEvent* );

    private:
    void paintCannon( QPainter& );
    void paintShot( QPainter& );
    void paintTarget( QPainter& );
    void paintBarrier( QPainter& );
    QRect cannonRect() const;
    QRect shotRect() const;
    QRect targetRect() const;
    QRect barrierRect() const;

    bool barrelHit( const QPoint& ) const;

    int currentAngle;
    int currentForce;

    int timerCount;
    QTimer* autoShootTimer;
    float shotAngle;
    float shotForce;

    QPoint target;

    bool gameEnded;
    bool barrelPressed;
};

#endif

