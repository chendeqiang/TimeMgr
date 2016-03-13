#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
       #include "wx/wx.h"
#endif
#include "wx/datetime.h"
#include "CDBSqlite.h"
#include <string>

static wxDateTime startTime;
static wxDateTime endTime;

static std::string gDBName = "./timeMgrData.db"; //���ݿ�·��������
//sqlite���ݿ��������
static CDBSqlite gSqlite(gDBName);

static std::string gInsertSql = "insert into things_set(start_time,end_time,do_things,priority) values(?,?,?,?)";

//��һ����ȡ��һ���ڵ����ݣ�7�죩
/*static std::string gFirstQrySql = "SELECT start_time,end_time,strftime('%s',end_time)-strftime('%s',start_time),do_things,priority,"
	"strftime('%w',start_time),strftime('%W',start_time),keyid from things_set order by start_time asc";*/

static std::string gFirstQrySql = "SELECT keyid,start_time,end_time,strftime('%s',end_time)-strftime('%s',start_time),do_things,priority,"
	"strftime('%w',start_time),strftime('%W',start_time) from things_set where "
	"strftime('%s',start_time)>(select strftime('%s',max(start_time))-7*24*60*60 from things_set) order by start_time asc";


//ʱ��ת�����������밴�մ�Сת��Ϊ���ʵĵ�λ��������ת�����string����
inline string timeConvert(int sec){
	char cTmp[32];
	string targetTime;
	memset(cTmp,'0',sizeof(cTmp));
	if( sec < 60){ //ʱ�䵥λ�жϣ�С��60��
		sprintf(cTmp,"%d",sec);
		targetTime = std::string(cTmp) + "��";
	}else if( sec < 60 * 60 ){ //С��60����
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/60);
		targetTime = std::string(cTmp) + "����";
	}else if( sec < 60*60*24){ //С��24Сʱ
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/(60*60));
		targetTime = std::string(cTmp) + "Сʱ";		
	}else{
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/(60*60*24));
		targetTime = std::string(cTmp) + "��";
	}

	return targetTime;
}

//�������ִ�0��ʼ������������
inline string GetDayOfWeek(int index){
	string target;
	switch(index){
		case 0:
			target = "������";
			break;
		case 1:
			target = "����һ";
			break;
		case 2:
			target = "���ڶ�";
			break;
		case 3:
			target = "������";
			break;
		case 4:
			target = "������";
			break;
		case 5:
			target = "������";
			break;
		case 6:
			target = "������";
			break;
	}
	
	return target;
}

#endif