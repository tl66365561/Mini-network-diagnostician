#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QMap>
#include <QString>
#include <QTcpSocket>
#include<QHostInfo>
#include <windows.h>
#include <QProgressDialog>
#include <QDebug>
#include <QHostAddress>
#include <QtNetwork\qhostinfo.h>
#include <QTcpSocket>
#include <QMessageBox>
#include<QMutex>
#include <time.h>
#include <QAbstractSocket>
#include <QTimer>
#include<QProgressDialog>
#include "LOG.h"
//#include "Log.hpp"




class WorkerThread : public QThread{

	Q_OBJECT
signals:
	void windowShow(QString text);

private:
	QVector<QString>_v1;   //元素是每一段
	QVector<QString>_v2;  //元素是每一小段每一行内容
	QVector<QString>_domain; //存储每一段的域名部分
	QMap< QString,QVector<QString> >_m;
	QString _text;
	QProgressDialog* progress;
	int count;
	LOG* log;
	//QTimer *timer;
	QMutex mutex;

private slots:
		void lookedUp(const QHostInfo &host);  

public:
	bool Search(QString s1,QString s2);
	WorkerThread(QObject *parent=0);
	~WorkerThread();
    void RequsetNewthread(QVector<QString> v,QMap< QString,QVector<QString> >m);

protected:
	void run();

};


#endif // WORKTHREAD_H