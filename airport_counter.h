#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// TAirport should be enum with sequential items and last item TAirport::Last_
template <typename TAirport>
class AirportCounter 
{
public:
// конструктор по умолчанию: список элементов пока пуст
	AirportCounter() { InitItems(); }


	void InitItems()
	{
		size_t N = static_cast<uint32_t>(TAirport::Last_);

		for ( size_t i = 0; i < N; i++ )
			stata.push_back( { static_cast<TAirport>(i), 0 } );
	}



	// конструктор от диапазона элементов типа TAirport
	template <typename TIterator>
	AirportCounter(TIterator begin, TIterator end)
	{
		InitItems();
		for ( auto it = begin; it < end; it++ )
			stata[ static_cast<uint32_t>( *it ) ].second++;
	}

	// получить количество элементов, равных данному
	size_t Get(TAirport airport) const
	{
		return stata[  static_cast<uint32_t>( airport )  ].second;
	}

	// добавить данный элемент
	void Insert(TAirport airport)
	{
		stata[  static_cast<uint32_t>( airport )  ].second++;
	}

	// удалить одно вхождение данного элемента
	void EraseOne(TAirport airport)
	{
		stata[  static_cast<uint32_t>( airport )  ].second--;
	}

	// удалить все вхождения данного элемента
	void EraseAll(TAirport airport)
	{
		stata[  static_cast<uint32_t>( airport )  ].second = 0;
	}

	using Item = pair<TAirport, size_t>;
	using Items = array<Item, static_cast<uint32_t>(TAirport::Last_)>;

	// получить некоторый объект, по которому можно проитерироваться,
	// получив набор объектов типа Item - пар (аэропорт, количество),
	// упорядоченных по аэропорту
	Items GetItems() const
	{
		stata;
	}

private:
	Items stata;
};


