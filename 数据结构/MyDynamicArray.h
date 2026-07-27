#pragma once
#include "MyArray.h";

template<typename T>
class MyDynamicArray : public MyArray<T>
{
public:
	//构造函数，默认容量为10，调用父类构造函数
    MyDynamicArray(int capacity = 10) : MyArray<T>(capacity) {}

    //复制构造函数(与父类对比，不需要传入capacity参数)
    MyDynamicArray(const MyDynamicArray<T>& other) : MyArray<T>(other.capacity) {
        this->size = other.size;
        for (int i = 0; i < this->size; ++i) {
            this->data[i] = other.data[i];
        }
	}
	
	//添加元素n到位置p，空间不足时，动态扩容
	void addInPlace(T n, int p) {
        try {
            if (this->pIsOutOfRange(p)) {
                throw MyArray<T>::POUTOFRANGEERROR;
            }
            else {
                if (this->isFull()) {
                    this->resize(2 * this->capacity);
                }
                for (int i = this->size - 1; i >= p; --i) {
                    this->data[i + 1] = this->data[i];
                }
                this->data[p] = n;
                ++this->size;
            }
        }
        catch (int e) {
            if (e == MyArray<T>::POUTOFRANGEERROR) {
                std::cout << "error happened in addInPlace!\n";
                std::cout << "capacity = " << this->capacity << "\n";
                std::cout << "the index p is out of range!\n";
            }
        }
        catch (...) {
            std::cout << "errors happened in addInPlace\n";
            std::cout << "errors not defined in class MyArrayP happened.\n";
            throw std::logic_error("Unexpected error in addInPlace function"); // Rethrow as a standard exception
        }
	}
};