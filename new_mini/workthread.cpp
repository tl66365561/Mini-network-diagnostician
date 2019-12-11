
#include "workthread.h"



 WorkerThread::WorkerThread(QObject *parent)
	: QThread(parent)
	{

	_text=" ";

}


 
 void WorkerThread::RequsetNewthread(QVector<QString> v, QMap< QString,QVector<QString> >m){

	 _v1=v;
	 _m=m;
	 start();


 }






void WorkerThread::run(){

//对每一个小段进行处理 
for( int i=0;i<9;++i){   

	_v2.clear();
	QString arr(_v1[i]);
	qDebug()<<"now process is"<< arr<<endl;


	//以\n为分隔符去提取，将每一段的没一行的内容作为一个vecor的元素   [account.wps.cn]\ndirectUseHttpDns=0\nip1=140.210.77.190\nip2=114.112.36.130\nip6=114.112.66.245 
	size_t begin=0;
	do 
	{

		size_t end=arr.indexOf("\n",begin);
		if(end==-1) {
			//最后一次，应该把从begin下标开始全部都读进去
			QString replenish=arr.mid(begin);
			qDebug()<<replenish<<endl;	
			_v2.push_back(replenish);
			break;

		}
		QString tmp_var=arr.mid(begin,end-begin);
		qDebug()<<tmp_var<<endl;
		_v2.push_back(tmp_var);
		begin=end+1;                                   

	} while(1);




	//判断v2[0]元素即指定域名的连通性
	QTcpSocket socket(0);
	socket.abort(); //取消原有连接
	qDebug()<<"v2[0]=  "<<_v2[0]<<endl;
	socket.connectToHost(_v2[0],80); //建立一个TCP连接             第二个参数是服务器方面的端口号

	// socket->connectToHost("imap", 143);
	if(socket.waitForConnected(1000))                
	{
		qDebug()<<_v2[0]<<"is regular \n";
		_text+=(_v2[0]+" is regular... \n");
	//	emit windowShow(_text);

		

	}
	else{

		qDebug()<<_v2[0]<<"is not regular \n";
		_text+=(_v2[0]+" is not regular... \n");
		//emit windowShow(_text);

		
	}


	QHostInfo::lookupHost(_v2[0],   
		this, SLOT(lookedUp(QHostInfo)));            //对，因为这边是异步执行的  解决方案：


}

}

void WorkerThread::lookedUp(const QHostInfo &host)
{

	if(count==9){
	
	emit windowShow(_text);
	
	}

	
	_text+="\n";
	QString tag;
	_text+=(host.hostName()+" analytical result is :   ");
	qDebug() << _text;
	//textEdit2->setText(tmp);
	//emit windowShow(_text);

	QList<QHostAddress> addrList = host.addresses();

	if (!addrList.isEmpty())
	{  	
		qDebug() <<"analytical list is not NULL..."<<endl;

		for  (int i = 0; i < addrList.size(); i++)
		{
			_text+=(addrList[i].toString());
			//textEdit2->setText(tmp);	
			//emit windowShow(_text);


			if(Search(addrList[i].toString(),host.hostName())) {      //Search():与host关联的域名在v2的元素项中一一比对判断是否存在

				tag="true";
				qDebug()<<"Address List Check...： "<<addrList[i].toString()<<endl;
				_text+=("  "+tag+"\n");
				//textEdit2->setText(tmp);
				//emit windowShow(_text);

			}
			else{
				tag="false";
				_text+=(" "+tag+"\n");
				//textEdit2->setText(tmp);
				emit windowShow(_text);

			}

		}//end of for:对应解析出的相关的ip列表遍历的循环

	}
	//如果列表为空，打印LOG
	else{
		_text+="The analytical result is NULL...";
		//textEdit2->setText(tmp);
		//emit windowShow(_text);

	}

	++count;

}

bool WorkerThread::Search(QString s1,QString s2){

	qDebug()<<"s1=  "<<s1;
	//在 成员变量 m  map<string,vector<string>>中去查找

	QVector<QString>vv=_m[s2];

	for(int i=0;i<vv.size();++i){
		qDebug()<<"before edit...... "<<vv[i];
		QString edit=vv[i].mid(4);
		qDebug()<<"after edit=  "<<edit<<endl;
		if( QString::compare(s1, edit) == 0){             //QString 的字符串相等的比对方法
			return true;
		}
	}
	return false;

}
