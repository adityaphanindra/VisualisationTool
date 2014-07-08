#include "PlotInterface.h"

//-----------------------------------------------------Constructors
PlotInterface::PlotInterface() :
    _currentHandle(-1),
    _plotType(PlotType::SCATTER),
    _orientationEnabled(false),
    _graphNumber(-1)
{
    customPlot = std::unique_ptr<QCustomPlot>(new QCustomPlot());
}

//-----------------------------------------------------Public Functions
uint PlotInterface::plotTrajectory(std::shared_ptr<Trajectory> trajectory) {
    //std::unique_ptr<QCustomPlot> customPlot = std::unique_ptr<QCustomPlot>(new QCustomPlot());

    if(!customPlot) {
        customPlot = std::unique_ptr<QCustomPlot>(new QCustomPlot());
    }

    _graphNumber++;
    const uint numPoints = trajectory->size();
    if(numPoints < 2)
        return -1;
    QVector<double> x(numPoints), y(numPoints);
    double maxX = 100, maxY = 100, minX = -100, minY = -100;
    for(uint index = 0; index < trajectory->size(); index++) {
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

    double orientation_begin = trajectory->pointAt(0).orientation;
    double orientation_end = trajectory->pointAt(numPoints - 1).orientation;

    customPlot->addGraph();
    customPlot->graph(_graphNumber)->setData(x, y);
    if(_plotType == PlotType::SCATTER) {
        customPlot->graph(_graphNumber)->setLineStyle(QCPGraph::LineStyle::lsNone);
        customPlot->graph(_graphNumber)->setScatterStyle(QCPScatterStyle( QCPScatterStyle::ScatterShape::ssCircle, 5));
    }
    else if(_plotType == PlotType::LINE) {
        customPlot->graph(_graphNumber)->setLineStyle(QCPGraph::LineStyle::lsLine);
        customPlot->graph(_graphNumber)->setScatterStyle(QCPScatterStyle( QCPScatterStyle::ScatterShape::ssCircle, 1));
        customPlot->graph(_graphNumber)->setBrush(Qt::NoBrush);
    }

    if(_orientationEnabled) {
        QCPItemLine *arrow = new QCPItemLine(customPlot.get());
        customPlot->addItem(arrow);
        arrow->setPen(QPen(QColor(0, 255, 0)));
        arrow->start->setCoords(x[0], y[0]);
        arrow->end->setCoords(x[0] + 50 * cos(orientation_begin), y[0] + 50 * sin(orientation_begin));
        arrow->setHead(QCPLineEnding::esSpikeArrow);

        QCPItemLine *arrow2 = new QCPItemLine(customPlot.get());
        customPlot->addItem(arrow2);
        arrow2->setPen(QPen(QColor(255, 0, 0)));
        arrow2->start->setCoords(x[trajectory->size() - 1], y[trajectory->size() - 1]);
        arrow2->end->setCoords(x[trajectory->size() - 1] + 50 * cos(orientation_end), y[trajectory->size() - 1] + 50 * sin(orientation_end));
        arrow2->setHead(QCPLineEnding::esSpikeArrow);
    }
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
    //_plots.push_back(std::move(customPlot));
    _currentHandle++;
    return _currentHandle;
}

void PlotInterface::clearAll() {
    //_plots.clear();
    customPlot->clearGraphs();
    customPlot->replot();
    _graphNumber = -1;
}

void PlotInterface::setPlotType(PlotType plotType) {
    _plotType = plotType;
}

void PlotInterface::enableOrientation(bool enable) {
    _orientationEnabled = enable;
}

//-----------------------------------------------------Public Slots
void PlotInterface::plotClicked(QMouseEvent * event) {
    if(event->button() == Qt::RightButton)   {

        if(customPlot) {
            double x = customPlot->xAxis->pixelToCoord(event->x());
            double y = customPlot->yAxis->pixelToCoord(event->y());
            std::cout << "PlotInterface::plotClicked():" << x << "\t" << y << std::endl;
            emit pointClicked(0, Point2d(x, y, 0));
        }
    }
}
