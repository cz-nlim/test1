#include"motorclass.h"

#include <tgmath.h>

#include"pid.h"
extern uint8_t tx_data[8];

   float M3508_Motor::angle_handle (float angle) {
       float nangle_=fmod(angle,360.0);
       return nangle_;
   }

void M3508_Motor::handle() {
    control_method_ = POSITION_SPEED;
    switch (control_method_) {
        case TORQUE: {
            intensity_=output_intensity_;
            Setcurrent(intensity_);
            break;
        }
        case SPEED: {
            float output_speed=spid_.calc(target_speed_, fdb_speed_);//这行要改一下发给电机
            float feedforward = feedforward_speed_ * feedforward_intensity_;
            output_intensity_ = output_speed + feedforward;
            Setcurrent(output_intensity_);
            break;
        }
        case POSITION_SPEED: {
            target_angle_=80.0f;
            fdb_angle_=angle_handle (fdb_angle_);
            float target_speed_=ppid_.calc(target_angle_,fdb_angle_);
            float pid_output = spid_.calc(target_speed_, fdb_speed_);
            //float feedforward = feedforward_speed_ * feedforward_intensity_;
            float feedforward=spid_.FeedforwardIntensityCalc(fdb_angle_);
            output_intensity_ = pid_output + feedforward;
            Setcurrent(output_intensity_);
            break;
        }
    }
}


void M3508_Motor::SetPosition(float target_position, float feedforward_speed, float feedforward_intensity) {
    control_method_ = POSITION_SPEED;
    target_angle_ = target_position;
    feedforward_speed_ = feedforward_speed;
    feedforward_intensity_ = feedforward_intensity;

}

void M3508_Motor::SetSpeed(float target_speed, float feedforward_intensity) {
    control_method_ = SPEED;
    target_speed_ = target_speed;
    feedforward_intensity_ = feedforward_intensity;
    feedforward_speed_ = target_speed;  // 速度前馈通常使用目标速度本身
}

void M3508_Motor::SetIntensity(float intensity) {
    control_method_ = TORQUE;
    output_intensity_ = intensity;
    // 扭矩模式下前馈通常不使用
    feedforward_speed_ = 0;
    feedforward_intensity_ = 0;
}

//解算反馈值
void M3508_Motor::canRxMsgCallback(const uint8_t rx_data[8]) {
    last_ecd_angle_=ecd_angle_;
    uint16_t ecd_angle_1=(rx_data[0]<<8)|rx_data[1];
    ecd_angle_=linearMapping(ecd_angle_1, 0,8191,0,360);
    int16_t rotate_speed1=(rx_data[2]<<8)|rx_data[3];
    fdb_speed=rotate_speed1;
    current_=(rx_data[4]<<8)|rx_data[5];
    uint8_t temp_1=rx_data[6];
    temp_=temp_1;
    delta_ecd_angle_= ecd_angle_-last_ecd_angle_;
    if (delta_ecd_angle_ > 180.0f) {
        delta_ecd_angle_ -= 360.0f;  // 正向溢出修正
    } else if (delta_ecd_angle_ < -180.0f) {
        delta_ecd_angle_ += 360.0f;  // 反向溢出修正
    }
    delta_angle_=delta_ecd_angle_/ratio_;
    fdb_angle_+=delta_angle_;
};
void M3508_Motor::setReferencePoint() {
    reference_angle_ = ecd_angle_;
}
float M3508_Motor::GetPosition() {
    float b=fmod(ecd_angle_,360.0)-reference_angle_;
    return b;
}
float M3508_Motor::Setcurrent(float current) {
 output_intensity_=current*16384.0f/20.0f;
    tx_data[0]=(int16_t)(output_intensity_)>>8;
    tx_data[1]=(int16_t)(output_intensity_)&0x00FF;
}

// Created by 29528 on 2025/10/3.
//
// Created by 29528 on 2025/10/23.
//