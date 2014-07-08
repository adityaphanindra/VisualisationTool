#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------------------------Constructors
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _application(std::unique_ptr<Application>(new Application()))
{
    _ui->setupUi(this);
    _application->initialiseSubjects(false);
    QObject::connect(_application.get(), SIGNAL(pointClicked(uint, float, float)), this, SLOT(displayXY(uint, float, float)));
    QObject::connect(this, SIGNAL(plotTypeChanged(PlotType)), _application.get(), SLOT(changePlotType(PlotType)));
    QObject::connect(this, SIGNAL(orientationEnabled(bool)), _application.get(), SLOT(enableOrientation(bool)));
    QObject::connect(this, SIGNAL(fixedSourceSelected(bool)), _application.get(), SLOT(fixSource(bool)));
    QObject::connect(this, SIGNAL(fixedTargetSelected(bool)), _application.get(), SLOT(fixTarget(bool)));
}

MainWindow::~MainWindow() {
    delete _ui;
}

//-------------------------------Public slots
void MainWindow::displayXY(uint, float x, float y) {
    _ui->xEdit->setText(QString(StringFunc::numToString(x).c_str()));
    _ui->yEdit->setText(QString(StringFunc::numToString(y).c_str()));
}

//-------------------------------Private slots
void MainWindow::on_seqNumSpinBox_valueChanged(int sequenceNumber) {
    uint targetNumber = static_cast<uint>(_application->getTargetNumber(_ui->subjectNumSpinBox->value(), sequenceNumber));
    _ui->targetNumSpinBox->setValue(targetNumber);
}

void MainWindow::on_plotTrajectoryButton_clicked() {
    _application->plotTrajectory(_ui->subjectNumSpinBox->value(), _ui->seqNumSpinBox->value());
}

void MainWindow::on_clearPlotsButton_clicked() {
    _application->clearAllPlots();
}

void MainWindow::on_scatterPlotRadioButton_clicked()
{
    emit plotTypeChanged(PlotType::SCATTER);
}

void MainWindow::on_linePlotRadioButton_clicked()
{
    emit plotTypeChanged(PlotType::LINE);
}

void MainWindow::on_orientationCheckBox_clicked(bool checked)
{
    emit orientationEnabled(checked);
}

void MainWindow::on_fixedSourceCheckBox_clicked(bool checked)
{
    emit fixedSourceSelected(checked);
}

void MainWindow::on_fixedTargetCheckBox_clicked(bool checked)
{
    emit fixedTargetSelected(checked);
}
