#include "MyArray.h"
#include "MyDynamicArray.h"

void testMyArray() {
	std::cout << "Testing MyArray..." << std::endl;
	MyArray<int> arr;
	arr.addToEnd(0);
	arr.addToEnd(2);
	arr.addInPlace(1, 1);
	arr.addInPlace(-1, -1);
	arr.readArray();
	MyArray<int> newarr(arr, 2);
	newarr.readArray();
	arr.remove(2);
	arr.readArray();
	arr.removeElementOnce(0);
	arr.readArray();
	std::cout << "Finished testing MyArray." << std::endl;
}

void testMyDynamicArray() {
	std::cout << "Testing MyDynamicArray..." << std::endl;
	MyDynamicArray<int> arr;
	arr.addToEnd(0);
	arr.addToEnd(2);
	arr.addInPlace(1, 1);
	arr.addInPlace(-1, -1);
	arr.readArray();
	MyDynamicArray<int> newarr(arr);
	newarr.readArray();
	newarr.addInPlace(3, 3);
	newarr.readArray();
	arr.remove(2);
	arr.readArray();
	arr.removeElementOnce(0);
	arr.readArray();
	std::cout << "Finished testing MyDynamicArray." << std::endl;
}

int main() {
	testMyArray();
	testMyDynamicArray();
	return 0;
}