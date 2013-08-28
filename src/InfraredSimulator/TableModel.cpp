//
//  TableModel.cpp
//  InfraredTarget
//
//  Created by Ymy on 13-8-16.
//  Copyright (c) 2013年 Ymy. All rights reserved.
//

#include "StdAfx.h"
#include "TableModel.h"
#include <GlobalConfig.h>

////////////////////////////////////////
// EnemyMissileTableModel
////////////////////////////////////////
ItemFlags EnemyMissileTableModel::flags(const QModelIndex & index) const
{
	return ItemIsSelectable | ItemIsEditable | ItemIsEnabled;
}

int EnemyMissileTableModel::rowCount(const QModelIndex & parent) const
{
	return DataManager::getEnemyMissileCount();
}

int EnemyMissileTableModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant EnemyMissileTableModel::data(const QModelIndex & index, int role) const
{
	switch (role)
	{
		case DisplayRole:
		case EditRole:
		{
			EnemyMissileInfo* missile = DataManager::getEnemyMissile(index.row());
			switch (index.column())
			{
				case 0: return QVariant(missile->name.c_str());
				case 1: return QVariant(missile->speed);
				case 2: return QVariant(missile->baitCount);
				case 3: return QVariant(missile->modelFile.c_str());
					
				default:
					break;
			}
		}
		case TextAlignmentRole:
		{
			switch (index.column())
			{
				case 0: return QVariant(AlignLeft | AlignVCenter);
				case 1: return QVariant(AlignRight | AlignVCenter);
				case 2: return QVariant(AlignRight | AlignVCenter);
				case 3: return QVariant(AlignLeft | AlignVCenter);
			}
		}
	}
	return QVariant();
}

QVariant EnemyMissileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Horizontal) { return QVariant(); }
	
	if (role == Qt::DisplayRole)
	{
		switch (section)
		{
			case 0: return QVariant(tr("导弹型号"));
			case 1: return QVariant(tr("速度 "));
			case 2: return QVariant(tr("诱饵个数"));
			case 3: return QVariant(tr("模型文件"));
		}
	}
	
	return QVariant();
}

bool EnemyMissileTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == EditRole)
	{
		EnemyMissileInfo* missile = DataManager::getEnemyMissile(index.row());
		switch (index.column())
		{
			case 0: missile->name = value.toString().toStdString(); break;
			case 1: missile->speed = value.toFloat(); break;
			case 2: missile->baitCount = value.toInt(); break;
			case 3: missile->modelFile = value.toString().toStdString(); break;
		}
		DataManager::commitEditEnemyMissile(*missile);
	}
	return true;
}

bool EnemyMissileTableModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::newEnemyMissile();
	}
	endInsertRows();
	return true;
}

bool EnemyMissileTableModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::delEnemyMissile(row + i);
	}
	endRemoveRows();
	return true;
}




////////////////////////////////////////
// OurMissileTableModel
////////////////////////////////////////
ItemFlags OurMissileTableModel::flags(const QModelIndex & index) const
{
	return ItemIsSelectable | ItemIsEditable | ItemIsEnabled;
}

int OurMissileTableModel::rowCount(const QModelIndex & parent) const
{
	return DataManager::getOurMissileCount();
}

int OurMissileTableModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant OurMissileTableModel::data(const QModelIndex & index, int role) const
{
	switch (role)
	{
		case DisplayRole:
		case EditRole:
		{
			OurMissileInfo* missile = DataManager::getOurMissile(index.row());
			switch (index.column())
			{
				case 0: return QVariant(missile->name.c_str());
				case 1: return QVariant(missile->speed);
				case 2: return QVariant(missile->angleRate);
				case 3: return QVariant(missile->modelFile.c_str());
			}
		}
		case TextAlignmentRole:
		{
			switch (index.column())
			{
				case 0: return QVariant(AlignLeft | AlignVCenter);
				case 1: return QVariant(AlignRight | AlignVCenter);
				case 2: return QVariant(AlignRight | AlignVCenter);
				case 3: return QVariant(AlignLeft | AlignVCenter);
			}
		}
	}
	return QVariant();
}

QVariant OurMissileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Horizontal) { return QVariant(); }
	
	if (role == Qt::DisplayRole)
	{
		switch (section)
		{
			case 0: return QVariant(tr("导弹型号"));
			case 1: return QVariant(tr("速度"));
			case 2: return QVariant(tr("角加速度"));
			case 3: return QVariant(tr("模型文件"));
		}
	}
	
	return QVariant();
}

bool OurMissileTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == EditRole)
	{
		OurMissileInfo* missile = DataManager::getOurMissile(index.row());
		switch (index.column())
		{
			case 0: missile->name = value.toString().toStdString(); break;
			case 1: missile->speed = value.toFloat(); break;
			case 2: missile->angleRate = value.toFloat(); break;
			case 3: missile->modelFile = value.toString().toStdString(); break;
		}
		DataManager::commitEditOurMissile(*missile);
	}
	return true;
}

bool OurMissileTableModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::newOurMissile();
	}
	endInsertRows();
	return true;
}

bool OurMissileTableModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::delOurMissile(row + i);
	}
	endRemoveRows();
	return true;
}




////////////////////////////////////////
// LocationTableModel
////////////////////////////////////////
ItemFlags LocationTableModel::flags(const QModelIndex & index) const
{
	return ItemIsSelectable | ItemIsEditable | ItemIsEnabled;
}

int LocationTableModel::rowCount(const QModelIndex & parent) const
{
	return DataManager::getLocationCount();
}

int LocationTableModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant LocationTableModel::data(const QModelIndex & index, int role) const
{
	switch (role)
	{
		case DisplayRole:
		case EditRole:
		{
			Location* loc = DataManager::getLocation(index.row());
			switch (index.column())
			{
				case 0: return QVariant(loc->name.c_str());
				case 1:	return QVariant(loc->lon);
				case 2: return QVariant(loc->lat);
				case 3: return QVariant(loc->dscpt.c_str());
			}
		}
		case TextAlignmentRole:
		{
			switch (index.column())
			{
				case 0: return QVariant(AlignLeft | AlignVCenter);
				case 1: return QVariant(AlignRight | AlignVCenter);
				case 2: return QVariant(AlignRight | AlignVCenter);
				case 3: return QVariant(AlignLeft | AlignVCenter);
			}
		}
	}
	return QVariant();
}

QVariant LocationTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Horizontal) { return QVariant(); }
	
	if (role == Qt::DisplayRole)
	{
		switch (section)
		{
			case 0: return QVariant(tr("名称"));
			case 1: return QVariant(tr("经度"));
			case 2: return QVariant(tr("纬度"));
			case 3: return QVariant(tr("描述"));
		}
	}
	
	return QVariant();
}

bool LocationTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == EditRole)
	{
		Location* loc = DataManager::getLocation(index.row());
		switch (index.column())
		{
			case 0: loc->name = value.toString().toStdString(); break;
			case 1: loc->lon = value.toFloat(); break;
			case 2: loc->lat = value.toFloat(); break;
			case 3: loc->dscpt = value.toString().toStdString(); break;
				
			default:
				break;
		}
		DataManager::commitEditLocation(*loc);
	}
	return true;
}

bool LocationTableModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	DataManager::newLocation();
	endInsertRows();
	return true;
}

bool LocationTableModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::delLocation(row + i);
	}
	endRemoveRows();
	return true;
}
