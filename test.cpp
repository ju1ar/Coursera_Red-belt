#include <iostream>
#include <array>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <utility>
#include <unordered_map>

using namespace std;

int main()
{
	unordered_map<int, int> test;

	cout << test.bucket_count() << endl;

}
