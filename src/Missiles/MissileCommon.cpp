#include "StdAfx.h"
#include "MissileCommon.h"
#include <osg/LineWidth>

void initCameraForTrackCalc( CameraBase* camera, float lon, float lat, float alt, double thetaEarth, double thetaNorth )
{
	/* 将视点移到导弹的位置 */
	const Vec3d& currEye = camera->getCameraController().getCurrEye();
	double currDist = currEye.length();
	camera->getCameraController().translateCamera(Vec3d(0, 0, alt+EARTH_R-currDist), COORD_TYPE_WORLD,  EYE_POINT_AND_AT_POINT);
	camera->getCameraController().rotateCamera(AXIS_X, DegreesToRadians(-lat), COORD_TYPE_WORLD, ALL_POINTS);
	camera->getCameraController().rotateCamera(AXIS_Y, DegreesToRadians(90 + lon), COORD_TYPE_WORLD, ALL_POINTS);

	/* 处理仰角 */
	camera->getCameraController().rotateCamera(AXIS_X, DegreesToRadians(90+thetaEarth), COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);

	Vec3d at = camera->getCameraController().getCurrAt();

	/* 处理与正北的偏角 */
	camera->getCameraController().rotateCamera(AXIS_Z, DegreesToRadians(-thetaNorth), COORD_TYPE_BASE_POINT_EYE_POINT, ALL_POINTS);

	at = camera->getCameraController().getCurrAt();
}

Geometry* createMissileTrackGeometry(const vector<Matrixd>& track, const Vec4d& trackColor)
{
	Geometry* geom = new Geometry;
	geom->setUseDisplayList(false);

	Vec3dArray* vertex = new Vec3dArray;
	Vec4dArray* color = new Vec4dArray;
	Vec3dArray* normal = new Vec3dArray;

	geom->setVertexArray(vertex);
	geom->setColorArray(color);
	geom->setNormalArray(normal);

	color->push_back(trackColor);
	normal->push_back(Vec3d(0, 0, 1));

	geom->setColorBinding(Geometry::BIND_OVERALL);
	geom->setNormalBinding(Geometry::BIND_OVERALL);

	Vec3d ori;
	for (unsigned int i = 0; i < track.size(); ++i)
	{
		Vec3d cur = ori * track[i];
		vertex->push_back(cur);
	}

	DrawArrays* drawArrays = new DrawArrays(GL_LINE_STRIP, 0, vertex->size());
	geom->addPrimitiveSet(drawArrays);

	LineWidth* w = new LineWidth(3);
	geom->getOrCreateStateSet()->setAttributeAndModes(w);

	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);

	return geom;
}