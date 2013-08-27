//
//  ListModel.cpp
//  InfraredTarget
//
//  Created by Ymy on 13-8-19.
//  Copyright (c) 2013年 Ymy. All rights reserved.
//

#include "StdAfx.h"
#include "ListModel.h"
#include <GlobalConfig.h>
#include <QtGui/QIcon>

ItemFlags PresetListModel::flags(const QModelIndex & index) const
{
	return ItemIsEnabled | ItemIsSelectable | ItemIsEditable;
}

int PresetListModel::rowCount(const QModelIndex & parent) const
{
	return DataManager::getPresetCount();
}

QVariant PresetListModel::data(const QModelIndex & index, int role) const
{
	Situation* preset = DataManager::getPreset(index.row());
	if (role == DisplayRole)
	{
		if (!preset->isValid())
		{
			return QVariant(QString::fromUtf8("新的想定\n或想定设置不正确"));
		}
		
		QString str;
		str.append(preset->enemy.missile->name.c_str());
		str.append(" (");
		str.append(preset->enemy.loc->name.c_str());
		str.append(")\n");
		str.append(preset->our.missile->name.c_str());
		str.append(" (");
		str.append(preset->our.loc->name.c_str());
		str.append(")");
		
		return QVariant(str);
	}
	else if (role == DecorationRole)
	{
		if (preset->isValid())
		{
			QIcon icon;
			icon.addFile(QString::fromUtf8(":/InfraredSimulator/resource/listIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
			return QVariant(icon);
		}
	}
	return QVariant();
}

bool PresetListModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::newPreset();
	}
	endInsertRows();
	return true;
}

bool PresetListModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	for (int i = 0; i < count; ++i)
	{
		DataManager::delPreset(row+i);
	}
	endRemoveRows();
	return true;
}


//////////////////////////////////////
// EnemyMissileComboModel
//////////////////////////////////////
ItemFlags EnemyMissileComboModel::flags(const QModelIndex & index) const
{
	return ItemIsEnabled | ItemIsSelectable | ItemIsEditable;
}

int EnemyMissileComboModel::rowCount(const QModelIndex & parent) const
{
	int c = DataManager::getEnemyMissileCount();
	return c;
}

QVariant EnemyMissileComboModel::data(const QModelIndex & index, int role) const
{
	if (role == DisplayRole)
	{
		return QVariant(DataManager::getEnemyMissile(index.row())->name.c_str());
	}
	return QVariant();
}

bool EnemyMissileComboModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	endInsertRows();
	return true;
}

bool EnemyMissileComboModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	endRemoveRows();
	return true;
}


//////////////////////////////////////
// OurMissileComboModel
//////////////////////////////////////
ItemFlags OurMissileComboModel::flags(const QModelIndex & index) const
{
	return ItemIsEnabled | ItemIsSelectable | ItemIsEditable;
}

int OurMissileComboModel::rowCount(const QModelIndex & parent) const
{
	int c = DataManager::getOurMissileCount();
	return c;
}

QVariant OurMissileComboModel::data(const QModelIndex & index, int role) const
{
	if (role == DisplayRole)
	{
		return QVariant(DataManager::getOurMissile(index.row())->name.c_str());
	}
	return QVariant();
}

bool OurMissileComboModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	endInsertRows();
	return true;
}

bool OurMissileComboModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	endRemoveRows();
	return true;
}


//////////////////////////////////////
// LocationComboModel
//////////////////////////////////////
ItemFlags LocationComboModel::flags(const QModelIndex & index) const
{
	return ItemIsEnabled | ItemIsSelectable | ItemIsEditable;
}

int LocationComboModel::rowCount(const QModelIndex & parent) const
{
	int c = DataManager::getLocationCount();
	return c;
}

QVariant LocationComboModel::data(const QModelIndex & index, int role) const
{
	if (role == DisplayRole)
	{
		return QVariant(DataManager::getLocation(index.row())->name.c_str());
	}
	return QVariant();
}

bool LocationComboModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row+count-1);
	endInsertRows();
	return true;
}

bool LocationComboModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row+count-1);
	endRemoveRows();
	return true;
}
