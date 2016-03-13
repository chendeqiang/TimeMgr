#ifndef INCLUDED_STARTDIALOG_H
#define INCLUDED_STARTDIALOG_H

//对不支持预编译编译器要包含"wx/wx.h"
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
	//构造函数
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