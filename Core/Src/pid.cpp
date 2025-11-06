#include"pid.h"

#include <cmath>
#include <stdint.h>
extern float kp;
extern float ki;
extern float kd;
extern float err_sum_;
extern float last_err_;
extern int16_t intensity;
PID::PID(float kp, float ki, float kd, float i_max, float out_max, float d_filter)
    : kp_(kp), ki_(ki), kd_(kd),
      i_max_(i_max), out_max_(out_max),
      d_filter_k_(d_filter)
{
    // 初始化状态变量
    reset();
}
void PID::reset() {
    last_err_=0;
    kp_=0.f;
    ki_=0.f;
    kd_=0.f;
} ;
float PID::calc(float ref, float fdb) {
     float err_=ref-fdb;
    pout_=kp_*err_;//比例
     err_sum_=err_+last_err_;
     iout_=ki_*err_sum_;
     if (iout_>i_max_) {
         iout_=i_max_;
     }
    if (iout_<-i_max_) {
        iout_=-i_max_;
    }//积分并限幅
    //微分项
    float del_=err_-last_err_;
    dout_=d_filter_k_*last_dout_+(1-d_filter_k_)*kd_*del_;
        last_err_=err_;
    last_dout_=dout_;
    output_=pout_+iout_+dout_;
    return output_;
}
int PID::FeedforwardIntensityCalc(float current_angle) {
    intensity = (int16_t)((5.0f*55.24f*0.001f*sin(current_angle* 3.14159f / 180.0)* 819.2f/0.3));
    if (intensity>16384) {
        intensity=16384;
    }
    else if (intensity<-16384) {
        intensity=-16384;
    }
    return intensity;
}
//
// Created by 29528 on 2025/10/18.
//