#pragma once
#include <PSDFCore/PSDFCore.h>
#include <decl.h>
#include <Database.h>

#include <sstream>

const string INFRARED_VIEW = "Infrared view";
const string RESOURCES_PATH = "./resources/";
const string DB_FILE = "Presets.db";

typedef unsigned char byte;

inline unsigned int GLOBALCONFIG_DECL MISSILES_DATA_UPDATE_func()
{
	static unsigned int n = generateCustomEventGroup();
	return n;
}
#define MISSILES_DATA_UPDATE MISSILES_DATA_UPDATE_func()


struct EnemyMissileInfo
{
	unsigned int	id;
	string			name;			/* 导弹名 */
	float			speed;			/* 刚进入中段飞行时的速度(千米/秒) */
	short			baitCount;		/* 诱饵个数 */
	string			modelFile;		/* 模型文件 */
	
	static string	_nameBase;		/* 新建实例时的基本名称 */
	static unsigned _namePostfix;	/* 新建实例时的名称后缀，防止重名问题 */

	EnemyMissileInfo(bool incPostfix = true) : id(0), speed(0), baitCount(0), modelFile("default_dt.ive")
	{
		if (_namePostfix == 0)
		{
			name = _nameBase;
		}
		else
		{
			ostringstream sout;
			sout << _nameBase << _namePostfix;
			name = sout.str();
		}
		if (incPostfix)
		{
			++_namePostfix;
		}
	}
	void refreshName()
	{
		ostringstream sout;
		sout << _nameBase << _namePostfix;
		name = sout.str();
		++_namePostfix;
	}
};

struct OurMissileInfo
{
	unsigned int	id;
	string			name;			/* 导弹名 */
	float			speed;			/* 刚进入中段飞行时的速度(千米/秒) */
	float			angleRate;		/* 制导时的旋转角速度(度/秒) */
	string			modelFile;		/* 模型文件 */

	static string	_nameBase;		/* 新建实例时的基本名称 */
	static unsigned	_namePostfix;	/* 新建实例时的名称后缀，防止重名问题 */
	
	OurMissileInfo(bool incPostfix = true) : id(0), speed(0), angleRate(10), modelFile("default_missile.ive")
	{
		if (_namePostfix == 0)
		{
			name = _nameBase;
		}
		else
		{
			ostringstream sout;
			sout << _nameBase << _namePostfix;
			name = sout.str();
		}
		if (incPostfix)
		{
			++_namePostfix;
		}
	}
	void refreshName()
	{
		ostringstream sout;
		sout << _nameBase << _namePostfix;
		name = sout.str();
		++_namePostfix;
	}
};

struct Location
{
	unsigned int	id;
	string			name;			/* 地点名 */
	float			lon;			/* 经度 */
	float			lat;			/* 纬度 */
	string			dscpt;			/* 描述 */

	static string	_nameBase;		/* 新建实例时的基本名称 */
	static unsigned	_namePostfix;	/* 新建实例时的后缀，防止重名问题 */
	
	Location(bool incPostfix = true) : id(0), lon(0), lat(0), dscpt("")
	{
		if (_namePostfix == 0)
		{
			name = _nameBase;
		}
		else
		{
			ostringstream sout;
			sout << _nameBase << _namePostfix;
			name = sout.str();
		}
		if (incPostfix)
		{
			++_namePostfix;
		}
	}
	void refreshName()
	{
		ostringstream sout;
		sout << _nameBase << _namePostfix;
		name = sout.str();
		++_namePostfix;
	}
};

struct GLOBALCONFIG_DECL Situation
{
	unsigned int id; /* 从数据库取得的id */
	
/* 敌方导弹 */
	struct
	{
		EnemyMissileInfo*	missile;
		Location*			loc;			/* 地点 */
		float				alt;			/* 刚进入中段飞行时的高度 */
		float				thetaEarth;		/* 刚进入中段飞行时相对地平面的仰角(度, (0, 90)) */
		float				thetaNorth;		/* 刚进入中段飞行时相对正北的偏角(度, (-180, 180]，向东为正) */
	} enemy;

/* 我方导弹 */
	struct
	{
		OurMissileInfo*	missile;
		Location*		loc;			/* 地点 */
		float			alt;			/* 刚进入中段飞行时的高度 */
		float			thetaEarth;		/* 刚进入中段飞行时相对地平面的仰角(度) */
		float			thetaNorth;		/* 刚进入中段飞行时相对正北的偏角(度) */
		float			delayTime;	 	/* 当敌方导弹进入中段飞行多久(秒)后，我方导弹进入中段飞行 */
	} our;

/* 红外探测器 */
	struct
	{
		float	cameraAngle;	/* 红外相机的视场角(度) */
		short	resolution;		/* 红外相机的分辨率(正方形，边长像素数) */
		float	blindRate;		/* 盲元率(%) */
		byte	updateRate;		/* 成像速率(成像数/秒) */
	} infrared;

/* 其他 */
	struct 
	{
		bool	saveToFile;
		/*wchar_t savePath[200]; */
		float	distForStartInfr;
	} other;

	Situation()
	{
		memset(this, 0, sizeof(Situation));
	}

	bool isValid()
	{
		if (enemy.missile == NULL) { return false; }
		if (enemy.loc == NULL) { return false; }
		if (enemy.thetaEarth <= 0 || enemy.thetaEarth >= 90) { return false; }
		if (enemy.missile->speed <= 0 || enemy.missile->speed >= 10) { return false; }
		if (our.missile == NULL) { return false; }
		if (our.loc == NULL) { return false; }
		if (our.thetaEarth <= 0 || enemy.thetaEarth >= 90) { return false; }
		if (our.missile->speed <= 0 || our.missile->speed >= 90) { return false; }
		if (our.missile->angleRate <= 0 || our.missile->angleRate >= 360) { return false; }
		if (infrared.cameraAngle <= 0 || infrared.cameraAngle >= 90) { return false; }
		if (infrared.resolution <= 0 || infrared.resolution > 512) { return false; }
		if (infrared.updateRate <= 0 || infrared.updateRate >= 500) { return false; }

		return true;
	}
};

struct MissileData
{
	float currTime;
	double distance;
};



class GLOBALCONFIG_DECL DataManager
{
public:
	static bool					loadData();
	
	static unsigned int			getPresetCount();
	static Situation*			getPreset(unsigned int index);
	static bool					commitEditPreset(const Situation& preset);
	static void					newPreset();
	static void					delPreset(unsigned int index);
	static vector<unsigned int>	findPresets(const vector<unsigned int>& enemyLocIndics,
											const vector<unsigned int>& ourLocIndics,
											const vector<unsigned int>& enemyMissileIndics,
											const vector<unsigned int>& ourMissileIndics);
	
	static unsigned int			getLocationCount();
	static Location*			getLocation(unsigned int index);
	static bool					commitEditLocation(const Location& loc);
	static void					newLocation();
	static void					delLocation(unsigned int index);

	static unsigned int			getEnemyMissileCount();
	static EnemyMissileInfo*	getEnemyMissile(unsigned int index);
	static bool					commitEditEnemyMissile(const EnemyMissileInfo& missile);
	static void					newEnemyMissile();
	static void					delEnemyMissile(unsigned int index);

	static unsigned int			getOurMissileCount();
	static OurMissileInfo*		getOurMissile(unsigned int index);
	static bool					commitEditOurMissile(const OurMissileInfo& missile);
	static void					newOurMissile();
	static void					delOurMissile(unsigned int index);

	static Situation*			getCurrSituation();
	static void					setCurrSituation(unsigned int indexInPresets);

	static int					findLocationIndex(Location* loc);
	static int					findOurMissileIndex(OurMissileInfo* missile);
	static int					findEnemyMissileIndex(EnemyMissileInfo* missile);
	
	static Location*			findLocationById(unsigned int id);
	static OurMissileInfo*		findOurMissileById(unsigned int id);
	static EnemyMissileInfo*	findEnemyMissileById(unsigned int id);
	
	static void					updatePresetsIfNeeded();
	static void					updateLocsIfNeeded();
	static void					updateEnemyMissilesIfNeeded();
	static void					updateOurMissilesIfNeeded();
	
private:
	static int						_currSituationIndex;
	static vector<Situation>		_presets;
	static bool						_presetsDirty;
	
	static vector<Location>			_locs;
	static bool						_locsDirty;
	static vector<EnemyMissileInfo>	_enemyMissiles;
	static bool						_enemyMissilesDirty;
	static vector<OurMissileInfo>	_ourMissiles;
	static bool						_ourMissilesDirty;
	
	static Database					_database;
};

#ifdef _WIN32
#  ifndef GLOBALCONFIG_EXPORTS
#    ifdef _DEBUG
#      pragma comment(lib, "GlobalConfigd.lib")
#    else
#      pragma comment(lib, "GlobalConfig.lib")
#    endif
#  endif
#endif
