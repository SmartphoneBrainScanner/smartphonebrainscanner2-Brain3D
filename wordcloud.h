#ifndef WORDCLOUD_H
#define WORDCLOUD_H

#include <QObject>
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
    bool myfunction(const QPair<QString, double> &a, const QPair<QString, double> &b);


signals:

public slots:
};

#endif // WORDCLOUD_H
