///
/// \file PlotInterface.h
/// \brief Acts as an between QCustomPlot and Core Classes
/// \author PISUPATI Phanindra
/// \date 20.04.2014
///
///
///
#ifndef PLOTINTERFACE_H
#define PLOTINTERFACE_H

#include "Trajectory.h"
#include "qcustomplot.h"

#include <memory>
#include <QObject>

class PlotInterface : public QObject
{
Q_OBJECT
private:
    int                                                 _currentHandle;
    std::vector<std::unique_ptr<QCustomPlot> >          _plots;
public:
    PlotInterface();
    uint plotTrajectory(std::shared_ptr<Trajectory> trajectory);
    void clearAll();
signals:
    void pointClicked(uint, Point2d);
public slots:
    void plotClicked(QMouseEvent *event);
};

#endif // PLOTINTERFACE_H
