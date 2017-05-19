#include "commandWindow.h"
#include "ui_commandWindow.h"
#include "qdatetime.h"
#include "qfiledialog.h"
#include "mainwindow.h"
#include "GWidget.h"
#include "qmessagebox.h"
#include <iostream>
#include <fstream>
#include "texToHtml.h"

commandWindow::commandWindow(GraphWidget *parent) :
  QDialog(parent),
  ui(new Ui::commandWindow)
{
  ui->setupUi(this);

  connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(newCommandSubmitted()));
  connect(ui->lineEdit, SIGNAL(navigate(QKeyEvent *)), this, SLOT(commandKeyRelease(QKeyEvent *)));

 // wtitle = title;
 // setWindowTitle(wtitle);
 // this->helpFile = helpFile;
  //alternateHelpFile = parent->defaultDir().toStdString() + "/" + helpFile;
  this->parent = parent;
  //  ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
 // ui->textEdit->
 // if (!loadHelpFile(alternateHelpFile))
//	  loadHelpFile(helpFile);
 // ui->save->hide();
 // updateButtons();
}
void commandWindow::newCommandSubmitted()
{
	commandsHistory.append(ui->lineEdit->text());
	nextIndex = commandsHistory.count() - 1;
	prevIndex = nextIndex;
	QString result = parent->runCommand(ui->lineEdit->text()).toString();

	ui->textEdit->append(QString(">%1").arg(ui->lineEdit->text()));
	ui->textEdit->append(result);
	ui->textEdit->append("\n");

	qDebug() << ui->textEdit->toPlainText();
	ui->lineEdit->setText("");
}

//void commandWindow::writetotempfile()
//{
//}

void commandWindow::commandKeyRelease(QKeyEvent *e)
{
	qDebug() << prevIndex << nextIndex;

/*	if (prevIndex < 0)
		prevIndex = 0;
	if (nextIndex > commandsHistory.count() - 1)
		nextIndex = commandsHistory.count() - 1;
	qDebug() << prevIndex << nextIndex;
	*/
	int index;
	if (e->key() == Qt::Key_Up)
	{
		index = prevIndex--;
		prevIndex = max(0, prevIndex);
		nextIndex = index + 1;
		nextIndex = min(commandsHistory.count() - 1, nextIndex);
	}
	if (e->key() == Qt::Key_Down)
	{
		index = nextIndex++;
		nextIndex = min(commandsHistory.count() - 1, nextIndex);
		prevIndex = index - 1;
		prevIndex = max(0, prevIndex);
	}

	qDebug() << prevIndex << index << nextIndex;
	ui->lineEdit->setText(commandsHistory[index]);
}
