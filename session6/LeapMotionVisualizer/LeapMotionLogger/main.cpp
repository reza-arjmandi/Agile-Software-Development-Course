#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

#include "LeapMotionDataAcquisitor.h"
#include "Viewer3DDataModel.h"
#include "HandExtractor.h"

static QObject* LeapMotionDataAcquisitorProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
static QObject* Viewer3DDataModelProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

LeapMotionDataAcquisitor *leapMotionDataAcquisitor;
Viewer3DDataModel *viewer3DDataModel;

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    auto handExtractor = std::make_unique<HandExtractor>();
    leapMotionDataAcquisitor = new LeapMotionDataAcquisitor(std::move(handExtractor));
    viewer3DDataModel = new Viewer3DDataModel();

    leapMotionDataAcquisitor->HandsDetectEvent += [](const std::vector<Point>& pointClouds){
        viewer3DDataModel->SetPointClouds(pointClouds);
    };

    qmlRegisterSingletonType<LeapMotionDataAcquisitor>("LeapMotion.DataAcquisitor", 1, 0, "LeapMotionDataAcquisitor", LeapMotionDataAcquisitorProvider);
    qmlRegisterSingletonType<Viewer3DDataModel>("Viewer3D.DataModel", 1, 0, "Viewer3DDataModel", Viewer3DDataModelProvider);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

static QObject* LeapMotionDataAcquisitorProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return leapMotionDataAcquisitor;
}

static QObject* Viewer3DDataModelProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return viewer3DDataModel;
}
