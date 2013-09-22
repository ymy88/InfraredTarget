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
	camera->getCameraController().rotateCamera(AXIS_X, DegreesToRadians(90+thetaEarth), COORD_TYPE_EYE, EYE_POINT_AND_AT_POINT);

	Vec3d at = camera->getCameraController().getCurrAt();

	/* 处理与正北的偏角 */
	camera->getCameraController().rotateCamera(AXIS_Z, DegreesToRadians(-thetaNorth), COORD_TYPE_BASE_EYE, ALL_POINTS);

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

float ClampUnity(float x)
{
	if (x >  1.0f) { return  1.0f; }
	if (x < -1.0f) { return -1.0f; }
	return x;
}

void MatrixToHpr(osg::Vec3& hpr, const osg::Matrix& rotation)
{
	// implementation converted from plib's sg.cxx
	// PLIB - A Suite of Portable Game Libraries
	// Copyright (C) 1998,2002  Steve Baker
	// For further information visit http://plib.sourceforge.net

	osg::Matrix mat;

	osg::Vec3 col1(rotation(0, 0), rotation(0, 1), rotation(0, 2));
	double s = col1.length();

	const double magic_epsilon = 0.00001;
	if (s <= magic_epsilon)
	{
		hpr.set(0.0f, 0.0f, 0.0f);
		return;
	}


	double oneOverS = 1.0f / s;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mat(i, j) = rotation(i, j) * oneOverS;
		}
	}


	double sin_pitch = ClampUnity(mat(1, 2));
	double pitch = asin(sin_pitch);
	hpr[1] = osg::RadiansToDegrees(pitch);

	double cp = cos(pitch);

	if (cp > -magic_epsilon && cp < magic_epsilon)
	{
		double cr = ClampUnity(-mat(2,1));
		double sr = ClampUnity(mat(0,1));

		hpr[0] = 0.0f;
		hpr[2] = osg::RadiansToDegrees(atan2(sr,cr));
	}
	else
	{
		double one_over_cp = 1.0 / cp;
		double sr = ClampUnity(-mat(0,2) * one_over_cp);
		double cr = ClampUnity( mat(2,2) * one_over_cp);
		double sh = ClampUnity(-mat(1,0) * one_over_cp);
		double ch = ClampUnity( mat(1,1) * one_over_cp);

		if ((osg::equivalent(sh,0.0,magic_epsilon) && osg::equivalent(ch,0.0,magic_epsilon)) ||
			(osg::equivalent(sr,0.0,magic_epsilon) && osg::equivalent(cr,0.0,magic_epsilon)) )
		{
			cr = ClampUnity(-mat(2,1));
			sr = ClampUnity(mat(0,1));;

			hpr[0] = 0.0f;
		}
		else
		{
			hpr[0] = osg::RadiansToDegrees(atan2(sh, ch));
		}

		hpr[2] = osg::RadiansToDegrees(atan2(sr, cr));
	}

	// 0 -> 2
	// 1 -> 0
	// 2 -> 1

	double tmp = hpr[2];
	hpr[2] = hpr[0];
	hpr[0] = hpr[1];
	hpr[1] = tmp;

	return;
}