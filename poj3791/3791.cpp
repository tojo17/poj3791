#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void solve(int ctKeys, double letterFreq[26]) {
	//将所有可能的演化方式模拟进行
	//筛掉无法完成分配的方式
	double avrStrike[26][26];//[m][n]，到第n个字母时使用了m个键。此时的平均击键数
	int ctLetter[26][26];//此时第m个键上的字母数
	double thisStrike = 0.0;//当前演化方式下的平均击键数
	//设定选择标记
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			avrStrike[i][j] = 9999.9;
		}
	}
	//首键单独处理防止数组越界
	for (int i = 0; i < 8; i++) {
		thisStrike += letterFreq[i] * (i + 1);
		avrStrike[0][i] = thisStrike;
		ctLetter[0][i] = i + 1;
	}
	//其他键位开始演化
	int maxLetters = 0;
	for (int i = 1; i < ctKeys; i++) {//i 为键位号
		for (int j = i; j < 26; j++) {//当前键上开始的字母，从可能的最前字母到z轮询
			maxLetters = 26 - (ctKeys - i - 1);//当前键可以放置的最多字母数
			if (maxLetters > 8) maxLetters = 8;
			if (j + maxLetters > 26) maxLetters = 26 - j;//防止数组越界
			thisStrike = avrStrike[i - 1][j - 1];//读取之前路径的总击键数便于比较
			if (thisStrike > 8999.0) {
				break;
			}//筛掉不存在的组合
			for (int k = 0; k < maxLetters; k++) {//尝试在当前键上放置不同数量的字母，比较击键数
				/*if (letterFreq[j + k] < 0) {
					cout << "ERR" << endl;
				}*/
				thisStrike += letterFreq[j + k] * (k + 1);
				//cout << thisStrike << endl;
				if (thisStrike < avrStrike[i][j + k]) {//若当前方案击键数更少，刷新保存的击键数，并保存当前分配方案
					avrStrike[i][j + k] = thisStrike;
					ctLetter[i][j + k] = k + 1;
				}
			}
		}
	}
	//演化完成
	//输出部分
	printf("%.3f ", avrStrike[ctKeys - 1][25]);
	char strBuff[53];//倒序查找序列，缓存后正序输出
	int p = 25 + ctKeys - 1;//26字母+空格数
	strBuff[p + 1] = '\0';
	int idx = 25;//字母表索引
	for (int i = ctKeys - 1; i >= 0; i--) {
		for (int j = 0; j < ctLetter[i][idx]; j++) {
			strBuff[p--] = 'A' + idx - j;
		}
		if (p > 0) strBuff[p--] = ' ';
		idx -= ctLetter[i][idx];
	}
	printf("%s\n", strBuff);
	return;
}




double letterFreq[26] = { 8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.075 };




int main() {
	//将输入的百分比转化为比例
	int ctKeys = 8;
	//double letterFreq[26] = { 8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.075 };
	for (int i = 0; i < 26; i++) letterFreq[i] /= 100.0;
	solve(ctKeys, letterFreq);
	return 0;
}
