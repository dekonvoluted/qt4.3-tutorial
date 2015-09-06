#include <QPainter>
#include <QTimer>
#include <cmath>

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
    if ( autoShootTimer->isActive() ) return;

    timerCount = 0;
    shotAngle = currentAngle;
    shotForce = currentForce;

    autoShootTimer->start( 5 );
}

void CannonField::moveShot()
{
    QRegion oldRegion = shotRect();
    timerCount++;
    QRect newRegion = shotRect();

    if ( newRegion.x() > this->width() or newRegion.y() > this->height() ) {
        autoShootTimer->stop();
    } else {
        oldRegion = oldRegion.unite( newRegion );
    }

    update( oldRegion );
}

void CannonField::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );

    paintCannon( painter );
    if ( autoShootTimer->isActive() ) paintShot( painter );
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

