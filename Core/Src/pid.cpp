#include"pid.h"
extern float kp;
extern float ki;
extern float kd;
extern float err_sum_;
extern float last_err_;
void reset() {

} ;
float PID::calc(float ref, float fdb) {
     float err_=ref-fdb;
    pout_=kp_*err_;
     err_sum_=err_+last_err_;
     iout_=ki_*err_sum_;
     if (iout_>i_max_) {
         iout_=i_max_;
     }
    if (iout_<-i_max_) {
        iout_=-i_max_;
    }
    float del_=err_-last_err_;
    dout_=d_filter_k_*last_dout_+(1-d_filter_k_)*kd_*del_;
        last_err_=err_;
    last_dout_=dout_;
    output_=pout_+iout_+dout_;
}

//
// Created by 29528 on 2025/10/18.
//