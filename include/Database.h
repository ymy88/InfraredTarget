#pragma once

#include <sqlite3.h>
#ifdef _WIN32
#pragma comment(lib, "sqlite3.lib")
#endif

#include <decl.h>

struct Location;
struct EnemyMissileInfo;
struct OurMissileInfo;
struct Situation;

class DataManager;

class GLOBALCONFIG_DECL Database
{
	friend class DataManager;
	
private:
	Database(void);
	~Database(void);
	
	bool			loadDatabase(const string& dbFile);

	void			getPresets(vector<Situation>& presets);
	bool			insertPreset(const Situation& preset);
	bool			updatePreset(const Situation& preset);
	void			delPreset(unsigned int id);

	void			getLocations(vector<Location>& locations);
	bool			insertLocation(const Location& loc);
	bool			updateLocation(const Location& loc);
	void			delLocation(unsigned int id);

	void			getEnemyMissiles(vector<EnemyMissileInfo>& missiles);
	bool			insertEnemyMissile(const EnemyMissileInfo& missile);
	bool			updateEnemyMissile(const EnemyMissileInfo& missile);
	void			delEnemyMissile(unsigned int id);

	void			getOurMissiles(vector<OurMissileInfo>& missiles);
	bool			insertOurMissile(const OurMissileInfo& missile);
	bool			updateOurMissile(const OurMissileInfo& missile);
	void			delOurMissile(unsigned int id);

	void			queryPresets(const vector<unsigned int>& enemyLocIds,
								 const vector<unsigned int>& ourLocIds,
								 const vector<unsigned int>& enemyMissileIds,
								 const vector<unsigned int>& ourMissileIds,
								 vector<unsigned int>& outputBuffer);

private:
	sqlite3*		_db;
	
	sqlite3_stmt*	_stmtGetPresets;
	sqlite3_stmt*	_stmtGetLocs;
	sqlite3_stmt*	_stmtGetEnemyMssl;
	sqlite3_stmt*	_stmtGetOurMssl;
};
