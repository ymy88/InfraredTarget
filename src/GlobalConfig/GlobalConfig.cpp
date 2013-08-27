#include "StdAfx.h"
#include <GlobalConfig.h>

const string PRESETS_DIR = "./resources/Missiles/";
const string PRESETS_PATH = "./resources/Missiles/Presets.dat";

string						EnemyMissileInfo::_nameBase = "New enemy missile ";
unsigned int				EnemyMissileInfo::_namePostfix = 0;
string						OurMissileInfo::_nameBase = "New our missile ";
unsigned int				OurMissileInfo::_namePostfix = 0;
string						Location::_nameBase = "New location";
unsigned int				Location::_namePostfix = 0;

int							DataManager::_currSituationIndex = -1;
vector<Situation>			DataManager::_presets;
bool						DataManager::_presetsDirty = true;
vector<Location>			DataManager::_locs;
bool						DataManager::_locsDirty = true;
vector<EnemyMissileInfo>	DataManager::_enemyMissiles;
bool						DataManager::_enemyMissilesDirty = true;
vector<OurMissileInfo>		DataManager::_ourMissiles;
bool						DataManager::_ourMissilesDirty = true;
Database					DataManager::_database;



bool DataManager::loadData()
{
	string presetPath = RESOURCES_PATH + DB_FILE;
	if (_database.loadDatabase(presetPath))
	{
		updateEnemyMissilesIfNeeded();
		updateOurMissilesIfNeeded();
		updateLocsIfNeeded();
		updatePresetsIfNeeded();
		return true;
	}
	return false;
}

unsigned int DataManager::getPresetCount()
{
	updatePresetsIfNeeded();
	return _presets.size();
}

Situation* DataManager::getPreset(unsigned int index)
{
	updatePresetsIfNeeded();
	
	if (_presets.size() == 0) { return NULL; }
	if (index >= _presets.size()) { return NULL; }
	return &_presets[index];
}

void DataManager::newPreset()
{
	Situation s;
	_database.insertPreset(s);
	_currSituationIndex = 0;
	_presetsDirty = true;
}

bool DataManager::commitEditPreset(const Situation& preset)
{
	// no need to update _presets
	// just need update database
	return _database.updatePreset(preset);
}

void DataManager::delPreset(unsigned int index)
{
	if (index >= _presets.size()) { return; }
	_database.delPreset(_presets[index].id);
	_presetsDirty = true;
}

vector<unsigned int> DataManager::findPresets(const vector<unsigned int>& enemyLocIndics,
											  const vector<unsigned int>& ourLocIndics,
											  const vector<unsigned int>& enemyMissileIndics,
											  const vector<unsigned int>& ourMissileIndics)
{
	vector<unsigned int> enemyLocIds(enemyLocIndics.size()),
						 ourLocIds(ourLocIndics.size()),
						 enemyMissileIds(enemyMissileIndics.size()),
						 ourMissileIds(ourMissileIndics.size());
	
	vector<unsigned int>::const_iterator iterIn;
	vector<unsigned int>::iterator iterOut;
	
	for (iterIn = enemyLocIndics.begin(), iterOut = enemyLocIds.begin(); iterIn != enemyLocIndics.end(); ++iterIn, ++iterOut)
	{
		*iterOut = _locs[*iterIn].id;
	}
	for (iterIn = ourLocIndics.begin(), iterOut = ourLocIds.begin(); iterIn != ourLocIndics.end(); ++iterIn, ++iterOut)
	{
		*iterOut = _locs[*iterIn].id;
	}
	for (iterIn = enemyMissileIndics.begin(), iterOut = enemyMissileIds.begin(); iterIn != enemyMissileIndics.end(); ++iterIn, ++iterOut)
	{
		*iterOut = _enemyMissiles[*iterIn].id;
	}
	for (iterIn = ourMissileIndics.begin(), iterOut = ourMissileIds.begin(); iterIn != ourMissileIndics.end(); ++iterIn, ++iterOut)
	{
		*iterOut = _ourMissiles[*iterIn].id;
	}
	vector<unsigned int> res;
	_database.queryPresets(enemyLocIds, ourLocIds, enemyMissileIds, ourMissileIds, res);
	return res;
}

unsigned int DataManager::getLocationCount()
{
	updateLocsIfNeeded();
	return _locs.size();
}

Location* DataManager::getLocation( unsigned int index )
{
	updateLocsIfNeeded();
	if (_locs.size() == 0) { return NULL; }
	if (index >= _locs.size()) { return NULL; }
	return &_locs[index];
}

void DataManager::newLocation()
{
	Location loc;
	bool res;
	while (true)
	{
		res = _database.insertLocation(loc);
		if (!res) { loc.refreshName(); }
		else { break; }
	}
	_locsDirty = true;
	_presetsDirty = true;
}

bool DataManager::commitEditLocation(const Location &loc)
{
	// no need to update _locs
	// just need to update database
	return _database.updateLocation(loc);
}

void DataManager::delLocation( unsigned int index )
{
	if (_locs.size() == 0) { return; }
	if (index >= _locs.size()) { return; }
	_database.delLocation(_locs[index].id);
	_locsDirty = true;
	_presetsDirty = true;
}

unsigned int DataManager::getEnemyMissileCount()
{
	updateEnemyMissilesIfNeeded();
	return _enemyMissiles.size();
}

EnemyMissileInfo* DataManager::getEnemyMissile( unsigned int index )
{
	updateEnemyMissilesIfNeeded();
	
	if (_enemyMissiles.size() == 0) { return NULL; }
	if (index >= _enemyMissiles.size()) { return NULL; }
	return &_enemyMissiles[index];
}

void DataManager::newEnemyMissile()
{
	EnemyMissileInfo mssl;
	bool res;
	while (true)
	{
		res = _database.insertEnemyMissile(mssl);
		if (!res) { mssl.refreshName(); }
		else { break; }
	}
	_database.insertEnemyMissile(mssl);
	_enemyMissilesDirty = true;
	_presetsDirty = true;
}

bool DataManager::commitEditEnemyMissile(const EnemyMissileInfo &missile)
{
	// no need to update _enemyMissiles
	// just need to update database
	return _database.updateEnemyMissile(missile);
}

void DataManager::delEnemyMissile( unsigned int index )
{
	if (_enemyMissiles.size() == 0) { return; }
	if (index >= _enemyMissiles.size()) { return; }

	_database.delEnemyMissile(_enemyMissiles[index].id);
	_enemyMissilesDirty = true;
	_presetsDirty = true;
}

unsigned int DataManager::getOurMissileCount()
{
	updateOurMissilesIfNeeded();
	return _ourMissiles.size();
}

OurMissileInfo* DataManager::getOurMissile( unsigned int index )
{
	updateOurMissilesIfNeeded();
	if (_ourMissiles.size() == 0) { return NULL; }
	if (index >= _ourMissiles.size()) { return NULL; }
	return &_ourMissiles[index];
}

void DataManager::newOurMissile()
{
	OurMissileInfo mssl;
	bool res;
	while (true)
	{
		res = _database.insertOurMissile(mssl);
		if (!res) { mssl.refreshName(); }
		else { break; }
	}
	_ourMissilesDirty = true;
	_presetsDirty = true;
}

bool DataManager::commitEditOurMissile(const OurMissileInfo &missile)
{
	// no need to update _ourMissiles
	// just need update database
	return _database.updateOurMissile(missile);
}

void DataManager::delOurMissile( unsigned int index )
{
	if (_ourMissiles.size() == 0) { return; }
	if (index >= _ourMissiles.size()) { return; }

	_database.delOurMissile(_ourMissiles[index].id);
	_ourMissilesDirty = true;
	_presetsDirty = true;
}

Situation* DataManager::getCurrSituation()
{
	if (_currSituationIndex < 0 || _currSituationIndex >= (int)_presets.size()) { return NULL; }
	return &_presets[_currSituationIndex];
}

void DataManager::setCurrSituation(unsigned int indexInPresets)
{
	if (indexInPresets >= _presets.size())
	{
		indexInPresets = _presets.size() - 1;
	}
	_currSituationIndex = indexInPresets;
}

int DataManager::findLocationIndex(Location* addr)
{
	if (addr == NULL) { return -1; }
	
	for (unsigned int i = 0; i < _locs.size(); ++i)
	{
		if (&_locs[i] == addr)
		{
			return i;
		}
	}
	return -1;
}

int DataManager::findOurMissileIndex(OurMissileInfo* missile)
{
	if (missile == NULL) { return -1; }
	
	for (unsigned int i = 0; i < _ourMissiles.size(); ++i)
	{
		if (&_ourMissiles[i] == missile)
		{
			return i;
		}
	}
	return -1;
}

int DataManager::findEnemyMissileIndex(EnemyMissileInfo* missile)
{
	if (missile == NULL) { return -1; }
	
	for (unsigned int i = 0; i < _enemyMissiles.size(); ++i)
	{
		if (&_enemyMissiles[i] == missile)
		{
			return i;
		}
	}
	return -1;
}

Location* DataManager::findLocationById(unsigned int id)
{
	if (id == 0) { return NULL; }
	
	for (unsigned int i = 0; i < _locs.size(); ++i)
	{
		if (_locs[i].id == id)
		{
			return &_locs[i];
		}
	}
	return NULL;
}

OurMissileInfo* DataManager::findOurMissileById(unsigned int id)
{
	if (id == 0) { return NULL; }
	
	for (unsigned int i = 0; i < _ourMissiles.size(); ++i)
	{
		if (_ourMissiles[i].id == id)
		{
			return &_ourMissiles[i];
		}
	}
	return NULL;
}

EnemyMissileInfo* DataManager::findEnemyMissileById(unsigned int id)
{
	if (id == 0) { return NULL; }
	
	for (unsigned int i = 0; i < _enemyMissiles.size(); ++i)
	{
		if (_enemyMissiles[i].id == id)
		{
			return &_enemyMissiles[i];
		}
	}
	return NULL;
}

void DataManager::updatePresetsIfNeeded()
{
	if (_presetsDirty)
	{
		_presets.clear();
		_database.getPresets(_presets);
		_presetsDirty = false;
	}
}

void DataManager::updateLocsIfNeeded()
{
	if (_locsDirty)
	{
		_locs.clear();
		_database.getLocations(_locs);
		_locsDirty = false;
	}
}

void DataManager::updateEnemyMissilesIfNeeded()
{
	if (_enemyMissilesDirty)
	{
		_enemyMissiles.clear();
		_database.getEnemyMissiles(_enemyMissiles);
		_enemyMissilesDirty = false;
	}
}

void DataManager::updateOurMissilesIfNeeded()
{
	if (_ourMissilesDirty)
	{
		_ourMissiles.clear();
		_database.getOurMissiles(_ourMissiles);
		_ourMissilesDirty = false;
	}
}
