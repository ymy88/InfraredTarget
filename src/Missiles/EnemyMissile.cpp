#include "StdAfx.h"
#include "EnemyMissile.h"
#include "MissileCommon.h"


EnemyMissile::EnemyMissile(OsgViewerBase* mainView)
{
	_mainView = mainView;
	_hitFrame = 0xffffffff;
	_maxFrame = 0;

	Group* group = new Group;

	_trackGeode = new Geode;
	_transformForInfrared = new MatrixTransform;
	_transformForHumanEye = new MatrixTransform;

	_transformForMissile = NULL;
	createTransformForMissile();

	MatrixTransform* scaleTrans1 = new MatrixTransform;
	Matrixd m;
	m.makeScale(0.001, 0.001, 0.001);
	scaleTrans1->setMatrix(m);
	scaleTrans1->addChild(_transformForMissile);

	MatrixTransform* scaleTrans2 = new MatrixTransform;
	//m.makeScale(0.1, 0.1, 0.1);
	scaleTrans2->setMatrix(m);
	scaleTrans2->addChild(_transformForMissile);

	//createTransformsForBaits(baitCount);
	_transformForBaits = NULL;
	createTransformForBaits();
	
	scaleTrans1->addChild(_transformForBaits);
	scaleTrans2->addChild(_transformForBaits);
	
//	for (unsigned int i = 0; i < baitCount; ++i)
//	{
//		scaleTrans1->addChild(_transformsForBaits[i]);
//		scaleTrans2->addChild(_transformsForBaits[i]);
//	}

	_transformForInfrared->addChild(scaleTrans1);
	_transformForHumanEye->addChild(scaleTrans2);

	_missileMaterial = new osg::Material;
	_missileMaterial->setAmbient(Material::FRONT, Vec4d(0, 0, 0, 1));
	_missileMaterial->setDiffuse(Material::FRONT, Vec4d(0, 0, 0, 1));
	_missileMaterial->setSpecular(Material::FRONT, Vec4d(0, 0, 0, 1));
	_missileMaterial->setEmission(Material::FRONT, Vec4d(0, 0, 0, 1));
	_transformForMissile->getOrCreateStateSet()->setAttributeAndModes(_missileMaterial, StateAttribute::ON | StateAttribute::OVERRIDE);

	_baitsMaterial = new osg::Material;
	_baitsMaterial->setAmbient(Material::FRONT, Vec4d(0, 0, 0, 1));
	_baitsMaterial->setDiffuse(Material::FRONT, Vec4d(0, 0, 0, 1));
	_baitsMaterial->setSpecular(Material::FRONT, Vec4d(0, 0, 0, 1));
	_baitsMaterial->setEmission(Material::FRONT, Vec4d(0, 0, 0, 1));
	_transformForBaits->getOrCreateStateSet()->setAttributeAndModes(_baitsMaterial, StateAttribute::ON | StateAttribute::OVERRIDE);

	_label = new Label(osgText::String("弹道导弹", osgText::String::ENCODING_UTF8),
					   14, 0, 0, 0, 1, 1, 1, TextBase::LEFT_BOTTOM);
	_label->setBackgroundColor(1, 0.5, 0.5, 1);
	_label->enablePickAndDragInViewer(mainView);

	group->addChild(_trackGeode);
	group->addChild(_transformForHumanEye);
	group->addChild(_label);

	mainView->getLayerManager()->addToNewLayer(group, "Enemy Missile");
	Recorder::inst()->getInfraredCamera()->addChild(_transformForInfrared);
	
	Recorder::inst()->addRecordable(this);
	EventCenter::inst()->registerHandler(this, KEYBOARD_GROUP, _mainView->getStationId());
	
	
}

EnemyMissile::~EnemyMissile(void)
{
}

void EnemyMissile::getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame )
{
	createTransformForMissile();
	createTransformForBaits();

	double r0 = (situation.enemy.alt + EARTH_R) * 1000;
	double v0 = situation.enemy.missile->speed * 1000;
	double theta0 = DegreesToRadians(90 - situation.enemy.thetaEarth);

	double A = -GM / r0 + 0.5 * v0 * v0;
	double B = v0 * r0 * sin(theta0);

	CameraBase camera(NULL, false);
	initCameraForTrackCalc(&camera, situation.enemy.loc->lon, situation.enemy.loc->lat, situation.enemy.alt, situation.enemy.thetaEarth, situation.enemy.thetaNorth);

	_track.clear();
	_track.push_back(camera.getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT));

	double t = 1.0 / situation.infrared.updateRate;
	double rT = r0, vT = v0, thetaT = theta0;
	double rT1, vT1, thetaT1;
	unsigned frame = 1;
	double lastThetaBeforeHeap = -1;
	bool isAtHeap = false;
	do 
	{
		/* 计算导弹轨迹参数 */
		double sEarth = vT * sin(thetaT) * t;	 /* 平行于地表的直线距离，近似等于沿着地表的曲面距离 */
		double angle = sEarth * 0.001 / EARTH_R; /* 导弹在t到t1时刻跨过的弧度 */
		camera.getCameraController().rotateCamera(AXIS_X, -angle, COORD_TYPE_BASE_POINT_EYE_POINT, ALL_POINTS);

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
		camera.getCameraController().translateCamera(Vec3d(0, 0, (rT1-rT)*0.001), COORD_TYPE_BASE_POINT_EYE_POINT, EYE_POINT_AND_AT_POINT);
		camera.getCameraController().rotateCamera(AXIS_X, thetaT-thetaT1, COORD_TYPE_EYE_POINT, EYE_POINT_AND_AT_POINT);

		/* 记录导弹的矩阵 */
		_track.push_back(camera.getCameraController().getCoordMatrix(COORD_TYPE_EYE_POINT));
		
		rT = rT1;
		vT = vT1;
		thetaT = thetaT1;

		if (isAtHeap) /* 上一帧为轨迹的极大值点，若不做处理，轨迹将一直沿圆周运动 */
		{
			thetaT = PI - lastThetaBeforeHeap;
			isAtHeap = false;
		}

		frame++;

	} while (rT > r0);

	/* update geometry */
	if (_trackGeode->getNumDrawables() > 0)
	{
		_trackGeode->removeDrawables(0, 1);		
	}
	Geometry* geom = createMissileTrackGeometry(_track, Vec4d(1, 0, 0, 1));
	_trackGeode->addDrawable(geom);
	_trackGeode->dirtyBound();

	/* 更新明暗所需参数 */
	missileGray = 1;
	gray = 1;
	gray0 = 1;
	grayState = 1;
	grayDelta = 0.002;
	grayX = 1;
	
	
	_maxFrame = frame - 1;
	begFrame = 0;
	endFrame = _maxFrame;
	_hitFrame = 0xffffffff;
}

void EnemyMissile::gotoFrame( unsigned int frame )
{
	unsigned f = _maxFrame < _hitFrame ? _maxFrame : _hitFrame;
	if (frame > f)
	{
		return;
	}

	/* 更新明暗 */
	_missileMaterial->setEmission(Material::FRONT, Vec4d(missileGray, 0, 0, 1));
	_baitsMaterial->setEmission(Material::FRONT, Vec4d(gray, 0, 0, 1));
	missileGray -= 0.0001;
	if (grayState== 1)
	{
		gray -= grayDelta;
		gray0 = gray;
		grayDelta /= 1.0008;
		if (gray <= 0.50032)
		{
			grayState = 2;
		}
	}
	else
	{
		gray = -0.5 * (1/grayX - 1) + gray0;
		grayX += 0.005;
	}

	/* 更新进动 */
	Matrix mat;
	mat.makeRotate(DegreesToRadians(1.0 * frame), 0, 0, 1);
	_transformForMissile->setMatrix(mat);

	/* 更新位置 */
	_transformForInfrared->setMatrix(_track[frame]);
	_transformForHumanEye->setMatrix(_track[frame]);
	_label->setPosition(_track[frame].getTrans());
}


void EnemyMissile::setBeenHitFrame(unsigned int frame)
{
	_hitFrame = frame;
	if (_hitFrame < _maxFrame)
	{
		Geometry* geom = dynamic_cast<Geometry*>(_trackGeode->getDrawable(0));
		if (geom)
		{
			DrawArrays* drawArrays = dynamic_cast<DrawArrays*>(geom->getPrimitiveSet(0));
			if (drawArrays)
			{
				drawArrays->setCount(_hitFrame + 1);
				geom->dirtyBound();
			}
		}
	}
}

const Matrixd& EnemyMissile::getMissileMatrixInFrame( unsigned int frame )
{
	unsigned int f = _maxFrame > _hitFrame ? _hitFrame : _maxFrame;

	if (frame > f)
	{
		return _track[f];
	}
	else
	{
		return _track[frame];
	}
}

void EnemyMissile::handleSystemEvent( unsigned int eventType, int param1, int param2 )
{
	if (eventType != KEY_UP) { return; }

	if (param1 == '2')
	{
		_mainView->getMainCamera()->flyTo(_transformForHumanEye);
	}
}

//void EnemyMissile::createTransformsForBaits( unsigned int count )
//{
//	_transformsForBaits.clear();
//	_speedForBaits.clear();
//	
//	for (unsigned int i = 0; i < count; ++i)
//	{
//		osg::Sphere* sphere = new osg::Sphere(Vec3d(0, 0, 0), 0.18);
//		ShapeDrawable* sphereDrawable = new ShapeDrawable(sphere);
//
//		Geode* geode = new Geode;
//		geode->addDrawable(sphereDrawable);
//
//		MatrixTransform* trans = new MatrixTransform;
//		trans->addChild(geode);
//
//		Vec3d v;
//		double flagX = 1;
//		if (rand() > 0.5 * RAND_MAX) { flagX = -1; }
//		double flagY = 1;
//		if (rand() > 0.5 * RAND_MAX) { flagY = -1; }
//		v.x() = flagX * (5.0 * rand() / RAND_MAX + 5.0);
//		v.y() = flagY * (5.0 * rand() / RAND_MAX + 5.0);
//		v.z() = 0;
//
//		Matrixd mat;
//		mat.makeTranslate(v);
//		trans->setMatrix(mat);
//
//		Vec3d vv;
//		vv = v * 0.001;
//
//		_transformsForBaits.push_back(trans);
//		_speedForBaits.push_back(vv);
//	}
//}

void EnemyMissile::createTransformForBaits()
{
	if (_transformForBaits == NULL)
	{
		_transformForBaits = new MatrixTransform;
	}
	else if (_transformForBaits->getNumChildren() > 0)
	{
		_transformForBaits->removeChildren(0, _transformForBaits->getNumChildren());
	}
	_speedForBaits.clear();
	
	Situation* situ = DataManager::getCurrSituation();
	if (!situ || !situ->enemy.missile) { return; }
	
	unsigned int count = situ->enemy.missile->baitCount;
	for (unsigned int i = 0; i < count; ++i)
	{
		osg::Sphere* sphere = new osg::Sphere(Vec3d(0, 0, 0), 0.18);
		ShapeDrawable* sphereDrawable = new ShapeDrawable(sphere);

		Geode* geode = new Geode;
		geode->addDrawable(sphereDrawable);

		MatrixTransform* trans = new MatrixTransform;
		trans->addChild(geode);

		Vec3d v;
		double flagX = 1;
		if (rand() > 0.5 * RAND_MAX) { flagX = -1; }
		double flagY = 1;
		if (rand() > 0.5 * RAND_MAX) { flagY = -1; }
		v.x() = flagX * (5.0 * rand() / RAND_MAX + 5.0);
		v.y() = flagY * (5.0 * rand() / RAND_MAX + 5.0);
		v.z() = 0;

		Matrixd mat;
		mat.makeTranslate(v);
		trans->setMatrix(mat);

		Vec3d vv;
		vv = v * 0.001;

		_transformForBaits->addChild(trans);
		_speedForBaits.push_back(vv);
	}
}

void EnemyMissile::createTransformForMissile()
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
	if (situ && situ->enemy.missile)
	{
		string file = situ->enemy.missile->modelFile;
		_transformForMissile->addChild(osgDB::readNodeFile("./resources/Missiles/" + file));
	}
}

void EnemyMissile::outputInfo( ofstream& fout, unsigned int frame )
{
	unsigned f = _maxFrame < _hitFrame ? _maxFrame : _hitFrame;
	if (frame > f)
	{
		return;
	}

	Vec3d v = _track[frame].getTrans();
	fout << setiosflags(ios::fixed) << setprecision(3) << v.x() << ' ' << v.y() << ' ' << v.z() << ' ';
}

