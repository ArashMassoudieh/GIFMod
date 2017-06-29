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

#include "scriptingengine.h"
commandWindow::commandWindow(GraphWidget *parent) :
	QDialog(parent),
	ui(new Ui::commandWindow)
{
	
	ui->setupUi(this);
	ui->textEdit->setEnabled(false);
	
	QStringList wordList;
	wordList << "alpha" << "omega" << "omicron" << "zeta";

	completer = new QCompleter(wordList, this);
	//completer = new QCompleter(this);
	//completer->setModel(modelFromFile(":/resources/wordlist.txt"));

	completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setWrapAround(false);
	ui->lineEdit->setCompleter(completer);

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
	QString result;
	commandsHistory.append(ui->lineEdit->text());
	nextIndex = commandsHistory.count() - 1;
	prevIndex = nextIndex;
	//if (ui->toolButtonBasicMode->isChecked()) {
		result = parent->runCommand(ui->lineEdit->text()).toString();
	//}
	/*else {
		QString code = ui->lineEdit->text().toStdString().data();		
		ScriptingEngine::instance()->eval(code, result);
		// result = parent->mainWindow->m_scriptPad.data()->runScript(ui->lineEdit->text(),false);
	}*/
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

void commandWindow::on_toolButtonScriptMode_toggled(bool checked)
{
}

void commandWindow::on_toolButtonBasicMode_toggled(bool checked)
{
}
