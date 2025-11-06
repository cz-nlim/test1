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
    PID ppid_;
    PID spid_;
    float target_angle_, fdb_angle_;
    float target_speed_, fdb_speed_, feedforward_speed_;
    float feedforward_intensity_, output_intensity_;
    float reference_angle_;
    enum {
        TORQUE,
        SPEED,
        POSITION_SPEED,
      } control_method_;
public:
    //添加构造函数M3508_Motor
    explicit M3508_Motor(const float ratio):ratio_(ratio) {};
    float linearMapping(int in, int in_min,int in_max,float out_min,float out_max) {
        float out=1.0f*in*(out_max-out_min)/(in_max-in_min);
        return out;
    }
    void canRxMsgCallback(const uint8_t rx_data[8]);
    void SetPosition(float target_position, float feedforward_speed, float feedforward_intensity);
   void SetSpeed(float target_speed, float feedforward_intensity);
    void SetIntensity(float intensity);
    void handle();
    float GetPosition();
    void setReferencePoint();
    float Setcurrent(float output);
    float angle_handle(float angle);
};
#ifndef LIGHTEN02_MOTORCLASS_H
#define LIGHTEN02_MOTORCLASS_H

#endif //LIGHTEN02_MOTORCLASS_H