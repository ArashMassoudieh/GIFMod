#pragma once
#include "qabstractitemmodel.h"
#include <QString>
//#include "node.h"
//#include "GWidget.h"

class Node;
class GraphWidget;
class QTableView;

class ConstituentTableModelPlant:	public QAbstractTableModel
{
public:
	ConstituentTableModelPlant(Node *node, QTableView *qTable, GraphWidget *gWidget);
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	int rowCount(const QModelIndex & index = QModelIndex()) const;
	int columnCount(const QModelIndex & parent = QModelIndex()) const { 
		return 2; };
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return QString("Constituent");
				case 1:
					return QString("Value");
				}
			}
		}
		return QVariant();
	};
	Qt::ItemFlags flags(const QModelIndex & index) const{
		int row = index.row();
		int col = index.column();
		if (row == rowCount() - 1 && col > 0) return  0;
		QString particle = data(createIndex(index.row(), 1)).toString();
		if ((particle == "Soil" || particle == "Aqueous") && col == 2)
			return  0;
		
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	};
	~ConstituentTableModelPlant(){
		gWidget = NULL;
		node = NULL;
		qTable = NULL;
	};
	bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
	bool removeRows(int firstRow, int lastRow, const QModelIndex & parent = QModelIndex());
	void removeCurrentItem();
public slots:

private:
	GraphWidget *gWidget;
	Node *node;
	QTableView *qTable;
	bool addingRow = false;
};

