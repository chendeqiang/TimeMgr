#include "StartDialog.h"

//ע�����봰�ڵ��¼�������
BEGIN_EVENT_TABLE(StartDialog, wxDialog)    
	EVT_BUTTON(ID_STARTCTRL_OK,   StartDialog::OnStart)
END_EVENT_TABLE()


//��ʼ���ڹ��캯��
StartDialog::StartDialog(wxWindow *parent,
					wxWindowID id, 
					const wxString& title,
					const wxPoint&  pos, 
					const wxSize& size,
					long  style,
					const wxString& name)
					:wxDialog(parent,id,title,pos,size,style,name)
{
	//wxStaticText *startNameText = new wxStaticText(this, -1, "������ʼ����ť��ʼ��ʱ",wxPoint(00, 10),wxSize(150, 20));
	//wxButton* startButton = new wxButton(this, ID_STARTCTRL_OK,"��ʼ��ʱ", wxPoint(00,40), wxSize(150,80));
	wxButton* startButton = new wxButton(this, ID_STARTCTRL_OK,"��ʼ��ʱ");
}

void StartDialog::OnStart(wxCommandEvent& event){
	startTime = wxDateTime::Now();
}