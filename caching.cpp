#include "caching.h"
#include <fstream>
#include <iostream>

void ReadCache(const std::string file_path, std::forward_list<std::string>& history){
  std::ifstream cache_file;
  cache_file.open(file_path);
  if(cache_file.fail()){
    std::cout << "Cache file failed to open" << std::endl;
    return;
  }
  // store num bytes to read
  std::string n_bytes = "0";
  // temporarily store read in string
  std::string next_item;

  // Read number of bytes that next clipboard entry is and get the entry
  // push it to the list
  while( std::getline(cache_file, n_bytes, '|') ){
    // Handle malformed cache file.
    // If the size of next item is not present(or is malformed),
    // only use entries read in so far
    try{
      for(int i = 0; i < std::stoi(n_bytes); i++){
        next_item += cache_file.get();
      }
    } catch(std::invalid_argument){
      std::cout << "Failed to parse cache file! Only values read so far will be used!" << std::endl;
      return;
    }
    history.push_front(next_item);
    // Reset temp vars
    n_bytes.clear();
    next_item.clear();
  }
  cache_file.close();
  // since it reads in reverse, call reverse to get it in right order
  history.reverse();
}
void WriteCache(const std::string file_path, const std::forward_list<std::string>& history){
  std::ofstream cache_file;
  cache_file.open(file_path);
  if(cache_file.fail()){
    std::cout << "Failed to open cache file! Exiting..." << std::endl;
    return;
  }
  // for each entry, output number of bytes it is and then the entry itself
  for(
    std::forward_list<std::string>::const_iterator it = history.begin();
    it != history.end(); it++
  ){
    cache_file << it->length() << "|" << *it;
  }
  cache_file.close();
}
