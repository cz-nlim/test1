class PID {
public:
    PID() : PID(0, 0, 0, 0, 0) {}
    PID(float kp, float ki, float kd, float i_max, float out_max,
        float d_filter_k = 1);

    void reset() ;
    float calc(float ref, float fdb);

    float kp_, ki_, kd_, d_filter_k_;
    float i_max_, out_max_;
    float output_;

private:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pout_, iout_, dout_, last_dout_;
};//
// Created by 29528 on 2025/10/18.
//

#ifndef LIGHTEN02_PID_H
#define LIGHTEN02_PID_H

#endif //LIGHTEN02_PID_H