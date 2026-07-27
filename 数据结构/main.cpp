#include "MyArray.h"

void testMyArray() {
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
}

int main() {
	testMyArray;
	return 0;
}