//SQL使用

#ifndef _NOTEDAO_H__
#define _NOTEDAO_H__

#include "cocos2d.h"
#include "sqlite3.h"

using namespace std;
USING_NS_CC;
class NoteDAO
{
public:
	//获取数据库文件的全路径
	static string dbDirectoryFile();
	//初始化数据库
	static int initDB();

	//插入Note函数
	static int create(string pDate, string pContent);

	//删除Note函数
	static int remove(string pDate);

	//修改Note函数
	static int modeify(string pDate, string pContent);

	//查询all数据函数
	static ValueVector findAll();

	//按照主键查询数据函数
	static ValueMap findById(string pDate);
};
#endif