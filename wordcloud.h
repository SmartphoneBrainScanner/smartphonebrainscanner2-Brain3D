#ifndef WORDCLOUD_H
#define WORDCLOUD_H

#include <sbs2callback.h>
#include <sbs2datahandler.h>
#include <glwidget.h>
#include <algorithm>

class Wordcloud
{
public:
    void initializewordcloud();
    void calculatePairs(DTU::DtuArray2D<double>* responsematrix_ );

private:
    QStringList wordList;
    DTU::DtuArray2D<double>* weightMatrix;
    QList<QPair<QString, double> > wordValuePairs;
    DTU::DtuArray2D<double>* responseVector;
    DTU::DtuArray2D<double>* responseWeightValues;

    void loadWordList();
    void loadWordMatrix();
    void initializePairs();
    //bool myfunction(const QPair<QString, double> &a, const QPair<QString, double> &b);
    //struct QPairSecondComparer;

signals:

public slots:
};

template<typename T1, typename T2>
bool sorter(const QPair<T1,T2> & a, const QPair<T1,T2> & b)
{
    return a.second > b.second;
}

#endif // WORDCLOUD_H
