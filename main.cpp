#include <QApplication>
#include "fenetre.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    fenetre aze;
    aze.show();

    return app.exec();
}
