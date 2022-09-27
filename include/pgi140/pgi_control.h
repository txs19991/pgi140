#ifndef PGI_CONTROL_H
#define PGI_CONTROL_H
#include "pgi140/modbus_rtu_base.h"

#define SPEED 50
#define FORCE 20
#define CURRENTLOW 100
#define CURRENTHIGH 1000

class pgi : public modbusrtu
{
public:
  using modbusrtu::modbusrtu;
  /**
   * @brief 夹爪单向初始化
   *
   */
  void initSingle();
  /**
   * @brief 夹爪双向初始化
   *
   */
  void initDouble();
  /**
   * @brief 设定夹爪位置，速度，闭合力和是否阻塞
   *
   * @param position 目标位置
   * @param block 若为真则阻塞直至停止运动
   * @param force 设定闭合力
   * @param speed 设定运动速度
   */
  void setall(uint16_t position, bool block, uint16_t force = FORCE, uint16_t speed = SPEED);
  /**
   * @brief 设定夹爪目标位置
   *
   * @param command 目标位置
   */
  void setPos(uint16_t command);
  /**
   * @brief 设定夹爪闭合力
   *
   * @param command 闭合力
   */
  void setForce(uint16_t command);
  /**
   * @brief 设定夹爪运动速度
   *
   * @param command 运动速度
   */
  void setSpeed(uint16_t command);
  /**
   * @brief 判断是否初始化
   *
   * @return true 已初始化
   * @return false 未初始化
   */
  bool isInit();
  /**
   * @brief 判断夹爪是否运动
   *
   * @return true 正在运动
   * @return false 空闲
   */
  bool isBusy();
  /**
   * @brief 是否夹持物体
   *
   * @return true 有夹持
   * @return false 没有夹持
   */
  bool isGrip();
  /**
   * @brief 根据电流判断是否夹持物体
   *
   * @return true
   * @return false
   */
  bool isGripCur();
  /**
   * @brief 夹持物体是否掉落
   *
   * @return true 掉落
   * @return false 未掉落
   */
  bool isDrop();
  /**
   * @brief 根据电流判断是否掉落
   *
   * @return true
   * @return false
   */
  bool isDropCur();
  /**
   * @brief 内部函数，用于写入寄存器
   *
   * @param out_buf
   * @param in_buf
   * @param command
   */
  void setcommand(uint8_t *out_buf, uint8_t *in_buf, std::string command);
  /**
   * @brief 内部函数，用于读取寄存器
   *
   * @param out_buf
   * @param in_buf
   * @param command
   */
  void readcommand(uint8_t *out_buf, uint8_t *in_buf, std::string command);
  /**
   * @brief 获取夹爪当前位置
   *
   * @return uint16_t 夹爪当前位置
   */
  uint16_t getPos();

private:
  /**
   * @brief 获取夹爪当前电流
   *
   * @return uint16_t 夹爪当前电流
   */
  uint16_t getCurrent();
};
#endif