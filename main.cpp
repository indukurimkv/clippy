#include <forward_list>
#include <iostream>
#include "clip.h"
#include <string>
#include <sys/types.h>
#include <thread>
#include <chrono>
#include <fstream>

void ReadCache(std::string, std::forward_list<std::string>&);
void WriteCache(std::string, const std::forward_list<std::string>&);


int main(){
  // History of copied text
  std::forward_list<std::string> copy_hist;
  // store currently copied text
  std::string temp;
  // store text copied on last iteration
  std::string last_copy;
  std::ofstream cache_file;
  cache_file.open("cache.txt");
  if(cache_file.fail()){
    std::cout << "Failed to open cache file!" << std::endl;
    return 0;
  }
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
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    temp.clear();
  }
  return 0;
}

void ReadCache(std::string file_path, std::forward_list<std::string>& history){
  std::ifstream cache_file;
  cache_file.open(file_path);
  if(cache_file.fail()){
    std::cout << "Cache file failed to open" << std::endl;
    return;
  }
  // Implement cache file read here
}
void WriteCache(std::string file_path, const std::forward_list<std::string>& history){
  std::ofstream cache_file;
  cache_file.open(file_path);
  if(cache_file.fail()){
    std::cout << "Failed to open cache file! Exiting..." << std::endl;
    return;
  }
  std::string metadata;
  std::string output;
  for(
    std::forward_list<std::string>::const_iterator it = history.begin();
    it != history.end(); it++
  ){
    output += *it;
    metadata += std::to_string(it->length()) + "|";
  }
  cache_file << metadata << std::endl;
  cache_file << output;
}
