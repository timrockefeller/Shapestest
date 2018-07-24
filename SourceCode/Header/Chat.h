#pragma once
#include <string>
#include <vector>
class Chat {
public :
	//存储两个位置的精灵接口名字
	std::string left_str;
	std::string right_str;
	//谁在说话（0:left,1:right,默认左,-1:全幅画面）
	int onChating=0;
	//存对话信息
	std::vector<std::string> diags;
/*	
	std::string getleft_str();
	void setleft_str(std::string left);
	std::string getright_str();
	void setright_str(std::string right);
	*/
};