#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>

#include <mycallback.h>
#include <mainwindow.h>

#include <hardware/emocap/sbs2emocapdatareader.h>
#include <hardware/emotiv/sbs2emotivdatareader.h>


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    qDebug() << "rootAppPath: "<<Sbs2Common::setDefaultRootAppPath();

    MainWindow mw;
    mw.setAttribute(Qt::WA_QuitOnClose);

    MyCallback* myCallback = new MyCallback(mw.glwidget);
    Sbs2EmotivDataReader* sbs2DataReader = Sbs2EmotivDataReader::New(myCallback);


    QObject::connect(app.data(),SIGNAL(aboutToQuit()),mw.glwidget,SLOT(quit()));
    QObject::connect(app.data(), SIGNAL(aboutToQuit()), sbs2DataReader, SLOT(aboutToQuit()));


    return app->exec();
}
