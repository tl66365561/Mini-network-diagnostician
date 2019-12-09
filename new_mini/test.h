#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QWidget>
#include <QMessageBox>
#include<QThread>
#include <QToolBar>
#include<fstream>
#include<QDebug>
#include<QPushButton>
#include <QValidator>
#include <QGridLayout>
#include <QFileDialog>
#include<QTextEdit>
#include<QString>
#include <QInputDialog>
#include <QList>
#include<QHostInfo>
#include <QHostAddress>
#include<windows.h>
#include <QtNetwork\qhostinfo.h>
#include <QDialog>
#include <QAbstractSocket>
#include <QTime>
#include <QTcpSocket>







class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	void mfunc_parse();
	bool Search(QString s1,QString s2);

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	//void func_parse(QString s,QTextEdit* &textEdit2);




private:
	QAction *openAction;
	QAction *saveAction;
	QAction *parseAction;

	QTextEdit* textEdit;
	QTextEdit* textEdit2;
	QMap< QString,QVector<QString> >m;
	QString str;  //用来传递文本内容
	QString tmp;  //用来诊断信息的（+=）输出
	QVector<QString>v2;  //元素是每一小段每一行内容


	private slots:
		void open();
		void save();
		void parse();
		void lookedUp(const QHostInfo &host);  


};






//class WorkerThread : public QThread
//{
//	Q_OBJECT
//
//private:
//	QWidget *win;
//	QHBoxLayout *layout;
////
////private slots:
////	void lookedUp(const QHostInfo &host);  
////
////
////
//public:
//	WorkerThread(QObject *parent, QWidget*& win1,QHBoxLayout*& layout1)
//		: QThread(parent)
//		,win(win1)
//		,layout(layout1)
//	{
//		
//	}
//
//protected:
//	void run()
//{
//	win->setLayout(layout); 
//	win->show();
//		
//}
//	
//};

#endif // MAINWINDOW_H