#pragma once
#include <string>
#include <vector>
class Chat {
public :
	//�洢����λ�õľ���ӿ�����
	std::string left_str;
	std::string right_str;
	//˭��˵����0:left,1:right,Ĭ����
	int speaking=0;
	//��Ի���Ϣ
	std::vector<std::string> diags;
};