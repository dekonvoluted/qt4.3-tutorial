#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <cmath>
#include <cstdlib>

#include "cannonField.h"

CannonField::CannonField( QWidget* parent ) : QWidget( parent )
{
    currentAngle = 45;
    currentForce = 0;

    timerCount = 0;
    autoShootTimer = new QTimer( this );

    connect( autoShootTimer, SIGNAL( timeout() ), this, SLOT( moveShot() ) );

    shotAngle = 0.0;
    shotForce = 0.0;

    this->setPalette( QPalette( QColor( 250, 250, 200 ) ) );
    this->setAutoFillBackground( true );

    target = QPoint( 0, 0 );
    gameEnded = false;

    barrelPressed = false;

    newTarget();
}

bool CannonField::gameOver() const
{
    return gameEnded;
}

bool CannonField::isShooting() const
{
    return autoShootTimer->isActive();
}

QSize CannonField::sizeHint() const
{
    return QSize( 400, 300 );
}

void CannonField::setAngle( int angle )
{
    if ( currentAngle == angle ) return;

    if ( angle < 5 ) angle = 5;
    if ( angle > 70 ) angle = 70;

    currentAngle = angle;
    this->update( cannonRect() );
    emit angleChanged( currentAngle );
}

void CannonField::setForce( int force )
{
    if ( currentForce == force ) return;

    if ( force < 0 ) force = 0;

    currentForce = force;
    emit forceChanged( currentForce );
}

void CannonField::shoot()
{
    if ( isShooting() ) return;

    timerCount = 0;
    shotAngle = currentAngle;
    shotForce = currentForce;

    autoShootTimer->start( 5 );

    emit canShoot( false );
}

void CannonField::newTarget()
{
    static bool firstTime = true;

    if ( firstTime ) {
        firstTime = false;
        QTime midnight( 0, 0, 0 );
        qsrand( midnight.secsTo( QTime::currentTime() ) );
    }

    target = QPoint( 200 + qrand() % 190, 10 + qrand() % 255 );
    update();
}

void CannonField::setGameOver()
{
    if ( gameEnded ) return;

    if ( isShooting() ) autoShootTimer->stop();
    gameEnded = true;
    update();
}

void CannonField::restartGame()
{
    if ( isShooting() ) autoShootTimer->stop();
    gameEnded = false;
    update();
    emit canShoot( true );
}

void CannonField::moveShot()
{
    QRegion oldRegion = shotRect();
    timerCount++;
    QRect newRegion = shotRect();

    if ( newRegion.intersects( targetRect() ) ) {
        autoShootTimer->stop();
        emit hit();
        emit canShoot( true );
    } else if ( newRegion.x() > this->width() or newRegion.y() > this->height() or newRegion.intersects( barrierRect() ) ) {
        autoShootTimer->stop();
        emit missed();
        emit canShoot( true );
    } else {
        oldRegion = oldRegion.united( newRegion );
    }

    update( oldRegion );
}

void CannonField::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );

    if ( gameEnded ) {
        painter.setPen( Qt::black );
        painter.setFont( QFont( "Courier", 48, QFont::Bold ) );
        painter.drawText( this->rect(), Qt::AlignCenter, "Game Over" );
    }

    paintCannon( painter );
    paintBarrier( painter );
    if ( isShooting() ) paintShot( painter );
    if ( not gameEnded ) paintTarget( painter );
}

void CannonField::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton ) return;

    if ( barrelHit( event->pos() ) ) barrelPressed = true;
}

void CannonField::mouseMoveEvent( QMouseEvent* event )
{
    if ( not barrelPressed ) return;

    QPoint pos = event->pos();
    if ( pos.x() <= 0 ) pos.setX( 1 );
    if ( pos.y() >= this->height() ) pos.setY( this->height() - 1 );

    double rad = atan( ( ( double ) this->rect().bottom() - pos.y() ) / pos.x() );
    setAngle( qRound( rad * 180 / M_PI ) );
}

void CannonField::mouseReleaseEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton ) barrelPressed = false;
}

const QRect barrelRect( 30, -5, 20, 10 );

void CannonField::paintCannon( QPainter& painter )
{
    painter.setPen( Qt::NoPen );
    painter.setBrush( Qt::blue );

    painter.save();
    painter.translate( 0, this->height() );
    painter.drawPie( QRect( -35, -35, 70, 70 ), 0, 90 * 16 );

    painter.rotate( -currentAngle );
    painter.drawRect( barrelRect );
    painter.restore();
}

void CannonField::paintShot( QPainter& painter )
{
    painter.setPen( Qt::NoPen );
    painter.setBrush( Qt::black );
    painter.drawRect( shotRect() );
}

void CannonField::paintTarget( QPainter& painter )
{
    painter.setPen( Qt::black );
    painter.setBrush( Qt::red );
    painter.drawRect( targetRect() );
}

void CannonField::paintBarrier( QPainter& painter )
{
    painter.setPen( Qt::black );
    painter.setBrush( Qt::yellow );
    painter.drawRect( barrierRect() );
}

QRect CannonField::cannonRect() const
{
    QRect result( 0, 0, 50, 50 );
    result.moveBottomLeft( this->rect().bottomLeft() );
    return result;
}

QRect CannonField::shotRect() const
{
    const double gravity = 4;

    double time = timerCount / 20.0;
    double velocity = shotForce;
    double radians = shotAngle * M_PI / 180;

    double velx = velocity * cos( radians );
    double vely = velocity * sin( radians );

    double x0 = ( barrelRect.right() + 5 ) * cos( radians );
    double y0 = ( barrelRect.right() + 5 ) * sin( radians );

    double x = x0 + velx * time;
    double y = y0 + vely * time - 0.5 * gravity * time * time;

    QRect result( 0, 0, 6, 6 );
    result.moveCenter( QPoint( qRound( x ), height() - 1 - qRound( y ) ) );
    return result;
}

QRect CannonField::targetRect() const
{
    QRect result( 0, 0, 20, 10 );
    result.moveCenter( QPoint( target.x(), height() - 1 - target.y() ) );
    return result;
}

QRect CannonField::barrierRect() const
{
    return QRect( 145, height() - 100, 15, 99 );
}

bool CannonField::barrelHit( const QPoint& point ) const
{
    QMatrix matrix;
    matrix.translate( 0, height() );
    matrix.rotate( -currentAngle );
    matrix = matrix.inverted();
    return barrelRect.contains( matrix.map( point ) );
}

