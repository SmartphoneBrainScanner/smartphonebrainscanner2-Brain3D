#include "wordcloud.h"

void wordcloud::initializewordcloud()
{
    loadWordList();
    initializePairs();
    loadWordMatrix();
    qDebug() << "initialization success!";
}

void wordcloud::loadWordList()
{
    //Load the words in a list of strings:
    QFile file(Sbs2Common::getRootAppPath() + QString("Annotator_words.csv"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "There was an error loading file Annotator_words.csv";
    }

    while (!file.atEnd()) {
        QString wordLine = file.readLine();
        //wordList will contain all words possible in the wordcloud
        wordList = wordLine.split(",");
    }
                qDebug() << "wordlist load! with size " << wordList.size();
}

void wordcloud::loadWordMatrix()
{
    //Load the vertex-weight-matrix:
    QFile file1(Sbs2Common::getRootAppPath() + QString("Annotator_matrix.csv"));
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "There was an error loading file Annotator_matrix.csv";
    }

    int row = 0;
    while (!file1.atEnd()) {
        QString weightLine = file1.readLine();
        QStringList weightList = weightLine.split(",");
    //qDebug() << weightList.size(); //1032
    //qDebug() << (weightList[0]).toDouble();

    //weightMatrix = new DTU::DtuArray2D<double>(1028,weightList.size()-1);
    weightMatrix = new DTU::DtuArray2D<double>(5000,5000);
        for (int col = 0; col < weightList.size()-1; col++)
        {
            (*weightMatrix)[row][col] = (weightList[col]).toDouble();
        }
        //qDebug() << row;
        row++;
    }
qDebug() << "wordmatrix load!";
}

void wordcloud::initializePairs()
{
    for (int i = 0; i < wordList.size(); i++)
    {
        wordValuePairs.append(qMakePair(wordList[i],0));
    }
qDebug() << "pairs initialized";
}


void wordcloud::calculatePairs(DTU::DtuArray2D<double>* responsematrix_ )
{
    responsevector = new DTU::DtuArray2D<double>(1,responsematrix_->dim2());

    //Getting a single response-vector from the response matrix.
    for (int i=0; i<responsematrix_->dim2(); i++)
    {
        double sum=0;
        for (int j=0; j<responsematrix_->dim1(); j++)
        {
           sum += (*responsematrix_)[j][i];
        }
        (*responsevector)[0][i] = sum;

    }
    qDebug() << "pairs are calculated";

    // get responsevector, multiply with weightmatrix, enter values into pairs, sort pairs.

    //sorting:
    /*std::sort(v.begin(), v.end(), [](const QPair<QString,double> &left, const sQPair<QString,double> &right) {
        return left.second < right.second;
    });*/
}














