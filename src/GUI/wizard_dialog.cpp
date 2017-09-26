#include "wizard_dialog.h"
#include "qfiledialog.h"
#include "mainwindow.h"
#include "imageviewer.h"
#include "qmessagebox.h"
#include "commandwindow.h"
#include "filebutton.h"

Wizard_Dialog::Wizard_Dialog(QString *template_selected, MainWindow *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	wiz = Wizard_Script_Reader(*template_selected);
	parent->mainGraphWidget->log(*template_selected + " was selected");
	_parent = parent; 
	mproplist = parent->mainGraphWidget->mList;
	setup_form();
	connect(ui.ButtonNext, SIGNAL(clicked()), this, SLOT(on_next_clicked()));
	connect(ui.Button_Ok, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
	connect(ui.Button_create_script, SIGNAL(clicked()), this, SLOT(on_create_script_clicked()));
	connect(ui.Button_Cancel, SIGNAL(clicked()), this, SLOT(on_cancel_clicked()));
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tab_changed()));
	_template_selected = *template_selected;
}

void Wizard_Dialog::on_next_clicked()
{
	tabWidget->setCurrentIndex(min(tabWidget->currentIndex()+1,tabWidget->count()-1));
	if (tabWidget->currentIndex() == tabWidget->count() - 1)
		ui.ButtonNext->setEnabled(false);
	else 
		ui.ButtonNext->setEnabled(true);
}

void Wizard_Dialog::on_ok_clicked()
{
	ui.Button_Ok->setEnabled(false);
	wiz = Wizard_Script_Reader(_template_selected);
	wiz.mproplist = mproplist;
	set_wiz_parameters();
	QList<CCommand> commands = wiz.get_script_commands();
	commandWindow *cwindow = new commandWindow(_parent->mainGraphWidget);
	QVariantList output = _parent->mainGraphWidget->runCommands(commands);
	for (int i=0; i<commands.size(); i++)
		cwindow->append(commands[i].toQString());
	
	cwindow->show();
	

}

void Wizard_Dialog::on_create_script_clicked()
{
	wiz = Wizard_Script_Reader(_template_selected);
	wiz.mproplist = mproplist;
	set_wiz_parameters();
	QList<CCommand> commands = wiz.get_script_commands();
	save_script(commands);
	
}

void Wizard_Dialog::save_script(QList<CCommand> commands)
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Open Green InfraStructure Script Text"), "",
		tr("Script Text (*.scr);;All Files (*)"));
	if (fileName == "") return;

	QFile scriptfile(fileName);
	if (!scriptfile.open(QIODevice::WriteOnly)) {
		QMessageBox msgBox;
		msgBox.setText("File '" + fileName + "' was not found");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
	}

	QTextStream output_stream(&scriptfile);
	for (int i = 0; i < commands.size(); i++)
		output_stream << commands[i].toQString() << endl;

	scriptfile.close();

}

void Wizard_Dialog::set_wiz_parameters()
{
	//QMap<QString, QLineEdit*> textedits;
	//QMap<QString, UnitTextBox3*> unittextedits;
	//QMap<QString, QComboBox*>  comboboxes;
	//QMap<QString, QDateTimeEdit*>  datetimepickers;
	//QMap<QString, QLineEdit*>  filetextedits;
	//QMap<QString, QSpinBox*>  spinboxes;
	//QMap<QString, QCheckBox*>  checkboxes;
	for (QString key : unittextedits.keys())
	{
		XString x(unittextedits[key]->text());
		x.setUnit(unittextedits[key]->unit());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
		
	}
	for (QString key : comboboxes.keys())
	{
		XString x(comboboxes[key]->currentText());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
	}
	for (QString key : filetextedits.keys())
	{
		XString x(filetextedits[key]->text());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
	}
	for (QString key : spinboxes.keys())
	{
		XString x(spinboxes[key]->text());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
	}
	for (QString key : checkboxes.keys())
	{
		XString x(checkboxes[key]->isChecked());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
	}
	for (QString key : datetimepickers.keys())
	{
		XString x(datetimepickers[key]->text());
		wiz.get_parameters()[key].set_value(x);
		qDebug() << key << "was set to" << x.toQString() << endl;
	}


}

void Wizard_Dialog::on_tab_changed()
{
	if (tabWidget->currentIndex() == tabWidget->count() - 1)
		ui.ButtonNext->setEnabled(false);
	else
		ui.ButtonNext->setEnabled(true);
}


void Wizard_Dialog::on_cancel_clicked()
{
	this->close(); 
}



Wizard_Dialog::~Wizard_Dialog()
{

}


void Wizard_Dialog::setup_form()
{
	qDebug() << "Inside setup_form()" << endl;
	tabWidget = new QTabWidget();
	tabWidget->setObjectName(QStringLiteral("tabWidget"));
	ui.verticalLayout_2->addWidget(tabWidget);
	QString icon = wiz.get_script_icon();
	
	ImageViewer *image = new ImageViewer();
	image->setObjectName(QStringLiteral("graphicsView"));
	image->loadFile(QApplication::applicationDirPath() + "/templates/" + wiz.get_script_icon());
	ui.horizontalLayout_2->addWidget(image);
	
	for (QString e : wiz.get_parameter_groups().keys())
	{
		qDebug() << "key1: " << e << endl;
		QWidget* tab = new QWidget();
		qDebug() << "desc " << wiz.get_parameter_groups()[e].get_description() << endl;
		tab->setObjectName(wiz.get_parameter_groups()[e].get_description());
		qDebug() << "tab_added " << wiz.get_parameter_groups()[e].get_description() << endl;
		tabs[e] = tab;
		
		QString description = wiz.get_parameter_groups()[e].get_description();
		tabWidget->addTab(tab, description);

		formLayout = new QFormLayout(tab);
		formLayout->setSpacing(6);
		formLayout->setContentsMargins(11, 11, 11, 11);
		formLayout->setObjectName(QStringLiteral("formLayout"));
		
		int i = 0;
		for (QString p : wiz.get_parameter_groups()[e].get_parameters())
		{
			qDebug() << "key2: " << p << endl;
			i++;
			QLabel *label = new QLabel(tab);
			label->setText(wiz.get_parameters()[p].get_question());
			label->setObjectName(wiz.get_parameters()[p].get_question());
			labels[p] = label;
			formLayout->setWidget(i, QFormLayout::LabelRole, label);

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "integer")
			{
				QSpinBox *spinbox = new QSpinBox(tab);
				spinbox->setObjectName(wiz.get_parameters()[p].get_name());
				if (wiz.get_parameters()[p].get_parameters().contains("default"))
					spinbox->setValue(wiz.get_parameters()[p].get_parameter("default").value.toInt());
				spinboxes[p] = spinbox;
				formLayout->setWidget(i, QFormLayout::FieldRole, spinbox);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "text")
			{
				QLineEdit *textEdit = new QLineEdit(tab);
				textEdit->setObjectName(wiz.get_parameters()[p].get_name());
				if (wiz.get_parameters()[p].get_parameters().contains("default"))
					textEdit->text() = wiz.get_parameters()[p].get_parameter("default").value;
				textedits[p] = textEdit;
				formLayout->setWidget(i, QFormLayout::FieldRole, textEdit);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "float")
			{
				mProp _filter;
				_filter.setstar();
				if (wiz.get_parameters()[p].get_parameter("object_type").value.trimmed()!="")
					_filter.ObjectType = wiz.get_parameters()[p].get_parameter("object_type").value.trimmed();
				_filter.VariableName = wiz.get_parameters()[p].get_parameter("prop_list_item").value.trimmed();
				mPropList m = mproplist->filter_abv(_filter); 
				XString xstr;
				if (wiz.get_parameters()[p].get_parameters().contains("default"))
					xstr = wiz.get_parameters()[p].get_parameter("default").value;
				if (m.size())
				{
					xstr.setString(m.DefaultValueLists()[0][0]);
					xstr.unitsList = m.VariableUnits()[0].split(";");
					xstr.defaultUnit = m.VariableUnits()[0].split(";").first();
		
				}
				UnitTextBox3 *unittextEdit = new UnitTextBox3(xstr,tab);
				unittextEdit->setObjectName(wiz.get_parameters()[p].get_name());
				unittextedits[p] = unittextEdit;
				formLayout->setWidget(i, QFormLayout::FieldRole, unittextEdit);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "combo_box")
			{
				QComboBox *combobox = new QComboBox(tab);
				combobox->setObjectName(wiz.get_parameters()[p].get_name());
				if (wiz.get_parameters()[p].get_parameters().contains("default"))
					combobox->setCurrentText(wiz.get_parameters()[p].get_parameter("default").value);
				
				mProp _filter;
				_filter.setstar();
				_filter.ObjectType = wiz.get_parameters()[p].get_parameter("object_type").value.trimmed();
				QStringList a = mproplist->filter_abv(_filter).SubTypes();
				combobox->addItems(a);
				comboboxes[p] = combobox;
				formLayout->setWidget(i, QFormLayout::FieldRole, combobox);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "date_time")
			{
				QDateTimeEdit *datetimeedit = new QDateTimeEdit(tab);
				datetimeedit->setObjectName(wiz.get_parameters()[p].get_name());
				datetimepickers[p] = datetimeedit;
				formLayout->setWidget(i, QFormLayout::FieldRole, datetimeedit);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "filename")
			{
				FileButton *filelineeedit = new FileButton(tab);
				filelineeedit->setObjectName(wiz.get_parameters()[p].get_name());
				filetextedits[p] = filelineeedit;
				formLayout->setWidget(i, QFormLayout::FieldRole, filelineeedit);
			}

			if (wiz.get_parameters()[p].get_role().toLower().trimmed() == "yesno")
			{
				QCheckBox *checkbox = new QCheckBox(tab);
				checkbox->setObjectName(wiz.get_parameters()[p].get_name());
				checkboxes[p] = checkbox;
				formLayout->setWidget(i, QFormLayout::FieldRole, checkbox);
			}

		}


	}

	//ui.horizontalLayout_2->addWidget(tabWidget);
	ui.horizontalLayout_2->setStretch(0, 70);
	ui.horizontalLayout_2->setStretch(1, 30);
}
