#pragma once
class PID {


private:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pout_, iout_, dout_, last_dout_;
public:
    PID(float kp = 0.0f, float ki = 0.0f, float kd = 0.0f,
        float i_max = 0.0f, float out_max = 0.0f, float d_filter = 1.0f);
    void reset() ;
    float calc(float ref, float fdb);
    int FeedforwardIntensityCalc(float current_angle);
    float kp_, ki_, kd_, d_filter_k_;
    float i_max_, out_max_;
    float output_;
};//
// Created by 29528 on 2025/10/18.
//

#ifndef LIGHTEN02_PID_H
#define LIGHTEN02_PID_H

#endif //LIGHTEN02_PID_H