#ifndef NEW_MINI_H
#define NEW_MINI_H

#include <QtGui/QMainWindow>
#include "ui_new_mini.h"

class new_mini : public QMainWindow
{
	Q_OBJECT

public:
	new_mini(QWidget *parent = 0, Qt::WFlags flags = 0);
	~new_mini();

private:
	Ui::new_miniClass ui;
};

#endif // NEW_MINI_H
