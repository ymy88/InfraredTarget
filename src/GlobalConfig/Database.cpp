#include "StdAfx.h"
#include "Database.h"
#include <GlobalConfig.h>
#include <sstream>

Database::Database(void)
{
	_db = NULL;
	
}

Database::~Database(void)
{
	if (_db)
	{
		sqlite3_finalize(_stmtGetPresets);
		sqlite3_finalize(_stmtGetLocs);
		sqlite3_finalize(_stmtGetOurMssl);
		sqlite3_finalize(_stmtGetEnemyMssl);
		sqlite3_close(_db);
	}
}

bool Database::loadDatabase(const string& dbFile)
{
	int res = sqlite3_open_v2(dbFile.c_str(), &_db, SQLITE_OPEN_READWRITE, NULL);
	
	if (res != SQLITE_OK) { _db = NULL; return false; }
	
	int isFKEnabled;
	res = sqlite3_db_config(_db, SQLITE_DBCONFIG_ENABLE_FKEY, 1, &isFKEnabled);
	if (res != SQLITE_OK || isFKEnabled == false) { sqlite3_close(_db); _db = NULL; return false; }
	
	sqlite3_prepare_v2(_db, "select * from Presets order by presetId desc;", -1, &_stmtGetPresets, NULL);
	sqlite3_prepare_v2(_db, "select * from Locations order by locId desc;", -1, &_stmtGetLocs, NULL);
	sqlite3_prepare_v2(_db, "select * from OurMissiles order by msslId desc;", -1, &_stmtGetOurMssl, NULL);
	sqlite3_prepare_v2(_db, "select * from EnemyMissiles order by msslId desc;", -1, &_stmtGetEnemyMssl, NULL);
	
	return true;
}

void Database::getPresets(vector<Situation>& presets)
{
	presets.clear();
	Situation preset;
	
	while (SQLITE_ROW == sqlite3_step(_stmtGetPresets))
	{
		preset.id = sqlite3_column_int(_stmtGetPresets, 0);
		
		preset.enemy.missile	= DataManager::findEnemyMissileById(sqlite3_column_int(_stmtGetPresets, 1));
		preset.enemy.loc		= DataManager::findLocationById(sqlite3_column_int(_stmtGetPresets, 2));
		preset.enemy.alt		= sqlite3_column_double(_stmtGetPresets, 3);
		preset.enemy.thetaEarth	= sqlite3_column_double(_stmtGetPresets, 4);
		preset.enemy.thetaNorth	= sqlite3_column_double(_stmtGetPresets, 5);
		
		preset.our.missile		= DataManager::findOurMissileById(sqlite3_column_int(_stmtGetPresets, 6));
		preset.our.loc			= DataManager::findLocationById(sqlite3_column_int(_stmtGetPresets, 7));
		preset.our.alt			= sqlite3_column_double(_stmtGetPresets, 8);
		preset.our.thetaEarth	= sqlite3_column_double(_stmtGetPresets, 9);
		preset.our.thetaNorth	= sqlite3_column_double(_stmtGetPresets, 10);
		preset.our.delayTime	= sqlite3_column_double(_stmtGetPresets, 11);
		
		preset.infrared.cameraAngle	= sqlite3_column_double(_stmtGetPresets, 12);
		preset.infrared.resolution	= sqlite3_column_int(_stmtGetPresets, 13);
		preset.infrared.blindRate	= sqlite3_column_double(_stmtGetPresets, 14);
		preset.infrared.updateRate	= sqlite3_column_double(_stmtGetPresets, 15);
		
		preset.other.saveToFile			= sqlite3_column_int(_stmtGetPresets, 16) > 0;
		preset.other.distForStartInfr	= sqlite3_column_int(_stmtGetPresets, 17);
		
		presets.push_back(preset);
	}
	sqlite3_reset(_stmtGetPresets);
}

bool Database::insertPreset(const Situation& preset)
{
	ostringstream sql;
	sql << "insert into Presets values (null, ";
	
	if (preset.enemy.missile == NULL) { sql << "null, "; }
	else { sql << preset.enemy.missile->id << ", "; }
	if (preset.enemy.loc == NULL) { sql << "null, "; }
	else { sql << preset.enemy.loc->id << ", "; }
	sql << preset.enemy.alt << ", "
		<< preset.enemy.thetaEarth << ", "
		<< preset.enemy.thetaNorth << ", ";
	
	if (preset.our.missile == NULL) { sql << "null, "; }
	else { sql << preset.our.missile->id << ", "; }
	if (preset.our.loc == NULL) { sql << "null, "; }
	else { sql << preset.our.loc->id << ", "; }
	sql << preset.our.alt << ", "
		<< preset.our.thetaEarth << ", "
		<< preset.our.thetaNorth << ", "
		<< preset.our.delayTime << ", ";
	
	sql << preset.infrared.cameraAngle << ", "
		<< preset.infrared.resolution << ", "
		<< preset.infrared.blindRate << ", "
		<< (int)preset.infrared.updateRate << ", ";
	
	sql << (int)preset.other.saveToFile << ", "
		<< preset.other.distForStartInfr << ");";
	
	
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

bool Database::updatePreset(const Situation& preset)
{
#define OUTPUT_ID(elem, subElem) \
	if (preset.elem.subElem == NULL) { sql << "null ,"; } \
	else { sql << preset.elem.subElem->id << ", "; }
	
	ostringstream sql;
	
	sql << "update Presets set enemyMsslId=";
	OUTPUT_ID(enemy, missile);
	sql << "enemyLocId=";
	OUTPUT_ID(enemy, loc);
	sql << "enemyAlt=" << preset.enemy.alt << ", "
		<< "enemyThetaEarth=" << preset.enemy.thetaEarth << ", "
		<< "enemyThetaNorth=" << preset.enemy.thetaNorth << ", ";
	
	sql << "OurMsslId=";
	OUTPUT_ID(our, missile);
	sql << "ourLocId=";
	OUTPUT_ID(our, loc);
	sql << "ourAlt=" << preset.our.alt << ", "
		<< "ourThetaEarth=" << preset.our.thetaEarth << ", "
		<< "ourThetaNorth=" << preset.our.thetaNorth << ", "
		<< "ourDelayTime=" << preset.our.delayTime << ", ";
	
	sql << "cameraAngle=" << preset.infrared.cameraAngle << ", "
		<< "resolution=" << preset.infrared.resolution << ", "
		<< "blindRate=" << preset.infrared.blindRate << ", "
		<< "updateRate=" << (int)preset.infrared.updateRate << ", ";
	
	sql << "saveToFile=" << (int)preset.other.saveToFile << ", "
		<< "initDist=" << preset.other.distForStartInfr;
	
	sql << " where presetId=" << preset.id << ";";
	
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
	return true;
	
#undef OUTPUT_ID
}

void Database::delPreset(unsigned int id)
{
	ostringstream sql;
	sql << "delete from Presets where presetId=" << id << ";";
	sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
}


void Database::getLocations(vector<Location>& locations)
{
#define GET_TEXT(var, index) \
	str = sqlite3_column_text(_stmtGetLocs, index); \
	count = sqlite3_column_bytes(_stmtGetLocs, index); \
	loc.var.clear(); \
	loc.var.insert(0, count, '\0'); \
	for (int i = 0; i < count; ++i) { loc.var[i] = (char)str[i]; }
	
	locations.clear();
	Location loc(false);
	const unsigned char* str = NULL;
	int count = 0;
	while (SQLITE_ROW == sqlite3_step(_stmtGetLocs))
	{
		loc.id = sqlite3_column_int(_stmtGetLocs, 0);
		GET_TEXT(name, 1);
		loc.lon = (float)sqlite3_column_double(_stmtGetLocs, 2);
		loc.lat = (float)sqlite3_column_double(_stmtGetLocs, 3);
		GET_TEXT(dscpt, 4);
		
		locations.push_back(loc);
	}
#undef GET_TEXT
}

bool Database::insertLocation(const Location& loc)
{
	ostringstream sql;
	sql << "insert into Locations values (null, \'"
		<< loc.name << "\', " << loc.lon << ", " << loc.lat << ", \'" << loc.dscpt
		<< "\');";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

bool Database::updateLocation(const Location& loc)
{
	ostringstream sql;
	sql << "update Locations set name=\'"
		<< loc.name << "\', lon=" << loc.lon << ", lat=" << loc.lat << ", dscpt=\'" << loc.dscpt
		<< "\' where locId=" << loc.id << ";";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

void Database::delLocation(unsigned int id)
{
	ostringstream sql;
	sql << "delete from Locations where locId=" << id << ";";
	sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
}


void Database::getEnemyMissiles(vector<EnemyMissileInfo>& missiles)
{
#define GET_TEXT(var, index) \
	str = sqlite3_column_text(_stmtGetEnemyMssl, index); \
	count = sqlite3_column_bytes(_stmtGetEnemyMssl, index); \
	mssl.var.clear(); \
	mssl.var.insert(0, count, '\0'); \
	for (int i = 0; i < count; ++i) { mssl.var[i] = (char)str[i]; }
	
	missiles.clear();
	EnemyMissileInfo mssl(false);
	const unsigned char* str = NULL;
	int count = 0;
	while (SQLITE_ROW == sqlite3_step(_stmtGetEnemyMssl))
	{
		mssl.id = sqlite3_column_int(_stmtGetEnemyMssl, 0);
		GET_TEXT(name, 1);
		mssl.speed = (float)sqlite3_column_double(_stmtGetEnemyMssl, 2);
		mssl.baitCount = sqlite3_column_int(_stmtGetEnemyMssl, 3);
		GET_TEXT(modelFile, 4);
		
		missiles.push_back(mssl);
	}
#undef GET_TEXT
}

bool Database::insertEnemyMissile(const EnemyMissileInfo& missile)
{
	ostringstream sql;
	sql << "insert into EnemyMissiles values (null, \'"
		<< missile.name << "\', " << missile.speed << ", " << missile.baitCount << ", \'" << missile.modelFile
		<< "\');";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

bool Database::updateEnemyMissile(const EnemyMissileInfo& missile)
{
	ostringstream sql;
	sql << "update EnemyMissiles set name=\'"
		<< missile.name << "\', speed=" << missile.speed << ", baitcnt=" << missile.baitCount << ", modelfile=\'" << missile.modelFile
		<< "\' where msslId=" << missile.id << ";";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

void Database::delEnemyMissile(unsigned int id)
{
	ostringstream sql;
	sql << "delete from EnemyMissiles where msslId=" << id << ";";
	sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
}


void Database::getOurMissiles(vector<OurMissileInfo>& missiles)
{
#define GET_TEXT(var, index) \
	str = sqlite3_column_text(_stmtGetOurMssl, index); \
	count = sqlite3_column_bytes(_stmtGetOurMssl, index); \
	mssl.var.clear(); \
	mssl.var.insert(0, count, '\0'); \
	for (int i = 0; i < count; ++i) { mssl.var[i] = (char)str[i]; }
	
	missiles.clear();
	OurMissileInfo mssl(false);
	const unsigned char* str = NULL;
	int count = 0;
	while (SQLITE_ROW == sqlite3_step(_stmtGetOurMssl))
	{
		mssl.id = sqlite3_column_int(_stmtGetOurMssl, 0);
		GET_TEXT(name, 1);
		mssl.speed = (float)sqlite3_column_double(_stmtGetOurMssl, 2);
		mssl.angleRate = (float)sqlite3_column_double(_stmtGetOurMssl, 3);
		GET_TEXT(modelFile, 4);
		
		missiles.push_back(mssl);
	}
#undef GET_TEXT
}

bool Database::insertOurMissile(const OurMissileInfo& missile)
{
	ostringstream sql;
	sql << "insert into OurMissiles values (null, \'"
		<< missile.name << "\', " << missile.speed << ", " << missile.angleRate << ", \'" << missile.modelFile
		<< "\');";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

bool Database::updateOurMissile(const OurMissileInfo& missile)
{
	ostringstream sql;
	sql << "update OurMissiles set name=\'"
		<< missile.name << "\', speed=" << missile.speed << ", anglerate=" << missile.angleRate << ", modelfile=\'" << missile.modelFile
		<< "\' where msslId=" << missile.id << ";";
	int res = sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
	return res == SQLITE_OK;
}

void Database::delOurMissile(unsigned int id)
{
	ostringstream sql;
	sql << "delete from OurMissiles where msslId=" << id << ";";
	sqlite3_exec(_db, sql.str().c_str(), NULL, NULL, NULL);
}


void Database::queryPresets(const vector<unsigned int>& enemyLocIds,
							const vector<unsigned int>& ourLocIds,
							const vector<unsigned int>& enemyMissileIds,
							const vector<unsigned int>& ourMissileIds,
							vector<unsigned int>& outputBuffer)
{
	
}
