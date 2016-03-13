#ifndef INCLUDED_HELLOWORLDAPP_H
#define INCLUDED_HELLOWORLDAPP_H

//�Բ�֧��Ԥ���������Ҫ����"wx/wx.h"
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


//������ʱ��ʹ�����ݵļ���ά��
class DataContainer{
public:
	int iWeekofYear; //һ���еĵڼ�������
	int idayOfWeek; //һ�������еĵڼ���
	std::string startTime;
	std::string endTime;
	int usedTimeSec; //ʹ��ʱ�䣬��λΪ��
	std::string doTings;
	std::string priority;
	int keyid;
};

vector<DataContainer> vecDataOfWeek; //���浱ǰ�����е���ϸ����
DataContainer curData; //��ǰ�����������ݣ���¼�����������ϵ�����

/**
 * HelloWorldApp�� * �������ʾһ��״̬���а����ı�"Hello World"�Ĵ���
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
		
		wxButton *startButton; //��ʼ��ť
		wxButton *endButton; //������ť
		wxTextCtrl *dotextCtrl; //�����
		wxChoice *priorityChoice; //���ȼ�
	private:
		void OnStart(wxCommandEvent& event);
		void OnEnd(wxCommandEvent& event);
		void OnReport(wxCommandEvent& event);
		//void OnAbout(wxCommandEvent& event);
		DECLARE_EVENT_TABLE();

};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(ID_START_BUTTON, OnStart) //������ʼ��ť���¼�������
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