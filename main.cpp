#include <QApplication>

#include "myWidget.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    MyWidget widget;
    widget.setGeometry( 100, 100, 500, 355 );
    widget.show();

    return app.exec();
}

