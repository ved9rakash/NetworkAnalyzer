#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addPacketInfo(const QString& info);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
