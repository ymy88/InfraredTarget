//
//  TableModel.h
//  InfraredTarget
//
//  Created by Ymy on 13-8-16.
//  Copyright (c) 2013年 Ymy. All rights reserved.
//

#ifndef __InfraredTarget__TableModel__
#define __InfraredTarget__TableModel__

#include <PSDFViewQt/PSDFViewQt.h>
#include <QtCore/QAbstractTableModel>

class EnemyMissileTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	EnemyMissileTableModel(){}	
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)							const;
	virtual int			rowCount(const QModelIndex & parent)						const;
	virtual int			columnCount(const QModelIndex & parent)						const;
	virtual QVariant	data(const QModelIndex & index, int role)					const;
	virtual QVariant	headerData(int section, Orientation orientation, int role)	const;
	
	virtual bool		setData(const QModelIndex & index, const QVariant & value, int role);
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};


class OurMissileTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	OurMissileTableModel(){}
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)							const;
	virtual int			rowCount(const QModelIndex & parent)						const;
	virtual int			columnCount(const QModelIndex & parent)						const;
	virtual QVariant	data(const QModelIndex & index, int role)					const;
	virtual QVariant	headerData(int section, Orientation orientation, int role)	const;
	
	virtual bool		setData(const QModelIndex & index, const QVariant & value, int role);
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};


class LocationTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	LocationTableModel(){}
	
public:
	virtual ItemFlags	flags(const QModelIndex & index)							const;
	virtual int			rowCount(const QModelIndex & parent)						const;
	virtual int			columnCount(const QModelIndex & parent)						const;
	virtual QVariant	data(const QModelIndex & index, int role)					const;
	virtual QVariant	headerData(int section, Orientation orientation, int role)	const;
	
	virtual bool		setData(const QModelIndex & index, const QVariant & value, int role);
	virtual bool		insertRows(int row, int count, const QModelIndex & parent);
	virtual bool		removeRows(int row, int count, const QModelIndex & parent);
};

#endif /* defined(__InfraredTarget__TableModel__) */
