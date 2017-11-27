#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QRenderAspect>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

#include <QGuiApplication>
#include <QPropertyAnimation>

#include "qt3dwindow.h"
#include "OrbitTransformController.h"
#include "qorbitcameracontroller.h"

Qt3DCore::QEntity* createScene()
{
	// Root entity
	Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity;

	// Torus
	Qt3DCore::QEntity* torusEntity = new Qt3DCore::QEntity(rootEntity);
	Qt3DExtras::QTorusMesh* torusMesh = new Qt3DExtras::QTorusMesh;
	torusMesh->setRadius(5);
	torusMesh->setMinorRadius(1);
	torusMesh->setRings(6);
	torusMesh->setSlices(3);

	Qt3DCore::QTransform* torusTransform = new Qt3DCore::QTransform;
	torusTransform->setScale3D(QVector3D(1.5, 1, 0.5));
	torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

	Qt3DExtras::QPhongMaterial* torusMaterial = new Qt3DExtras::QPhongMaterial(rootEntity);
	torusMaterial->setDiffuse(QColor(QRgb(0x00ff00)));

	torusEntity->addComponent(torusMesh);
	torusEntity->addComponent(torusTransform);
	torusEntity->addComponent(torusMaterial);

	// Sphere
	Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(rootEntity);
	Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh;
	sphereMesh->setRadius(3);
	sphereMesh->setRings(2);
	sphereMesh->setSlices(4);

	Qt3DCore::QTransform* sphereTransform = new Qt3DCore::QTransform;
	OrbitTransformController* controller = new OrbitTransformController(sphereTransform);
	controller->setTarget(sphereTransform);
	controller->setRadius(20.0f);

	Qt3DExtras::QPhongMaterial* sphereMaterial = new Qt3DExtras::QPhongMaterial(rootEntity);
	sphereMaterial->setDiffuse(QColor(QRgb(0xff0000)));

	QPropertyAnimation* sphereRotateTransformAnimation = new QPropertyAnimation(sphereTransform);
	sphereRotateTransformAnimation->setTargetObject(controller);
	sphereRotateTransformAnimation->setPropertyName("angle");
	sphereRotateTransformAnimation->setStartValue(QVariant::fromValue(0));
	sphereRotateTransformAnimation->setEndValue(QVariant::fromValue(360));
	sphereRotateTransformAnimation->setDuration(10000);
	sphereRotateTransformAnimation->setLoopCount(-1);
	sphereRotateTransformAnimation->start();

	sphereEntity->addComponent(sphereMesh);
	sphereEntity->addComponent(sphereTransform);
	sphereEntity->addComponent(sphereMaterial);

	return rootEntity;
}

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);
	Qt3DExtras::Qt3DWindow view;

	Qt3DCore::QEntity* scene = createScene();

	// Camera
	Qt3DRender::QCamera* camera = view.camera();
	camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(0, 0, 40.0f));
	camera->setViewCenter(QVector3D(0, 0, 0));

	// For camera controls
	Qt3DExtras::QOrbitCameraController* camController = new Qt3DExtras::QOrbitCameraController(scene);
	camController->setLinearSpeed(50.0f);
	camController->setLookSpeed(180.0f);
	camController->setCamera(camera);

	view.setRootEntity(scene);
	view.show();

	return app.exec();
}