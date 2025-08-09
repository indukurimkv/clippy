#ifndef CACHING_H
#define CACHING_H
#include <string>
#include <forward_list>

// Appned entries from cache file onto list
void ReadCache(const std::string, std::forward_list<std::string>&);
// Writes entries from list into cache file
void WriteCache(const std::string, const std::forward_list<std::string>&);


#endif //header guard
