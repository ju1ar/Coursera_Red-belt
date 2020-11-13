#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate()
  {
	if ( freed.empty() )
	{
		T* new_active = new T;
		active.insert( new_active );
		return new_active;
	}
	else
	{
		T* to_active = freed.front();
		freed.pop();
		active.insert( to_active );
		return to_active;
	}
  }



  T* TryAllocate()
  {
	if ( freed.empty() )
	{
		return nullptr;
	}
	else
	{
		T* to_active = freed.front();
		freed.pop();
		active.insert( to_active );
		return to_active;
	}
  }

  void Deallocate(T* object)
  {
	  auto obj = active.find( object );

	  if ( obj == active.end() )
	  {
		  throw invalid_argument( "wtf" );
	  }


	  active.erase( obj );
	  freed.push( object );
  }

  ~ObjectPool()
  {
	  for ( auto& x : active )
		  delete x;
	  active.clear();

	  int f_size = freed.size();
	  for ( int i = 0; i < f_size; i++ )
	  {
		  delete freed.front();
		  freed.pop();
	  }
  }

private:
  // Добавьте сюда поля
  set<T*> active;
  queue<T*> freed;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
