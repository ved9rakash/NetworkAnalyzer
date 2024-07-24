#include <QApplication>
#include "main_window.h"
#include "analysis_engine.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    NetworkAnalyzer analyzer("eth0");  // Change to your network interface
    analyzer.start();

    return app.exec();
}
