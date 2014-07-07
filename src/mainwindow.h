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

private:
    Ui::MainWindow *                    _ui;
    std::unique_ptr<Application>        _application; ///< The main application
};

#endif // MAINWINDOW_H
