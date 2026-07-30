#include "MyArray.h"
#include "MyDynamicArray.h"
#include "MyStack.h"
#include "MyQueue.h"

void testMyArray() {
	std::cout << "Testing MyArray..." << std::endl;
	MyArray<int> arr;
	arr.addLast(0);
	arr.addLast(2);
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
	MyDynamicArray<int> arr(50);
	arr.addLast(0);
	arr.addLast(2);
	arr.addInPlace(1, 1);
	arr.addInPlace(-1, -1);
	arr.readArray();
	MyDynamicArray<int> newarr(arr);
	newarr.readArray();
	newarr.addInPlace(3, 3);
	newarr.addLast(4);
	newarr.readArray();
	arr.remove(2);
	arr.readArray();
	arr.removeElementOnce(0);
	arr.readArray();
	for(int i=0;i<21;i++){
		arr.addLast(i);
		if(i%10==0){
			arr.readArray();
		}
	}
	std::cout << "Finished testing MyDynamicArray." << std::endl;
}

void testMyArrayStack() {
	std::cout << "Testing MyArrayStack..." << std::endl;
	MyArrayStack<int> stack;
	for(int i=1;i<=40;i++){
		stack.push(i);
	}
	for (int i = 1; i <= 39; i++) {
		int presentPopElement = stack.pop();
		if(i%5==0){
			stack.readMyArrayStack();
		}
	}
	std::cout << stack.peek() << std::endl;
	while (!stack.isEmpty())
	{
		stack.pop();
	}
	stack.readMyArrayStack();
	std::cout << "Finished testing MyArrayStack." << std::endl;
}

void testMyQueue() {
	std::cout << "Testing MyQueue..." << std::endl;
	MyArrayQueue<int> queue;
	for(int i=1;i<=40;i++){
		queue.enqueue(i);
		if (i % 10 == 0) {
			queue.readMyQueue();
		}
	}
	for (int i = 1; i <= 39; i++) {
		int presentDequeueElement = queue.dequeue();
		if(i%10==0){
			queue.readMyQueue();
			std::cout << "Front element: " << queue.getFront() << std::endl;
		}
	}
	std::cout << queue.getFront() << std::endl;
	while (!queue.isEmpty())
	{
		queue.dequeue();
	}
	queue.readMyQueue();
	std::cout << "Finished testing MyQueue." << std::endl;
}

int main() {
	//testMyArray();
	//testMyDynamicArray();
	//testMyArrayStack();
	testMyQueue();
	return 0;
}