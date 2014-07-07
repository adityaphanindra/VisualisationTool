#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------------------------Constructors
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _application(std::unique_ptr<Application>(new Application())),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _application->initialiseSubjects(false);
    QObject::connect(_application.get(), SIGNAL(pointClicked(uint, float, float)), this, SLOT(displayXY(uint, float, float)));

}

MainWindow::~MainWindow() {
    delete _ui;
}

//-------------------------------Public slots
void MainWindow::displayXY(uint plotId, float x, float y) {
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
