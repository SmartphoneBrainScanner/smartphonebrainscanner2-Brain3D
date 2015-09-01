#include "wordcloud.h"

Wordcloud::Wordcloud(QObject *)
{
    // loadWordList();
    loadWordMatrix();
    initializePairs();

    responseWeightValues = new DTU::DtuArray2D<double>(1, weightMatrix->dim2());
    (*responseWeightValues) = 0;

    qDebug() << "Wordcloud::Wordcloud: initialization success!";
}


void Wordcloud::loadWordMatrix()
{
    // Load the vertex-word-matrix:
    QFile file(Sbs2Common::getRootAppPath() + QString("functional_annotator_neurosynth.csv"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Wordcloud::loadWordMatrix: "
                    "There was an error loading file functional_annotator_neurosynth.csv";

    // Read words from first line
    QString wordLine = file.readLine();
    wordList = wordLine.split(",");

    // Read numerical data from the rest of the file.
    weightMatrix = new DTU::DtuArray2D<double>(1028, wordList.size());
    int row = 0;
    while (!file.atEnd()) {
        // Read line with numerical data
        QString weightLine = file.readLine();
        QStringList weightList = weightLine.split(",");

        // Setup row in matrix
        for (int col = 0; col < weightList.size(); col++)
            (*weightMatrix)[row][col] = weightList[col].toDouble();

        row++;
    }
    qDebug() << "Wordcloud::loadWordMatrix: wordmatrix load!";
}


void Wordcloud::initializePairs()
{
    for (int i = 0; i < wordList.size(); i++)
        wordValuePairs.append(qMakePair(wordList.at(i), 0));

    qDebug() << "Wordcloud::initializePairs: wordcloud pairs initialized";
}


void Wordcloud::calculatePairsFromResponseVector(DTU::DtuArray2D<double> *responseVector_)
{
    responseVector_->multiply(weightMatrix, 1, responseWeightValues);

    // Iterating over words
    for (int i=0; i < wordValuePairs.size(); i++)
        wordValuePairs[i].second = (*responseWeightValues)[0][i];

    // Copy and sorting
    sortedWordValuePairs = wordValuePairs;
    std::sort(sortedWordValuePairs.begin(), sortedWordValuePairs.end(), sorter<QString, double>);

    emit wordPairListSignal(sortedWordValuePairs);
}


void Wordcloud::calculatePairs(DTU::DtuArray2D<double>* responseMatrix_ )
{
    responseVector = new DTU::DtuArray2D<double>(1, responseMatrix_->dim2());

    // Getting a single response-vector from the response matrix.
    int lowFreq = 8;
    int highFreq = 12;
    for (int i = 0; i < responseMatrix_->dim2(); i++) {
        double sum = 0;
        for (int freq = lowFreq; freq < highFreq; ++freq)
           sum += (*responseMatrix_)[freq][i];

        (*responseVector)[0][i] = sum;
    }

    calculatePairsFromResponseVector(responseVector);
}


