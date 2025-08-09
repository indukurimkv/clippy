#include <forward_list>
#include <iostream>
#include "clip.h"
#include <string>
#include <thread>
#include <chrono>
#include "caching.h"


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
