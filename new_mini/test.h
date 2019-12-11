#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include<windows.h>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include<QThread>
#include <QToolBar>
#include <QTime>
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

#include "workthread.h"




//弹窗类
class MainWindow2 : public QMainWindow{

	Q_OBJECT
public:
	MainWindow2(QWidget *parent = 0);
	~MainWindow2();
	void Show_window(QString content);
	void mfunc_parse(QVector<QString>v,QMap< QString,QVector<QString> >m);

private:
	QAction *saveAction;	



private:
	QTextEdit* textEdit2;        //文本框指针
	WorkerThread thread_;        //线程类对象


	private slots:		
		void save();
		void onWindowShow(QString text);

};








//主窗口类
class MainWindow : public QMainWindow{

	Q_OBJECT
public:
	//void mfunc_parse();
	//bool Search(QString s1,QString s2);

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	//void func_parse(QString s,QTextEdit* &textEdit2);
	
    void RequsetNewthread(QVector<QString> v, QMap<QString,QVector<QString>>m);


private slots:		
	void open();
	void save();
	void parse();		


protected:
	void funcParse();


private:
	QAction *saveAction;	
	QAction *openAction;
	QAction *parseAction;
	QTextEdit* textEdit;
	
	QString path; //保存打开文件的路径
	QString str;  //用来传递文本内容
	QVector<QString>v1;//元素是每一段
	QVector<QString>v2;  //元素是每一小段每一行内容
	MainWindow2 win2;
	QMap< QString,QVector<QString> >m;


	//static QString tmp;  //用来诊断信息的（+=）输出

};







#endif // MAINWINDOW_H