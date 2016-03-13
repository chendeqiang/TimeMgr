#ifndef INCLUDED_STARTDIALOG_H
#define INCLUDED_STARTDIALOG_H

//�Բ�֧��Ԥ���������Ҫ����"wx/wx.h"
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
       #include "wx/wx.h"
#endif

#include "common.h"

enum{
	ID_STARTCTRL_OK = 200
};

class StartDialog : public wxDialog
{
public: 
	//���캯��
	StartDialog(wxWindow *parent,
		wxWindowID id, 
		const wxString& title,
		const wxPoint&  pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize,
		long  style = wxDEFAULT_DIALOG_STYLE,
		const wxString &  name = wxDialogNameStr);


	void OnStart(wxCommandEvent& event);
	DECLARE_EVENT_TABLE();
};

#endif