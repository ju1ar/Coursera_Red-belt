#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <set>
#include <list>
#include <deque>

using namespace std;



template <typename T>
class PriorityCollection {
public:
  using Item = pair<T, size_t>;
  using Id = typename list<Item>::iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object)
  {
	  items.push_front( { move( object ), 0 } );

	  if ( items.size() == 1 || max_elem->second == 0)
		max_elem = items.begin();
						

	  return items.begin();
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
  {
	  for ( auto it = range_begin; it != range_end; it++ )
	  {
		 *( ids_begin++ )  = Add( *it );
	  }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const
  {
	  bool is_valid = false;
	  for ( auto it = items.begin(); it != items.end(); it++ )
	  {
		  if ( it == id ) { is_valid = true; break; }
	  }

	  return is_valid;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const
  {
	  return id->first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id)
  {
	  id->second++;

	  if ( id->second > max_elem->second )
		  max_elem = id;
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const
  {
	return { max_elem->first, max_elem->second };
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax()
  {
	auto to_return = make_pair( move( max_elem->first ), max_elem->second );
	items.erase( max_elem );

	return to_return;
  }

private:
  
  // Приватные поля и методы
	list<Item> items;
	Id max_elem;
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
    cout << 1 << endl;
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
  /* list<pair<T, size_t>> */ 
  PriorityCollection<int> ints;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
