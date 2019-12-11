
#include"test.h"



MainWindow2::MainWindow2(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr(" opening new  Window..."));
	textEdit2 = new QTextEdit(this);
	setCentralWidget(textEdit2);

	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	//��ӵ��˵���
	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(saveAction);

	//��ӵ�������
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



	//�ж���HOST��ͨ��֮����ȥ�����õ�������ip��ַ�б�Ȼ��ȥ�ȶ�
	///ִ���������������⣺ ��û�а���Ԥ��ִ�е����֮��Ȼ��ȥ�õ���ϵ��IP�б�����ж�

void MainWindow2::onWindowShow(QString text){

		textEdit2->setText(text);
		this->show();

}





MainWindow2::~MainWindow2(){

	delete textEdit2;

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////�����ָ�//////////////////////////�����ָ�////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent){

	setWindowTitle(tr("Main Window"));
	textEdit = new QTextEdit(this);
	setCentralWidget(textEdit);
	//win2=new MainWindow2(this);
	

	//����ͼ��
	openAction = new QAction(QIcon(":/new_mini/doc-open1"), tr("&Open..."), this);
	parseAction = new QAction(QIcon(":/new_mini/doc-open3"), tr("&Parse..."), this);
	saveAction = new QAction(QIcon(":/new_mini/doc-open2"), tr("&Save..."), this);
	
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



void MainWindow::funcParse(){


	//��content�ַ���S����Ԥ��������ȡ��һ��
	QString tmp_;//����ÿһС��ȫ�����ݵ�string
	QVector<QString>vtmp;													


	//����ѭ����'\n\n'Ϊ�ָ�������ÿһ�ε�����push��v1;	
	size_t start=0;
	size_t index=0;	
	for(int i=0;i<10-1;++i){

		vtmp.clear();
		size_t finish=str.indexOf("\n\n",start);      //�����������з���ʱ��Ȼ��ֹͣ����ȡһ����
		//if(finish==-1) 
		//	break;
		tmp_=str.mid(start,finish-start);
		v1.push_back(tmp_);
		start=finish+2;                                                   
		qDebug()<<tmp_;



		size_t end=tmp_.indexOf("\n",0);
		QString nowords=tmp_.mid(0,end);//tmp_�ĵ�һ��
		size_t begin=0;															
		do 																		
		{																		
			//
			size_t end=tmp_.indexOf("\n",begin);								
			if(end==-1) {														
				//���һ�Σ�Ӧ�ðѴ�begin�±꿪ʼȫ��������ȥ					
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


	} //  V1ÿһ����ε����ݽ������


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
	

	//��֮����ŵ���һ������ȥ���V1��m������

	funcParse();


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

void MainWindow::RequsetNew(QVector<QString> v, QMap<QString,QVector<QString>>m){


       win2.mfunc_parse(v,m);


}




//parseAction�Ĳۺ���
void MainWindow::parse(){

	RequsetNew(v1,m);	
	
	//(win2.textEdit2)->setText("loading .... .... ....");
	//win2.show();
}


MainWindow::~MainWindow(){

}











