#include <QPainter>

#include "cannonField.h"

CannonField::CannonField( QWidget* parent ) : QWidget( parent )
{
    currentAngle = 45;
    currentForce = 0;
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

void CannonField::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );
    painter.setPen( Qt::NoPen );
    painter.setBrush( Qt::blue );

    painter.translate( 0, this->height() );
    painter.drawPie( QRect( -35, -35, 70, 70 ), 0, 90 * 16 );

    painter.rotate( -currentAngle );
    painter.drawRect( QRect( 30, -5, 20, 10) );
}

QRect CannonField::cannonRect() const
{
    QRect result( 0, 0, 50, 50 );
    result.moveBottomLeft( this->rect().bottomLeft() );
    return result;
}

