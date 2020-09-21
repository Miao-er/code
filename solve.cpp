// 八皇后问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
bool place[9][9];
bool R[17], L[17],column[9]; 
int num = 0;
void solution(int i);

int main()
{
	cout<<"this is my code."<<endl;
		solution(1);
	}
void solution(int i){
	int j;
	for (j = 1; j <= 8; j++){

		if (!place[i][j] && !L[i + j] && !R[i - j + 9] && !column[j]) {
			column[j] = true;
			place[i][j] = true;
			L[i + j] = true;
			R[i - j + 9] = true;
			if (i < 8)
				solution(i + 1);
			else {
				num++;
				cout << num << endl; 
				for (int m = 1; m < 9; m++) {
					for (int k = 1; k < 9; k++) {//这里要求按照每一列皇后的
						if (place[k][m])
							cout << "*";//行数最小优先顺序排列，即将原字符阵列转置
						else
							cout << ".";//因为原顺序是列数最小优先，故此处先对m循环，
						if (k != 8)
							cout << " ";//再对k循环
					}
					cout << endl;
				}
			}
			column[j] = false;
			place[i][j] = false;
			L[i + j] = false;
			R[i - j + 9] = false;
		}
	}
}
