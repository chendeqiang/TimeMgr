#ifndef INCLUDED_HELLOWORLDAPP_H
#define INCLUDED_HELLOWORLDAPP_H

//对不支持预编译编译器要包含"wx/wx.h"
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
       #include "wx/wx.h"
#endif
#include "wx/timectrl.h"
#include "wx/button.h"
#include <wx/grid.h>
#include "common.h"
#include "StartDialog.h"
#include <string>
#include <vector>
#include <map>
#include "CDBSqlite.h"


//包含了时间使用数据的几个维度
class DataContainer{
public:
	int iWeekofYear; //一年中的第几个星期
	int idayOfWeek; //一个星期中的第几天
	std::string startTime;
	std::string endTime;
	int usedTimeSec; //使用时间，单位为秒
	std::string doTings;
	std::string priority;
	int keyid;
};

vector<DataContainer> vecDataOfWeek; //保存当前周所有的明细数据
DataContainer curData; //当前遍历到的数据，记录起来用来做断点续查

/**
 * HelloWorldApp类 * 这个类显示一个状态栏中包含文本"Hello World"的窗口
 */
class HelloWorldApp : public wxApp
{
      public: virtual bool OnInit();
};

enum
{
	ID_START_BUTTON = 1000,
	ID_END_BUTTON,
	ID_MENU_REPORT,
	ID_MENU_START,
	ID_MENU_END,
	ID_REPORT_GRID,
	ID_PREVIOUS_BUTTON,
	ID_NEXTPAGE_BUTTON
};

class MyFrame: public wxFrame
{
	public:    
		MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		
		wxButton *startButton; //开始按钮
		wxButton *endButton; //结束按钮
		wxTextCtrl *dotextCtrl; //事项框
		wxChoice *priorityChoice; //优先级
	private:
		void OnStart(wxCommandEvent& event);
		void OnEnd(wxCommandEvent& event);
		void OnReport(wxCommandEvent& event);
		//void OnAbout(wxCommandEvent& event);
		DECLARE_EVENT_TABLE();

};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(ID_START_BUTTON, OnStart) //声明开始按钮的事件处理函数
	EVT_BUTTON(ID_END_BUTTON, OnEnd)
	EVT_MENU(ID_MENU_REPORT, OnReport)
	//EVT_MENU(wxID_EXIT,  MyFrame::OnExit)    
	//EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
END_EVENT_TABLE()

class RptDialog: public wxDialog{
public:
	RptDialog(wxFrame *parent, wxWindowID id, const wxString &title, wxPoint& point, wxSize& size);

};

#endif // INCLUDED_HELLOWORLDAPP_H