#include <iostream> 
using namespace std;

int main() {
	// 随机数组
	int arr[10] = {9, 2, 4, 5, 3, 1, 8, 7, 6, 0};
	// 排序前
	cout << "排序前数组：" << endl;
	for (int y = 0; y < 10; y++) {
		cout << arr[y] << " ";
	}
	cout << endl;

	// 冒泡排序实现升序序列
	for (int i = 0; i < 9; i++) {  // 总轮数 = 元素个数 - 1
		for (int j = 0; j < 9 - i - 1; j++) {  // 每轮对比次数 = 元素个数 - 当前轮数 - 1
			if (arr[j] > arr[j + 1]) {  // 如果第一个数比第二个数大则交换
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	// 输出数组元素
	cout << "排序后数组：" << endl;
	for (int x = 0; x < 10; x++) {
		cout << arr[x] << " ";
	}
}
