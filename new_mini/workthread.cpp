
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

//��ÿһ��С�ν��д��� 
for( int i=0;i<9;++i){   

	_v2.clear();
	QString arr(_v1[i]);
	qDebug()<<"now process is"<< arr<<endl;


	//��\nΪ�ָ���ȥ��ȡ����ÿһ�ε�ûһ�е�������Ϊһ��vecor��Ԫ��   [account.wps.cn]\ndirectUseHttpDns=0\nip1=140.210.77.190\nip2=114.112.36.130\nip6=114.112.66.245 
	size_t begin=0;
	do 
	{

		size_t end=arr.indexOf("\n",begin);
		if(end==-1) {
			//���һ�Σ�Ӧ�ðѴ�begin�±꿪ʼȫ��������ȥ
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




	//�ж�v2[0]Ԫ�ؼ�ָ����������ͨ��
	QTcpSocket socket(0);
	socket.abort(); //ȡ��ԭ������
	qDebug()<<"v2[0]=  "<<_v2[0]<<endl;
	socket.connectToHost(_v2[0],80); //����һ��TCP����             �ڶ��������Ƿ���������Ķ˿ں�

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
		this, SLOT(lookedUp(QHostInfo)));            //�ԣ���Ϊ������첽ִ�е�  ���������


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


			if(Search(addrList[i].toString(),host.hostName())) {      //Search():��host������������v2��Ԫ������һһ�ȶ��ж��Ƿ����

				tag="true";
				qDebug()<<"Address List Check...�� "<<addrList[i].toString()<<endl;
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

		}//end of for:��Ӧ����������ص�ip�б������ѭ��

	}
	//����б�Ϊ�գ���ӡLOG
	else{
		_text+="The analytical result is NULL...";
		//textEdit2->setText(tmp);
		//emit windowShow(_text);

	}

	++count;

}

bool WorkerThread::Search(QString s1,QString s2){

	qDebug()<<"s1=  "<<s1;
	//�� ��Ա���� m  map<string,vector<string>>��ȥ����

	QVector<QString>vv=_m[s2];

	for(int i=0;i<vv.size();++i){
		qDebug()<<"before edit...... "<<vv[i];
		QString edit=vv[i].mid(4);
		qDebug()<<"after edit=  "<<edit<<endl;
		if( QString::compare(s1, edit) == 0){             //QString ���ַ�����ȵıȶԷ���
			return true;
		}
	}
	return false;

}
