#pragma once
#include <string>
#include <vector>
class Chat {
public :
	//�洢����λ�õľ���ӿ�����
	std::string left_str;
	std::string right_str;
	//˭��˵����0:left,1:right,Ĭ����,-1:ȫ�����棩
	int onChating=0;
	//��Ի���Ϣ
	std::vector<std::string> diags;
/*	
	std::string getleft_str();
	void setleft_str(std::string left);
	std::string getright_str();
	void setright_str(std::string right);
	*/
};