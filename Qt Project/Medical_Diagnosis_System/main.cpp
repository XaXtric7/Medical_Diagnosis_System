#include <QtWidgets/QApplication>
#include "DiagnosisWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DiagnosisWidget mainWidget;
    mainWidget.show();

    return app.exec();
}
