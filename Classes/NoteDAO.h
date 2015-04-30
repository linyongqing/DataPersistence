//SQLʹ��

#ifndef _NOTEDAO_H__
#define _NOTEDAO_H__

#include "cocos2d.h"
#include "sqlite3.h"

using namespace std;
USING_NS_CC;
class NoteDAO
{
public:
	//��ȡ���ݿ��ļ���ȫ·��
	static string dbDirectoryFile();
	//��ʼ�����ݿ�
	static int initDB();

	//����Note����
	static int create(string pDate, string pContent);

	//ɾ��Note����
	static int remove(string pDate);

	//�޸�Note����
	static int modeify(string pDate, string pContent);

	//��ѯall���ݺ���
	static ValueVector findAll();

	//����������ѯ���ݺ���
	static ValueMap findById(string pDate);
};
#endif