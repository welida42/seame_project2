#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include "speedometer.h"
//#include <wiringPiSPI.h>
#include <unistd.h>

//static const int CHANNEL = 1;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<Speedometer>("com.ulasdikme.speedometer",1,0,"Speedometer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *object = engine.rootObjects()[0];
    QObject *speedometer = object->findChild<QObject*>("speedoMeter");

    Speedometer *ptrSpeedometer = qobject_cast<Speedometer*>(speedometer);
    //Speedometer *ptrSpeedometer = dynamic_cast<Speedometer*>(speedometer);

    qreal val = 0;
    ptrSpeedometer->setSpeed(val);

    bool direction = true;
    QTimer timer;

    // analog value from ltc2400
//    float volt = 0;

    QObject::connect(&timer, &QTimer::timeout, [&]()
    {


       // val = volt;

        if(val < 5001)
                ptrSpeedometer->setOuterColor(QColor(128,255,0));
        else if(val > 5000 && val < 7501)
                ptrSpeedometer->setOuterColor(QColor(255,255,0));
        else if(val > 7500)
                ptrSpeedometer->setOuterColor(QColor(255,0,0));

//        if(abs(volt-val) <=10)
//            val = volt;
//        else if(volt > val)
//            val = val + 10;
//        else if( volt < val)
//            val = val - 10;

        if(val >= ptrSpeedometer->getHighestRange())
            direction = false;
        else if(val <= 0.1)
            direction = true;

        if(direction)
            val = val + 10;
        else
            val = val - 10;

        ptrSpeedometer->setSpeed(val);

    }
    );


//    unsigned char buffer[100];
//    wiringPiSPISetup(CHANNEL, 1000000);

//    long int ltw = 0;

//    QTimer timer2;

//    QObject::connect(&timer2,&QTimer::timeout, [&]()
//    {

//        wiringPiSPIDataRW(CHANNEL, buffer, 4);

//       // bool sig;
//        ltw = 0;

//        //f((buffer[0]&0x20)==0) sig = 1;
//                buffer[0] &= 0x1F;
//                ltw |= buffer[0];
//                ltw <<= 8;
//                ltw |= buffer[1];
//                ltw <<= 8;
//                ltw |= buffer[2];
//                ltw <<= 8;
//                ltw |= buffer[3];

//                //if(sig) ltw |= 0xf0000000;
//                ltw = ltw/16;
//                volt = ltw*4000.1 / 16777216;
//             //   qDebug()<<(unsigned int)volt;

//    });

   // usleep(180000);


//    timer2.start(180);
    //TODO: pretend first timer to update the data before start the seond timer

//    QProgressBar progressBar;
//    progressBar.setMinimum(0);
//    progressBar.setMaximum(100);
//    // or as alternative to the two above, you could call
//    // progressBar.setRange(0,100);

//    for( int i = 0; i <100; ++i ) {
//        progressBar.setValue(i);
//    }

    timer.start(10);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
