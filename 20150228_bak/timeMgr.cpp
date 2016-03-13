#include "timeMgr.h"

IMPLEMENT_APP(HelloWorldApp)
/* 程序从这里开始执行，类似非wxWindows程序中的main() */
bool HelloWorldApp::OnInit()
{
	MyFrame *frame = new MyFrame( _T("时间管理工具"), wxPoint(0,0),wxSize(400,300));
	frame->CreateStatusBar();

	//wxStaticText *startTimeStaticText = new wxStaticText(frame,-1,"开始时间：",wxPoint(0,0),wxSize(60,50));
	//wxTimePickerCtrl *startTimePickerCtrl = new wxTimePickerCtrl(frame,100,wxDefaultDateTime,wxPoint(0,35),wxSize(100,30),wxTP_DEFAULT,wxDefaultValidator,"my time ctrl");
	
	frame->Centre();
	frame->Show(TRUE);
	SetTopWindow(frame);

	/*StartDialog *mydialog = new StartDialog(NULL,100,"开始 对话框",wxPoint(0, 0),wxSize(240, 120),wxDEFAULT_DIALOG_STYLE,"11111");
	mydialog ->Centre();
	mydialog->Show();*/
	
	gSqlite.open();

	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	//文件菜单
    wxMenu *menuFile = new wxMenu;
	
	menuFile->Append(ID_MENU_REPORT,"&Report\tCtrl-R","显示报表");
    menuFile->Append(ID_MENU_START, "&Start...\tCtrl-S","开始计时");
	menuFile->Append(ID_MENU_END, "&End...\tCtrl-E","结束计时");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

/*	//帮助菜单
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;

	//添加到菜单栏中
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );*/

	//添加到菜单栏中
	wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
	SetMenuBar( menuBar );

	startButton = new wxButton(this, ID_START_BUTTON,"开始计时",wxPoint(0,00),wxSize(100,50),0);
	wxStaticText *dotextText = new wxStaticText(this, -1, "事项:",wxPoint(0, 50),wxSize(20, 40));
	dotextCtrl = new wxTextCtrl(this,-1,"",wxPoint(20,50),wxSize(size.GetWidth()-20,100),wxTE_MULTILINE|wxHSCROLL);

	wxString tmpString[] = {"第1象限","第2象限","第3象限","第4象限"};
	priorityChoice = new wxChoice(this,-1,wxPoint(0,150),wxDefaultSize,4,tmpString);
	endButton = new wxButton(this, ID_END_BUTTON,"结束",wxPoint(30,150),wxSize(100,50),0);

	priorityChoice->SetSelection(0);
	startButton->CentreOnParent(wxHORIZONTAL);
	endButton->CentreOnParent(wxHORIZONTAL);
	endButton->Disable();
}

void MyFrame::OnStart(wxCommandEvent& event){
	startTime = wxDateTime::Now();
	
	this->startButton->Disable();
	endButton->Enable();
	//wxMessageBox(startTime.Format("%H:%M:%S"));
}

void MyFrame::OnEnd(wxCommandEvent& event){
	endTime = wxDateTime::Now();
	wxTimeSpan tmp = endTime - startTime;

	int lineNum = dotextCtrl->GetNumberOfLines();
	std::string text;
	for(int i=0; i<lineNum; i++){
		text += dotextCtrl->GetLineText(i);
		if( i<lineNum-1 ) text += "\n";
	}
	if( text == "" ){
		wxMessageBox("事项不能为空！");
		return;
	}
	string strPriority = priorityChoice->GetString(priorityChoice->GetSelection());//获取优先级

	gSqlite.setSql(gInsertSql);
	if( gSqlite.prepare() < 0 ){
		wxMessageBox(gSqlite.errString);
		return;
	}
	
	std::string tmpStartTime = startTime.Format("%Y-%m-%d %H:%M:%S");
	std::string tmpEndTime = endTime.Format("%Y-%m-%d %H:%M:%S");
	gSqlite.bindString(1, tmpStartTime.c_str(), -1, SQLITE_STATIC);
	gSqlite.bindString(2, tmpEndTime.c_str(), -1, SQLITE_STATIC);
	gSqlite.bindString(3, text.c_str(), -1, SQLITE_STATIC);
	gSqlite.bindString(4, strPriority.c_str(), -1, SQLITE_STATIC);

	if(gSqlite.step() < 0){
		wxMessageBox(gSqlite.errString);
		return;
	};
	gSqlite.finalize();//释放pstmt指向的对象，防止内存泄露和多次准备导致数据返还忙状态

	dotextCtrl->SetLabel("");
	//wxMessageBox(startTime.Format("%Y%m%d %H:%M:%S")+","+endTime.Format("%H:%M:%S")+", inter="+tmp.Format("%H:%M:%S")+", "+text);
	
	startButton->Enable();
	endButton->Disable();
}

void MyFrame::OnReport(wxCommandEvent& event){
	RptDialog *rptDialog = new RptDialog(this,wxID_ANY,"报表",wxPoint(0,0),wxSize(800,500));
	
	rptDialog->Centre();
	rptDialog->Show(true);
	return;
}

RptDialog::RptDialog(wxFrame *parent, wxWindowID id, const wxString &title, wxPoint& point, wxSize& size)
	:wxDialog(parent, id, title, point, size,wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER){
	wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    // create text ctrl with minimal size 100x60    
/*	topsizer->Add(tmpFrame1,1,// make vertically stretchable
		wxEXPAND |    // make horizontally stretchable        
		wxALL,        //   and make border all around        
		10 );         // set border width to 10*/

	wxGrid *rptGrid = new wxGrid( this,ID_REPORT_GRID,wxPoint(0,0));
	topsizer->Add(rptGrid,1,// make vertically stretchable
			wxEXPAND |    // make horizontally stretchable        
			wxALL,        //   and make border all around        
			10 );         // set border width to 10

	wxGridStringTable *dataSource = new wxGridStringTable(1,7);
	
	dataSource->SetColLabelValue(0,"周数");
	dataSource->SetColLabelValue(1,"星期");
	dataSource->SetColLabelValue(2,"开始时间");
	dataSource->SetColLabelValue(3,"结束时间");
	dataSource->SetColLabelValue(4,"用时");
	dataSource->SetColLabelValue(5,"事项");
	dataSource->SetColLabelValue(6,"优先级");
	
	//gSqlite.open();
	gSqlite.setSql(gFirstQrySql);
	if( gSqlite.prepare() < 0 ){
		wxMessageBox(gSqlite.errString);
		return;
	}
	
	int curWeekOfYear=-1;
	int j=0;
	while ( 1 == gSqlite.step() ){
		DataContainer tmpDataCER;
		tmpDataCER.iWeekofYear = gSqlite.getColumnInt(6)+1;
		tmpDataCER.idayOfWeek = gSqlite.getColumnInt(5);
		tmpDataCER.startTime = gSqlite.getColumnString(0);
		tmpDataCER.endTime = gSqlite.getColumnString(1);
		tmpDataCER.usedTimeSec = gSqlite.getColumnInt(2);
		tmpDataCER.doTings = gSqlite.getColumnString(3);
		tmpDataCER.priority = gSqlite.getColumnString(4);
		tmpDataCER.keyid = gSqlite.getColumnInt(7);
		
		curData = tmpDataCER; //记录当前遍历到的记录
/*		if( j == 0) { curWeekOfYear = tmpDataCER.iWeekofYear; } //第一条记录
		if( curWeekOfYear!= tmpDataCER.iWeekofYear ){ //已经取到了上一周，记录此次位置后退出
			break;
		}*/

		//给dataSource赋值
		dataSource->InsertRows(0,1);

		char cWeekOfYear[16];
		memset(cWeekOfYear,'0',sizeof(cWeekOfYear));
		sprintf(cWeekOfYear,"第%d周",tmpDataCER.iWeekofYear);
		dataSource->SetValue(0,0,cWeekOfYear);  //每次都在第0行插入值
		dataSource->SetValue(0,1,GetDayOfWeek(tmpDataCER.idayOfWeek));
		dataSource->SetValue(0,2,tmpDataCER.startTime);
		dataSource->SetValue(0,3,tmpDataCER.endTime);
		dataSource->SetValue(0,4,timeConvert(tmpDataCER.usedTimeSec));
		dataSource->SetValue(0,5,tmpDataCER.doTings);
		dataSource->SetValue(0,6,tmpDataCER.priority);
		
		curWeekOfYear = tmpDataCER.iWeekofYear; //当前周数赋值
		vecDataOfWeek.push_back(tmpDataCER);
		j++;
	}
	gSqlite.finalize();//释放pstmt指向的对象，防止内存泄露和多次准备导致数据返还忙状态

	dataSource->DeleteRows(dataSource->GetNumberRows()-1, 1);//删除最后一行（因为一定为空行）
	rptGrid->SetTable(dataSource,true);
	rptGrid->AutoSize();

	wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );

	wxGrid *statisticGrid = new wxGrid( this,wxID_ANY);
	wxGridStringTable *statisticDS = new wxGridStringTable(4,3);
	statisticDS->SetColLabelValue(0,"周数");
	statisticDS->SetColLabelValue(1,"优先级");
	statisticDS->SetColLabelValue(2,"总百分比");
	
	map<string,int> mapSepUsedTime;
	int totalUsedTime=0;
	int iWeekofYear=-1;
	for(vector<DataContainer>::reverse_iterator vIt=vecDataOfWeek.rbegin(); vIt!=vecDataOfWeek.rend(); ++vIt){
		iWeekofYear = vIt->iWeekofYear; //周数

		map<string,int>::iterator mIt = mapSepUsedTime.find(vIt->priority);
		if( mIt == mapSepUsedTime.end() ){ //找不到键值
			mapSepUsedTime.insert(pair<string,int>(vIt->priority,vIt->usedTimeSec));
		}else{ //找到了键值
			mIt->second += vIt->usedTimeSec;
		}
		
		totalUsedTime += vIt->usedTimeSec;
	}
	
	int index = 0;
	for(map<string,int>::iterator mIt = mapSepUsedTime.begin(); mIt!=mapSepUsedTime.end(); ++mIt){
		char cWeekOfYear[16];
		memset(cWeekOfYear,'0',sizeof(cWeekOfYear));
		sprintf(cWeekOfYear,"第%d周",iWeekofYear);
		statisticDS->SetValue(index,0,cWeekOfYear);  //每次都在第0行插入值
		statisticDS->SetValue(index,1,mIt->first);  //优先级
		char cPecent[16];
		memset(cPecent,'0',sizeof(cPecent));
		double tmp1=static_cast<double>(mIt->second)/totalUsedTime*100;
		sprintf(cPecent,"%.2f%%",tmp1);
		statisticDS->SetValue(index,2,cPecent);  //优先级
		index++;
	}
	statisticGrid->SetTable(statisticDS,true);
	//statisticGrid->AutoSize();

	button_sizer->Add(statisticGrid,0,wxALL,10 ); 

	button_sizer->Add(        
		new wxButton( this, ID_PREVIOUS_BUTTON, "上一页" ),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10 );        // set border width to 10

    button_sizer->Add(
		new wxButton( this, ID_NEXTPAGE_BUTTON, "下一页" ),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10 );        // set border width to 10

    topsizer->Add(
		button_sizer,
		0,                // make vertically unstretchable
		wxALIGN_CENTER ); // no border and centre horizontally

	SetSizerAndFit(topsizer);
}