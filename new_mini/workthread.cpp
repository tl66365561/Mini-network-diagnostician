
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

	
	



while(1){//ʵʱ���


	Sleep(1000);
    _domain.clear();
	count=0;

	QString log_=log->Log_record(" Paring result: ");
	_text+=log_;
	_text+="\n";
	
	
	//��ÿһ��С�ν��д��� 
  for( int i=0;i<9;++i){   
		
	    QString arr(_v1[i]);
	    _v2.clear();
		

	//��\nΪ�ָ���ȥ��ȡ����ÿһ�ε�ûһ�е�������Ϊһ��vecor��Ԫ��   [account.wps.cn]\ndirectUseHttpDns=0\nip1=140.210.77.190\nip2=114.112.36.130\nip6=114.112.66.245 
      	size_t begin=0;
	 do 
	    {

		 size_t end=arr.indexOf("\n",begin);
		 if(end==-1) {
			//���һ�Σ�Ӧ�ðѴ�begin�±꿪ʼȫ��������ȥ
			QString replenish=arr.mid(begin);
			_v2.push_back(replenish);
			break;

		}
		 QString tmp_var=arr.mid(begin,end-begin);
	 	 _v2.push_back(tmp_var);
		 begin=end+1;                                   

	 } while(1);




	//�ж�v2[0]Ԫ�ؼ�ָ����������ͨ��
	QTcpSocket socket(0);
	socket.abort(); //ȡ��ԭ������
	socket.connectToHost(_v2[0],80); //����һ��TCP����             �ڶ��������Ƿ���������Ķ˿ں�

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


//��ÿһ���������洢һ��

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

			if(Search(addrList[i].toString(),host.hostName())) {      //Search():��host������������v2��Ԫ������һһ�ȶ��ж��Ƿ����

				tag="true";
				_text+=("  "+tag+"\n");
			

			}
			else{
				tag="false";
				_text+=(" "+tag+"\n");
				

			}

		}//end of for:��Ӧ����������ص�ip�б������ѭ��

	}
	
	//����б�Ϊ�գ���ӡLOG
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

	//�� ��Ա���� m  map<string,vector<string>>��ȥ����

	QVector<QString>vv=_m[s2];

	for(int i=0;i<vv.size();++i){

		QString edit=vv[i].mid(4);
		if( QString::compare(s1, edit) == 0){             //QString ���ַ�����ȵıȶԷ���
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

//���ƵĻ���   1.�����ڵ���֮ǰ����һ�������Ľ�����ƣ��������Ի���     2.ÿһ�����ǰ��ӡһ��Log       3.���ڰ�������