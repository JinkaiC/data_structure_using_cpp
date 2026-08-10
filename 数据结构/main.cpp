#include "MyArray.h"
#include "MyDynamicArray.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "MyLinkedList.h"
#include "MyBST.h"

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

void testMyArrayQueue() {
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

void testMyLoopQueue() {
    std::cout << "Testing MyLoopQueue..." << std::endl;

    // ---------- 1. 基本入队出队 ----------
    MyLoopQueue<int> queue(10);  // 有效容量为10，内部 array 容量为11
    std::cout << "Initial capacity (effective): " << queue.getCapacity() << std::endl;
    std::cout << "Initial size: " << queue.getSize() << std::endl;
    queue.readMyQueue();

    // 入队 5 个元素
    for (int i = 1; i <= 5; ++i) {
        queue.enqueue(i);
    }
    queue.readMyQueue();
    std::cout << "Front element: " << queue.getFront() << std::endl;

    // 出队 3 个元素
    for (int i = 0; i < 3; ++i) {
        std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    }
    queue.readMyQueue();

    // 再入队 5 个元素，此时 tail 会绕回（因为之前出队腾出了空间）
    for (int i = 6; i <= 10; ++i) {
        queue.enqueue(i);
    }
    queue.readMyQueue();
    std::cout << "Front element: " << queue.getFront() << std::endl;

    // ---------- 2. 测试扩容 ----------
    // 当前队列 size = 7 (1,2,3,4? 实际上我们出队了1,2,3，剩下4,5，再入队6-10，所以有4,5,6,7,8,9,10 共7个元素)
    // 容量是10，还有3个空位，继续入队到满，再入队触发扩容
    std::cout << "\n--- Testing expansion ---" << std::endl;
    for (int i = 11; i <= 15; ++i) {
        queue.enqueue(i);   // 第11个入队时，队列满（10个元素），再入队会扩容到有效容量20
    }
    queue.readMyQueue();
    std::cout << "After expansion, capacity: " << queue.getCapacity() << ", size: " << queue.getSize() << std::endl;

    // 验证元素顺序是否正确：应该是 4,5,6,7,8,9,10,11,12,13,14,15 (共12个)
    // 出队检查
    std::cout << "Dequeue all elements: ";
    while (!queue.isEmpty()) {
        std::cout << queue.dequeue() << " ";
    }
    std::cout << std::endl;
    queue.readMyQueue();  // 应显示空

    // ---------- 3. 测试缩容 ----------
    std::cout << "\n--- Testing shrinkage ---" << std::endl;
    // 重新填充 15 个元素（初始容量10，会扩容到20）
    MyLoopQueue<int> queue2(10);
    for (int i = 1; i <= 15; ++i) {
        queue2.enqueue(i);
    }
    queue2.readMyQueue();
    std::cout << "Initial capacity after expansion: " << queue2.getCapacity() << std::endl;

    // 出队大量元素，使 size < capacity/4 (20/4=5) 且 capacity/2 >=10
    for (int i = 0; i < 12; ++i) {  // 出队12个，剩下3个
        queue2.dequeue();
    }
    queue2.readMyQueue();
    std::cout << "After dequeue 12 elements, capacity: " << queue2.getCapacity() << ", size: " << queue2.getSize() << std::endl;
    // 此时 size=3，capacity=20，3 < 5，且 20/2=10 >=10，应缩容到10
    // 再出队一个，触发缩容条件检查（每次出队都会检查）
    queue2.dequeue();
    queue2.readMyQueue();
    std::cout << "After one more dequeue, capacity: " << queue2.getCapacity() << ", size: " << queue2.getSize() << std::endl;
    // 此时 size=2，capacity 应为10（因为缩容到10）

    // ---------- 4. 边界情况 ----------
    std::cout << "\n--- Testing edge cases ---" << std::endl;
    MyLoopQueue<int> emptyQueue(5);
    // 空队列出队和取队首
    std::cout << "Dequeue from empty: " << emptyQueue.dequeue() << std::endl;
    std::cout << "GetFront from empty: " << emptyQueue.getFront() << std::endl;
    emptyQueue.readMyQueue();

    // 入队超出容量但未满？实际上入队到满后继续入队会自动扩容，不会出错

    // ---------- 5. 拷贝构造和赋值测试 ----------
    std::cout << "\n--- Testing copy constructor and assignment ---" << std::endl;
    MyLoopQueue<int> queue3(10);
    for (int i = 1; i <= 7; ++i) queue3.enqueue(i);
    queue3.readMyQueue();

    // 拷贝构造
    MyLoopQueue<int> queue4 = queue3;
    queue4.readMyQueue();
    std::cout << "Original front: " << queue3.getFront() << ", copy front: " << queue4.getFront() << std::endl;

    // 修改拷贝不影响原对象
    queue4.dequeue();
    queue4.enqueue(100);
    queue3.readMyQueue();
    queue4.readMyQueue();

    // 赋值
    MyLoopQueue<int> queue5(3);
    queue5 = queue3;
    queue5.readMyQueue();

    std::cout << "Finished testing MyLoopQueue." << std::endl;
}

void testMyNoRingLinkedList() {
    std::cout << "Testing MyNoRingLinkedList..." << std::endl;

    // ---------- 1. 构造与基本操作 ----------
    MyNoRingLinkedList<int> list;
    std::cout << "Empty? " << list.isEmpty() << ", size = " << list.getSize() << std::endl;

    // addFirst, addLast, addInPlace
    list.addFirst(10);
    list.addLast(30);
    list.addInPlace(1, 20);   // 10,20,30
    list.addInPlace(0, 5);    // 5,10,20,30
    list.addInPlace(4, 40);   // 5,10,20,30,40
    std::cout << "After inserts (size=" << list.getSize() << "): ";
    for (int i = 0; i < list.getSize(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;

    // getFirst, getLast
    std::cout << "First: " << list.getFirst() << ", Last: " << list.getLast() << std::endl;

    // set
    list.set(2, 99);   // 5,10,99,30,40
    std::cout << "After set(2,99): ";
    for (int i = 0; i < list.getSize(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;

    // contains
    std::cout << "Contains 99? " << list.contains(99) << std::endl;
    std::cout << "Contains 100? " << list.contains(100) << std::endl;

    // ---------- 2. 边界测试 ----------
    std::cout << "\n--- Edge cases ---" << std::endl;
    // 空链表 get
    MyNoRingLinkedList<int> emptyList;
    std::cout << "Empty list get(0): " << emptyList.get(0) << std::endl; // 越界，打印错误并返回0
    // 越界插入
    emptyList.addInPlace(5, 100); // 打印错误
    // 删除不存在（该类没有删除方法，但可以测试 set 越界）
    emptyList.set(0, 100); // 打印错误

    // ---------- 3. 拷贝构造与赋值 ----------
    std::cout << "\n--- Copy constructor and assignment ---" << std::endl;
    MyNoRingLinkedList<int> list2 = list; // 拷贝构造
    std::cout << "Copied list: ";
    for (int i = 0; i < list2.getSize(); ++i) {
        std::cout << list2.get(i) << " ";
    }
    std::cout << std::endl;

    MyNoRingLinkedList<int> list3;
    list3 = list; // 赋值
	std::cout << list.getSize() << "    " << list2.getSize() << "    " << list3.getSize() << std::endl;
    std::cout << "Assigned list: ";
    for (int i = 0; i < list3.getSize(); ++i) {
        std::cout << list3.get(i) << " ";
    }
    std::cout << std::endl;

    // 修改原列表，不影响拷贝/赋值
    list.addLast(999);
    std::cout << "Original after adding 999: ";
    for (int i = 0; i < list.getSize(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Copied list unchanged: ";
    for (int i = 0; i < list2.getSize(); ++i) {
        std::cout << list2.get(i) << " ";
    }
    std::cout << std::endl;

    // ---------- 4. 数组构造 ----------
    std::cout << "\n--- Array constructor ---" << std::endl;
    int arr[] = { 1, 2, 3, 4, 5 };
    MyNoRingLinkedList<int> listFromArray(arr, 5);
    std::cout << "From array: ";
    for (int i = 0; i < listFromArray.getSize(); ++i) {
        std::cout << listFromArray.get(i) << " ";
    }
    std::cout << std::endl;

    // ---------- 5. 大量操作（测试性能与内存） ----------
    std::cout << "\n--- Large operations ---" << std::endl;
    MyNoRingLinkedList<int> bigList;
    for (int i = 0; i < 100; ++i) {
        bigList.addLast(i);
    }
    std::cout << "Big list size: " << bigList.getSize() << std::endl;
    // 检查一些值
    std::cout << "bigList.get(50) = " << bigList.get(50) << std::endl;
    std::cout << "bigList.contains(99) = " << bigList.contains(99) << std::endl;
    std::cout << "bigList.contains(100) = " << bigList.contains(100) << std::endl;

    std::cout << "Finished testing MyNoRingLinkedList." << std::endl;
}

void testMyLinkedListStack() {
    std::cout << "Testing MyLinkedListStack..." << std::endl;

    // ---------- 1. 基本操作 ----------
    MyLinkedListStack<int> stack;
    std::cout << "Initial size: " << stack.getSize() << ", empty? " << stack.isEmpty() << std::endl;

    // 入栈 40 个元素
    for (int i = 1; i <= 40; ++i) {
        stack.push(i);
        if (i % 10 == 0) {
            std::cout << "After pushing " << i << ": ";
            stack.readMyLinkedListStack();
        }
    }

    // 查看栈顶
    std::cout << "Peek top: " << stack.peek() << std::endl;

    // ---------- 2. 出栈操作 ----------
    std::cout << "\n--- Pop operations ---" << std::endl;
    for (int i = 1; i <= 39; ++i) {
        int popped = stack.pop();
        if (i % 10 == 0) {
            std::cout << "After popping " << i << " times: ";
            stack.readMyLinkedListStack();
            std::cout << "Top element now: " << stack.peek() << std::endl;
        }
    }

    // 还剩一个元素
    std::cout << "Remaining top: " << stack.peek() << std::endl;
    std::cout << "Final size: " << stack.getSize() << std::endl;

    // ---------- 3. 清空栈 ----------
    std::cout << "\n--- Empty the stack ---" << std::endl;
    while (!stack.isEmpty()) {
        stack.pop();
    }
    stack.readMyLinkedListStack();
    std::cout << "Size after empty: " << stack.getSize() << ", empty? " << stack.isEmpty() << std::endl;

    // ---------- 4. 边界测试：空栈操作 ----------
    std::cout << "\n--- Edge cases ---" << std::endl;
    MyLinkedListStack<int> emptyStack;
    std::cout << "Peek on empty: " << emptyStack.peek() << std::endl;   // 依赖底层 getFirst() 处理
    std::cout << "Pop on empty: " << emptyStack.pop() << std::endl;     // 依赖 removeFirst() 处理
    emptyStack.readMyLinkedListStack();

    // ---------- 5. 大量数据测试（性能） ----------
    std::cout << "\n--- Large data test ---" << std::endl;
    MyLinkedListStack<int> bigStack;
    for (int i = 0; i < 1000; ++i) {
        bigStack.push(i);
    }
    std::cout << "Big stack size: " << bigStack.getSize() << std::endl;
    for (int i = 0; i < 500; ++i) {
        bigStack.pop();
    }
    std::cout << "After 500 pops, size: " << bigStack.getSize() << std::endl;
    std::cout << "Top: " << bigStack.peek() << std::endl;

    std::cout << "Finished testing MyLinkedListStack." << std::endl;
}

void testMyNRLLQueue() {
    std::cout << "Testing MyNRLLQueue..." << std::endl;
    // ---------- 1. 基本操作 ----------
    MyNRLLQueue<int> queue;
    std::cout << "Initial size: " << queue.getSize() << ", empty? " << queue.isEmpty() << std::endl;
    // 入队 40 个元素
    for (int i = 1; i <= 40; ++i) {
        queue.enqueue(i);
        if (i % 10 == 0) {
            std::cout << "After enqueueing " << i << ": ";
            queue.readMyQueue();
        }
    }
    // 查看队首
    std::cout << "Front element: " << queue.getFront() << std::endl;
    // ---------- 2. 出队操作 ----------
    std::cout << "\n--- Dequeue operations ---" << std::endl;
    for (int i = 1; i <= 39; ++i) {
        int dequeued = queue.dequeue();
        if (i % 10 == 0) {
            std::cout << "After dequeueing " << i << " times: ";
            queue.readMyQueue();
            std::cout << "Front element now: " << queue.getFront() << std::endl;
        }
    }
    // 还剩一个元素
    std::cout << "Remaining front: " << queue.getFront() << std::endl;
    std::cout << "Final size: " << queue.getSize() << std::endl;
    // ---------- 3. 清空队列 ----------
    std::cout << "\n--- Empty the queue ---" << std::endl;
    while (!queue.isEmpty()) {
        queue.dequeue();
    }
    queue.readMyQueue();
    std::cout << "Size after empty: " << queue.getSize() << ", empty? " << queue.isEmpty() << std::endl;
    // ---------- 4. 边界测试：空队列操作 ----------
    std::cout << "\n--- Edge cases ---" << std::endl;
    MyNRLLQueue<int> emptyQueue;
    std::cout << "GetFront on empty: " << emptyQueue.getFront() << std::endl;   // 依赖底层 getFirst() 处理
    std::cout << "Dequeue on empty: " << emptyQueue.dequeue() << std::endl;

	std::cout << "\nFinished testing MyNRLLQueue." << std::endl;
}

void testMyBST() {
	MyBST<int> bst;
	int testValues[8] = { 50, 30, 70, 20, 40, 60, 80, 55 };
    for(int v: testValues) {
        bst.insert(v);
	}
    std::cout << "BST size: " << bst.getSize() << std::endl;
    std::cout << "Contains 40? " << bst.contains(40) << std::endl;
    std::cout << "Contains 100? " << bst.contains(100) << std::endl;

    std::cout << "read MyBST:" << "\n";
    std::cout << "\nPre-order traversal: ";
    bst.readMyBST(0); // Pre-order
    std::cout << "\nIn-order traversal: ";
    bst.readMyBST(1); // In-order
    std::cout << "\nPost-order traversal: ";
    bst.readMyBST(2); // Post-order
    std::cout << "\nLevel-order traversal: ";
	bst.readMyBST(3); // Level-order
}

int main() {
    //testMyArray();
    //testMyDynamicArray();
    //testMyArrayStack();
    //testMyArrayQueue();
    //testMyLoopQueue();
    //testMyNoRingLinkedList();
    //testMyLinkedListStack();
    //testMyNRLLQueue();
    testMyBST();
    return 0;
}