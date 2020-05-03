// 505bonus.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Merge(int array[], int* left_part, int left_size, int* right_part, int right_size) {
	int i = 0, j = 0, k = 0;
	while (i < left_size && j < right_size) {
		if (left_part[i] < right_part[j])
			array[k++] = left_part[i++];
		else array[k++] = right_part[j++];
	}
	while (i < left_size)
		array[k++] = left_part[i++];
	while (j < right_size)
		array[k++] = right_part[j++];
}

void MergeSort(int array[], int length, int min, int threads, int current_threads) {
	int mid, * left_part, * right_part;
	if (length < 2)
		return;
	mid = length / 2;
	left_part = new int[mid];
	right_part = new int[length - mid];
	for (int i = 0; i < mid; i++)
		left_part[i] = array[i];
	for (int i = mid; i < length; i++)
		right_part[i - mid] = array[i];
	if (current_threads > threads or mid < min or length - mid < min) {
		MergeSort(left_part, mid, min, threads, current_threads * 2);
		MergeSort(right_part, length - mid, min, threads, current_threads * 2);
	}
	else {
		srand((unsigned)time(NULL));
		thread a(MergeSort, left_part, mid, min, threads, current_threads * 2);
		thread b(MergeSort, right_part, length - mid, min, threads, current_threads * 2);
		a.join();
		b.join();
	}
	Merge(array, left_part, mid, right_part, length - mid);
	delete[] right_part;
	delete[] left_part;
}

int main(int argc, char* argv[]) {
	if (argc > 4) {
		printf("Wrong input");
		exit(1);
	}
	int array[1000];
	int datalen=0, min, threads;
	min = atoi(argv[2]);
	threads = atoi(argv[3]);
	//const char filename[] = argv[1];
	ifstream file(argv[1]);
	while (!file.eof())
		file >> array[datalen++];
	file.close();
	MergeSort(array, 1000, min, threads, 1);
	//ofstream OutFile("test.txt");
	for (int i = 0; i < 1000; i++) {
		printf("%d ", array[i]);
		//OutFile << array[i] << endl;
	}
	//OutFile.close();
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
