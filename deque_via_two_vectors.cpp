#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque
{
public:
	Deque() : front_(), back_() {}

	bool Empty() const
	{
		return front_.empty() && back_.empty();
	}

	size_t Size() const
	{
		return front_.size() + back_.size();
	}

	T& operator[](size_t index) 
	{
		return ( index < front_.size() )? 
				front_[ front_.size() - (index+1) ] :
				back_ [ index - front_.size() ];
	}
	   
	const T& operator[](size_t index) const
	{
		return ( index < front_.size() )? 
				front_[ front_.size() - (index+1) ] :
				back_ [ index - front_.size()];
	}

	T& At(size_t index)
	{
		if ( index >= Size() )
			throw out_of_range("");

		return operator[](index);
	}

	const T& At(size_t index) const
	{
		if ( index >= Size() )
			throw out_of_range("");

		return operator[](index);
	}

	T& Front() 
	{
		return At(0);
	}
	T& Back() 
	{
		return At( Size() - 1 );
	}
	const T& Front() const
	{
		return At(0);
	}
	const T& Back() const
	{
		return At( Size() - 1 );
	}

	void PushFront( const T& elem )
	{
		front_.push_back( elem );
	}

	void PushBack( const T& elem )
	{
		back_.push_back( elem );
	}
	

private:
	vector<T> front_;
	vector<T> back_;
};


/* int main() */
/* { */
/* 	Deque<int> deq; */

/* 	/1* deq.PushBack( 7 ); *1/ */
/* 	/1* deq.PushBack( 8 ); *1/ */
/* 	/1* deq.PushBack( 8 ); *1/ */

/* 	/1* deq.PushFront( 3 ); *1/ */
/* 	/1* deq.PushFront( 2 ); *1/ */
/* 	/1* cout << deq.Front() << endl; *1/ */
/* 	/1* cout << deq.Back() << endl; *1/ */
/* 	cout << deq.Size() << endl; */
/* 	cout << deq.Front() << endl; */

	 
/* 	return 0; */
/* } */
