#include "BCI.h"

#define TIME 3

#define WIDTH 1280
#define HEIGHT 720



int main(int argc, char** argv) {

    BCI bci("C:/Users/xdoyo/Desktop/JetBrains/CLion/Research/EEG.txt", TIME);

    QApplication app(argc, argv);
    QLineSeries *series = new QLineSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);

    bci.DrawChart("T (Seconds)", "Amplitude (uV)" ,series, chart, chartView);


    QMainWindow window;
    window.resize(WIDTH, HEIGHT);
    window.setCentralWidget(chartView);
    window.show();

    QLineSeries *series2 = new QLineSeries();
    QChart *chart2 = new QChart();
    QChartView *chartView2 = new QChartView(chart2);

    bci.DrawChart(bci.FFT(),"Frequency (Hz)", "Power Spectral Density (uV ^ 2)", series2, chart2, chartView2);
    QMainWindow window2;
    window2.resize(WIDTH, HEIGHT);
    window2.setCentralWidget(chartView2);
    window2.show();
    app.exec();
}
