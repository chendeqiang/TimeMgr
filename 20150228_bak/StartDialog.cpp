#include "StartDialog.h"

//注册买入窗口的事件处理函数
BEGIN_EVENT_TABLE(StartDialog, wxDialog)    
	EVT_BUTTON(ID_STARTCTRL_OK,   StartDialog::OnStart)
END_EVENT_TABLE()


//开始窗口构造函数
StartDialog::StartDialog(wxWindow *parent,
					wxWindowID id, 
					const wxString& title,
					const wxPoint&  pos, 
					const wxSize& size,
					long  style,
					const wxString& name)
					:wxDialog(parent,id,title,pos,size,style,name)
{
	//wxStaticText *startNameText = new wxStaticText(this, -1, "按“开始”按钮开始计时",wxPoint(00, 10),wxSize(150, 20));
	//wxButton* startButton = new wxButton(this, ID_STARTCTRL_OK,"开始计时", wxPoint(00,40), wxSize(150,80));
	wxButton* startButton = new wxButton(this, ID_STARTCTRL_OK,"开始计时");
}

void StartDialog::OnStart(wxCommandEvent& event){
	startTime = wxDateTime::Now();
}