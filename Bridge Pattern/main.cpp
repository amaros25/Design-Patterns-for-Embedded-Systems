
/*
 * C++ Design Patterns: Bridge
 * Author: Ammar Salhi
 * 2025
 */

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class MotorController{
    public:
        virtual ~MotorController(){};
        virtual void set_speed(int speed) = 0;
        virtual void start_motor() = 0;
        virtual void stop_motor() = 0;
};

class CANMotorController: public MotorController{
        void set_speed(int speed){
            cout << "set speed CAN motor: " << speed << endl;
        }
        void start_motor(){
            cout << "init CAN motor" << endl;
        }
        void stop_motor(){
            cout << "stop CAN motor" << endl;
        }
};

class UARTMotorController: public MotorController{
        void set_speed(int speed){
            cout << "set speed UART motor: " << speed << endl;
        }
        void start_motor(){
            cout << "init UART motor" << endl;
        }
        void stop_motor(){
            cout << "stop UART motor" << endl;
        }
};

class PWMMotorController: public MotorController{
        void set_speed(int speed){
            cout << "set speed PWM motor: " << speed << endl;
        }
        void start_motor(){
            cout << "init PWM motor" << endl;
        }
        void stop_motor(){
            cout << "stop PWM motor" << endl;
        }
};
 
class Motor{
    protected:
        std::unique_ptr<MotorController> motor_controller;
    public:
        Motor(std::unique_ptr<MotorController> controller): motor_controller(std::move(controller)){}
        void set_speed(int speed){
             motor_controller->set_speed(speed);
        }
        void start_motor(){
             motor_controller->start_motor();
        }
        void stop_motor(){
             motor_controller->stop_motor();
        }
};

int main(){
    auto can_motor_controller = std::make_unique<CANMotorController>();
    auto can_motor = std::make_unique<Motor>(std::move(can_motor_controller));

    auto uart_motor_controller = std::make_unique<UARTMotorController>();
    auto uart_motor = std::make_unique<Motor>(std::move(uart_motor_controller));

    auto pwm_motor_controller = std::make_unique<PWMMotorController>();
    auto pwm_motor = std::make_unique<Motor>(std::move(pwm_motor_controller));

    can_motor->start_motor();
    uart_motor->start_motor();
    pwm_motor->start_motor();

    can_motor->set_speed(20);
    uart_motor->set_speed(70);
    pwm_motor->set_speed(100);

    can_motor->stop_motor();
    uart_motor->stop_motor();
    pwm_motor->stop_motor();

    return 0;
}