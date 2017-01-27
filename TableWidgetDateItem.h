#pragma once
#include "C:\Qt\Qt5.6.1\5.6\msvc2015_64\include\QtWidgets\qtablewidget.h"
class TableWidgetDateItem :
	public QTableWidgetItem
{
public:
	TableWidgetDateItem();
	virtual ~TableWidgetDateItem();

	void setData(int role, const QVariant & value);
	QVariant data(int role) const;

};

