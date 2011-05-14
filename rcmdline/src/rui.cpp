#include "rui.h"

RUI::RUI()
	:_spliter(UI_DEFAULT_RESULT_SPLITER)
	,_spliterLength(UI_DEFAULT_RESULT_SPLITER_LEN) {
}

void RUI::show_warning(const string warning) {
	cout<<warning<<endl;
}

void RUI::show_check_result(const string result) {
	cout<<result<<endl;
}

void RUI::show_check_result_spliter() {
	for (int i = 0; i < _spliterLength; ++i) {
		printf("%s",_spliter.c_str());
	}
	printf("\n");
}

void RUI::set_spliter(const string spliter, int length) {
	if (spliter.empty() || length <= 0)
		return;
	_spliter = spliter;
	_spliterLength = length;
}
