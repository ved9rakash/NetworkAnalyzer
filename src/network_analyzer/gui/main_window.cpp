#include "main_window.h"

#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::addPacketInfo(const QString& info) {
    ui->textEdit->append(info);
}

MainWindow::~MainWindow() {
    delete ui;
}
