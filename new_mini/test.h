#ifndef TEST_H
#define TEST_H

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



//���ö��߳�ȥ��




class WorkerThread : public QThread{
	
	Q_OBJECT
signals:
	void windowShow();

private:
	QWidget *win;
	QHBoxLayout *layout;
	QTextEdit* textEdit2;

public:
	WorkerThread(QObject *parent, QWidget* win1,QHBoxLayout* layout1,QTextEdit* textEdit2_)
		: QThread(parent)
		,win(win1)
		,layout(layout1)
		,textEdit2(textEdit2_)
		//,tmp2(tmp_)
	{

	}


protected:
	void run(){

		
		//layout->addWidget(textEdit2);
		//setCentralWidget(textEdit2);

		//saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), win);
		//connect(saveAction, SIGNAL(triggered()), win, SLOT(save()));
		////��ӵ��˵���
		//QMenu *file = menuBar()->addMenu(tr("&File"));
		//file->addAction(saveAction);

		////��ӵ�������
		//QToolBar *toolBar = addToolBar(tr("&File"));
		//toolBar->addAction(saveAction);
		//
		emit windowShow();
	}
		

};


//////////////////////////////////////////////////////////////////


class MainWindow : public QMainWindow{
	
	Q_OBJECT
public:
	void mfunc_parse();
	bool Search(QString s1,QString s2);

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	//void func_parse(QString s,QTextEdit* &textEdit2);

public slots:
	void onWindowShow(QWidget* win,QHBoxLayout *layout);
	

private slots:
		void open();
		void save();
		void parse();
		void lookedUp(const QHostInfo &host);  


private:
	QAction *openAction;
	QAction *saveAction;
	QAction *parseAction;

	QTextEdit* textEdit;
	QTextEdit* textEdit2;
	QMap< QString,QVector<QString> >m;
	QString str;  //���������ı�����
	QVector<QString>v2;  //Ԫ����ÿһС��ÿһ������
	QString tmp;  //���������Ϣ�ģ�+=�����


};





#endif // MAINWINDOW_H