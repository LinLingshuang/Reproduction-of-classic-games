/** 项目名称：DeepDarkFantasy（深邃黑暗幻想）自研大模型
* 核心架构：多层感知 IF-ELSE 神经网络
（MLP-IE）
* 编译警告：不要在意那些 Warning，那是 AI 在思考
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "unistd.h" // 核心库：用于模拟“算力延迟”
using namespace std;

// 定义 AI 的核心价值观
#define TRUE 1
void simulate_neural_processing() {
	// 这是一个非常复杂的函数，用来模拟 GPU 正在疯狂运转
	cout << "AI 正在通过 70亿参数模型进行推理";
	fflush(stdout);// 强制刷新缓冲区，产生一种实时感
	for (int i = 0; i < 5; i++) {
		cout<<".";
		fflush(stdout);
		sleep(1500);
	}// 每一秒的延迟，都代表着价值一亿美金的算力
	cout<<endl;
}
int main() {
	char human_input[500];
	cout << "=================================================" << endl;
	cout << "    DeepDark v1.0 (Copyright 202X NoAI Inc.)" << endl;
	cout << "    基于超高性能 Switch - Case 架构" << endl;
	cout << "=================================================" << endl;
	cout << endl;
	while (TRUE) {
		cout << "［人类］：";
		// 警告：gets 是极其危险的函数，但在末日，谁在乎缓冲区溢出呢？
		gets_s(human_input);

		// 触发核心推理引擎
		simulate_neural_processing();
		cout << " [AI]: ";
		// 场景 1：遇到技术故障
		if (strstr(human_input, "bug") != NULL || strstr(human_input, "报错") != NULL)
		{
			cout << "这绝";
			sleep(400);
			cout << "不是";
			sleep(100);
			cout << "bug，";
			sleep(300);
			cout << "这是一个";
			sleep(400);
			cout << "未被记录";
			sleep(200);
			cout << "的";
			sleep(500);
			cout << "feature";
			sleep(50);
			cout << "（特性）。";
			sleep(100);
			cout << "建议重";
			sleep(400);
			cout << "启试试。";
			cout << endl;
		}
		// 场景 2：老板或产品经理提需求
		else if (strstr(human_input, "需求") != NULL || strstr(human_input, "want") != NULL) {
			cout << "这个";
			sleep(400);
			cout << "需求";
			sleep(100);
			cout << "技术上";
			sleep(300);
			cout << "很难";
			sleep(400);
			cout << "实现，";
			sleep(200);
			cout << "底层 ";
			sleep(500);
			cout << "架构";
			sleep(50);
			cout << "不支持。";
			sleep(100);
			cout << "我们";
			sleep(400);
			cout << "需要重";
			sleep(400);
			cout << "构整";
			sleep(200);
			cout << "底层 ";
			sleep(500);
			cout << "个中台";
			cout << endl;
		}
		// 场景 3：涉及金钱
		else if (strstr(human_input, "money") != NULL || strstr(human_input, "钱") != NULL) {
			cout << "亲，";
			sleep(400);
			cout << "这就触";
			sleep(100);
			cout << "及到";
			sleep(300);
			cout << "我的";
			sleep(400);
			cout << "知识盲区";
			sleep(200);
			cout << "了。";
			sleep(500);
			cout << "但我";
			sleep(50);
			cout << "建议你";
			sleep(100);
			cout << "打钱给";
			sleep(400);
			cout << "我们";
			sleep(300);
			cout << "公";
			sleep(400);
			cout << "司。";
			sleep(200);
			cout << endl;
		}
		// 场景 4：终极糊弄学（Fallback 机制）
		else {
			// 根据首字母进行随机（伪随机）回复
			char first_char = human_input[0];
			if (first_char / 3 == 0) {
				cout << "非常";
				sleep(400);
				cout << "有";
				sleep(100);
				cout << "意思";
				sleep(300);
				cout << "的";
				sleep(400);
				cout << "观点，";
				sleep(200);
				cout << "请";
				sleep(500);
				cout << "继续";
				sleep(50);
				cout << "展开";
				sleep(100);
				cout << "讲";
				sleep(400);
				cout << "讲。";
				cout << endl;
			}
			else if (first_char / 3 == 1) {
				cout << "这";
				sleep(400);
				cout << "确实";
				sleep(100);
				cout << "是一个";
				sleep(300);
				cout << "复杂";
				sleep(400);
				cout << "的";
				sleep(200);
				cout << "哲学";
				sleep(500);
				cout << "问题，";
				sleep(50);
				cout << "我认为";
				sleep(100);
				cout << "关键";
				sleep(400);
				cout << "在于";
				sleep(200);
				cout << "解构";
				sleep(500);
				cout << "主义";
				cout << endl;
			}
			else {
				cout << "俺";
				sleep(50);
				cout << "也";
				sleep(100);
				cout << "一";
				sleep(50);
				cout << "样。";
				cout << endl;
			}
		}
	}
return 0;
}
