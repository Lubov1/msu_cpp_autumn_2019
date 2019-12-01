#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <stdexcept>

using namespace std;

template<class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	template<class... ArgsT>
	void construct(pointer ptr, ArgsT&& ... Args){
		new (ptr)T(std::forward<ArgsT>(Args)...);
	}
	pointer allocate(size_type size){
		return static_cast<pointer> (::operator new[](sizeof(value_type) * size));
	}
	void deallocate(pointer ptr, size_type size){
		::operator delete[](ptr);
	}
	void destroy(pointer ptr){
		ptr->~T();

	}
};


template <class T>
class Iterator
	: public iterator<random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using reference = T&;
	explicit Iterator(T* ptr)
		: ptr_(ptr){
	}

	bool operator==(const Iterator<T>& other) const{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) const{
		return !(*this == other);
	}

	reference operator*() const{
		return *ptr_;
	}

	Iterator& operator++(){
		++ptr_;
		return *this;
	}
	Iterator& operator--(){
		--ptr_;
		return *this;
	}
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using iterator = Iterator<T>;

	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using allocator_type = Alloc;
	using pointer = T*;
	size_type allocated;
	T* data;
	size_type used;
	explicit Vector(size_type count = 0){
		used = count;
		data = alloc.allocate(count * 2);
		allocated = count * 2;
		if (used != 0)
			for (pointer p = data; p != data + count; ++p){
				alloc.construct(p);
			}
	}
	explicit Vector(size_type count, const_reference value){
		used = count;
		data = alloc.allocate(count * 2);
		allocated = count * 2;

		for (pointer p = data; p != data + count; ++p){
			alloc.construct(p,value);
		}
	}
	iterator begin() noexcept{
		return iterator(data);
	}
	reverse_iterator<T> rbegin() noexcept{
		return reverse_iterator<T>(iterator(data));
	}

	iterator end() noexcept{
		return iterator(data+used);

	}
	reverse_iterator<T> rend() noexcept{
		return reverse_iterator<T>(iterator(data));
	}

	size_type size() const{
		return used;
	}

	void push_back(const value_type& value){
		if (used + 1 > allocated)
			reserve(allocated*2);
		alloc.construct(data + (used)++, value);
	}
	value_type pop_back(){
		used--;
		value_type el = move(data[used]);
		alloc.destroy(data + used);
		return el;
	}
	reference operator[](size_type pos){
		return data[pos];
	}
	bool empty()const{
		return this->used == 0;
	}

	void reserve(size_type count){
		pointer data1;
		if (count > allocated){
			data1 = alloc.allocate(count);
			for (pointer p = data1; p < data1 + used; p++){
				alloc.construct(p, move(*p));
				alloc.destroy(p);
			}
			alloc.deallocate(data, used);
			allocated = count;
			data = data1;

		}
	}
	void resize(size_type newSize){
		if (newSize > used){
			if(newSize >= allocated)
				alloc.reserve(newSize);
			for (pointer p = used+1; p<newSize; p++)
				alloc.construct(p);
		}
		if (newSize < used){
			for (pointer p = data + used; p > data + newSize; p--)
				alloc.destroy(p);
		}
		used = newSize;
	}
	void clear() noexcept{
		for (pointer p = data; p < data + used; p++)
			alloc.destroy(p);
		used = 0;
	}
	~Vector(){
		for (pointer p = data; p != data + used; ++p)
			alloc.destroy(p);
		alloc.deallocate(data, allocated);
	}
	private:
		Alloc alloc;
};

