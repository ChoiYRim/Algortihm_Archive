#include <iostream>
#include <chrono>
#include <random>
#include "mergesort.h"

std::vector<int> arr;
const int kLimit = 100000;

int BinarySearch(int key)
{
	int left = 0,right = (int)arr.size()-1;

	while(left <= right)
	{
		int mid = (left+right)/2;

		if(arr[mid] == key)
			return arr[mid];
		else if(arr[mid] < key)
			left = mid+1;
		else
			right = mid-1;
	}

	return -1;
}

int LinearSearch(int key)
{
	for(int i = 0; i < (int)arr.size(); i++)
		if(arr[i] == key)
			return key;
	return -1;
}

int main(int argc,char* argv[])
{
	std::chrono::system_clock::time_point begin,end;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0,kLimit);

	arr.push_back(1000000);
	for(int i = 0; i < 10000000; i++)
		arr.push_back(static_cast<int>(dis(gen)));

	userdefine_mergesort::merge_sort<int> ms;
	ms.SetArray(arr);
	ms.mSort(0,static_cast<int>(ms.GetSize())-1);
	arr = ms.GetArray();

	begin = std::chrono::system_clock::now();
	std::cout << BinarySearch(1000000) << '\n';
	end = std::chrono::system_clock::now();
	auto timeResult = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
	std::cout << "Running Time(Binary Search) : " << timeResult.count() << " us\n";


	begin = std::chrono::system_clock::now();
	std::cout << LinearSearch(1000000) << '\n';
	end = std::chrono::system_clock::now();
	timeResult = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
	std::cout << "Running Time(Linear Search) : " << timeResult.count() << " us\n";

	return 0;
}
