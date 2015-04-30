#include "NoteDAO.h"

string NoteDAO::dbDirectoryFile()
{
	FileUtils *pFileUtils = FileUtils::getInstance();
	string writeablePath = pFileUtils->getWritablePath();
	string fullPath = writeablePath + "NotesList.sqlite3";
	return fullPath;
}

int NoteDAO::initDB()
{
	FileUtils *pFileUtils = FileUtils::getInstance();

	string path = dbDirectoryFile();

	bool isExist = false;

	sqlite3 *db = nullptr;
	//sqlite3_open 打开数据库 第一个参数数据库文件的完整路径, 第二个参数是返回指针变量db的地址
	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false, "DB open failure");
	}
	else
	{
		char *err;
		string createSQL = "CREATE TABLE IF NOT EXISTS Note(cdate TEXT PPIMARY KEY, content TXT)";
		//sqlite3_exec 新建一个表，参数一：sqlite3的指针变量地址 参数二: 要执行的SQL语句，三：要回调的函数 四：回调函数的参数 五：执行的出错信息
		if (sqlite3_exec(db, createSQL.c_str(), NULL, NULL, &err) != SQLITE_OK)
		{
			sqlite3_close(db);
			CCASSERT(false, "create table failure");
		}
	}
	log("DB init sucess");
	return 0;
}

//插入Note方法
int NoteDAO::create(string pDate, string pContent)
{
	initDB();
	sqlite3 *db = nullptr;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		log("SQL is open fail");
	}
	else
	{
		string sqlStr = "INSERT OR REPLACE INTO note (cdate, content) VALUES (?,?)";
		sqlite3_stmt *statement;
		//预处理过程
		//sqlite3_prepare_v2 预处理语句，提高SQL语句的速度
		//第三个参数表示SQL字符串的长度 -1表示全部SQL字符串
		if (sqlite3_prepare_v2(db, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//绑定参数开始
			//sqlite3_bind_text 第二个参数：插入值得位置，第三个参数：插入的值，第四个参数：字符串的长度
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
			sqlite3_bind_text(statement, 2, pContent.c_str(), -1, NULL);

			//执行插入
			if (sqlite3_step(statement) != SQLITE_DONE) {
				CCASSERT(false, "Insert Data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

ValueMap NoteDAO::findById(string pDate)
{
	//初始化数据库
	initDB();
	sqlite3* db = NULL;
	ValueMap dict;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	}
	else {
		string qsql = "SELECT cdate,content FROM Note where cdate =?";
		sqlite3_stmt *statement;
		//预处理过程
		if (sqlite3_prepare_v2(db, qsql.c_str(), -1, &statement, NULL) == SQLITE_OK) {

			//绑定参数开始
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);

			//执行
			if (sqlite3_step(statement) == SQLITE_ROW) {

				char *cdate = (char *)sqlite3_column_text(statement, 0);
				char *content = (char *)sqlite3_column_text(statement, 1);

				dict["date"] = Value(cdate);
				dict["content"] = Value(content);
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return dict;
}

ValueVector NoteDAO::findAll()
{
	//初始化数据库
	initDB();

	sqlite3 *db = nullptr;
	string path = dbDirectoryFile();
	ValueVector listData;
	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		log("SQL open fail");
	}
	else
	{
		string qsql = "SELECT cdate, content From Note";
		sqlite3_stmt *statement;
		//预处理
		if (sqlite3_prepare_v2(db, qsql.c_str(), -1, &statement, NULL) == SQLITE_OK)
		{
			while (sqlite3_step(statement) == SQLITE_ROW)
			{
				char *cdate = (char *)sqlite3_column_text(statement, 0);
				char *content = (char *)sqlite3_column_text(statement, 1);
				ValueMap dict;
				dict["date"] = Value(cdate);
				dict["content"] = Value(content);

				listData.push_back(Value(dict));
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return listData;
}


int NoteDAO::remove(string pDate)
{
	initDB();

	sqlite3 *db = nullptr;
	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		log("SQL open fail");
	}
	else
	{
		sqlite3_stmt *statement;
		string sqlstr = "DELETE from Note where cdate =?";
		//预处理
		if (sqlite3_prepare_v2(db, sqlstr.c_str(), -1, &statement, NULL) == SQLITE_OK)
		{
			//绑定参数开始
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
			//执行删除
			if (sqlite3_step(statement) == SQLITE_DONE)
				log("date delete sucess");
			else
				log("date delete fail");
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

int NoteDAO::modeify(string pDate, string pContent)
{
	initDB();
	sqlite3 *db = nullptr;
	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		log("SQL open fail");
	}
	else
	{
		sqlite3_stmt *statment;
		string sqlstr = "UPDATE Note set content = ? where cdate = ?";
		//预处理
		if (sqlite3_prepare_v2(db, sqlstr.c_str(), -1, &statment, NULL) == SQLITE_OK)
		{
			//绑定参数
			sqlite3_bind_text(statment, 1, pDate.c_str(), -1, NULL);
			sqlite3_bind_text(statment, 2, pContent.c_str(), -1, NULL);
			//执行更新
			if (sqlite3_step(statment) != SQLITE_DONE)
				log("update date fail");
		}
		sqlite3_finalize(statment);
		sqlite3_close(db);
	}


	return 0;
}

