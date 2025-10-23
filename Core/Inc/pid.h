class PID {


private:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pout_, iout_, dout_, last_dout_;
public:
    PID() : PID(0, 0, 0, 0, 0) {}
    PID(float kp, float ki, float kd, float i_max, float out_max,
     float d_filter_k = 1):kp_(kp),ki_(ki),kd_(kd),i_max_(i_max),out_max_(out_max),d_filter_k_(d_filter_k){}
    void reset() ;
    float calc(float ref, float fdb);

    float kp_, ki_, kd_, d_filter_k_;
    float i_max_, out_max_;
    float output_;
};//
// Created by 29528 on 2025/10/18.
//

#ifndef LIGHTEN02_PID_H
#define LIGHTEN02_PID_H

#endif //LIGHTEN02_PID_H