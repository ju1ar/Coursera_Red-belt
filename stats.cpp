#include "stats.h"
#include <iostream>


HttpRequest ParseRequest(string_view line)
{
	HttpRequest hq;

	while ( line.front() == ' ') { line.remove_prefix( 1 ); }

	size_t space = line.find(' ');
	hq.method = line.substr( 0, space );

	line.remove_prefix( space + 1 );
	space = line.find(' ');
	hq.uri = line.substr( 0, space );

	line.remove_prefix( space + 1 );
	hq.protocol = line.substr( 0, line.npos );

	return hq;
}


void Stats::AddMethod(string_view method)
{
	auto is_known = method_stats.find( method );

	if ( is_known != method_stats.end() )  
		 method_stats[ method ]++;
	else
		 method_stats[ "UNKNOWN" ]++;
}

void Stats::AddUri(string_view uri)
{
	auto is_known = uri_stats.find( uri );

	if ( is_known != uri_stats.end() )  
		 uri_stats[ uri ]++;
	else
		 uri_stats[ "unknown" ]++;
}

const map<string_view, int>& Stats::GetMethodStats() const
{
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const
{
	return uri_stats;
}

