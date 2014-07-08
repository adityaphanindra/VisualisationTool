#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "Settings.h"
#include "Application.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void displayXY(uint plotId, float x, float y);

private slots:
    void on_seqNumSpinBox_valueChanged(int newValue);
    void on_plotTrajectoryButton_clicked();
    void on_clearPlotsButton_clicked();
    void on_scatterPlotRadioButton_clicked();

    void on_linePlotRadioButton_clicked();

    void on_orientationCheckBox_clicked(bool checked);

    void on_fixedSourceCheckBox_clicked(bool checked);

    void on_fixedTargetCheckBox_clicked(bool checked);

signals:
    void plotTypeChanged(PlotType);
    void orientationEnabled(bool);
    void fixedTargetSelected(bool);
    void fixedSourceSelected(bool);

private:
    Ui::MainWindow *                    _ui;
    std::unique_ptr<Application>        _application; ///< The main application
};

#endif // MAINWINDOW_H
