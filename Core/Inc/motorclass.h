//
// Created by 29528 on 2025/10/3.
//
class M3508_Motor {
private:
    const float ratio_;//电机减速比
    float angle_=0.f;
    float delta_angle_=0.f;
    float ecd_angle_=0.f;
    float last_ecd_angle_=0.f;
    float delta_ecd_angle_=0.f;
    float rotate_speed=0.f;
    float current_=0.f;
    float temp_=0.f;
public:
    explicit M3508_Motor(const float ratio):ratio_(ratio) {};
    void canRxMsgCallback(const uint8_t rx_data[8]);
};
#ifndef LIGHTEN02_MOTORCLASS_H
#define LIGHTEN02_MOTORCLASS_H

#endif //LIGHTEN02_MOTORCLASS_H