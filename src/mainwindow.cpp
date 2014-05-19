#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _application(std::unique_ptr<Application>(new Application())),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _application->initialiseSubjects(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_seqNumSpinBox_valueChanged(int sequenceNumber)
{
    uint targetNumber = static_cast<uint>(_application->getTargetNumber(ui->subjectNumSpinBox->value(), sequenceNumber));
    ui->targetNumSpinBox->setValue(targetNumber);
}

void MainWindow::on_plotTrajectoryButton_clicked()
{
    _application->plotTrajectory(ui->subjectNumSpinBox->value(), ui->seqNumSpinBox->value());
}
