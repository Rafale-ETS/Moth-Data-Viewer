#include "modelview.h"

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QQuaternion>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QPlaneMesh>

#include <QDebug>

ModelView::ModelView(QWidget *parent)
   : QWidget(parent)
{
    /*
    QTextStream(stdout) << "std out \n";
    qDebug("debug");
    qInfo("info");
    qWarning("warning");
    qCritical("critical");
    */

    auto view = new Qt3DExtras::Qt3DWindow();

    // create a container for Qt3DWindow
    container = createWindowContainer(view,this);

    // background color
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x575757)));

    // Root entity
    auto rootEntity = new Qt3DCore::QEntity();

    // Camera
    auto cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(55.0f, 16.0f/9.0f, 0.1f, 1000.0f);

    cameraEntity->setPosition(QVector3D(-2.0f, 0.65f, -0.4f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    //Moth mesh
    Qt3DRender::QMesh *mothMesh = new Qt3DRender::QMesh();
    mothMesh->setSource(QUrl("qrc:models/HullUnit"));

    // Moth Mesh Transform
    auto meshTransform = new Qt3DCore::QTransform();
    meshTransform->setScale(1.0f);
    meshTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    meshTransform->setRotation(QQuaternion(1,0,0,0).normalized());

    auto meshMaterial = new Qt3DExtras::QPhongMaterial();
    meshMaterial->setDiffuse(QColor(QRgb(0x55AA88)));

    // assamble entity
    auto meshEntity = new Qt3DCore::QEntity(rootEntity);
    meshEntity->addComponent(mothMesh);
    meshEntity->addComponent(meshMaterial);
    meshEntity->addComponent(meshTransform);

    //WaterPlane Mesh
    // Plane shape data
    Qt3DExtras::QPlaneMesh *waterPlaneMesh = new Qt3DExtras::QPlaneMesh();
    waterPlaneMesh->setWidth(1);
    waterPlaneMesh->setHeight(1);

    // Plane mesh transform
    Qt3DCore::QTransform *waterPlaneTransform = new Qt3DCore::QTransform();
    waterPlaneTransform->setScale(100.0f);
    waterPlaneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 0.0f));
    waterPlaneTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QPhongAlphaMaterial *waterPlaneMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    waterPlaneMaterial->setDiffuse(QColor(QRgb(0x4466DD)));
    waterPlaneMaterial->setAlpha(0.7f);

    // Plane
    auto waterPlaneEntity = new Qt3DCore::QEntity(rootEntity);
    waterPlaneEntity->addComponent(waterPlaneMesh);
    waterPlaneEntity->addComponent(waterPlaneMaterial);
    waterPlaneEntity->addComponent(waterPlaneTransform);
/*
    //skyPlane Mesh
    // Plane shape data
    Qt3DExtras::QPlaneMesh *skyPlaneMesh = new Qt3DExtras::QPlaneMesh();
    skyPlaneMesh->setWidth(1);
    skyPlaneMesh->setHeight(1);

    // Plane mesh transform
    Qt3DCore::QTransform *skyPlaneTransform = new Qt3DCore::QTransform();
    skyPlaneTransform->setScale(500.0f);
    skyPlaneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 0.0f));
    skyPlaneTransform->setTranslation(QVector3D(0.0f, 10.0f, 0.0f));

    Qt3DExtras::QPhongMaterial *skyPlaneMaterial = new Qt3DExtras::QPhongMaterial();
    skyPlaneMaterial->setDiffuse(QColor(QRgb(0xAAAAFF)));

    // Plane
    auto skyPlaneEntity = new Qt3DCore::QEntity(rootEntity);
    skyPlaneEntity->addComponent(skyPlaneMesh);
    skyPlaneEntity->addComponent(skyPlaneMaterial);
    skyPlaneEntity->addComponent(skyPlaneTransform);
*/
    // Set root object of the scene
    view->setRootEntity(rootEntity);
}

void
ModelView::resizeView(QSize size)
{
    container->resize(size);
}

void
ModelView::resizeEvent ( QResizeEvent * /*event*/ )
{
  resizeView(this->size());
}
