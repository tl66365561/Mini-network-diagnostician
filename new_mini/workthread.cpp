
#include "workthread.h"


 WorkerThread::WorkerThread(QObject *parent)
	: QThread(parent)
	{

		_text+="\n******************************************************************\n\n";
		_text+="\n********************  NetWork Checking... ...  *******************\n\n";
		_text+="\n******************************************************************\n\n";

    	count=0;	
		log=new LOG();
}


 
 void WorkerThread::RequsetNewthread(QVector<QString> v, QMap< QString,QVector<QString> >m){

	 _v1=v;
	 _m=m;
	 start();


 }



void WorkerThread::run(){

	/* timer = new QTimer(this);
	timer->start(100);
	*/

	progress=new QProgressDialog("Parsing content", "Cancel", 0,100);
	progress->setWindowModality(Qt::WindowModal);
	progress->setMinimumDuration(5);  
	progress->setWindowTitle("Parsing now ..."); 
	progress->show();

	if(progress->wasCanceled())                                  
	{
	
		QMessageBox::warning(NULL,"Warning","you have canceled this action.");
	    return;
	}


	for (int i = 0; i < 100; i++) {
    
		Sleep(100);
		progress->setValue(i);

	}
	progress->setValue(100);

	
	



while(1){//实时监控


	Sleep(1000);
    _domain.clear();
	count=0;

	QString log_=log->Log_record(" Paring result: ");
	_text+=log_;
	_text+="\n";
	
	
	//对每一个小段进行处理 
  for( int i=0;i<9;++i){   
		
	    QString arr(_v1[i]);
	    _v2.clear();
		

	//以\n为分隔符去提取，将每一段的没一行的内容作为一个vecor的元素   [account.wps.cn]\ndirectUseHttpDns=0\nip1=140.210.77.190\nip2=114.112.36.130\nip6=114.112.66.245 
      	size_t begin=0;
	 do 
	    {

		 size_t end=arr.indexOf("\n",begin);
		 if(end==-1) {
			//最后一次，应该把从begin下标开始全部都读进去
			QString replenish=arr.mid(begin);
			_v2.push_back(replenish);
			break;

		}
		 QString tmp_var=arr.mid(begin,end-begin);
	 	 _v2.push_back(tmp_var);
		 begin=end+1;                                   

	 } while(1);




	//判断v2[0]元素即指定域名的连通性
	QTcpSocket socket(0);
	socket.abort(); //取消原有连接
	socket.connectToHost(_v2[0],80); //建立一个TCP连接             第二个参数是服务器方面的端口号

	// socket->connectToHost("imap", 143);
	if(socket.waitForConnected(1000))                
	{
		_text+=(_v2[0]+" is regular... \n\n");
	}
	else{
		_text+=(_v2[0]+" is not regular... \n\n");	
	}

	
  _domain.push_back(_v2[0]);

}//end of for...


   emit windowShow(_text);


//把每一个域名都存储一下

 for(int j=0;j<9;++j){
   	QHostInfo::lookupHost(_domain[j], this, SLOT(lookedUp(QHostInfo)));          

  
}


}//end of while(1);

}








void WorkerThread::lookedUp(const QHostInfo &host)
{

	mutex.lock();
	++count;
	

	QString tag;
	_text+="\n";
	_text+=(host.hostName()+" analytical result is :   ");
	QList<QHostAddress> addrList = host.addresses();

	if (!addrList.isEmpty())
	{  	

		for  (int i = 0; i < addrList.size(); i++)
		{
			_text+=(addrList[i].toString());

			if(Search(addrList[i].toString(),host.hostName())) {      //Search():与host关联的域名在v2的元素项中一一比对判断是否存在

				tag="true";
				_text+=("  "+tag+"\n");
			

			}
			else{
				tag="false";
				_text+=(" "+tag+"\n");
				

			}

		}//end of for:对应解析出的相关的ip列表遍历的循环

	}
	
	//如果列表为空，打印LOG
	else{
		_text+="The analytical result is NULL...";
	}



if(count==9){
		_text += "\n\n\n\n\n\n";
		emit windowShow(_text);
	}


   mutex.unlock();

}

bool WorkerThread::Search(QString s1,QString s2){

	//在 成员变量 m  map<string,vector<string>>中去查找

	QVector<QString>vv=_m[s2];

	for(int i=0;i<vv.size();++i){

		QString edit=vv[i].mid(4);
		if( QString::compare(s1, edit) == 0){             //QString 的字符串相等的比对方法
			return true;
		}
	}
	return false;

}


WorkerThread::~WorkerThread(){

	delete progress;
	delete log;
	//delete timer;
}

//完善的话：   1.可以在弹窗之前增加一个解析的界面设计：进度条对话框     2.每一个大段前打印一次Log       3.窗口伴随下移