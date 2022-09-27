#include "pgi140/pgi_control.h"

void pgi::initSingle()
{
  uint8_t out_buf[8] = {0x01, 0x06, 0x01, 0x00, 0x00, 0x01};
  uint8_t in_buf[8];
  setcommand(out_buf, in_buf, "initSingle");
  std::cout<<"gripper is initializing"<<std::endl;
  while(!isInit())  sleep(0.5);
  std::cout<<"gripper init succeed"<<std::endl;
}

void pgi::initDouble()
{
  uint8_t out_buf[8] = {0x01, 0x06, 0x01, 0x00, 0x00, 0xA5};
  uint8_t in_buf[8];
  setcommand(out_buf, in_buf, "initDouble");
  std::cout<<"gripper is initializing"<<std::endl;
  while(!isInit())  sleep(0.5);
  std::cout<<"gripper init succeed"<<std::endl;
}

void pgi::setall(uint16_t position,bool block,uint16_t force, uint16_t speed)
{
  if(speed != SPEED)
  {
    setSpeed(speed);
  }
  if(force != FORCE)
  {
    setForce(force);
  }
  setPos(position);
  if(block)
  {
    while(isBusy()) sleep(0.5);
  }
}

void pgi::setPos(uint16_t command)
{
  uint8_t out_buf[8] = {0x01, 0x06, 0x01, 0x03, uint8_t(command >> 8), uint8_t(command & 0xFF)};
  uint8_t in_buf[8];
  setcommand(out_buf, in_buf, "setPos");
}

void pgi::setForce(uint16_t command)
{
  uint8_t out_buf[8] = {0x01, 0x06, 0x01, 0x01, uint8_t(command >> 8), uint8_t(command & 0xFF)};
  uint8_t in_buf[8];
  setcommand(out_buf, in_buf, "setForce");
}
void pgi::setSpeed(uint16_t command)
{
  uint8_t out_buf[8] = {0x01, 0x06, 0x04, 0x01, uint8_t(command >> 8), uint8_t(command & 0xFF)};
  uint8_t in_buf[8];
  setcommand(out_buf, in_buf, "setSpeed");
}

bool pgi::isInit()
{
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x00, 0x00, 0x01};
  uint8_t in_buf[8];
  readcommand(out_buf, in_buf, "isInit");
  return (in_buf[4]==0x01);
}

bool pgi::isBusy()
{
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x01, 0x00, 0x01};
  uint8_t in_buf[8];
  readcommand(out_buf, in_buf, "isBusy");
  return (in_buf[4]==0x00);
}

bool pgi::isGrip()
{
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x01, 0x00, 0x01};
  uint8_t in_buf[8];
  readcommand(out_buf, in_buf, "isGrip");
  std::cout << "isGrip: " << std::hex << (in_buf[4] & 0xff) <<std::endl;
  return (in_buf[4]==0x02);
}

bool pgi::isGripCur()
{
  uint16_t current = getCurrent();
  // std::cout << "isGripCur: " << current <<std::endl;
  if(current>CURRENTLOW && current<CURRENTHIGH)
  {
    return true;
  }
  return false;
}

bool pgi::isDrop()
{ 
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x01, 0x00, 0x01};
  uint8_t in_buf[8];
  size_t count =0;
  for(size_t i=0;i<3;++i)
  {
    readcommand(out_buf, in_buf, "isDrop");
    // std::cout << "isDrop: " << std::hex << (in_buf[4] & 0xff) <<std::endl;
    if(in_buf[4]!=0x03)
    {
      return false;
    }
  }
  return true;
}

bool pgi::isDropCur()
{
  for(size_t i=0;i<3;++i)
  {
    if(!isGripCur())  return true;
  }
  return false;
}

uint16_t pgi::getPos()
{
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x02, 0x00, 0x01};
  uint8_t in_buf[8];
  readcommand(out_buf, in_buf, "getPos");
  return ((in_buf[3] << 8) + (in_buf[4] & 0xFF));
}

uint16_t pgi::getCurrent()
{
  uint8_t out_buf[8] = {0x01, 0x03, 0x02, 0x04, 0x00, 0x01};
  uint8_t in_buf[8];
  readcommand(out_buf, in_buf, "getCurrent");
  return ((in_buf[3] << 8) + (in_buf[4] & 0xFF));
}

void pgi::setcommand(uint8_t *out_buf, uint8_t *in_buf, std::string command)
{
  if (!write(out_buf, 6))
  {
    ROS_ERROR_STREAM(command << " failed!");
    throw std::string(command + " failed!");
  }
  if (!read(in_buf, 8))
  {
    ROS_ERROR_STREAM(command << " failed!");
    throw std::string(command + " failed!");
  }
}

void pgi::readcommand(uint8_t *out_buf, uint8_t *in_buf, std::string command)
{
  if (!write(out_buf, 6))
  {
    ROS_ERROR_STREAM(command << " failed!");
    throw std::string(command + " failed!");
  }
  if (!read(in_buf, 7))
  {
    ROS_ERROR_STREAM(command << " failed!");
    throw std::string(command + " failed!");
  }
}