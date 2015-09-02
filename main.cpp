#include <QApplication>
#include <QFont>
#include <QFontMetrics>
#include <QPushButton>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    QPushButton quit( "Quit" );
    quit.setFont( QFont( "Times", 18, QFont::Bold ) );

    // Resize button to exactly bound the text
    quit.resize( QFontMetrics( QFont( "Times", 18, QFont::Bold ) ).size( Qt::TextSingleLine, "Quit" ) );

    QObject::connect( &quit, SIGNAL( clicked() ), &app, SLOT( quit() ) );

    quit.show();
    return app.exec();
}

