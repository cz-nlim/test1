#include <stdint.h>

#include "pid.h"
//
// Created by 29528 on 2025/10/3.
//
class M3508_Motor {
private:
    const float ratio_;//电机减速比
    float fdb_angle=0.f;
    float delta_angle_=0.f;
    float ecd_angle_=0.f;
    float last_ecd_angle_=0.f;
    float delta_ecd_angle_=0.f;
    float fdb_speed=0.f;
    float current_=0.f;
    float temp_=0.f;
    float intensity_=0.f;
    PID spid_(float kp_speed,float ki_speed,float i_max,float out_max);
    PID ppid_(float kp_speed,float ki_speed,float i_max,float out_max);
    float target_angle_, fdb_angle_;
    float target_speed_, fdb_speed_, feedforward_speed_;
    float feedforward_intensity_, output_intensity_;
    enum {
        TORQUE,
        SPEED,
        POSITION_SPEED,
      } control_method_;
public:
    //添加构造函数M3508_Motor
    explicit M3508_Motor(const float ratio):ratio_(ratio) {};
    float linearMapping(int in, int in_min,int in_max,float out_min,float out_max) {
        float out=in*(out_max-out_min)/(in_max-in_min);
        return out;
    }
    void canRxMsgCallback(const uint8_t rx_data[8]) {
        last_ecd_angle_=ecd_angle_;
        float angle_0=ecd_angle_/ratio_;
        uint8_t ecd_angle_1=rx_data[0]<<8|rx_data[1];
        ecd_angle_=linearMapping(ecd_angle_1, 0,8191,0,360);
        uint8_t rotate_speed1=rx_data[2]<<8|rx_data[3];
        fdb_speed=rotate_speed1;
        uint8_t current_1=rx_data[4]<<8|rx_data[5];
        current_=linearMapping(current_1,-16384,16384,-20,20);
        uint8_t temp_1=rx_data[6];
        temp_=temp_1;
        delta_ecd_angle_= ecd_angle_-last_ecd_angle_;
        delta_angle_=delta_ecd_angle_/ratio_;
        fdb_angle_=angle_0+delta_angle_;
    };
    void SetPosition(float target_position, float feedforward_speed, float feedforward_intensity);
    void SetSpeed(float target_speed, float feedforward_intensity);
    void SetIntensity(float intensity);
    void handle();
};
#ifndef LIGHTEN02_MOTORCLASS_H
#define LIGHTEN02_MOTORCLASS_H

#endif //LIGHTEN02_MOTORCLASS_H