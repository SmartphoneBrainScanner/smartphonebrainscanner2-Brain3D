#ifndef WORDCLOUD_H
#define WORDCLOUD_H

#include <QObject>
#include <sbs2callback.h>
#include <sbs2datahandler.h>
#include <glwidget.h>

class wordcloud : public QObject
{
    Q_OBJECT
public:
    void Wordcloud();
    void calculatePairs(DTU::DtuArray2D<double>* responsematrix_ );

private:
    QString wordList;
    DTU::DtuArray2D<double>* weightMatrix;
    QPair<QString, double> wordValuePairs;
    DTU::DtuArray2D<double>* responsevector;

    void loadWordList();
    void loadWordMatrix();
    void initializePairs();


signals:

public slots:
};

#endif // WORDCLOUD_H
