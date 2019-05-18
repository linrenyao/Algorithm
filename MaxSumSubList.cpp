#include <iostream>
using namespace std;

//时间复杂度为O(n^3) 
int algorithm1(int list[],int n) {
	int MaxSum = 0,TempSum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			TempSum = 0;
			for (int k = j; k < n; k++) {
				TempSum += list[k];
				if (TempSum > MaxSum) MaxSum = TempSum;
			}
		}
	}
	return MaxSum;
}
// O(n^2)
int algorithm2(int list[], int n) {
	int MaxSum = 0, TempSum = 0;
	for (int i = 0; i < n; i++) {
		TempSum = 0;
		for (int j = i; j < n; j++) {
			TempSum += list[j];
			if (TempSum > MaxSum) MaxSum = TempSum;
		}
	}
	return MaxSum;
}
// 比较三个数的大小 return A > B ? A > C ? A : C : B > C ? B : C;
//                             return A > B? (A>C?A:C) : (B>C?B:C);
int max(int a, int b) {
	return a > b ? a : b;
}
//分治算法
int algorithm3(int *list,int start,int end) {
	int mid = (end + start) / 2;
	int num = (end - start) / 2;
	if (num >= 1) {
		int leftMaxSubListSum, RightMaxSubListSum;
		leftMaxSubListSum = algorithm3(list, start, mid);
		RightMaxSubListSum = algorithm3(list, mid, end);
		//左右两部分的最大子序列和
		int MaxSubListSum = 0, TempSubListSum = 0;
		int i = 0;
		while (num--) {
			TempSubListSum += list[mid-1-i];
			if (TempSubListSum > MaxSubListSum) MaxSubListSum = TempSubListSum;
			TempSubListSum += list[mid+i];
			if (TempSubListSum > MaxSubListSum) MaxSubListSum = TempSubListSum;
			i++;
		}
		int maxSum = max(leftMaxSubListSum, RightMaxSubListSum) > MaxSubListSum ? max(leftMaxSubListSum, RightMaxSubListSum) : MaxSubListSum;
		return maxSum;
	}
	else{ //当子列中只有一个元素时返回子列
		int MaxSubListSum = 0, TempSubListSum = 0;
		for (int i = start; i < end; i++) {
			TempSubListSum += list[i];
			if (TempSubListSum > MaxSubListSum) MaxSubListSum = TempSubListSum;
		}
		return MaxSubListSum;
	}
}
//在线处理算法 O(n)
int algorithm4(int list[], int n) {
	int MaxSum = 0, TempSum = 0;
	for (int i = 0; i < n; i++) {
		TempSum += list[i];
		if (TempSum > MaxSum) MaxSum = TempSum;
		else if(TempSum < 0) TempSum = 0;
	}
	return MaxSum;
}
# include<time.h>
double waste_cpu_time3(int(*algorithm)(int*, int,int), int *list,int first, int end) {
	clock_t start, stop;
	start = clock();
	algorithm(list, first,end);
	stop = clock();
	return (double)(stop - start) / CLOCKS_PER_SEC;//(stop - start) / CLOCKS_PER_SEC == s
}
double waste_cpu_time(int (*algorithm)(int*,int),int *list,int n) {
	clock_t start, stop;
	start = clock();
	algorithm(list,n);
	stop = clock();
	return (double)(stop - start)/ CLOCKS_PER_SEC;//(stop - start) / CLOCKS_PER_SEC == s
}
void random_array(int *arr, int n, int (*getNextRandom)(void)) {//函数指针，回调函数传参函数名
	for (int i = 0; i < n; i++) arr[i] = getNextRandom();
	return;
}
void print_array(int *arr, int n) {
	printf("[");
	for (int i = 0; i < n - 1; i++) printf("%d,", arr[i]);
	printf("%d]\n", arr[n - 1]);
	return;
}
#include <stdlib.h>
int random(void) {
	return rand()%10 - rand()%10; // -10~10随机数
}
int main() {
	int list[8] = { 4,-3,5,-2,-1,2,8,-2 };
	int MaxSubListSum = algorithm1(list, 8);
	cout << "algorithm1 result:"<<MaxSubListSum << endl;
	MaxSubListSum = algorithm2(list, 8);
	cout << "algorithm2 result:" << MaxSubListSum << endl;
	MaxSubListSum = algorithm3(list, 0,8);
	cout << "algorithm3 result:" << MaxSubListSum << endl;
	MaxSubListSum = algorithm4(list, 8);
	cout << "algorithm4 result:" << MaxSubListSum << endl;
	const int arr_len = 10000;//int arr[]使用栈内存，默认栈内存(1MB ,1024*1024/4 = 262144多，可修改stack大小)存储不了1000000*4byte,stack overflow
	int arr[arr_len];
	random_array(arr, arr_len, random);
	//print_array(arr, arr_len);
	double waste_time;
	waste_time = waste_cpu_time(algorithm4, arr, arr_len); //100000，0s，250000，0.001s
	cout << "algorithm4 waste cpu :" << waste_time << "s" << endl;
	waste_time = waste_cpu_time3(algorithm3, arr, 0,arr_len); //100000 0.018s
	cout << "algorithm3 waste cpu :" << waste_time << "s" << endl;
	waste_time = waste_cpu_time(algorithm2, arr, arr_len); //10000 waste 0.195 ,100000 15.658
	cout << "algorithm2 waste cpu :" << waste_time << "s" << endl;
	waste_time = waste_cpu_time(algorithm1, arr, arr_len);//5000,64s,10000,516.935s
	cout << "algorithm1 waste cpu :" << waste_time << "s" << endl;
	/*int a = 1, b = 2, c = 3,d = 4;
	int f = a > b ? a > c ? a > d ? a : d : c > d ? c : d : b > c ? b > d ? b : d : c > d ? c : d;
	cout << f << endl;*/
	system("pause");
	return 0;
}