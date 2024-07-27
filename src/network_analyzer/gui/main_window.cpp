#include "main_window.h"
#include "ui_main_window.h"
#include "analysis_engine.h"

#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    analyzer(new NetworkAnalyzer(this)),
    chart(new QtCharts::QChart()),
    series(new QtCharts::QLineSeries()),
    timeCounter(0) {

    ui->setupUi(this);

    // Setup charts
    chart->addSeries(series);
    chart->createDefaultAxes();
    ui->chartView->setChart(chart);

    // Listing available interfaces
    std::vector<std::string> interfaceList = NetworkAnalyzer::listInterfaces();
    QStringList interfaces;
    for (const auto& iface : interfaceList) {
        interfaces.append(QString::fromStdString(iface));
    }
    ui->interfaceComboBox->addItems(interfaces);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startCapture);
    connect(analyzer, &NetworkAnalyzer::packetCaptured, this, &MainWindow::addPacketInfo);
}

void MainWindow::addPacketInfo(const QString& info) {
    ui->textEdit->append(info);
    QStringList parts = info.split(" ");
    if (parts.size() >= 3) {
        bool ok;
        int bytes = parts[2].toInt(&ok);
        if (ok) {
            updateGraph(bytes);
        }
    }
}

void MainWindow::startCapture() {
    QString selectedInterface = ui->interfaceComboBox->currentText();
    try {
        analyzer->setInterface(selectedInterface.toStdString());
        analyzer->start();
        ui->statusLabel->setText("Capturing on: " + selectedInterface);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::updateGraph(int bytes) {
    series->append(timeCounter++, bytes);
    chart->axisX()->setRange(0, timeCounter);
    auto yAxis = qobject_cast<QtCharts::QValueAxis*>(chart->axisY());
    if (yAxis) {
        yAxis->setRange(0, std::max(yAxis->max(), static_cast<qreal>(bytes)));
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
