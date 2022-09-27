#include "pgi140/pgi_control.h"

int main()
{
  pgi pgi140(std::string("/dev/PGI"), uint32_t(115200));
  if(!pgi140.isInit())  pgi140.initSingle();
  uint16_t pos=0;
  while(true)
  {
    std::cout<<"position:"<<std::endl;
    std::cin>>pos;
    pgi140.setall(pos,true);
    std::cout<<(pgi140.isGripCur()?"Grip YES":"Grip NO")<<std::endl;
    // std::cout<<(pgi140.isDropCur()?"Drop YES":"")<<std::endl;
    // sleep(1);
  }
}