#include "BCI.h"

#define MIN (-50)
#define MAX 50


#define INCR 0.005


#define FIRST 0
#define SECOND std::advance(it, 1)
#define THIRD std::advance(it, 2)
#define FOURTH std::advance(it, 3)


#define MACRO FIRST



BCI::BCI(const char name[], double dur) : duration(dur) {
    double time=0;
    Point p;
    std::string str;
    std::ifstream file;
    file.open(name);
    std::getline(file, str); // Move to next line


    if (!file.is_open())
        std::cout << "Error" << std::endl;
    int i=0;

    while(!file.eof()) {
        str ="";
        file >> str;
        i++;
        if(i == MACRO+1) {
            if( *(str.begin())=='\n' )
                str.erase(str.begin());
            p.y = std::stof(str);
            eeg.push_back(p);
        }
        if(i==4)
            i=0;


    }

    if ( ( (eeg.end()->x)==0 && (eeg.end()->y)==0 ) )
        eeg.pop_back(); eeg.pop_back();

    time = INCR;
    i=1;

    for(std::list<Point>::iterator it=eeg.begin(); it!=eeg.end(); it++) {
        it->x = time;
        i++;
        time = time + INCR;
        }

    file.close();
    }






std::vector<double> BCI::FFT() {
    arma::vec data(eeg.size()); int n=0;
    for (std::list<Point>::iterator it=eeg.begin(); it!=eeg.end(); it++) {
        data(n) = it->y;
        n++;
    }
    std::vector<double> out;
    arma::cx_vec fft_res = arma::fft(data);

    for (int i=0; i < n; i++)
        out.push_back(std::abs(fft_res(i)));

    return out;
}











void BCI::DrawChart(const QString& xtext,  const QString& ytext, QLineSeries *series,QChart* chart, QChartView* chartView) {
    QT_CHARTS_USE_NAMESPACE
    std::list<Point> &l=eeg;
    std::list<Point>::iterator it=eeg.begin();
    for(MACRO; it!=eeg.end(); std::advance(it,4))
        *series << QPointF(it->x, it->y);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(0, duration);
    chart->axes(Qt::Vertical).back()->setRange(MIN, MAX);
    chart->axes(Qt::Horizontal).back()->setTitleText(xtext);
    chart->axes(Qt::Vertical).back()->setTitleText(ytext);
    chart->setTitle("Before");
    chartView->setRenderHint(QPainter::Antialiasing);

}






void BCI::DrawChart(const std::vector<double>& vec, const QString& xtext,  const QString& ytext, QLineSeries *series,QChart* chart, QChartView* chartView) {
    QT_CHARTS_USE_NAMESPACE
    int n=vec.size();
    for(int i=0; i<n; i++)
        *series << QPointF(i, vec[i]);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    //chart->axes(Qt::Horizontal).back()->setRange(0, Interface.duration);
    chart->axes(Qt::Vertical).back()->setRange(MIN, round(*std::max_element(vec.begin(), vec.end())) );
    chart->axes(Qt::Horizontal).back()->setTitleText(xtext);
    chart->axes(Qt::Vertical).back()->setTitleText(ytext);
    chart->setTitle("After");
    chartView->setRenderHint(QPainter::Antialiasing);


}

