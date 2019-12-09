
#include"test.h"





MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr("Main Window"));
	textEdit = new QTextEdit(this);
	textEdit2= new QTextEdit(this);
	setCentralWidget(textEdit);

	

	//����ͼ��
	openAction = new QAction(QIcon(":/new_mini/doc-open1"), tr("&Open..."), this);
	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	parseAction = new QAction(QIcon(":/new_mini/doc-open3"), tr("&Parse..."), this);
	
	//���ÿ�ݼ�
	openAction->setShortcuts(QKeySequence::Open);
	saveAction->setShortcuts(QKeySequence::Save);
	
	//������ʾ��Ϣ
	openAction->setStatusTip(tr("Open an existing file"));
	saveAction->setStatusTip(tr("Save a file"));
	parseAction->setStatusTip(tr("Parse an existing file"));
	
	//�����źŲ�
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	//connect(parseAction,  SIGNAL(triggered()), this, SLOT(parse()));
	connect(parseAction,  SIGNAL(triggered()), this, SLOT(parse()));

	
	//��ӵ��˵���
	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);
	file->addAction(saveAction);
	file->addAction(parseAction);
	
	//��ӵ�������
	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(parseAction);

	


	statusBar();


}


//openAction�Ĳۺ���
void MainWindow::open(){


	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.txt)"));
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream in(&file);
		str=in.readAll();
		textEdit->setText(str);
		file.close();
	} else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
	
}

	
//saveAction�Ĳۺ���
void MainWindow::save(){

	
	QString path = QFileDialog::getSaveFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.txt)"));
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		out << textEdit->toPlainText();
		file.close();
	} else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
	

}


//parseAction�Ĳۺ���
void MainWindow::parse(){

	QWidget* win= new QWidget();
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(textEdit2);
	setCentralWidget(textEdit2);

	qDebug()<<str<<endl;    



	 //����ö�ʱ���Ļ������parse��ʱ��������򴰿ھͻῨ��
     //���ö��߳�ȥ����һ�£������� 

	 //QTimer *timer = new QTimer(this);
	 //connect(timer, SIGNAL(timeout()), this, SLOT(mfunc_parse())); 
	 //timer->start(1000); // ÿ��1s


	/* WorkerThread work(this,win,layout);
	work.start(); */
 

	 mfunc_parse();//�����ı����ݵ�Ԥ����	 
	  
	  win->setLayout(layout); 
	  win->show();
	
	
	
}


//////////////////////////////////////////////////////////////////////////////

void  MainWindow:: mfunc_parse(){

	
	//��content�ַ���S����Ԥ��������ȡ��һ��
	QVector<QString>v1;//Ԫ����ÿһС��
	QString tmp_;//����ÿһС��ȫ�����ݵ�string
	QVector<QString>vtmp;													

	
    //����ѭ����'\n\n'Ϊ�ָ�������ÿһ�ε�����push��v1;	
	size_t start=0;
    size_t index=0;	
	for(int i=0;i<10-1;++i){
		
		vtmp.clear();
		size_t finish=str.indexOf("\n\n",start);      //Ԥ������������\n��ʱ��Ȼ��ֹͣ����ȡһ����
		//if(finish==-1) 
		//	break;
		tmp_=str.mid(start,finish-start);
		v1.push_back(tmp_);
		start=finish+2;                                                   
		qDebug()<<tmp_;



		size_t end=tmp_.indexOf("\n",0);
		QString nowords=tmp_.mid(0,end);//tmp_�ĵ�һ��
		qDebug()<<"map's key_valued is"<<nowords<<endl;

		/////////////////////////////////////////////////////////////////////////
														//
		size_t begin=0;															//
		do 																		//
		{																		//
			//
			size_t end=tmp_.indexOf("\n",begin);								//
			if(end==-1) {														//
				//���һ�Σ�Ӧ�ðѴ�begin�±꿪ʼȫ��������ȥ					 //
				QString replenish=tmp_.mid(begin);								//
				vtmp.push_back(replenish);										//
				break;															//
				//
			}																	//
			QString tmp_var=tmp_.mid(begin,end-begin);							//
			vtmp.push_back(tmp_var);											//
			begin=end+1;    													//
		}while(1);																//
		/////////////////////////////////////////////////////////////////////////


		m[nowords]=vtmp;


	} //  V1ÿһ����ε����ݽ������

	 
	qDebug()<<endl;


    //��ÿһ��С�ν��д��� 
	for( int i=0;i<9;++i){   

		v2.clear();
		QString arr(v1[i]);
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
				v2.push_back(replenish);
				break;

			}
			QString tmp_var=arr.mid(begin,end-begin);
			qDebug()<<tmp_var<<endl;
			v2.push_back(tmp_var);
			begin=end+1;                                   

		} while(1);




		//�ж�v2[0]Ԫ�ؼ�ָ����������ͨ��
		QTcpSocket socket(0);
		socket.abort(); //ȡ��ԭ������
		qDebug()<<"v2[0]=  "<<v2[0]<<endl;
		socket.connectToHost(v2[0],80); //����һ��TCP����             �ڶ��������Ƿ���������Ķ˿ں�

		// socket->connectToHost("imap", 143);
		if(socket.waitForConnected(1000))                //1000�Ļ�����regular,1/100���� not regular
		{
			qDebug()<<v2[0]<<"is regular \n";
			tmp+=(v2[0]+" is regular... \n");
			textEdit2->setText(tmp);

		}
		else{

			qDebug()<<v2[0]<<"is not regular \n";
			tmp+=(v2[0]+" is not regular... \n");
			textEdit2->setText(tmp);
		}



		//�ж���HOST��ͨ��֮����ȥ�����õ�������ip��ַ�б�Ȼ��ȥ�ȶ�
		///ִ���������������⣺ ��û�а���Ԥ��ִ�е����֮��Ȼ��ȥ�õ���ϵ��IP�б�����ж�

		QHostInfo::lookupHost(v2[0],   
			this, SLOT(lookedUp(QHostInfo)));            //�ԣ���Ϊ������첽ִ�е�  ���������

	}

}














//////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow(){

}



bool MainWindow::Search(QString s1,QString s2){

	qDebug()<<"s1=  "<<s1;
	//�� ��Ա���� m  map<string,vector<string>>��ȥ����

	QVector<QString>vv=m[s2];

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
void MainWindow::lookedUp(const QHostInfo &host)
{

	tmp+="\n";
	textEdit2->setText(tmp);


	QString tag;
	tmp+=(host.hostName()+" analytical result is :   ");
	qDebug() << tmp;
	textEdit2->setText(tmp);

	QList<QHostAddress> addrList = host.addresses();

	if (!addrList.isEmpty())
	{  	
		qDebug() <<"analytical list is not NULL..."<<endl;

		for  (int i = 0; i < addrList.size(); i++)
	 {
			    tmp+=(addrList[i].toString());
				textEdit2->setText(tmp);	
		
				//�����޸�һ��search();                       map<string,vector<string> 

		if(Search(addrList[i].toString(),host.hostName())) {      //Search():��host������������v2��Ԫ������һһ�ȶ��ж��Ƿ����
			
			tag="true";
			qDebug()<<"Address List Check...�� "<<addrList[i].toString()<<endl;
			tmp+=("  "+tag+"\n");
			textEdit2->setText(tmp);
		}
		else{
			tag="false";
			tmp+=(" "+tag+"\n");
			textEdit2->setText(tmp);

		}
	 }//end of for:��Ӧ����������ص�ip�б������ѭ��

}
	//����б�Ϊ�գ���ӡLOG
	else{
		tmp+="The analytical result is NULL...";
		textEdit2->setText(tmp);

	}
}



//���⣺  lookuphost���첽����      -��lookedup����


//��ʱ������while��1����