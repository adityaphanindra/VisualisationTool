#include "PlotInterface.h"

PlotInterface::PlotInterface() :
    _currentHandle(-1)
{
}

uint PlotInterface::plotTrajectory(std::shared_ptr<Trajectory> trajectory)
{
    std::unique_ptr<QCustomPlot> customPlot = std::unique_ptr<QCustomPlot>(new QCustomPlot());
    const uint numPoints = trajectory->size();
    QVector<double> x(numPoints), y(numPoints);
    double maxX = 100, maxY = 100, minX = -100, minY = -100;
    for(uint index = 0; index < trajectory->size(); index++)
    {
        Point2d point = trajectory->pointAt(index);
        x[index] = point.x;
        y[index] = point.y;

        if(x[index] > maxX)
            maxX = x[index];
        else if(x[index] < minX)
            minX = x[index];
        if(y[index] > maxY)
            maxY = y[index];
        else if(y[index] < minY)
            minY = y[index];
    }
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle( QCPScatterStyle::ScatterShape::ssCircle, 5));
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(minX - 100, maxX + 100);
    customPlot->yAxis->setRange(minY - 100, maxY + 100);
    customPlot->resize(600, 600);

    customPlot->show();
    customPlot->replot();
    _plots.push_back(std::move(customPlot));
    _currentHandle++;
    return _currentHandle;
}

void PlotInterface::clearAll()
{
    _plots.clear();
}
