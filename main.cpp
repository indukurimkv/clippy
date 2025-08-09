#include <forward_list>
#include <iostream>
#include "clip.h"
#include <stdexcept>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

// Appned entries from cache file onto list
void ReadCache(const std::string, std::forward_list<std::string>&);
// Writes entries from list into cache file
void WriteCache(const std::string, const std::forward_list<std::string>&);


int main(){
  // History of copied text
  std::forward_list<std::string> copy_hist;
  // store currently copied text
  std::string temp;
  // store text copied on last iteration
  std::string last_copy;

  // Read in clipboard history from previous session
  ReadCache("cache.txt", copy_hist);
  while(true){
    // Check for new things in clipboard and record if true
    clip::get_text(temp);
    if(last_copy != temp){
      // Remove duplicate entries that may have been copied in the past
      copy_hist.remove_if([temp](std::string e){return e == temp;});
      copy_hist.push_front(temp);
    }
    last_copy = temp;

    //clear console
    std::cout << "\033[2J\033[1;1H";
    for(
      std::forward_list<std::string>::iterator it = copy_hist.begin();
      it != copy_hist.end(); it++
    ){
        std::cout << *it << std::endl;
     }
    WriteCache("cache.txt", copy_hist);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    temp.clear();
  }
  return 0;
}

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
    // handle malformed cache file.
    // if the size of next item is not present(or is malformed),
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
