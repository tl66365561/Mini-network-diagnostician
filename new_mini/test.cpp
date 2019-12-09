
#include"test.h"





MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr("Main Window"));
	textEdit = new QTextEdit(this);
	textEdit2= new QTextEdit(this);
	setCentralWidget(textEdit);

	

	//设置图标
	openAction = new QAction(QIcon(":/new_mini/doc-open1"), tr("&Open..."), this);
	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	parseAction = new QAction(QIcon(":/new_mini/doc-open3"), tr("&Parse..."), this);
	
	//设置快捷键
	openAction->setShortcuts(QKeySequence::Open);
	saveAction->setShortcuts(QKeySequence::Save);
	
	//设置提示信息
	openAction->setStatusTip(tr("Open an existing file"));
	saveAction->setStatusTip(tr("Save a file"));
	parseAction->setStatusTip(tr("Parse an existing file"));
	
	//设置信号槽
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	//connect(parseAction,  SIGNAL(triggered()), this, SLOT(parse()));
	connect(parseAction,  SIGNAL(triggered()), this, SLOT(parse()));

	
	//添加到菜单栏
	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);
	file->addAction(saveAction);
	file->addAction(parseAction);
	
	//添加到工具栏
	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(parseAction);

	


	statusBar();


}


//openAction的槽函数
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

	
//saveAction的槽函数
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


//parseAction的槽函数
void MainWindow::parse(){

	QWidget* win= new QWidget();
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(textEdit2);
	setCentralWidget(textEdit2);

	qDebug()<<str<<endl;    



	 //如果用定时器的话，如果parse的时间过长，则窗口就会卡死
     //利用多线程去尝试一下，，，， 

	 //QTimer *timer = new QTimer(this);
	 //connect(timer, SIGNAL(timeout()), this, SLOT(mfunc_parse())); 
	 //timer->start(1000); // 每隔1s


	/* WorkerThread work(this,win,layout);
	work.start(); */
 

	 mfunc_parse();//进行文本内容的预处理	 
	  
	  win->setLayout(layout); 
	  win->show();
	
	
	
}


//////////////////////////////////////////////////////////////////////////////

void  MainWindow:: mfunc_parse(){

	
	//对content字符串S进行预处理，先提取第一段
	QVector<QString>v1;//元素是每一小段
	QString tmp_;//包含每一小段全部内容的string
	QVector<QString>vtmp;													

	
    //利用循环以'\n\n'为分隔符，把每一段的内容push进v1;	
	size_t start=0;
    size_t index=0;	
	for(int i=0;i<10-1;++i){
		
		vtmp.clear();
		size_t finish=str.indexOf("\n\n",start);      //预期是遇到两个\n的时候然后停止，读取一个段
		//if(finish==-1) 
		//	break;
		tmp_=str.mid(start,finish-start);
		v1.push_back(tmp_);
		start=finish+2;                                                   
		qDebug()<<tmp_;



		size_t end=tmp_.indexOf("\n",0);
		QString nowords=tmp_.mid(0,end);//tmp_的第一行
		qDebug()<<"map's key_valued is"<<nowords<<endl;

		/////////////////////////////////////////////////////////////////////////
														//
		size_t begin=0;															//
		do 																		//
		{																		//
			//
			size_t end=tmp_.indexOf("\n",begin);								//
			if(end==-1) {														//
				//最后一次，应该把从begin下标开始全部都读进去					 //
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


	} //  V1每一个大段的内容解析完毕

	 
	qDebug()<<endl;


    //对每一个小段进行处理 
	for( int i=0;i<9;++i){   

		v2.clear();
		QString arr(v1[i]);
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
				v2.push_back(replenish);
				break;

			}
			QString tmp_var=arr.mid(begin,end-begin);
			qDebug()<<tmp_var<<endl;
			v2.push_back(tmp_var);
			begin=end+1;                                   

		} while(1);




		//判断v2[0]元素即指定域名的连通性
		QTcpSocket socket(0);
		socket.abort(); //取消原有连接
		qDebug()<<"v2[0]=  "<<v2[0]<<endl;
		socket.connectToHost(v2[0],80); //建立一个TCP连接             第二个参数是服务器方面的端口号

		// socket->connectToHost("imap", 143);
		if(socket.waitForConnected(1000))                //1000的话都是regular,1/100都是 not regular
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



		//判断玩HOST连通性之后，再去解析拿到关联的ip地址列表，然后去比对
		///执行流在这块存在问题： 并没有按照预期执行到这块之后然后去拿到关系的IP列表进行判断

		QHostInfo::lookupHost(v2[0],   
			this, SLOT(lookedUp(QHostInfo)));            //对，因为这边是异步执行的  解决方案：

	}

}














//////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow(){

}



bool MainWindow::Search(QString s1,QString s2){

	qDebug()<<"s1=  "<<s1;
	//在 成员变量 m  map<string,vector<string>>中去查找

	QVector<QString>vv=m[s2];

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
		
				//重新修改一下search();                       map<string,vector<string> 

		if(Search(addrList[i].toString(),host.hostName())) {      //Search():与host关联的域名在v2的元素项中一一比对判断是否存在
			
			tag="true";
			qDebug()<<"Address List Check...： "<<addrList[i].toString()<<endl;
			tmp+=("  "+tag+"\n");
			textEdit2->setText(tmp);
		}
		else{
			tag="false";
			tmp+=(" "+tag+"\n");
			textEdit2->setText(tmp);

		}
	 }//end of for:对应解析出的相关的ip列表遍历的循环

}
	//如果列表为空，打印LOG
	else{
		tmp+="The analytical result is NULL...";
		textEdit2->setText(tmp);

	}
}



//问题：  lookuphost的异步处理      -》lookedup（）


//定时器还是while（1）；