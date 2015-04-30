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
	//sqlite3_open �����ݿ� ��һ���������ݿ��ļ�������·��, �ڶ��������Ƿ���ָ�����db�ĵ�ַ
	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false, "DB open failure");
	}
	else
	{
		char *err;
		string createSQL = "CREATE TABLE IF NOT EXISTS Note(cdate TEXT PPIMARY KEY, content TXT)";
		//sqlite3_exec �½�һ��������һ��sqlite3��ָ�������ַ ������: Ҫִ�е�SQL��䣬����Ҫ�ص��ĺ��� �ģ��ص������Ĳ��� �壺ִ�еĳ�����Ϣ
		if (sqlite3_exec(db, createSQL.c_str(), NULL, NULL, &err) != SQLITE_OK)
		{
			sqlite3_close(db);
			CCASSERT(false, "create table failure");
		}
	}
	log("DB init sucess");
	return 0;
}

//����Note����
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
		//Ԥ�������
		//sqlite3_prepare_v2 Ԥ������䣬���SQL�����ٶ�
		//������������ʾSQL�ַ����ĳ��� -1��ʾȫ��SQL�ַ���
		if (sqlite3_prepare_v2(db, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//�󶨲�����ʼ
			//sqlite3_bind_text �ڶ�������������ֵ��λ�ã������������������ֵ�����ĸ��������ַ����ĳ���
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
			sqlite3_bind_text(statement, 2, pContent.c_str(), -1, NULL);

			//ִ�в���
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
	//��ʼ�����ݿ�
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
		//Ԥ�������
		if (sqlite3_prepare_v2(db, qsql.c_str(), -1, &statement, NULL) == SQLITE_OK) {

			//�󶨲�����ʼ
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);

			//ִ��
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
	//��ʼ�����ݿ�
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
		//Ԥ����
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
		//Ԥ����
		if (sqlite3_prepare_v2(db, sqlstr.c_str(), -1, &statement, NULL) == SQLITE_OK)
		{
			//�󶨲�����ʼ
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
			//ִ��ɾ��
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
		//Ԥ����
		if (sqlite3_prepare_v2(db, sqlstr.c_str(), -1, &statment, NULL) == SQLITE_OK)
		{
			//�󶨲���
			sqlite3_bind_text(statment, 1, pDate.c_str(), -1, NULL);
			sqlite3_bind_text(statment, 2, pContent.c_str(), -1, NULL);
			//ִ�и���
			if (sqlite3_step(statment) != SQLITE_DONE)
				log("update date fail");
		}
		sqlite3_finalize(statment);
		sqlite3_close(db);
	}


	return 0;
}

