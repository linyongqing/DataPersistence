#ifndef  _UTILITY_H_
#define  _UTILITY_H_

#include "cocos2d.h"

using namespace std;

class MyUtility 
{
public:
	static string getCurrentTime();

	static string gbk_2_utf8(const string text);
};

#endif // _UTILITY_H_
