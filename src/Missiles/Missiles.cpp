#include "StdAfx.h"
#include "Missiles.h"
#include <GlobalConfig.h>

const string DATA_FILE_PATH = "./resources/Missiles/data.txt";
//const string DATA_FILE_PATH = "c:/data.txt";

Missiles::Missiles(void)
{
}

Missiles::~Missiles(void)
{
	delete _enemyMissile;
	delete _ourMissile;
}

bool Missiles::initPlugin()
{
	_enemyMissile = new EnemyMissile(getParentViewer());
	_ourMissile = new OurMissile(getParentViewer(), _enemyMissile);

	Recorder::inst()->addRecordable(this);

	return true;
}

void Missiles::getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame )
{
	_shouldSaveFile = situation.other.saveToFile;

	_timeForFrame = 1.0 / situation.infrared.updateRate;

	begFrame = 0;
	endFrame = 0;

	const Matrixd& mat1 = _enemyMissile->getMissileMatrixInFrame(0);	
	const Matrixd& mat2 = _ourMissile->getMissileMatrixInFrame(0);	

	Vec3d p1(0, 0, 0);
	Vec3d p2(0, 0, 0);

	p1 = p1 * mat1;
	p2 = p2 * mat2;

	Vec3d pM = (p1 + p2) / 2;

	double lon, lat, alt;
	SceneCenter::inst()->ellipsoidXYZToLLA(pM.x(), pM.y(), pM.z(), lon, lat, alt);

	double eyeDist = 0.6 * (p1 - p2).length() * COT_CAMERA_FOV_2;

	getParentViewer()->getMainCamera()->flyTo(lon, lat, eyeDist, DegreesToRadians(45.0), 0);

	if (situation.other.saveToFile)
	{
		if (_fout.is_open())
		{
			_fout.close();
		}
		_fout.open(DATA_FILE_PATH.c_str());
	}
}

void Missiles::gotoFrame( unsigned int frame )
{
	const Matrixd& mat1 = _enemyMissile->getMissileMatrixInFrame(frame);	
	const Matrixd& mat2 = _ourMissile->getMissileMatrixInFrame(frame);	
	
	Vec3d p1 = Vec3d(0, 0, 0);
	Vec3d p2 = Vec3d(0, 0, 0);

	p1 = p1 * mat1;
	p2 = p2 * mat2;

	double dist = (p1 - p2).length();

	/* 更新UI */
	MissileData missileData;
	missileData.currTime = frame * _timeForFrame;
	missileData.distance = dist;
	int dataIndex = DataCenter::inst()->addData((char*)&missileData, sizeof(MissileData));
	
	EventCenter::inst()->triggerEvent(MISSILES_DATA_UPDATE, dataIndex, 0, getParentViewer()->getStationId());

	/* 输出文件 */
	if (_shouldSaveFile)
	{
		_fout << frame << ' ';
		_enemyMissile->outputInfo(_fout, frame);
		_ourMissile->outputInfo(_fout, frame);
		_fout << endl;
	}
}

void Missiles::end()
{
	_fout.close();
}
