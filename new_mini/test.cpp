
#include"test.h"



MainWindow2::MainWindow2(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr(" opening new  Window..."));
	textEdit2 = new QTextEdit(this);
	setCentralWidget(textEdit2);

	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	//添加到菜单栏
	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(saveAction);

	//添加到工具栏
	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(saveAction);


	connect( &thread_, SIGNAL(windowShow(QString )),
		this, SLOT(onWindowShow(QString)) );
	


	statusBar();


}



void MainWindow2::save(){


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
		out << textEdit2->toPlainText();
		file.close();
	} else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}


}

void  MainWindow2:: mfunc_parse(QVector<QString>v, QMap< QString,QVector<QString> >m){

	thread_.RequsetNewthread(v,m);


}



	//判断玩HOST连通性之后，再去解析拿到关联的ip地址列表，然后去比对
	///执行流在这块存在问题： 并没有按照预期执行到这块之后然后去拿到关系的IP列表进行判断

void MainWindow2::onWindowShow(QString text){

		textEdit2->setText(text);
		this->show();

}





MainWindow2::~MainWindow2(){

	delete textEdit2;

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////华丽分割//////////////////////////华丽分割////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr("Main Window"));
	textEdit = new QTextEdit(this);
	setCentralWidget(textEdit);
	//win2=new MainWindow2(this);
	

	//设置图标
	openAction = new QAction(QIcon(":/new_mini/doc-open1"), tr("&Open..."), this);
	parseAction = new QAction(QIcon(":/new_mini/doc-open3"), tr("&Parse..."), this);
	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	
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



void MainWindow::funcParse(){


	//对content字符串S进行预处理，先提取第一段
	QString tmp_;//包含每一小段全部内容的string
	QVector<QString>vtmp;													


	//利用循环以'\n\n'为分隔符，把每一段的内容push进v1;	
	size_t start=0;
	size_t index=0;	
	for(int i=0;i<10-1;++i){

		vtmp.clear();
		size_t finish=str.indexOf("\n\n",start);      //遇到两个换行符的时候然后停止，读取一个段
		//if(finish==-1) 
		//	break;
		tmp_=str.mid(start,finish-start);
		v1.push_back(tmp_);
		start=finish+2;                                                   
		qDebug()<<tmp_;



		size_t end=tmp_.indexOf("\n",0);
		QString nowords=tmp_.mid(0,end);//tmp_的第一行
		size_t begin=0;															
		do 																		
		{																		
			//
			size_t end=tmp_.indexOf("\n",begin);								
			if(end==-1) {														
				//最后一次，应该把从begin下标开始全部都读进去					
				QString replenish=tmp_.mid(begin);								
				vtmp.push_back(replenish);										
				break;															
				//
			}																	
			QString tmp_var=tmp_.mid(begin,end-begin);							
			vtmp.push_back(tmp_var);											
			begin=end+1;    													
		}while(1);																


		m[nowords]=vtmp;


	} //  V1每一个大段的内容解析完毕


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
	

	//打开之后跟着调用一个函数去填充V1和m的内容

	funcParse();


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

void MainWindow::RequsetNew(QVector<QString> v, QMap<QString,QVector<QString>>m){


       win2.mfunc_parse(v,m);


}




//parseAction的槽函数
void MainWindow::parse(){

	RequsetNew(v1,m);	
	
	//(win2.textEdit2)->setText("loading .... .... ....");
	//win2.show();
}


MainWindow::~MainWindow(){

}











