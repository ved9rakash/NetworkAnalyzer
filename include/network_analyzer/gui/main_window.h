#pragma once

#include "analysis_engine.h"

#include <QMainWindow>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addPacketInfo(const QString& info, int bytes, bool isOutGoing);
    void startCapture();
    void stopCapture();
    void updateGraph(int bytes, bool isOutGoing);

private:
    Ui::MainWindow *ui;
    NetworkAnalyzer *analyzer;
    QtCharts::QChart *chart;
    // QtCharts::QLineSeries *series;
    QtCharts::QLineSeries *incomingSeries;
    QtCharts::QLineSeries *outgoingSeries;
    int timeCounter;
};
