#include "driveMotors.h"
#include "pros/misc.h"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void driverControl()
{

	opcontrol();

}
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
	//intake_motor.move_velocity(250);
	//pros::delay(500);


}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int flywheel = 0;	
	bool flywheelOn = false;
	bool intakeOn = false;
	bool intakeTwoOn = false;
	bool outtakeOn = false;

	bool flywheelHigh = false;
	bool OFF = false;
	
	while (true) {

		
		//flywheel code

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
		{
			flywheelOn = !flywheelOn;
		}
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
		{
			flywheelHigh = false;
		}
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
		{
			flywheelHigh = true;
		}
		if(flywheelOn && flywheelHigh)
		{
			flywheel_motor.move_velocity(-600);
		}
		else if(flywheelOn && !flywheelHigh)
		{
			flywheel_motor.move_velocity(-400);
		}
		if(!flywheelOn)
		{
			flywheel_motor.move_velocity(0);
		}

		
		




		//intake code
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
		{
			intakeOn = !intakeOn;
		}
		if(intakeOn)
		{
			intake_motor.move_velocity(500);
			//intake_motor_2.move_velocity(-500);
		}
	
		if(!intakeOn)
		{
			intake_motor.move_velocity(0);
			//intake_motor_2.move_velocity(0);
			
		}
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{
			outtakeOn = !outtakeOn;
		}
		if(outtakeOn && !OFF)
		{
			intake_motor.move_velocity(-500);
			intake_motor_2.move_velocity(500);
		}
		if(!outtakeOn && !OFF)
		{
			intake_motor.move_velocity(500);
			intake_motor_2.move_velocity(-500);
		}
		
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			OFF = true;
			intake_motor.move_velocity(0);
			intake_motor_2.move_velocity(0);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			OFF = false;
		}


		
	
	//	 if(!intakeTwoOn)
	//	{
	//		intake_motor_2.move_velocity(0);
	//	}



		//deploy piston code
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
		{
			piston.set_value(true);
		}



		int power = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);

		int left = power + turn;
		int right = power - turn;

		left_front.move(left);
		right_front.move(right);
		left_back.move(left);
		right_back.move(right);
		
		pros::delay(20);
	}
}
