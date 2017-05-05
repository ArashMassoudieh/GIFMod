#ifndef EXPRESSIONTABLEMODEL_H
#define EXPRESSIONTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
class GraphWidget;

struct ReactionTableModelPri;

class ReactionTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit ReactionTableModel(GraphWidget* mainGraphWidget, const QStringList& constituents, const QStringList& parameters,
		const QStringList& functions, const QStringList& physical, const QList<QStringList>& data = QList<QStringList>(), QObject* p = 0);
    ~ReactionTableModel();

signals:
    void invalidExpressoinDetected(const QString& msg);
	void wrongSymbolDetected(const QModelIndex&, const QString &sym);

public:
    QStringList constituents() const;
    QStringList functions() const;
	QStringList physicals() const;
    QStringList parameters() const;
    QStringList operators() const;
	bool validateExp(const QString& exp) const;
static	bool validateNetworkRXNExp(const QString &exp, GraphWidget *gw, const QStringList &functions, const QStringList &physicals);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parentt = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool removeRow(QString processName, int row);// int position, int rows, const QModelIndex &parent = QModelIndex());

    void addItem(int rowIndex, bool after);
    void removeItem(int currentRow);
	QList<QStringList> exportToExpession() const;
	GraphWidget *mainGraphWidget;

private:
    ReactionTableModelPri* d;
	QString wrongSymbol;
};

struct ReactionTableModelPri {
	ReactionTableModel* This;
	QStringList Words, Constituents, Parameters, Functions, Physicals;
	QList<QStringList> Data;

	QStringList Brackets, BinaryOperators;

	ReactionTableModelPri()
	{
		Brackets << "(" << ")";
		BinaryOperators << "^" << "*" << "/" << "+" << "-";
	}

	QStringList emptyRow()
	{
		QStringList list;
		for (int i = 0; i < Constituents.count() + 2; i++) {
			list.append("");
		}
		return list;
	}
	QString Export(const QString& s)
	{
		QString d;
		int l = 0, r = s.length();
		for (int i = 0; i < s.length();) {
			if (s[i].isSpace()) {
				i++;  continue;
			}
			l = i;
			// the first char must start with a letter or underscore
			if (s[i].isLetter() || s[i] == QChar('_')) {
				while (i < s.length() && (s[i].isLetter() || s[i] == QChar('_') || s[i].isNumber())) i++;
			}
			r = i;
			if (l == r) {
				d.append(s[i]); i++;
			}
			else {
				QString var = s.mid(l, r - l);
				if (Constituents.contains(var))
					d.append(QString("c[%1]").arg(var));
				else if (Parameters.contains(var))
					d.append(QString("p[%1]").arg(var));
				else if (Functions.contains(var))
					d.append(QString("f[%1]").arg(var));
				else if (Physicals.contains(var))
					d.append(QString("f[%1]").arg(var)); // ASK
				else
					d.append(var);
			}
		}
		return d;
	}

	QString Import(const QString& s)
	{
		QString d;
		int i = 0;
		while (i < s.length()) {
			int iStart = s.indexOf('[', i);
			int iEnd = s.indexOf(']', i);
			if (iStart > 0 && iEnd > 0) {
				d.append(s.mid(i, iStart - i - 1));
				int ind = s.mid(iStart + 1, iEnd - iStart - 1).toInt();
				QChar c = s.at(iStart - 1);
				QString var;
				switch (c.toLatin1()) {
				case 'c': var = Constituents.at(ind); break;
				case 'p': var = Parameters.at(ind); break;
				case 'f': var = Functions.at(ind); break;
				case 'g': var = Physicals.at(ind); break; //ASK
				}
				d.append(var);
				i = iEnd + 1;
			}
			else {
				d.append(s.right(s.length() - i)); break;
			}
		}
		return d;
	}
};


#endif // EXPRESSIONTABLEMODEL_H
