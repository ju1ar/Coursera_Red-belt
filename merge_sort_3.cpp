#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ( distance( range_begin, range_end ) < 2 ) return;

	vector<typename RandomIt::value_type> elements( make_move_iterator(range_begin), 
													make_move_iterator( range_end ));

	auto left_border = elements.begin() + elements.size() / 3 ;
	auto right_border =  elements.begin() + 2*elements.size() / 3 ;

	MergeSort( elements.begin(), left_border);
	MergeSort( left_border, right_border);
	MergeSort( right_border, elements.end());


	vector<typename RandomIt::value_type> temp;

	merge( make_move_iterator( elements.begin() ), make_move_iterator( left_border ), 
		   make_move_iterator( left_border ),      make_move_iterator( right_border ), 
		   back_inserter( temp ));

	merge( make_move_iterator( temp.begin() ), make_move_iterator ( temp.end() ),
		   make_move_iterator ( right_border ), make_move_iterator ( elements.end() ), 
		                range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
