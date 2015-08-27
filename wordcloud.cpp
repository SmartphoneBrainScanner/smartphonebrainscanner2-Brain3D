#include "wordcloud.h"

void wordcloud::Wordcloud()
{
    //loadWordList();
    //initializePairs();
    //loadWordMatrix();
    qDebug() << "wordcloud init success"
}

void wordcloud::loadWordList()
{
    //Load the words in a list of strings:
    QFile file(Sbs2Common::getRootAppPath() + QString("Annotator_words.csv"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDebug() << "There was an error loading file Annotator_words.csv";
    }

    while (!file.atEnd()) {
        QString wordLine = in.readLine();
        //wordList will contain all words possible in the wordcloud
        wordList = wordLine.split(",");
    }
}

void wordcloud::loadWordMatrix()
{
    //Load the vertex-weight-matrix:
    QFile file(Sbs2Common::getRootAppPath() + QString("Annotator_matrix.csv"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDebug() << "There was an error loading file Annotator_matrix.csv";
    }

    int row = 0;
    while (!file.atEnd()) {
        QString weightLine = in.readLine();
        QString weightList = weightLine.split(",");

        for (int col = 0; col < size(weightList); col++)
        {
            *weightMatrix[row][col] = (weightList[col]).toDouble();
        }
        row++;
    }

}

void wordcloud::initializePairs()
{
    for (int i = 0; i < size(wordList); i++)
    {
        (wordValuePairs[i]).first = wordList[i];
    }
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
           sum += *responsematrix_[j][i];
        }
        *responsevector[0][i] = sum;
        qDebug() << sum;
    }



    // get responsevector, multiply with weightmatrix, enter values into pairs, sort pairs.

    //sorting:
    std::sort(v.begin(), v.end(), [](const QPair<QString,double> &left, const sQPair<QString,double> &right) {
        return left.second < right.second;
    });
}














