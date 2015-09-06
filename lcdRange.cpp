#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>

#include "lcdRange.h"

LCDRange::LCDRange( const QLabel& title, QWidget* parent ) : QWidget( parent )
{
    label = new QLabel( title.text() + ": " );

    QSpinBox* lcd = new QSpinBox( this );
    lcd->setRange( 0, 99 );

    slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 0, 99 );
    slider->setValue( 0 );

    connect( slider, SIGNAL( valueChanged( int ) ), lcd, SLOT( setValue( int ) ) );
    connect( lcd, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
    connect( slider, SIGNAL( valueChanged( int ) ), this, SIGNAL( valueChanged( int ) ) );

    QGridLayout* layout = new QGridLayout( this );
    layout->addWidget( label, 0, 0 );
    layout->addWidget( lcd, 0, 1 );
    layout->addWidget( slider, 1, 0, 1, 2 );
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

