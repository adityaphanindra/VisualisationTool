#include "PlotInterface.h"

//-----------------------------------------------------Constructors
PlotInterface::PlotInterface() :
    _currentHandle(-1)
{
}

//-----------------------------------------------------Public Functions
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
    customPlot->setInteraction( QCP::Interaction::iRangeZoom, true);
    customPlot->setInteraction( QCP::Interaction::iRangeDrag, true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(minX - 100, maxX + 100);
    customPlot->yAxis->setRange(minY - 100, maxY + 100);
    customPlot->resize(600, 600);

    QObject::connect(customPlot.get(), SIGNAL(mousePress(QMouseEvent *)), this, SLOT(plotClicked(QMouseEvent *)));
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

//-----------------------------------------------------Public Slots
void PlotInterface::plotClicked(QMouseEvent * event)
{
    if(event->button() == Qt::RightButton)
    {
        if(_plots[0])
        {
            double x = _plots[0]->xAxis->pixelToCoord(event->x());
            double y = _plots[0]->yAxis->pixelToCoord(event->y());
            std::cout << x << "\t" << y << std::endl;
            emit pointClicked(0, Point2d(x, y, 0));
        }
    }
}
