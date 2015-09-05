#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>

#include "lcdRange.h"

LCDRange::LCDRange( QWidget* parent ) : QWidget( parent )
{
    QLCDNumber* lcd = new QLCDNumber( 2, this );
    lcd->setSegmentStyle( QLCDNumber::Filled );

    slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 0, 99 );
    slider->setValue( 0 );

    connect( slider, SIGNAL( valueChanged( int ) ), lcd, SLOT( display( int ) ) );
    connect( slider, SIGNAL( valueChanged( int ) ), this, SIGNAL( valueChanged( int ) ) );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( lcd );
    layout->addWidget( slider );
    this->setLayout( layout );

    this->setFocusProxy( slider );
}

void LCDRange::setValue( int value )
{
    slider->setValue( value );
}

void LCDRange::setRange( int minValue, int maxValue )
{
    if ( minValue < 0 or maxValue > 99 or minValue > maxValue ) {
        qWarning( "LCDRange::setRange( %d, %d )\n"
                    "\tRange must be 0..99\n"
                    "\tand minValue must not be greater than maxValue",
                    minValue, maxValue );
        return;
    }

    slider->setRange( minValue, maxValue );
}

