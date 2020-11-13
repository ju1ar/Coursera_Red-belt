#pragma once
#include <cstdint>
#include <iostream>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  const T* begin() const;
  const T* end() const; 
  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value) ;

  void PushBack(T&& value) ;
  // При необходимости перегрузите
  // существующие публичные методы

private:
  // Добавьте сюда поля
  T* data = nullptr ;
  size_t capacity_ = 0;
  size_t size_ = 0;
};
template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
{
	data = new T[ size ];
	capacity_ = size;
	size_ = size;
}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
	if ( capacity_ != 0 )
		delete[] data;
}

template <typename T>
T& SimpleVector<T>:: operator[](size_t index)
{
	if ( index >= size_ )
		throw invalid_argument( "wtf" );

	return data[ index ];
}

template <typename T>
const T* SimpleVector<T>::begin() const
{
	return data;
}



template <typename T>
const T* SimpleVector<T>::end() const
{
	return data +  size_;
}

template <typename T>
T* SimpleVector<T>::begin()
{
	return data;
}



template <typename T>
T* SimpleVector<T>::end()
{
	return data +  size_;
}

template <typename T>
size_t SimpleVector<T>::Size() const
{
	return size_;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const
{
	return capacity_;
}

template <typename T>
void SimpleVector<T>::PushBack(T&& value)
{

	if ( size_ == 0 ) 
	{
		capacity_ = 1;
		data = new T[1];
	}
	else if ( size_ != 0 && size_ == capacity_ ) 
	{
		capacity_ *= 2;
		T* tmp_data = new T[ capacity_ ];
		move( data, data + size_, tmp_data );

		delete[] data;
		data = tmp_data;
	}

	size_++;
	data[ size_-1 ] = move( value );
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value)
{

	if ( size_ == 0 ) 
	{
		capacity_ = 1;
		data = new T[1];
	}
	else if ( size_ != 0 && size_ == capacity_ ) 
	{
		capacity_ *= 2;
		T* tmp_data = new T[ capacity_ ];
		move( data, data + size_, tmp_data );

		delete[] data;
		data = tmp_data;
	}

	size_++;
	data[ size_-1 ] = move( value );
}
