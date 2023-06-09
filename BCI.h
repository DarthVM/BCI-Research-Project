#ifndef RESEARCH_BCI_H
#define RESEARCH_BCI_H

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <iomanip>


#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QMainWindow>
#include <QApplication>

#include <armadillo>


QT_CHARTS_USE_NAMESPACE


struct Point {
    double x=0;
    double y=0;
};


class BCI {
private:
    std::list<Point> eeg;
    double duration;
public:
    BCI(const char [], double);
    std::vector<double> FFT();
    void DrawChart(const QString&,  const QString&, QLineSeries*,QChart*, QChartView*);
    void DrawChart(const std::vector<double>&,const QString&,  const QString&, QLineSeries*,QChart*, QChartView*);
};

#endif //RESEARCH_BCI_H
