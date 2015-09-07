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

    LCDRange* angle = new LCDRange( "Angle" );
    angle->setRange( 5, 70 );

    LCDRange* force = new LCDRange( "Force" );
    force->setRange( 10, 50 );

    CannonField* cannonField = new CannonField;

    connect( angle, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setAngle( int ) ) );
    connect( cannonField, SIGNAL( angleChanged( int ) ), angle, SLOT( setValue( int ) ) );

    connect( force, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setForce( int ) ) );
    connect( cannonField, SIGNAL( forceChanged( int ) ), force, SLOT( setValue( int ) ) );

    QPushButton* shoot = new QPushButton( "Shoot", this );
    shoot->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( shoot, SIGNAL( clicked() ), cannonField, SLOT( shoot() ) );

    connect( cannonField, SIGNAL( hit() ), cannonField, SLOT( newTarget() ) );

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget( shoot );
    topLayout->addStretch( 1 );


    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addWidget( angle );
    leftLayout->addWidget( force );

    QGridLayout* layout = new QGridLayout( this );
    layout->addWidget( quit, 0, 0 );
    layout->addLayout( topLayout, 0, 1 );
    layout->addLayout( leftLayout, 1, 0 );
    layout->addWidget( cannonField, 1, 1, 2, 1 );
    layout->setColumnStretch( 1, 10 );
    this->setLayout( layout );

    angle->setValue( 60 );
    force->setValue( 25 );

    angle->setFocus();
}

