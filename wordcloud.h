#ifndef WORDCLOUD_H
#define WORDCLOUD_H

#include <sbs2callback.h>
#include <sbs2datahandler.h>
#include <glwidget.h>
#include <algorithm>

class Wordcloud : public QObject
{
    Q_OBJECT
public:
    explicit Wordcloud(QObject *parent = 0);
    void calculatePairs(DTU::DtuArray2D<double>* responsematrix_ );

private:
    QStringList wordList;
    DTU::DtuArray2D<double>* weightMatrix;
    QList<QPair<QString, double> > wordValuePairs;
    QList<QPair<QString, double> > sortedWordValuePairs;
    DTU::DtuArray2D<double>* responseVector;
    DTU::DtuArray2D<double>* responseWeightValues;

    void loadWordMatrix();
    void initializePairs();

signals:
    void wordPairListSignal(QList<QPair<QString, double> > wordValuePairs_);

public slots:
};

template<typename T1, typename T2>
bool sorter(const QPair<T1,T2> & a, const QPair<T1,T2> & b)
{
    return a.second > b.second;
}

#endif // WORDCLOUD_H
