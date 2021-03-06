#ifndef MYECALLBACK_H
#define MYECALLBACK_H

#include <sbs2callback.h>
#include <sbs2datahandler.h>
#include <glwidget.h>
#include <QDateTime>

class MyCallback : public Sbs2Callback
{
    Q_OBJECT
public:
    explicit MyCallback(GLWidget* glwidget_, QObject *parent = 0);
    void getData(Sbs2Packet *packet);


private:
    DTU::DtuArray2D<double>* verticesData;
    GLWidget* glwidget;
    DTU::DtuArray2D<double>* colorData;

    int lowFreq; //included
    int highFreq; //excluded
    int visualized;
    int collectedSamples;

    QVector<double>* maxValues;
    QVector<double>* minValues;
    double meanPower;
    int meanWindowLength;
    QVector<double> cmap;

private:
    void createColorMatrix(DTU::DtuArray2D<double>* verticesData_);
    void updateModel();
    void createColorMatrix2(DTU::DtuArray2D<double> *verticesData_);

signals:
    
public slots:
    void sourceReconstructionPowerReady();
    void changeBand(QString name);
    void updateColorMap(int colorMap);
    
};

#endif // MYCALLBACK_H
