#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "lcdRange.h"
#include "myWidget.h"

MyWidget::MyWidget( QWidget* parent ) : QWidget( parent )
{
    QPushButton* quit = new QPushButton( "Quit", this );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );

    QGridLayout* grid = new QGridLayout;
    LCDRange* previousRange = 0;

    for ( int row = 0; row < 3; ++row ) {
        for ( int col = 0; col < 3; ++col ) {
            LCDRange* lcdRange = new LCDRange( this );
            grid->addWidget( lcdRange, row, col );

            if ( previousRange ) {
                connect( lcdRange, SIGNAL( valueChanged( int ) ), previousRange, SLOT( setValue( int ) ) );
            }
            previousRange = lcdRange;
        }
    }

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( quit );
    layout->addLayout( grid );
    this->setLayout( layout );
}

