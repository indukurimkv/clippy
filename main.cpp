#include <functional>
#include <iostream>
#include "clip.h"
#include <list>
#include <string>
#include <sys/types.h>
#include <thread>
#include <chrono>


int main(){
  std::hash<std::string> hasher;
  std::list<std::string> copy_hist;
  std::string temp;
  u_int32_t temp_hash;
  u_int32_t last_hash = 0;
  while(true){
    // Check for new things in clipboard and record if true
    clip::get_text(temp);
    temp_hash = hasher(temp);
    if(last_hash != temp_hash){
      copy_hist.remove_if([temp](std::string e){return e == temp;});
      copy_hist.insert(copy_hist.begin(), temp);
    }
    last_hash = temp_hash;

    //clear console
    std::cout << "\033[2J\033[1;1H";
    std::cout << copy_hist.size() << std::endl;
    for(
      std::list<std::string>::iterator it = copy_hist.begin();
      it != copy_hist.end(); it++
    ){
        std::cout << *it << std::endl;
     }
//    IncrementIndeces(copy_hist);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    temp.clear();
  }
  return 0;
}
