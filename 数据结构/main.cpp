#include "MyArray.h"
#include "MyDynamicArray.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "MyLinkedList.h"
#include "MyBST.h"
#include "MySet.h"
#include "MyMap.h"

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
    std::cout << "\nIn-order traversal with stack：";
	bst.readMyBST(4); // In-order with stack
    std::cout << "\nRemove Element in BST\n";
    int save;
    bst.removeMaxElement(save);
	bst.readMyBST(1);
    std::cout << std::endl;
	bst.removeMinElement(save);
	bst.readMyBST(1);
    std::cout << std::endl;
    bst.removeOneElement(40);
	bst.readMyBST(1);
    std::cout << std::endl;
	bst.removeOneElement(100);//test remove value not in BST
    while (bst.getSize() > 0) {
		bst.removeMinElement(save);
    }
    std::cout<<"Last removed element: " << save << std::endl;
	//test remove from empty BST
    bst.removeOneElement(100);
	bst.removeMaxElement(save);
}

void testMyBSTSet() {
    std::cout << "Testing MyBSTSet..." << std::endl;

    // 1. 基本插入与大小
    MyBSTSet<int> set;
    std::cout << "Initial size: " << set.getSize() << ", isEmpty: " << set.isEmpty() << std::endl;

    int testValues[] = { 50, 30, 70, 20, 40, 60, 80, 55 };
    for (int v : testValues) {
        set.add(v);
    }
    std::cout << "After inserting 8 elements, size = " << set.getSize() << std::endl;   // 应为 8
    std::cout << "Contains 40? " << set.contains(40) << std::endl;   // true
    std::cout << "Contains 100? " << set.contains(100) << std::endl; // false

    // 2. 重复插入测试（集合不应增加大小）
    set.add(50);
    std::cout << "After inserting duplicate 50, size = " << set.getSize() << std::endl; // 仍为 8
    std::cout << "Contains 50? " << set.contains(50) << std::endl;   // true

    // 3. 删除元素
    set.remove(40);
    std::cout << "After removing 40, size = " << set.getSize() << std::endl;  // 7
    std::cout << "Contains 40? " << set.contains(40) << std::endl;   // false

    // 删除不存在的元素
    set.remove(100);
    std::cout << "After removing 100 (not exist), size = " << set.getSize() << std::endl; // 仍为 7

    // 4. 清空集合（逐个删除）
    while (!set.isEmpty()) {
        // 由于无法获得元素，我们可以用一个已知存在的元素删除，但更合理的是删除最小值/最大值？
        // 这里我们选择删除特定已知值，但为了通用性，我们可以依次删除剩余元素。
        // 由于无法遍历，只能通过已知存在的值删除。为了测试，我们按顺序删除初始插入的值中剩余的元素。
        // 简单起见，我们已知剩余元素有：50,30,70,20,60,80,55（40已删）
        // 但为了测试所有删除，我们可以依赖 remove 方法多次调用。
        // 这里我们直接循环删除已知存在的元素（但不知道内部结构），更好的方式是连续删除最小值，
        // 但集合没有提供该接口。因此只能通过 contains 判断是否存在，然后删除。
        // 我们用一个循环暴力尝试删除所有可能的值（但不够严谨）。
        // 实际测试中，我们可以用一套已知值列表，但为简便，我们删除刚才插入的所有值（除了40）。
        // 由于没有遍历接口，我们只能手动列出。
        int knownValues[] = { 50, 30, 70, 20, 60, 80, 55 };
        for (int v : knownValues) {
            if (set.contains(v)) {
                set.remove(v);
                std::cout << "Removed " << v << ", size now = " << set.getSize() << std::endl;
            }
        }
        // 由于循环中可能会重复删除已删除的，但 contains 检查过，所以不会重复。
        // 循环结束后应为空。
    }
    std::cout << "After clearing, size = " << set.getSize() << ", isEmpty = " << set.isEmpty() << std::endl;

    // 5. 边界测试：对空集合操作
    set.remove(10);
    std::cout << "Remove on empty set (should print not found message)" << std::endl;
    std::cout << "Contains 10? " << set.contains(10) << std::endl;

    std::cout << "Finished testing MyBSTSet." << std::endl;
}

void testMyNRLLSet() {
    std::cout << "Testing MyNRLLSet..." << std::endl;

    // 1. 基本插入与大小
    MyNRLLSet<int> set;
    std::cout << "Initial size: " << set.getSize() << ", isEmpty: " << set.isEmpty() << std::endl;

    int testValues[] = { 50, 30, 70, 20, 40, 60, 80, 55 };
    for (int v : testValues) {
        set.add(v);
    }
    std::cout << "After inserting 8 elements, size = " << set.getSize() << std::endl;   // 应为 8
    std::cout << "Contains 40? " << set.contains(40) << std::endl;   // true
    std::cout << "Contains 100? " << set.contains(100) << std::endl; // false

    // 2. 重复插入测试（集合不应增加大小）
    set.add(50);
    std::cout << "After inserting duplicate 50, size = " << set.getSize() << std::endl; // 仍为 8
    std::cout << "Contains 50? " << set.contains(50) << std::endl;   // true

    // 3. 删除元素
    set.remove(40);
    std::cout << "After removing 40, size = " << set.getSize() << std::endl;  // 7
    std::cout << "Contains 40? " << set.contains(40) << std::endl;   // false

    // 删除不存在的元素
    set.remove(100);
    std::cout << "After removing 100 (not exist), size = " << set.getSize() << std::endl; // 仍为 7

    // 4. 清空集合（逐个删除）
    while (!set.isEmpty()) {
        // 由于无法获得元素，我们可以用一个已知存在的元素删除，但更合理的是删除最小值/最大值？
        // 这里我们选择删除特定已知值，但为了通用性，我们可以依次删除剩余元素。
        // 由于无法遍历，只能通过已知存在的值删除。为了测试，我们按顺序删除初始插入的值中剩余的元素。
        // 简单起见，我们已知剩余元素有：50,30,70,20,60,80,55（40已删）
        // 但为了测试所有删除，我们可以依赖 remove 方法多次调用。
        // 这里我们直接循环删除已知存在的元素（但不知道内部结构），更好的方式是连续删除最小值，
        // 但集合没有提供该接口。因此只能通过 contains 判断是否存在，然后删除。
        // 我们用一个循环暴力尝试删除所有可能的值（但不够严谨）。
        // 实际测试中，我们可以用一套已知值列表，但为简便，我们删除刚才插入的所有值（除了40）。
        // 由于没有遍历接口，我们只能手动列出。
        int knownValues[] = { 50, 30, 70, 20, 60, 80, 55 };
        for (int v : knownValues) {
            if (set.contains(v)) {
                set.remove(v);
                std::cout << "Removed " << v << ", size now = " << set.getSize() << std::endl;
            }
        }
        // 由于循环中可能会重复删除已删除的，但 contains 检查过，所以不会重复。
        // 循环结束后应为空。
    }
    std::cout << "After clearing, size = " << set.getSize() << ", isEmpty = " << set.isEmpty() << std::endl;

    // 5. 边界测试：对空集合操作
    set.remove(10);
    std::cout << "Remove on empty set (should print not found message)" << std::endl;
    std::cout << "Contains 10? " << set.contains(10) << std::endl;

    std::cout << "Finished testing MyNRLLSet." << std::endl;
}

void testMyNRLLMap() {
    std::cout << "Testing MyNRLLMap..." << std::endl;

    // ---------- 1. 构造与基本操作 ----------
    MyNRLLMap<int, std::string> map;
    std::cout << "Initial size: " << map.getSize() << ", empty? " << map.isEmpty() << std::endl;

    // 插入键值对
    map.add(1, "one");
    map.add(2, "two");
    map.add(3, "three");
    std::cout << "After adding 3 pairs, size = " << map.getSize() << std::endl;

    // 获取值
    std::cout << "get(1) = " << map.get(1) << std::endl;
    std::cout << "get(2) = " << map.get(2) << std::endl;
    std::cout << "get(3) = " << map.get(3) << std::endl;

    // 包含性测试
    std::cout << "contains(2)? " << map.contains(2) << std::endl;
    std::cout << "contains(5)? " << map.contains(5) << std::endl;

    // ---------- 2. 覆盖已有键 ----------
    map.add(2, "TWO");   // 应覆盖值，并打印提示
    std::cout << "After add(2, \"TWO\"), get(2) = " << map.get(2) << std::endl;

    // ---------- 3. set 更新 ----------
    map.set(3, "THREE");
    std::cout << "After set(3, \"THREE\"), get(3) = " << map.get(3) << std::endl;

    // 尝试 set 不存在的键（应打印错误）
    map.set(5, "five");

    // ---------- 4. 删除元素 ----------
    std::cout << "remove(2) = " << map.remove(2) << std::endl;   // 返回 "TWO"
    std::cout << "After removal, size = " << map.getSize() << std::endl;
    std::cout << "contains(2)? " << map.contains(2) << std::endl;

    // 删除不存在的键
    std::cout << "remove(10) = " << map.remove(10) << std::endl; // 打印错误并返回默认值

    // ---------- 5. 清空所有元素 ----------
    map.clear();
    std::cout << "After clear, size = " << map.getSize() << ", empty? " << map.isEmpty() << std::endl;

    // ---------- 6. 边界测试：空 map 操作 ----------
    std::cout << "get(1) on empty: " << map.get(1) << std::endl;
    map.remove(1);
    std::cout << "contains(1)? " << map.contains(1) << std::endl;

    // ---------- 7. 批量插入 ----------
    for (int i = 0; i < 10; ++i) {
        map.add(i, "value: key*10");
    }
    std::cout << "After inserting 10 elements, size = " << map.getSize() << std::endl;
    std::cout << "get(5) = " << map.get(5) << std::endl;

    std::cout << "Finished testing MyNRLLMap." << std::endl;
}

void testMyBSTMap() {
    std::cout << "Testing MyBSTMap..." << std::endl;

    // ---------- 1. 构造与基本操作 ----------
    MyBSTMap<int, std::string> map;
    std::cout << "Initial size: " << map.getSize() << ", empty? " << map.isEmpty() << std::endl;

    // 插入键值对（顺序打乱，测试 BST 结构）
    map.add(50, "fifty");
    map.add(30, "thirty");
    map.add(70, "seventy");
    map.add(20, "twenty");
    map.add(40, "forty");
    map.add(60, "sixty");
    map.add(80, "eighty");
    map.add(55, "fifty-five");
    std::cout << "After inserting 8 pairs, size = " << map.getSize() << std::endl;

    // 获取值
    std::cout << "get(50) = " << map.get(50) << std::endl;
    std::cout << "get(40) = " << map.get(40) << std::endl;
    std::cout << "get(55) = " << map.get(55) << std::endl;
    std::cout << "get(100) (not exist) = " << map.get(100) << std::endl; // 打印错误并返回默认

    // 包含性测试
    std::cout << "contains(60)? " << map.contains(60) << std::endl;
    std::cout << "contains(100)? " << map.contains(100) << std::endl;

    // ---------- 2. 覆盖已有键 ----------
    map.add(30, "THIRTY");   // 覆盖值
    std::cout << "After add(30, \"THIRTY\"), get(30) = " << map.get(30) << std::endl;

    // ---------- 3. set 更新 ----------
    map.set(70, "SEVENTY");
    std::cout << "After set(70, \"SEVENTY\"), get(70) = " << map.get(70) << std::endl;

    // 尝试 set 不存在的键
    map.set(90, "ninety");

    // ---------- 4. 删除元素 ----------
    std::cout << "remove(40) = " << map.remove(40) << std::endl;   // 返回 "forty"
    std::cout << "After removing 40, size = " << map.getSize() << std::endl;
    std::cout << "contains(40)? " << map.contains(40) << std::endl;

    // 删除不存在的键
    std::cout << "remove(100) = " << map.remove(100) << std::endl; // 打印错误并返回默认值

    // 删除根节点（50）
    std::cout << "remove(50) = " << map.remove(50) << std::endl;
    std::cout << "After removing root 50, size = " << map.getSize() << std::endl;
    std::cout << "contains(50)? " << map.contains(50) << std::endl;

    // 删除叶子节点（20）
    std::cout << "remove(20) = " << map.remove(20) << std::endl;
    std::cout << "size now = " << map.getSize() << std::endl;

    // ---------- 5. 清空所有元素 ----------
    map.clear();
    std::cout << "After clear, size = " << map.getSize() << ", empty? " << map.isEmpty() << std::endl;

    // ---------- 6. 边界测试：空 map 操作 ----------
    std::cout << "get(1) on empty: " << map.get(1) << std::endl;
    map.remove(1);
    std::cout << "contains(1)? " << map.contains(1) << std::endl;

    // ---------- 7. 批量插入 ----------
    for (int i = 0; i < 10; ++i) {
        map.add(i * 10, "val: key*10");
    }
    std::cout << "After inserting 10 elements, size = " << map.getSize() << std::endl;
    std::cout << "get(50) = " << map.get(50) << std::endl;

    std::cout << "Finished testing MyBSTMap." << std::endl;
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
    //testMyBST();
    //testMyBSTSet();
    //testMyNRLLSet();
    testMyNRLLMap();
    testMyBSTMap();
    return 0;
}