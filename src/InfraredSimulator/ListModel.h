//
//  ListModel.h
//  InfraredTarget
//
//  Created by Ymy on 13-8-19.
//  Copyright (c) 2013年 Ymy. All rights reserved.
//

#ifndef __InfraredTarget__ListModel__
#define __InfraredTarget__ListModel__

#include <PSDFViewQt/PSDFViewQt.h>
#include <QtCore/QAbstractListModel>
#include <GlobalConfig.h>


class PresetListModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	PresetListModel(){}
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)			const;
	virtual int			rowCount(const QModelIndex & parent)		const;
	virtual QVariant	data(const QModelIndex & index, int role)	const;
	
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};

class EnemyMissileComboModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)			const;
	virtual int			rowCount(const QModelIndex & parent)		const;
	virtual QVariant	data(const QModelIndex & index, int role)	const;
	
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};

class OurMissileComboModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)			const;
	virtual int			rowCount(const QModelIndex & parent)		const;
	virtual QVariant	data(const QModelIndex & index, int role)	const;
	
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};

class LocationComboModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	LocationComboModel(): _lastCount(0) {}
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)			const;
	virtual int			rowCount(const QModelIndex & parent)		const;
	virtual QVariant	data(const QModelIndex & index, int role)	const;
	
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
	
private:
	int	_lastCount;
};

#endif /* defined(__InfraredTarget__ListModel__) */
