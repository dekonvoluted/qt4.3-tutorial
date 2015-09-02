#include <QApplication>
#include <QPushButton>
#include <QFont>

#include "mywidget.h"

MyWidget::MyWidget( QWidget* parent ) : QWidget( parent )
{
    setFixedSize( 200, 120 );

    QPushButton* quit = new QPushButton( "Quit", this );
    quit->setGeometry( 62, 40, 75, 30 );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );
}

