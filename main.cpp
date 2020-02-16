#include <QApplication>
#include "Principalwind.h"
//#include "webEngineTools.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PrincipalWind p(nullptr);
    p.show();
    return app.exec();
}
