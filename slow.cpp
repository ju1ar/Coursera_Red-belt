#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_num(MAX_USER_COUNT_ + 1, 0),
        page_users_count(MAX_PAGE_COUNT_ + 1, 0),
		active_users(0)   {}

  void Read(int user_id, int page_count) {
	  size_t old_pages_valuse = user_page_num[ user_id ];
	  if (  old_pages_valuse == 0 )	  active_users++;
	  else  page_users_count[ old_pages_valuse ]--;

	  user_page_num[ user_id ] = page_count;
	  page_users_count[ page_count ]++;
  }

	double Cheer(int user_id) const {
		size_t page_count = user_page_num[ user_id ];

		if ( page_count == 0)	return 0;
		if ( active_users == 1 && page_count > 0)	return 1;

		double num_less = accumulate( page_users_count.begin(), 
									  page_users_count.begin() + page_count, 0 );


		return num_less / (active_users - 1);
	}

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1000;

  /* vector<int> user_page_counts_; */
  /* vector<int> sorted_users_;   // отсортированы по убыванию количества страниц */
  /* vector<int> user_positions_; // позиции в векторе sorted_users_ */

    vector<int> user_page_num;
    vector<int> page_users_count;
	size_t active_users;

  /* int GetUserCount() const { */
  /*   return sorted_users_.size(); */
  /* } */
  /* void AddUser(int user_id) { */
  /*   sorted_users_.push_back(user_id); */
  /*   user_positions_[user_id] = sorted_users_.size() - 1; */
  /* } */
  /* void SwapUsers(int lhs_position, int rhs_position) { */
  /*   const int lhs_id = sorted_users_[lhs_position]; */
  /*   const int rhs_id = sorted_users_[rhs_position]; */
  /*   swap(sorted_users_[lhs_position], sorted_users_[rhs_position]); */
  /*   swap(user_positions_[lhs_id], user_positions_[rhs_id]); */
  /* } */
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;


  return 0;
}
