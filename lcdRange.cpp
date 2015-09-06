#include <QLCDNumber>
#include <QLabel>
#include <QSlider>
#include <QString>
#include <QVBoxLayout>

#include "lcdRange.h"

LCDRange::LCDRange( const QString& text, QWidget* parent ) : QWidget( parent )
{
    label = new QLabel( text );
    label->setAlignment( Qt::AlignCenter | Qt::AlignTop );

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
    layout->addWidget( label );
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

