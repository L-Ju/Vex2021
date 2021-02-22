#include "main.h"
#include "globals.hpp"

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
		pros::lcd::set_text(2, "I was pressed! YAYYYYYY");
	} else {
		pros::lcd::clear_line(2);
	}
}


void driveFeet (double distanceInFeet) {
    double distanceInTicks = distanceInFeet * 12 * ticksPerInch;

    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

//     std::cout << "FrontLeft: " << MTR_frontLeft.getPosition() << std::endl;
//     std::cout << "BackLeft: " << MTR_backLeft.getPosition() << std::endl;
//     std::cout << "FrontRight: " << MTR_frontRight.getPosition() << std::endl;
//     std::cout << "BackRight: " << MTR_backRight.getPosition() << std::endl;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    double leftVelocity = 100;
    double rightVelocity = 100;
    MTR_frontLeft.moveVelocity(leftVelocity);
    MTR_frontRight.moveVelocity(rightVelocity);
    MTR_backLeft.moveVelocity(leftVelocity);
    MTR_backRight.moveVelocity(rightVelocity);

    while ( MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() < distanceInTicks*2) {

//         std::cout << "FrontLeft: " << MTR_frontLeft.getPosition() << std::endl;
//         std::cout << "BackLeft: " << MTR_backLeft.getPosition() << std::endl;
//         std::cout << "FrontRight: " << MTR_frontRight.getPosition() << std::endl;
//         std::cout << "BackRight: " << MTR_backRight.getPosition() << std::endl;

        error = (MTR_frontLeft.getPosition() + MTR_backLeft.getPosition()) - (MTR_frontRight.getPosition()*-1 + MTR_backRight.getPosition()*-1);
        integral = integral + error;
        derivative = error - lastError;

        rightVelocity = leftVelocity + (error * kP)
                                     + (integral * kI)
                                     + (derivative * kD);

//         std::cout << "right " << rightVelocity << std::endl;
//         std::cout << "left " << leftVelocity << std::endl;
        MTR_frontRight.moveVelocity(-rightVelocity);
        MTR_backRight.moveVelocity(-rightVelocity);


        // FOR TUNING THE P LOOP
//         std::cout << error << ",";

        pros::delay(50);
    }
//     std::cout << "FrontLeft End: " << MTR_frontLeft.getPosition() << std::endl;
//     std::cout << "BackLeft End: " << MTR_backLeft.getPosition() << std::endl;
//     std::cout << "FrontRight End: " << MTR_frontRight.getPosition() << std::endl;
//     std::cout << "BackRight End: " << MTR_backRight.getPosition() << std::endl;
    MTR_frontLeft.moveVelocity(0);
    MTR_frontRight.moveVelocity(0);
    MTR_backLeft.moveVelocity(0);
    MTR_backRight.moveVelocity(0);
}


void pickUpBalls() {
    MTR_rollerLeft.moveVelocity(-600);
    MTR_rollerRight.moveVelocity(600);
    MTR_pushup.moveVelocity(-600);
}

void ejectBalls() {
    MTR_rollerLeft.moveVelocity(600);
    MTR_rollerRight.moveVelocity(-600);
    MTR_pushup.moveVelocity(600);
}

void stopIntake() {
    MTR_rollerLeft.moveVelocity(0);
    MTR_rollerRight.moveVelocity(0);
    MTR_pushup.moveVelocity(0);
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello OperationNightFury!");

	pros::lcd::register_btn1_cb(on_center_button);

    pros::Motor MTR_1(FRONT_LEFT_MOTOR_PORT);
    MTR_1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    pros::Motor MTR_2(FRONT_RIGHT_MOTOR_PORT);
    MTR_2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    pros::Motor MTR_3(BACK_LEFT_MOTOR_PORT);
    MTR_3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    pros::Motor MTR_4(BACK_RIGHT_MOTOR_PORT);
    MTR_4.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
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
void autonomous() {
    // 0 = move a metre
    // 1 = original auto plan (back of notebook)
    // 2 = Jem's youtube video
    int test_dist = 0;

    if (test_dist == 0){
        drive->turnAngle(90_deg); 
    } else if (test_dist == 1) {
        drive->setMaxVelocity(100);
        drive->moveDistance(1.6_m);
        drive->stop();
        MTR_rollerLeft.moveVelocity(-600);
        MTR_rollerRight.moveVelocity(600);
        MTR_pushup.moveVelocity(-300);
        drive->setMaxVelocity(20);
        drive->moveDistance(0.2_m);
        pros::delay(2000);
        MTR_rollerLeft.moveVelocity(-100);
        MTR_rollerRight.moveVelocity(100);
        MTR_pushup.moveVelocity(0);
        drive->setMaxVelocity(100);
        drive->moveDistance(-0.2_m);
        drive->turnAngle(180_deg);
        drive->moveDistance(0.715_m);
        drive->turnAngle(45_deg);
        drive->moveDistance(1_m);
    } else if (test_dist == 2){
			drive->moveDistance(23.5_in);
			drive->turnAngle(135_deg);
			drive->moveDistance(27.3_in);
			pickUpBalls();
			MTR_shooter.moveVelocity(-600);
			pros::delay(500);
			MTR_shooter.moveVelocity(0);
			pros::delay(500);
			stopIntake();
			drive->moveDistance(-27.3_in);
			drive->turnAngle(135_deg);
			drive->moveDistance(41.5_in);
			drive->turnAngle(-90_deg);
			drive->moveDistance(12.9_in);
			MTR_pushup.moveVelocity(-600);
			MTR_shooter.moveVelocity(-600);
			pros::delay(500);
			MTR_pushup.moveVelocity(0);
			MTR_shooter.moveVelocity(0);
			drive->moveDistance(-51.8_in);
			drive->turnAngle(56_deg);
			drive->moveDistance(83.5_in);
			pickUpBalls();
			pros::delay(500);
			stopIntake();
			MTR_pushup.moveVelocity(-600);
			MTR_shooter.moveVelocity(-600);
			pros::delay(1000);
			MTR_pushup.moveVelocity(0);
			MTR_shooter.moveVelocity(0);
			drive->moveDistance(-12_in);
	/*
        drive->moveDistance(2_ft);
        drive->turnAngle(135_deg);
        drive->moveDistance(2_ft);
        pickUpBalls();
        MTR_shooter.moveVelocity(-600);
        pros::delay(500);
        MTR_shooter.moveVelocity(0);
        pros::delay(500);
        stopIntake();
        drive->moveDistance(-2_ft);
        drive->turnAngle(135_deg);
        drive->moveDistance(3_ft);
        drive->turnAngle(-90_deg);
        drive->moveDistance(1_ft);
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        pros::delay(500);
        MTR_pushup.moveVelocity(0);
        MTR_shooter.moveVelocity(0);
        drive->moveDistance(-3_ft);
        drive->turnAngle(56_deg);
        drive->moveDistance(6.04_ft);
        pickUpBalls();
        pros::delay(500);
        stopIntake();
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        pros::delay(1000);
        MTR_pushup.moveVelocity(0);
        MTR_shooter.moveVelocity(0);
        drive->moveDistance(-1_ft);
		*/
    } else {
        drive->moveDistance(2_ft);
    }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *Git
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {

	while(1){

//tank drive
		drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY),
                                    controller.getAnalog(ControllerAnalog::rightY));
		if (controller.getDigital(okapi::ControllerDigital::L1))  {
			MTR_shooter.moveVelocity(-600);
		} else if (controller.getDigital(okapi::ControllerDigital::L2)) {
			MTR_shooter.moveVelocity(600);
		}else if (controller.getDigital(okapi::ControllerDigital::X)) {
			MTR_shooter.moveVelocity(-600);
			MTR_pushup.moveVelocity(-600);
		}else {
			MTR_shooter.moveVelocity(0);
		}

		if (controller.getDigital(okapi::ControllerDigital::R1)) {
			pickUpBalls();
		} else if (controller.getDigital(okapi::ControllerDigital::R2)) {
			ejectBalls();
		} else {
			MTR_rollerLeft.moveVelocity(0);
	    MTR_rollerRight.moveVelocity(0);
			if(!controller.getDigital(okapi::ControllerDigital::X)){
				MTR_pushup.moveVelocity(0);
			}
		}

		pros::delay(10);
	}

}
