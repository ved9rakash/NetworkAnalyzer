#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    //Start the QT Window
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
