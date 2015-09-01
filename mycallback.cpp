#include "mycallback.h"


MyCallback::MyCallback(GLWidget *glwidget_, QObject *parent) :
    Sbs2Callback(parent), glwidget(glwidget_)
{
    verticesData = new DTU::DtuArray2D<double>(64,1028);  // frequency-times-vertices
    colorData = new DTU::DtuArray2D<double>(1028,4);      // rgba values
    normalizedVertexData = new DTU::DtuArray2D<double>(1, 1028);

    (*colorData) = 0;
    (*normalizedVertexData) = 0;


    QObject::connect(sbs2DataHandler,SIGNAL(sourceReconstructionSpectrogramReady()),this,SLOT(sourceReconstructionPowerReady()));



    //QObject::connect(sbs2DataHandler,SIGNAL(sourceReconstructionReady()),this,SLOT(sourceReconstructionReady()));

    //QObject::connect(glwidget,SIGNAL(turnSourceReconstructionPowerOn(int,int,int,int, QString)),this,SLOT(turnSourceReconstructionPowerOn(int,int,int,int, QString)));
    QObject::connect(glwidget,SIGNAL(turnSourceReconstructionPowerOn(int,int,int,int,QString)),this,SLOT(turnOnSourceReconstructionLoreta(int,int,int,int,QString)));
    QObject::connect(glwidget,SIGNAL(changeBand(QString)),this,SLOT(changeBand(QString)));
    QObject::connect(&wordCloud, SIGNAL(wordPairListSignal(QList<QPair<QString, double> >)),
                     glwidget, SLOT(updateWordCloud(QList<QPair<QString, double> >)));


    QObject::connect(this,SIGNAL(deviceFoundSignal(QMap<QString,QVariant>)),glwidget,SLOT(deviceFound(QMap<QString,QVariant>)));
    qsrand(QDateTime::currentMSecsSinceEpoch());
    updateColorMap(3);


    /* This is optional. Remove to work on all brain or add additional regions. */
    //dtuEmotivRegion = new DtuEmotivRegion();
    //dtuEmotivRegion->addRegion("Frontal_Lobe");

    meanWindowLength = 32;
    maxValues = new QVector<double>();
    minValues = new QVector<double>();

    changeBand("alpha");

    int channels2 = 14;
    int sources2 = 1028;
    int sourcesReconstructionDelta2 = 8;

    int numDatosTrain2 = 8;
    int numDatosTest2 = 6;

    collectedSamples = 0;
    int visualized = 1;

    QVector<double> lambdas = QVector<double>(5);

    lambdas[0]=0.01;
    lambdas[1]=0.1;
    lambdas[2]=1;
    lambdas[3]=10;
    lambdas[4]=100;

    //turnOnSourceReconstructioSparse(8, lambdas);

}

void MyCallback::changeBand(QString name)
{
    minValues->clear();
    maxValues->clear();
    if (name.compare("delta"))
    {
    lowFreq = 1;
	highFreq = 4;
    }
    if (name.compare("theta"))
    {
	lowFreq = 4;
	highFreq = 8;
    }
    if (name.compare("alpha"))
    {
	lowFreq = 8;
	highFreq = 12;
    }
    if (name.compare("lowBeta"))
    {
	lowFreq = 12;
	highFreq = 16;
    }
    if (name.compare("beta"))
    {
	lowFreq = 16;
	highFreq = 20;
    }
}


void MyCallback::getData(Sbs2Packet *packet)
{
    thisPacket = packet;
    currentPacketCounter = packet->counter;
    currentPacket += 1;

    glwidget->updateGyroX(packet->gyroX);
    glwidget->updateGyroY(packet->gyroY);

    sbs2DataHandler->setThisPacket(thisPacket);
    //sbs2DataHandler->doSourceReconstruction();
    sbs2DataHandler->doSourceReconstructionSpectrogram();
}


void MyCallback::sourceReconstructionPowerReady()
{
    responseDataMatrix = (sbs2DataHandler->getSourceReconstructionSpectrogramValues());
    normalizeVertexData(sbs2DataHandler->getSourceReconstructionSpectrogramValues(), normalizedVertexData);

    // Compute and update word cloud
    calculateDataForWordCloud();

    // Compute color for surface and update model
    setColorDataFromNormalizedVertexData(normalizedVertexData);
    updateModel();
}

void MyCallback::calculateDataForWordCloud()
{
    // Call directly from sourceReconstructionPowerReady() ?
    // wordCloud.calculatePairs(responseDataMatrix);
    wordCloud.calculatePairsFromResponseVector(normalizedVertexData);
}


void MyCallback::normalizeVertexData(DTU::DtuArray2D<double> *verticesData_,
                                     DTU::DtuArray2D<double> *normalizedVertexData_)
{
    // Min values across a window
    double meanMin = 0;
    for (int t = 0; t < minValues->size(); ++t)
        meanMin += minValues->at(t);
    if (minValues->size())
        meanMin /= (double)minValues->size();

    // Max values across a window
    double meanMax = 0;
    for (int t = 0; t < maxValues->size(); ++t)
        meanMax += maxValues->at(t);
    if (maxValues->size())
        meanMax /= (double)maxValues->size();

    // Current max and min over vertex values for the current sample
    double currentMax = -999999999;
    double currentMin = 9999999999;

    double scaling = meanMax - meanMin;

    // Iterate over vertices
    for (int vertex = 0; vertex < verticesData_->dim2(); ++vertex) {
        double this_vertex_power = 0.0;
        // Iterate over frequencies
        for (int freq = lowFreq; freq < highFreq; ++freq)
            this_vertex_power += (*verticesData_)[freq][vertex];

        // Non-linear scaling
        this_vertex_power = 20 * qLn(this_vertex_power + 1) / qLn(10);

        // Store current
        if (this_vertex_power > currentMax)
            currentMax = this_vertex_power;
        if (this_vertex_power < currentMin)
            currentMin = this_vertex_power;

        // Convert vertex values to one between 0 and 1.
        double v = (this_vertex_power - meanMin) / scaling;
        if (v < 0.5)
            v = 0;
        if (v > 1.0)
            v = 1.0;

        (*normalizedVertexData_)[0][vertex] = v;
    }

    // Store min and max values in the window buffer
    minValues->append(currentMin);
    if (minValues->size() == meanWindowLength)
        minValues->erase(minValues->begin());

    maxValues->append(currentMax);
    if (maxValues->size() == meanWindowLength)
        maxValues->erase(maxValues->begin());
}


void MyCallback::setColorDataFromNormalizedVertexData(DTU::DtuArray2D<double> *normalizedVertexData_)
{
    for (int vertex = 0; vertex < normalizedVertexData_->dim2(); ++vertex) {
        double v = (*normalizedVertexData_)[0][vertex];
        (*colorData)[vertex][0] = 1.0-v;
        (*colorData)[vertex][1] = 1.0-v;
        (*colorData)[vertex][2] = 1.0;
        (*colorData)[vertex][3] = 1.0;
    }
}


void MyCallback::createColorMatrix2(DTU::DtuArray2D<double> *verticesData_)
{
    for (int vertex = 0; vertex<verticesData_->dim2(); ++vertex)
    {
	double v = 0.0;

	if ((*verticesData_)[0][vertex] > 0) v = 1.0;

	(*colorData)[vertex][0] = 1.0-v;
	(*colorData)[vertex][1] = 1.0-v;
	(*colorData)[vertex][2] = 1.0;
	(*colorData)[vertex][3] = 1.0;
    }

}


/**
  This function sees 64x1028 input matrix and write so the 1028x3 colorData matrix ready
  for visualization.
  */
void MyCallback::createColorMatrix(DTU::DtuArray2D<double> *verticesData_)
{
    // Min values across a window
    double meanMin = 0;
    for (int t = 0; t < minValues->size(); ++t)
        meanMin += minValues->at(t);
    if (minValues->size())
        meanMin /= (double)minValues->size();

    // Max values across a window
    double meanMax = 0;
    for (int t = 0; t < maxValues->size(); ++t)
        meanMax += maxValues->at(t);
    if (maxValues->size())
        meanMax /= (double)maxValues->size();

    // Current max and min over vertex values for the current sample
    double currentMax = -999999999;
    double currentMin = 9999999999;

    double scaling = meanMax - meanMin;

    // Iterate over vertices
    for (int vertex = 0; vertex < verticesData_->dim2(); ++vertex) {
        double this_vertex_power = 0.0;
        // Iterate over frequencies
        for (int freq = lowFreq; freq < highFreq; ++freq)
            this_vertex_power += (*verticesData_)[freq][vertex];

        // Non-linear scaling
        this_vertex_power = 20 * qLn(this_vertex_power + 1) / qLn(10);

        // Store current
        if (this_vertex_power > currentMax)
            currentMax = this_vertex_power;
        if (this_vertex_power < currentMin)
            currentMin = this_vertex_power;

        // Convert vertex values to one between 0 and 1.
        double v = (this_vertex_power - meanMin) / scaling;
        if (v < 0.5)
            v = 0;
        if (v > 1.0)
            v = 1.0;

        // Set vertex color from scaled vertex value
        (*colorData)[vertex][0] = 1.0 - v;
        (*colorData)[vertex][1] = 1.0 - v;
        (*colorData)[vertex][2] = 1.0;
        (*colorData)[vertex][3] = 1.0;
    }

    // Store min and max values in the window buffer
    minValues->append(currentMin);
    if (minValues->size() == meanWindowLength)
        minValues->erase(minValues->begin());

    maxValues->append(currentMax);
    if (maxValues->size() == meanWindowLength)
        maxValues->erase(maxValues->begin());
}


void MyCallback::updateModel()
{
    for (int vertex = 0; vertex < colorData->dim1(); ++vertex)
    {
	glwidget->updateColorForVertex(vertex,(*colorData)[vertex][0],(*colorData)[vertex][1],(*colorData)[vertex][2], (*colorData)[vertex][3]);
    }
    visualized = 1;
}

void MyCallback::updateColorMap(int colorMap)
{

    qDebug() << "updating color map "<<colorMap;

    QString filename(":/colortable");
    filename.append(QString::number(colorMap));

    QFile file2(filename);

    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
	qDebug() <<"file problem";

    int i=0;
    cmap.clear();
    while (!file2.atEnd())
    {
	QByteArray line = file2.readLine();
	QString str = line.data();
	QStringList list1 = str.split(",");
	for (int j = 0; j < list1.size(); j++)
	{
	    cmap.push_back(list1.at(j).toDouble());
	}
	++i;
    }
}
