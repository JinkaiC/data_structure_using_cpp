#include "MyArray.h"
int main() {
	MyArray arr;
	arr.addToEnd(0);
	arr.addToEnd(2);
	arr.addInPlace(1, 1);
	arr.addInPlace(-1, -1);
	arr.readArray();
	MyArray newarr(arr, 2);
	newarr.readArray();
	return 0;
}