#include "wordcloud.h"

void Wordcloud::initializewordcloud()
{
    loadWordList();
    initializePairs();
    loadWordMatrix();
    qDebug() << "initialization success!";
}

void Wordcloud::loadWordList()
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

void Wordcloud::loadWordMatrix()
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
    //qDebug() << weightList.size(); //1031
    //qDebug() << (weightList[0]).toDouble();

    //weightMatrix = new DTU::DtuArray2D<double>(1028,weightList.size()-1);
    weightMatrix = new DTU::DtuArray2D<double>(1028,weightList.size());
        for (int col = 0; col < weightList.size(); col++)
        {
            (*weightMatrix)[row][col] = (weightList[col]).toDouble();
        }
        //qDebug() << row;
        row++;
    }
qDebug() << "wordmatrix load!";
}

void Wordcloud::initializePairs()
{
    for (int i = 0; i < wordList.size(); i++)
    {
        wordValuePairs.append(qMakePair(wordList[i],0));
    }
qDebug() << "pairs initialized";
}


void Wordcloud::calculatePairs(DTU::DtuArray2D<double>* responseMatrix_ )
{
    responseVector = new DTU::DtuArray2D<double>(1,responseMatrix_->dim2());

    //Getting a single response-vector from the response matrix.
    for (int i=0; i<responseMatrix_->dim2(); i++)
    {
        double sum=0;
        for (int j=0; j<responseMatrix_->dim1(); j++)
        {
           sum += (*responseMatrix_)[j][i];
        }
        (*responseVector)[0][i] = sum;

    }

    responseWeightValues = new DTU::DtuArray2D<double>(1,weightMatrix->dim2());
    responseVector->multiply(weightMatrix, 1, responseWeightValues);

    for (int i=0; i<wordValuePairs.size(); i++)
    {
        wordValuePairs[i].second = (*responseWeightValues)[0][i];

    }

    //sorting:
    std::sort(wordValuePairs.begin(), wordValuePairs.end(), myfunction);
}

/*struct wordcloud::QPairSecondComparer
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b)
    {
        return a.second < b.second;
    }
} sorting;*/

bool Wordcloud::myfunction (const QPair<QString, double> &a, const QPair<QString, double> &b) { return a.second < b.second; }








