#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class QCompleter;

class CommandTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	CommandTextEdit(QWidget *parent = 0);
	~CommandTextEdit();

	void setCompleter(QCompleter *c);
	QCompleter *completer() const;

protected:
	void keyPressEvent(QKeyEvent *e) override;
	void focusInEvent(QFocusEvent *e) override;

	private slots:
	void insertCompletion(const QString &completion);

private:
	QString textUnderCursor() const;

private:
	QCompleter *c;
};

#endif // TEXTEDIT_H
