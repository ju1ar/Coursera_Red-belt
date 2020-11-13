#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

int main()
{
	  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}

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

	/* merge( left.begin(), left.end(), right.begin(), right.end(), range_begin ); */
	merge(temp.begin(), temp.end(),
		  right_border, elements.end(), 
		                range_begin);
}
