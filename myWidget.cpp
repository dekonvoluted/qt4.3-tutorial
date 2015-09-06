#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "cannonField.h"
#include "lcdRange.h"
#include "myWidget.h"

MyWidget::MyWidget( QWidget* parent ) : QWidget( parent )
{
    QPushButton* quit = new QPushButton( "Quit", this );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );

    LCDRange* angle = new LCDRange;
    angle->setRange( 5, 70 );

    LCDRange* force = new LCDRange;
    force->setRange( 10, 50 );

    CannonField* cannonField = new CannonField;

    connect( angle, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setAngle( int ) ) );
    connect( cannonField, SIGNAL( angleChanged( int ) ), angle, SLOT( setValue( int ) ) );

    connect( force, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setForce( int ) ) );
    connect( cannonField, SIGNAL( forceChanged( int ) ), force, SLOT( setValue( int ) ) );

    QGridLayout* layout = new QGridLayout( this );
    layout->addWidget( quit, 0, 0 );
    layout->addWidget( angle, 1, 0 );
    layout->addWidget( force, 2, 0 );
    layout->addWidget( cannonField, 0, 1, 3, 1 );
    layout->setColumnStretch( 1, 10 );
    this->setLayout( layout );

    angle->setValue( 60 );
    force->setValue( 25 );

    angle->setFocus();
}

