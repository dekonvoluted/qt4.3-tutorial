#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

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

    CannonField* cannonField = new CannonField;

    connect( angle, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setAngle( int ) ) );
    connect( cannonField, SIGNAL( angleChanged( int ) ), angle, SLOT( setValue( int ) ) );

    QGridLayout* layout = new QGridLayout( this );
    layout->addWidget( quit, 0, 0 );
    layout->addWidget( angle, 1, 0 );
    layout->addWidget( cannonField, 1, 1, 2, 1 );
    layout->setColumnStretch( 1, 10 );
    this->setLayout( layout );

    angle->setValue( 60 );
    angle->setFocus();
}

