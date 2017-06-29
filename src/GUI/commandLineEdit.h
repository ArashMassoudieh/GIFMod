#pragma once
#include "qlineedit.h"
#include "qevent.h"
#include "qcompleter.h"
#include "qtextedit.h"

class commandLineEdit : public QTextEdit
{
	Q_OBJECT

public:
	explicit commandLineEdit(QWidget *parent = Q_NULLPTR);
	void setCompleter(QCompleter *c);
	QCompleter *completer() const;
	QString text();
protected:
	void keyPressEvent(QKeyEvent *e) override;
	void focusInEvent(QFocusEvent *e) override;

	private slots:
	void insertCompletion(const QString &completion);

private:
	QString textUnderCursor() const;

private:
	QCompleter *c;
	
/*	struct expEditorPri {
		//ReactionTableModel* Model;
		QCompleter* Comp;
		QStringList Words;
		expEditorPri() : Comp(0), Editing(false) {}
		//StatusViewer* Statusbar;
		bool Editing;
		QString OldExpression;
	};

	void setupCompleter()
	{
		if (d->Comp) {
			d->Comp->deleteLater();
			d->Comp = 0;
		}

		//d->Words << d->Model->constituents() << d->Model->parameters() << d->Model->physicals() << d->Model->functions();
		d->Comp = new QCompleter(d->Words, this);
		d->Comp->setWidget(this);
		d->Comp->setCompletionMode(QCompleter::PopupCompletion);
		d->Comp->setCaseSensitivity(Qt::CaseSensitive);
		connect(d->Comp, SIGNAL(activated(QString)), this, SLOT(onCompletorActivated(QString)));
	}

/*

	void focusInEvent(QFocusEvent *e)
	{
		qDebug() << "FocusIn event";
		if (d->Comp) {
			d->Comp->setWidget(this);
		}
		if (!d->Editing) {
			d->OldExpression = text();
		}
		d->Editing = true;
		QLineEdit::focusInEvent(e);
	}


	void focusOutEvent(QFocusEvent *e)
	{
		qDebug() << "FocusOut event";
		d->Editing = false;
		QLineEdit::focusOutEvent(e);
	}


	void replaceWordUnderCursorWith(const QString &c)
	{
		QString t = text();
		int i = cursorPosition() - 1, r, l;
		while (i < t.length() && (t[i].isLetter() || t[i] == QChar('_') || t[i].isNumber() || t[i] == '.' || t[i] == '~')) i++;
		r = i - 1;
		i = cursorPosition() - 1;
		while (i >= 0 && (t[i].isLetter() || t[i] == QChar('_') || t[i].isNumber() || t[i] == '.' || t[i] == '~')) i--;
		l = i + 1;
		t = t.replace(l, r - l + 1, c);
		setText(t);
	}


	QString cursorWord(const QString &sentence) const
	{
		int ind = lastIndexOfNonVariable(sentence.left(cursorPosition()));
		QString word = sentence.mid(ind + 1, cursorPosition() - ind - 1);
		return word;
	}

	void keyPressEvent(QKeyEvent *e)
	{
		QLineEdit::keyPressEvent(e);
		QCompleter* c = d->Comp;
		if (!c) {
			return;
		}
		else {
			if (c->popup()->isVisible() && e->key() == Qt::Key_Escape) {
				setText(d->OldExpression); return;
			}
		}

		QChar ck(e->key());
		QStringList Brackets;	Brackets << "(" << ")";
		QStringList BinaryOperators;	BinaryOperators << "^" << "*" << "/" << "+" << "-";
		QStringList operators;
		operators << Brackets << BinaryOperators;

		QList<int> escapeKeys; escapeKeys << Qt::Key_Backspace << Qt::Key_Delete << Qt::Key_Enter << Qt::Key_Return
			<< Qt::Key_Left << Qt::Key_Right << Qt::Key_Up << Qt::Key_Down
			<< Qt::Key_Control << Qt::Key_Alt << Qt::Key_Shift << Qt::Key_CapsLock
			<< Qt::Key_Escape << Qt::Key_Underscore << 46;

		if (!escapeKeys.contains(e->key()) && !ck.isLetterOrNumber() && !operators.contains(QString(ck))) {
			qDebug() << e->key() << int(Qt::Key_Enter);
			backspace(); return;
		}

		c->setCompletionPrefix(cursorWord(this->text()));
		if (c->completionPrefix().length() < 0) {
			c->popup()->hide(); return;
		}
		if (c->completionCount() < 1) {
			if (QChar(e->key()).isLetter()) {
				backspace();
			}
		}

		c->complete();
	}


	void onCompletorActivated(const QString &arg)
	{
		int ind = lastIndexOfNonVariable(text().left(cursorPosition()));
		setText(text().replace(ind + 1, cursorPosition() - ind - 1, arg));
	}


	*/


private slots:
	void keyReleaseEvent(QKeyEvent *e)
	{
		if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)
			emit navigate(e);
	}
	
signals:
	void navigate(QKeyEvent*);
};