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
    std::unique_ptr<Application>         _application; ///< The main application

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_seqNumSpinBox_valueChanged(int newValue);

    void on_plotTrajectoryButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
