#include <QApplication>

#include <mycallback.h>
#include <mainwindow.h>

#include <hardware/emocap/sbs2emocapdatareader.h>
#include <hardware/filereader/sbs2filedatareader.h>
#include <hardware/emotiv/sbs2emotivdatareader.h>


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "rootAppPath: "<<Sbs2Common::setDefaultRootAppPath();

    QCommandLineParser parser;
    QCommandLineOption dataFilePath("datafile","File to read instead of device", "filepath");
    parser.addOption(dataFilePath);
    parser.addHelpOption();
    parser.process(app);

    MainWindow mw;
    mw.setAttribute(Qt::WA_QuitOnClose);

    MyCallback* myCallback = new MyCallback(mw.glwidget);
    Sbs2DataReader* sbs2DataReader = nullptr;
    if (!parser.isSet(dataFilePath))
    {
        sbs2DataReader = Sbs2EmotivDataReader::New(myCallback);
    }
    else
    {
        sbs2DataReader = new Sbs2FileDataReader(myCallback,parser.value(dataFilePath));
    }


    QObject::connect(&app,SIGNAL(aboutToQuit()),mw.glwidget,SLOT(quit()));
    QObject::connect(&app,SIGNAL(aboutToQuit()),sbs2DataReader,SLOT(aboutToQuit()));


    return app.exec();
}
