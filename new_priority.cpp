#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  
  struct Item
  {
	T val;
	size_t prior;
	size_t n;

	bool operator<( const Item& other ) const
	{
		return tie( prior, n ) > tie( other.prior , other.n); 
	}
  };

  using Id = typename set< Item >::const_iterator; //const??

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object)
  {
	return items.insert( { move( object ), 0, add_count++ } ).first;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
  {
	  for ( auto it = range_begin; it != range_end; it++ )
		  *ids_begin++ = Add( move(*it ));
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const
  {
	  for ( auto it = items.begin(); it != items.end(); it++ )
		  if ( it == id ) return true;

	  return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const
  {
	  return id->val;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id)
  {
      auto nh = items.extract( id );
      nh.value().prior++;
      items.insert( move(nh) );
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const
  {
	return { items.begin()->val, items.begin()->prior };
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax()
  {
      auto nh = items.extract( items.begin() );

	  return { move( nh.value().val ), nh.value().prior  };
  }

private:
  // Приватные поля и методы
  set<Item> items;
  size_t add_count = 0;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
