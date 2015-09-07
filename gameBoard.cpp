#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

#include "cannonField.h"
#include "gameBoard.h"
#include "lcdRange.h"

GameBoard::GameBoard( QWidget* parent ) : QWidget( parent )
{
    QPushButton* quit = new QPushButton( "&Quit", this );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );

    LCDRange* angle = new LCDRange( "Angle" );
    angle->setRange( 5, 70 );

    LCDRange* force = new LCDRange( "Force" );
    force->setRange( 10, 50 );

    QFrame* cannonBox = new QFrame;
    cannonBox->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );

    cannonField = new CannonField;

    connect( angle, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setAngle( int ) ) );
    connect( cannonField, SIGNAL( angleChanged( int ) ), angle, SLOT( setValue( int ) ) );

    connect( force, SIGNAL( valueChanged( int ) ), cannonField, SLOT( setForce( int ) ) );
    connect( cannonField, SIGNAL( forceChanged( int ) ), force, SLOT( setValue( int ) ) );

    connect( cannonField, SIGNAL( hit() ), this, SLOT( hit() ) );
    connect( cannonField, SIGNAL( missed() ), this, SLOT( missed() ) );

    QPushButton* shoot = new QPushButton( "&Shoot", this );
    shoot->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( shoot, SIGNAL( clicked() ), this, SLOT( fire() ) );
    connect( cannonField, SIGNAL( canShoot( bool ) ), shoot, SLOT( setEnabled( bool ) ) );

    QPushButton* restart = new QPushButton( "&New Game" );
    restart->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( restart, SIGNAL( clicked() ), this, SLOT( newGame() ) );

    hits = new QLCDNumber( 2 );
    hits->setSegmentStyle( QLCDNumber::Filled );

    shotsLeft = new QLCDNumber( 2 );
    shotsLeft->setSegmentStyle( QLCDNumber::Filled );

    QLabel* hitsLabel = new QLabel( "Hits" );
    QLabel* shotsLeftLabel = new QLabel( "Shots Left" );

    new QShortcut( Qt::Key_Enter, this, SLOT( fire() ) );
    new QShortcut( Qt::Key_Return, this, SLOT( fire() ) );
    new QShortcut( Qt::CTRL + Qt::Key_Q, this, SLOT( close() ) );

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget( shoot );
    topLayout->addWidget( hits );
    topLayout->addWidget( hitsLabel );
    topLayout->addWidget( shotsLeft );
    topLayout->addWidget( shotsLeftLabel );
    topLayout->addStretch( 1 );
    topLayout->addWidget( restart );

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addWidget( angle );
    leftLayout->addWidget( force );

    QVBoxLayout* cannonLayout = new QVBoxLayout;
    cannonLayout->addWidget( cannonField );
    cannonBox->setLayout( cannonLayout );

    QGridLayout* layout = new QGridLayout( this );
    layout->addWidget( quit, 0, 0 );
    layout->addLayout( topLayout, 0, 1 );
    layout->addLayout( leftLayout, 1, 0 );
    layout->addWidget( cannonBox, 1, 1, 2, 1 );
    layout->setColumnStretch( 1, 10 );
    this->setLayout( layout );

    angle->setValue( 60 );
    force->setValue( 25 );

    angle->setFocus();

    newGame();
}

void GameBoard::fire()
{
    if ( cannonField->gameOver() or cannonField->isShooting() ) return;

    shotsLeft->display( shotsLeft->intValue() - 1 );
    cannonField->shoot();
}

void GameBoard::hit()
{
    hits->display( hits->intValue() + 1 );
    if ( shotsLeft->intValue() == 0 ) {
        cannonField->setGameOver();
    } else {
        cannonField->newTarget();
    }
}

void GameBoard::missed()
{
    if ( shotsLeft->intValue() == 0 ) cannonField->setGameOver();
}

void GameBoard::newGame()
{
    shotsLeft->display( 15 );
    hits->display( 0 );
    cannonField->restartGame();
    cannonField->newTarget();
}

