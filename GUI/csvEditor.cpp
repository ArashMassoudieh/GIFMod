#include "csvEditor.h"
#include "ui_csvEditor.h"

#include "qdatetime.h"
#include "qfiledialog.h"
#include "mainwindow.h"
#include "GWidget.h"
#include "qmessagebox.h"
#include <iostream>
#include <fstream>
#include "qmenu.h"

csvEditor::csvEditor(MainWindow *parent, QString title, QString fileName, QString fileType, bool modal) :
	QDialog(parent),
	ui(new Ui::csvEditor)
{
	ui->setupUi(this);
	wtitle = title;
	setWindowTitle(wtitle);
	this->fileType = fileType;
	this->fileName = fileName;
	mainWindow = parent;
	setModal(modal);
	load(fileName);
	show();
//	load("D:/a.csv");
	ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
	if (ui->tableWidget->columnCount() < 2)
		ui->tableWidget->setColumnCount(2);
	if (ui->tableWidget->rowCount() < 1)
		ui->tableWidget->setRowCount(1);

}

void csvEditor::showContextMenu(const QPoint&p)
{
//	QTableWidgetItem *item = ui->tableWidget->itemAt(p);
//	if (!item)
//		return;
//	int row = ui->tableWidget->row(item);
//	int col = ui->tableWidget->column(item);

	int row = ui->tableWidget->rowAt(p.y());
	int col = ui->tableWidget->columnAt(p.x());

	if (row == -1 || col == -1)
		return;
	QMenu menu;
	menu.addAction("insert row");
	menu.addAction("delete row");
	menu.addAction("insert column");
	menu.addAction("delete column");
	//menu.addAction("");
	//menu.addAction("");
	//menu.addAction("");

	QAction *ac = menu.exec(mapToGlobal(p));
	if (!ac)
		return;

	if (ac->text() == "insert row")
		ui->tableWidget->insertRow(row);

	if (ac->text() == "insert column")
		ui->tableWidget->insertColumn(col);
	
	if (ac->text() == "delete row")
		ui->tableWidget->removeRow(row);
	
	if (ac->text() == "delete column")
		ui->tableWidget->removeColumn(col);


}

void csvEditor::load(QString fileName)
{
	if (fileName.size())
		this->fileName = fileName;
	ifstream file(fileName.toStdString());
	if (!file.good())
		return;
	string line;
	ui->tableWidget->clear();
	int row = 0;
	while (file.eof() == false)
	{
		getline(file, line);
		QStringList list = QString::fromStdString(line).split(",");
		for (int col = 0; col < list.size(); col++)
		{
			if (ui->tableWidget->rowCount() < row + 1)
				ui->tableWidget->setRowCount(row + 1);
			if (ui->tableWidget->columnCount() < col + 1)
				ui->tableWidget->setColumnCount(col + 1);
			ui->tableWidget->setItem(row, col, new QTableWidgetItem(list[col]));
			qDebug() << row << col;
		}
		row++;
	}
	file.close();
	dataChanged = false;
}

void csvEditor::save(QString fileName)
{
	ofstream file(fileName.toStdString());
	if (!file.good()) 
		return;

	for (int i = 0; i < ui->tableWidget->rowCount(); i++)
	{
		QStringList list;
		for (int j = 0; j < ui->tableWidget->columnCount(); j++)
		{
			qDebug() << i << j;
			list.append(ui->tableWidget->item(i, j) ? ui->tableWidget->item(i, j)->text() : "");
			qDebug() << i<<j<< (ui->tableWidget->item(i, j) ? ui->tableWidget->item(i, j)->text() : "");
		}
		QString line = list.join(",");
		file << line.toStdString() << "\n";
	}
	file.close();
	dataChanged = false;
}


void csvEditor::append(QString text)
{
	//ui->textEdit->append(QTime::currentTime().toString().append(", ").append(text));
	//QApplication::processEvents();
}
void csvEditor::append(vector<string> text)
{
//	QStringList list;
//	for (int i = 0; i < text.size(); i++)
//		list.append(QString::fromStdString(text[i]));
//	append(list);
}
void csvEditor::setHtml(vector<string> text)
{
//	QString html;
//	for (int i = 0; i < text.size(); i++)
//		html.append(QString::fromStdString(text[i]));
///	ui->textEdit->setHtml(html);
}
void csvEditor::append(QStringList text)
{
//	for each (QString line in text)
//		ui->textEdit->append(line);
}

void csvEditor::on_buttonBox_clicked(QAbstractButton * button)
{
	if (button->text() == "Reset")
		ui->tableWidget->clear();
	if (button->text() == "Save")
	{
		QString file = (!(fileName.isEmpty() || fileName=="Unititled.csv")) ? fileName : QFileDialog::getSaveFileName(this,
			tr("Save ").append(mainWindow->applicationName), mainWindow->modelPathname().append("/Untitled.csv"),
			fileType + ";;All Files (*)");
		if (file.isEmpty())
			return;
		else {
			save(file);
		}
	}

//			QFile file(fileName);
//			if (!file.open(QIODevice::WriteOnly)) {
//				QMessageBox::information(this, tr("Unable to open file"),
//					file.errorString());
//				return;
//			}

			//			QDataStream out(&file);
//			std::ofstream out;
//			out.open(fileName.toStdString());
//
//			out << mainWindow->applicationName.toLatin1().toStdString() << "\n";
//			XString text = ui->textEdit->toPlainText();
//			out << text.reformBack().toStdString();
//			out.close();
//			logfilename = fileName;
//			setWindowTitle(OnlyFilename(fileName).append(" - ").append(wtitle));
//			return;
//		}
//	}
}
void csvEditor::writetotempfile()
{
//	QString fileName = (!logfilename.isEmpty()) ? logfilename : mainWindow->modelPathname() + "/temp.log";
//	QFile file(fileName);
//	if (!file.open(QIODevice::WriteOnly)) {
///		return;
//	}
	//	QDataStream out(&file);
//	std::ofstream out;
//	out.open(fileName.toStdString());
//	out << mainWindow->applicationName.toStdString() + " temp log file." << "\n";
//	XString text = ui->textEdit->toPlainText();
//	out << text.reformBack().toStdString();
//	out.close();
//	return;
}

QString csvEditor::text()
{
	QString text;
	for (int i = 0; i < ui->tableWidget->rowCount(); i++)
	{
		QStringList list;
		for (int j = 0; j < ui->tableWidget->columnCount(); j++)
			list.append(ui->tableWidget->itemAt(i, j)->text());
		QString line = list.join(",");
		text.append(line).append("\n");
	}
	return text;
}
