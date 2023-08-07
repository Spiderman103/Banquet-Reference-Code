#include "main.h"
#include "pros/motors.h"

pros:: Controller controller(pros:: E_CONTROLLER_MASTER);

pros::Motor left_front(2, pros::E_MOTOR_GEARSET_18,true,pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor right_front(1, pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor left_back(4, pros::E_MOTOR_GEARSET_18,true,pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor right_back(3, pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor flywheel_motor(6, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor intake_motor(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::ADIDigitalOut piston('A');


pros::Motor intake_motor_2(18,pros::E_MOTOR_GEARSET_06,false,pros::E_MOTOR_ENCODER_COUNTS);