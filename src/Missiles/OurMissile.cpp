#include "StdAfx.h"
#include "Ourmissile.h"
#include "MissileCommon.h"
#include <osg/LineStipple>

const unsigned int DISTANCE_TO_START_AIM = 200;

OurMissile::OurMissile(OsgViewerBase* mainView, EnemyMissile* enemyMissile)
{
	_mainView = mainView;
	_enemyMissile = enemyMissile;

	Group* group = new Group;

	_trackGeode = new Geode;
	_transformForHumanEye = new MatrixTransform;
	_atTransform = new MatrixTransform;

	_transformForMissile = NULL;
	createTransformForMissile();
	
	Node* sight = createSight();
	_atTransform->addChild(sight);

	MatrixTransform* scaleTrans = new MatrixTransform;
	Matrixd m;
	m.makeScale(0.05, 0.05, 0.05);
	scaleTrans->setMatrix(m);
	scaleTrans->addChild(_transformForMissile);
	_transformForHumanEye->addChild(scaleTrans);

	_label = new Label(osgText::String("拦截导弹", osgText::String::ENCODING_UTF8),
					   14, 0, 0, 0, 1, 1, 1, TextBase::LEFT_BOTTOM);
	_label->setBackgroundColor(0.5, 0.5, 1, 1);
	_label->enablePickAndDragInViewer(mainView);

	group->addChild(_trackGeode);
	group->addChild(_transformForHumanEye);
	group->addChild(_atTransform);
	group->addChild(_label);
	group->setNodeMask(0);

	mainView->getLayerManager()->addToNewLayer(group, "Our Missile");
	
	Recorder::inst()->addRecordable(this, true);
	EventCenter::inst()->registerHandler(this, KEYBOARD_GROUP, _mainView->getStationId());

	_disturbAngleX = _disturbAngleY = 0;
}

OurMissile::~OurMissile(void)
{
}

void OurMissile::getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame )
{
	_transformForHumanEye->getParent(0)->setNodeMask(0xffffffff);

	createTransformForMissile();
	
	begFrame = 0;

	_delayFrame = situation.our.delayTime * situation.infrared.updateRate;

	int resolution = situation.infrared.resolution;
	double angle = situation.infrared.cameraAngle;

	CameraBase camera(NULL, false);
	camera.setViewport(0, 0, resolution, resolution);
	camera.setProjectionMatrixAsPerspective(DegreesToRadians(angle), 1, 0.01, 1000);
	initCameraForTrackCalc(&camera, situation.our.loc->lon, situation.our.loc->lat, situation.our.alt, situation.our.thetaEarth, situation.our.thetaNorth);

	_track.clear();
	_posture.clear();
	_disturb.clear();
	_track.push_back(camera.getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT));
	_posture.push_back(Matrixd());

	//
	// 轨迹生成
	//
	unsigned frame = flyByTrack(situation, &camera, 1);
	_aimStartFrame = frame + _delayFrame;
	begFrame = frame;

	const Matrixd& matEnemy = _enemyMissile->getMissileMatrixInFrame(frame-1);
	const Matrixd& matOur = _track[frame-1];
	Vec3d enemyPos(0, 0, 0);
	Vec3d ourPos(0, 0, 0);
	enemyPos = enemyPos * matEnemy;
	ourPos = ourPos * matOur;
	if ((enemyPos - ourPos).length2() <= DISTANCE_TO_START_AIM * DISTANCE_TO_START_AIM)
	{
		frame = aimAtTarget(situation, &camera, frame);
	}

	//
	// 轨迹Geometry生成
	//
	PosixThread::msleep(10);

	if (_trackGeode->getNumDrawables() > 0)
	{
		_trackGeode->removeDrawables(0, 1);		
	}
	Geometry* geom = createMissileTrackGeometry(_track, Vec4d(0.0, 0.0, 1, 1));
	_trackGeode->addDrawable(geom);
	_trackGeode->dirtyBound();

	_maxFrame = _delayFrame + frame - 1;
	begFrame += _delayFrame;

	endFrame = _maxFrame;


// 	static char ch = 'a';
// 	ch++;
// 	string file("a.txt");
// 	file[0] = ch;
// 	ofstream fout(file.c_str());
// 
// 	for (unsigned int i = 0; i < _track.size(); ++i)
// 	{
// 		Vec3d trans = _track[i].getTrans();
// 		fout << trans.x() << '\t' << trans.y() << '\t' << trans.z() << endl;
// 	}
}

void OurMissile::gotoFrame( unsigned int frame )
{
	if (frame < _delayFrame)
	{
		_transformForHumanEye->setMatrix(_track[0]);
		_label->setPosition(_track[0].getTrans());
		Recorder::inst()->getInfraredCamera()->getCameraController().setCameraEyeMatrix(_track[0], 1);
	}
	else if (frame <= _maxFrame)
	{
		_transformForHumanEye->setMatrix(_track[frame - _delayFrame]);
		_atTransform->setMatrix(_track[frame-_delayFrame]);
		_label->setPosition(_track[frame-_delayFrame].getTrans());
		Recorder::inst()->getInfraredCamera()->getCameraController().setCameraEyeMatrix(_track[frame - _delayFrame], 1);
	}
}

void OurMissile::handleSystemEvent( unsigned int eventType, int param1, int param2 )
{
	if (eventType != KEY_UP) { return; }

	if (param1 == '1')
	{
		_mainView->getMainCamera()->flyTo(_transformForHumanEye);
	}
}

const Matrixd& OurMissile::getMissileMatrixInFrame( unsigned int frame )
{
	if (frame > _maxFrame)
	{
		return _track[_maxFrame - _delayFrame];
	}
	else if (frame < _delayFrame)
	{
		return _track[0];
	}
	else
	{
		return _track[frame - _delayFrame];
	}
}

const Vec2& OurMissile::getDisturb( unsigned int frame )
{
	if (frame > _maxFrame)
	{
		return _disturb[_maxFrame - _delayFrame];
	}
	else if (frame < _delayFrame)
	{
		return _disturb[0];
	}
	else
	{
		return _disturb[frame - _delayFrame];
	}
}

void OurMissile::createTransformForMissile()
{
	if (_transformForMissile == NULL)
	{
		_transformForMissile = new MatrixTransform;
	}
	else if (_transformForMissile->getNumChildren() > 0)
	{
		_transformForMissile->removeChildren(0, _transformForMissile->getNumChildren());
	}
	
	Situation* situ = DataManager::getCurrSituation();
	if (situ && situ->our.missile)
	{
		string file = situ->our.missile->modelFile;
		_transformForMissile->addChild(osgDB::readNodeFile("./resources/Missiles/" + file));
	}
}

Node* OurMissile::createSight()
{
	Geometry* geom = new Geometry;
	Vec3dArray* vertex = new Vec3dArray;
	Vec4dArray* color = new Vec4dArray;
	Vec3dArray* normal = new Vec3dArray;

	vertex->push_back(Vec3d(0, 0, 0));
	vertex->push_back(Vec3d(0, 0, -100));

	color->push_back(Vec4d(1, 1, 0.5, 0.5));

	normal->push_back(Vec3d(0, 0, 1));

	geom->setVertexArray(vertex);
	geom->setColorArray(color);
	geom->setNormalArray(normal);
	geom->setColorBinding(Geometry::BIND_OVERALL);
	geom->setNormalBinding(Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new DrawArrays(GL_LINES, 0, 2));

	osg::LineStipple* lineStipple = new LineStipple(1, 0x20f0);
	geom->getOrCreateStateSet()->setAttributeAndModes(lineStipple);
	geom->getOrCreateStateSet()->setMode(GL_BLEND, StateAttribute::ON);

	Geode* geode = new Geode;
	geode->addDrawable(geom);

	return geode;
}

unsigned OurMissile::flyByTrack(const Situation& situation, CameraBase* camera, unsigned frame)
{
	double r0 = (situation.our.alt + EARTH_R) * 1000;
	double v0 = situation.our.missile->speed * 1000;
	double theta0 = DegreesToRadians(90 - situation.our.thetaEarth);

	double A = -GM / r0 + 0.5 * v0 * v0;
	double B = v0 * r0 * sin(theta0);

	double t = 1.0 / situation.infrared.updateRate;
	double rT = r0, vT = v0, thetaT = theta0;
	double rT1, vT1, thetaT1;
	double lastThetaBeforeHeap = -1;
	bool isAtHeap = false;
	do 
	{
		/* 计算导弹轨迹参数 */
		double sEarth = vT * sin(thetaT) * t;	 /* 平行于地表的直线距离，近似等于沿着地表的曲面距离 */
		camera->getCameraController().translateCamera(Vec3d(0, sEarth * 0.001, 0), COORD_TYPE_BASE_POINT_EYE_POINT, EYE_POINT_AND_AT_POINT);

		rT1 = rT + vT * t * cos(thetaT);
		vT1 = sqrt(2 * A + 2 * GM / rT1);
		double tmp = B / (vT1 * rT1);
		if (!isAtHeap && tmp > 1)  /* 由于double经度问题，得出的值可能略大于1 */
		{
			thetaT1 = PI_2;
			lastThetaBeforeHeap = thetaT; /* 保存到达极大值的前一个角度值 */
			isAtHeap = true;
		}
		else
		{
			thetaT1 = asin(B / (vT1 * rT1));
			if (thetaT > PI_2) { thetaT1 = PI - thetaT1; }
		}

		/* 调整导弹转换矩阵 */
		camera->getCameraController().translateCamera(Vec3d(0, 0, (rT1-rT)*0.001), COORD_TYPE_BASE_POINT_EYE_POINT, EYE_POINT_AND_AT_POINT);
		camera->getCameraController().rotateCamera(AXIS_X, thetaT-thetaT1, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);

		const Matrixd& matOur = camera->getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT);

		/* 记录导弹的矩阵 */
		_track.push_back(matOur);
		_posture.push_back(Matrixd());
		
		rT = rT1;
		vT = vT1;
		thetaT = thetaT1;

		if (isAtHeap) /* 上一帧为轨迹的极大值点，若不做处理，轨迹将一直沿圆周运动 */
		{
			thetaT = PI - lastThetaBeforeHeap;
			isAtHeap = false;
		}

		frame++;

		const Matrixd& matEnemy = _enemyMissile->getMissileMatrixInFrame(frame);
		Vec3d enemyPos = matEnemy.getTrans();
		Vec3d ourPos = matOur.getTrans();

		double dist2 = (enemyPos - ourPos).length2();
		if (dist2 <= DISTANCE_TO_START_AIM * DISTANCE_TO_START_AIM)
		{
			break;
		}

	} while (rT > r0);

	return frame;
}

unsigned OurMissile::aimAtTarget(const Situation& situation, CameraBase* camera, unsigned frame)
{
	double t = 1.0 / situation.infrared.updateRate;
	double dist = situation.our.missile->speed * t;
	double maxAngle = DegreesToRadians(situation.our.missile->angleRate) * t;
	double disturbRange = DegreesToRadians(0.02);
	double maxDistance;
	unsigned firstFrame = frame;
	do 
	{
		Matrixd postureMat;

		if (frame + _delayFrame > _enemyMissile->getHitTargetFrame()) { break; }

		if (frame == MAX_END_FRAME) { break; }

		/* 计算敌方导弹相对于自身的位置 */
		const Matrixd& enemyMatrix = _enemyMissile->getMissileMatrixInFrame(frame + _delayFrame);
		Vec3d enemyPos = Vec3d(0, 0, 0) * enemyMatrix;
		Vec3d enemyPosEye = camera->getCameraController().switchCoordinateSystem_point(enemyPos, COORD_TYPE_WORLD, COORD_TYPE_EYE_POINT);

		/* 旋转我方导弹，对准敌方导弹 */
		enemyPosEye.normalize();
		Vec3d sight = Vec3d(0, 0, -1);

		double cosAngle = enemyPosEye * sight;
		bool targeted;
		if (abs(cosAngle) < 1)
		{
			double angle = acos(cosAngle);
			if (angle <= maxAngle)
			{
				targeted = true;
			}
			else
			{
				targeted = false;
				angle = maxAngle;
			}
			Vec3d axis = sight ^ enemyPosEye;
			
			camera->getCameraController().rotateCamera(axis, angle, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);
			postureMat.makeRotate(angle, axis);
		}

		/* 判断是否会击中 */
		enemyPosEye = camera->getCameraController().switchCoordinateSystem_point(enemyPos, COORD_TYPE_WORLD, COORD_TYPE_EYE_POINT);
		if (/* targeted && */fabs(enemyPosEye.z()) <= dist)
		{
			Vec3d v = enemyPos - camera->getCameraController().getCurrEye();
			camera->getCameraController().translateCamera(v, COORD_TYPE_WORLD, EYE_POINT_AND_AT_POINT);	
			_track.push_back(camera->getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT));
			_posture.push_back(Matrixd());
			_disturb.push_back(Vec2(0, 0));
			_enemyMissile->setBeenHitFrame(_delayFrame + frame);

			enemyPosEye = camera->getCameraController().switchCoordinateSystem_point(enemyPos, COORD_TYPE_WORLD, COORD_TYPE_EYE_POINT);

			frame++;
			break;
		}
		if (frame == firstFrame)
		{
			maxDistance = enemyPosEye.z();
		}


		/* 扰动 */
		double rnd;
		double tmp = disturbRange * enemyPosEye.z() / maxDistance * 0.9;
		rnd = 0.2 * rand() / RAND_MAX + 0.9;
		double disturbXAngle = sin(0.07 * frame) * tmp * rnd;
		rnd = 0.2 * rand() / RAND_MAX + 0.9;
		double disturbYAngle = sin(0.04 * frame) * tmp * rnd;
		camera->getCameraController().rotateCamera(AXIS_X, disturbXAngle, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);
		camera->getCameraController().rotateCamera(AXIS_Y, disturbYAngle, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);

		/* 翻转（翻转需要在扰动后做，才比较真实） */
		rnd = 0.2 * rand() / RAND_MAX + 0.9;
		double disturbZAngle = 0.1 * sin(0.03 * frame) * rnd;
		camera->getCameraController().rotateCamera(AXIS_Z, disturbZAngle, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);

		Matrixd matR;
		matR.makeRotate(disturbXAngle, Vec3d(1, 0, 0),
			disturbYAngle, Vec3d(0, 1, 0),
			disturbZAngle, Vec3d(0, 0, 1));

		postureMat = postureMat * matR;
		_posture.push_back(postureMat);

		/* 前进 */
		camera->getCameraController().translateCamera(Vec3d(0, 0, -dist), COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);	

		/* 记录相机的视点矩阵 */
		_track.push_back(camera->getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT));

		/* 记录扰动 */
		int x, y;
		camera->worldToScreen(enemyPos, x, y);
		Vec2 v = Vec2(x, y);
		_disturb.push_back(v);

		frame++;

	} while (true);

	return frame;
}

void OurMissile::outputInfo( ofstream& fout, unsigned frame )
{
	if (frame <= _maxFrame)
	{
		Vec3d v = _track[frame - _delayFrame].getTrans();
		Vec3 hpr;
		MatrixToHpr(hpr, _posture[frame - _delayFrame]);
		fout << setiosflags(ios::fixed) << setprecision(4) << v.x() << ' ' << v.y() << ' ' << v.z() << ' ' << hpr.x() << ' ' << hpr.y() << ' ' << hpr.z() << ' ';
		Vec2f d = _disturb[frame - _aimStartFrame];
		fout << setprecision(0) << d.x() << ' ' << d.y();
	}
}
