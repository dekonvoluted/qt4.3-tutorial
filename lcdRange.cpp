#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>

#include "lcdRange.h"

LCDRange::LCDRange( QWidget* parent ) : QWidget( parent )
{
    QLCDNumber* lcd = new QLCDNumber( 2, this );
    lcd->setSegmentStyle( QLCDNumber::Filled );

    QSlider* slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 0, 99 );
    slider->setValue( 0 );

    connect( slider, SIGNAL( valueChanged( int ) ), lcd, SLOT( display( int ) ) );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( lcd );
    layout->addWidget( slider );
    this->setLayout( layout );
}

