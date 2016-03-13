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

static std::string gDBName = "./timeMgrData.db"; //数据库路径及名称
//sqlite数据库操作对象
static CDBSqlite gSqlite(gDBName);

static std::string gInsertSql = "insert into things_set(start_time,end_time,do_things,priority) values(?,?,?,?)";

//第一次先取出一星期的数据（7天）
/*static std::string gFirstQrySql = "SELECT start_time,end_time,strftime('%s',end_time)-strftime('%s',start_time),do_things,priority,"
	"strftime('%w',start_time),strftime('%W',start_time),keyid from things_set order by start_time asc";*/

static std::string gFirstQrySql = "SELECT keyid,start_time,end_time,strftime('%s',end_time)-strftime('%s',start_time),do_things,priority,"
	"strftime('%w',start_time),strftime('%W',start_time) from things_set where "
	"strftime('%s',start_time)>(select strftime('%s',max(start_time))-7*24*60*60 from things_set) order by start_time asc";


//时间转换函数，将秒按照大小转换为合适的单位，并返还转换后的string对象。
inline string timeConvert(int sec){
	char cTmp[32];
	string targetTime;
	memset(cTmp,'0',sizeof(cTmp));
	if( sec < 60){ //时间单位判断，小于60秒
		sprintf(cTmp,"%d",sec);
		targetTime = std::string(cTmp) + "秒";
	}else if( sec < 60 * 60 ){ //小于60分钟
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/60);
		targetTime = std::string(cTmp) + "分钟";
	}else if( sec < 60*60*24){ //小于24小时
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/(60*60));
		targetTime = std::string(cTmp) + "小时";		
	}else{
		sprintf(cTmp,"%.2f",static_cast<double>(sec)/(60*60*24));
		targetTime = std::string(cTmp) + "天";
	}

	return targetTime;
}

//传入数字从0开始，传出星期数
inline string GetDayOfWeek(int index){
	string target;
	switch(index){
		case 0:
			target = "星期天";
			break;
		case 1:
			target = "星期一";
			break;
		case 2:
			target = "星期二";
			break;
		case 3:
			target = "星期三";
			break;
		case 4:
			target = "星期四";
			break;
		case 5:
			target = "星期五";
			break;
		case 6:
			target = "星期六";
			break;
	}
	
	return target;
}

#endif