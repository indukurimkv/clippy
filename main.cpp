#include <functional>
#include <iostream>
#include "clip.h"
#include <string>
#include <vector>
#include <sys/types.h>

int main(){
  std::hash<std::string> hasher;
  std::vector<std::string> copy_hist;
  std::string temp;
  u_int32_t temp_hash;
  u_int32_t last_hash = 0;
  while(true){
    // Check for new things in clipboard and record if true
    clip::get_text(temp);
    temp_hash = hasher(temp);
    if(last_hash != temp_hash){
      copy_hist.push_back(temp);
    }
    last_hash = temp_hash;

    //clear console
    std::cout << "\033[2J\033[1;1H";
    std::cout << copy_hist.size() << std::endl;
     for(int i = 0; i < copy_hist.size(); i++){
       std::cout << copy_hist.at(i) << '\n';
     }
//    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    temp.clear();
  }
  return 0;
}
