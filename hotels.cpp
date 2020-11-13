#include <iostream> 
#include <algorithm> 
#include <map> 
#include <set> 
#include <vector> 
#include <cstdint>

using namespace std;

class TimeStep
{
public:
	TimeStep( int64_t t, size_t r, unsigned long cl )
		: time(t), rooms_by_step(r), client(cl) {}
	int64_t time;
	size_t rooms_by_step;
	unsigned long client;

	bool operator<( const TimeStep& other ) const
		{ return time < other.time; }
};

class Info
{
public:
	Info() {total_rooms = 0; } 
	void AddTimeStep( int64_t time, unsigned long client_id, size_t room_count );
	unsigned long GetRoomsLastDay  ( int64_t time );
	unsigned long GetClientsLastDay( int64_t time );


private:
	vector<TimeStep> time_steps;
	unsigned long total_rooms;
	set<unsigned long> all_clients;
};

class Booking
{
private:
	map< string, Info > hotel_books;
	int64_t curr_time;
public:
	void Book( int64_t time, string hotel_name, 
			   unsigned long client_id, unsigned long room_count );

	unsigned long Rooms  ( string hotel_name ) ;
	unsigned long Clients( string hotel_name ) ;
};




unsigned long Booking::Clients( string hotel_name ) 
{
	if ( hotel_books.find( hotel_name) == hotel_books.end() )
		return 0;

	auto& hotel = hotel_books[ hotel_name ];

	return hotel.GetClientsLastDay( curr_time );
}



void Booking::Book( int64_t time, string hotel_name, 
				    unsigned long client_id, unsigned long room_count )
{
	curr_time = time;
	auto& hotel = hotel_books[ hotel_name ];

	hotel.AddTimeStep( time, client_id, room_count );
}

unsigned long Booking::Rooms  ( string hotel_name ) 
{
	if ( hotel_books.find( hotel_name) == hotel_books.end() )
		return 0;

	auto& hotel = hotel_books[ hotel_name ];

	return hotel.GetRoomsLastDay( curr_time );
}


void Info::AddTimeStep( int64_t time, unsigned long client_id, size_t room_count )
{
	total_rooms += room_count;
	all_clients.insert( client_id );
	
	time_steps.push_back( {time, room_count, client_id} );
}

unsigned long Info::GetClientsLastDay( int64_t time )
{
	auto border = upper_bound( time_steps.begin(), time_steps.end(),
                              TimeStep(time - 86400, 0, 0) );

	if ( border == time_steps.begin() ) return all_clients.size();

	set<unsigned long> clients_last_day( all_clients.begin(), all_clients.end() );
	for (auto it = prev( border ); it >= time_steps.begin(); it-- )
		clients_last_day.erase( it->client );

	for (auto it = border; it < time_steps.end(); it++ )
		clients_last_day.insert( it->client );

	return clients_last_day.size();
}

unsigned long Info::GetRoomsLastDay( int64_t time )
{
	auto border = upper_bound( time_steps.begin(), time_steps.end(),
                              TimeStep(time - 86400, 0, 0) );

	if ( border == time_steps.begin() ) return total_rooms;

	unsigned long rooms_last_day = total_rooms;
	for (auto it = prev( border ); it >= time_steps.begin(); it-- )
			rooms_last_day -= it->rooms_by_step;

	return rooms_last_day;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	Booking booking;

    int query_count;
    cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) 
	{
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") 
		{
		    int64_t time = 0;
			string hotel_name;
			unsigned long client_id = 0;
			size_t room_count = 0;
			cin >> time >> hotel_name >> client_id >> room_count;
			booking.Book( time, hotel_name, client_id, room_count );

		} else if (query_type == "ROOMS") 
		{
			string hotel_name;
			cin >> hotel_name;
			cout << booking.Rooms( hotel_name )	<< '\n';
		}
		else if (query_type == "CLIENTS") 
		{
			string hotel_name;
			cin >> hotel_name;
			cout << booking.Clients( hotel_name )	<< '\n';
		}
	}

	return 0;
}
