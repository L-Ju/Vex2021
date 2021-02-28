#include "main.h"
#include "globals.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_left_button()
{
    autoRoutine = 1;
    pros::lcd::print(2, "LEFT");
}

void on_middle_button(){
    autoRoutine = 2;
    pros::lcd::print(2, "MIDDLE");
}

void on_right_button(){
    autoRoutine = 3;
    pros::lcd::print(2, "RIGHT");
}

//turn right *NO neagtive angle values
/*
void turnAngleRIGHT(double angleInRadians){
    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    double newAngle = 0;
    double lastLeftInch = 0;
    double lastRightInch = 0;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    while(newAngle < angleInRadians){
      double allVelocity;
      double newLeftInch = MTR_frontLeft.getPosition() * ticksPerInch2;
      double newRightInch = MTR_frontRight.getPosition() * ticksPerInch2;

      double dLeftInch = newLeftInch - lastLeftInch;
      double dRightInch = newRightInch - lastRightInch;

      lastLeftInch = newLeftInch;
      lastRightInch = newRightInch;

      double dAngle =  (dLeftInch - dRightInch) / chassisWidthInch;
      newAngle += dAngle;

      std::cout << "FrontLeft: " << dLeftInch << std::endl;
      std::cout << "BackRight: " << dRightInch << std::endl;

      std::cout << "dAngle = " << dAngle << std::endl;
      std::cout << "newAngle = " << newAngle << std::endl;

      error = angleInRadians - newAngle;
      integral = integral + error;
      derivative = error - lastError;

       allVelocity = (error * gP)
                     +(integral * gI)
                     +(derivative * gD);

      std::cout << "allVelocity = " << allVelocity << ' ';

      MTR_frontLeft.moveVelocity(allVelocity);
      MTR_frontRight.moveVelocity(allVelocity);
      MTR_backLeft.moveVelocity(allVelocity);
      MTR_backRight.moveVelocity(allVelocity);
      pros::delay(500);
    }
    MTR_frontLeft.moveVelocity(0);
    MTR_frontRight.moveVelocity(0);
    MTR_backLeft.moveVelocity(0);
    MTR_backRight.moveVelocity(0);
}
*/

//turn right *NO neagtive angle values
void turnAngleRIGHT(double angleInDegrees){
    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    double angleinTicks = 0;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    while(angleinTicks < angleInDegrees){
      double allVelocity;
      double circleticks = MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() + MTR_frontRight.getPosition() + MTR_backRight.getPosition();
      circleticks  =  circleticks / 4.0;

      angleinTicks = circleticks /8.547499;

      error = angleInDegrees - angleinTicks;
      integral = integral + error;
      derivative = error - lastError;

       allVelocity = (error * gP)
                     +(integral * gI)
                     +(derivative * gD);

      MTR_frontLeft.moveVelocity(allVelocity);
      MTR_frontRight.moveVelocity(allVelocity);
      MTR_backLeft.moveVelocity(allVelocity);
      MTR_backRight.moveVelocity(allVelocity);
      pros::delay(20);
    }
    MTR_frontLeft.moveVelocity(0);
    MTR_frontRight.moveVelocity(0);
    MTR_backLeft.moveVelocity(0);
    MTR_backRight.moveVelocity(0);
}

void turnAngleLEFT(double angleInDegrees){
    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    double angleinTicks = 0;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    while(angleinTicks < angleInDegrees){
      double allVelocity;
      double circleticks = MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() + MTR_frontRight.getPosition() + MTR_backRight.getPosition();
      circleticks  =  circleticks / 4.0;

      angleinTicks = circleticks /8.547499;

      error = angleInDegrees - angleinTicks;
      integral = integral + error;
      derivative = error - lastError;

       allVelocity = (error * gP)
                     +(integral * gI)
                     +(derivative * gD);

      MTR_frontLeft.moveVelocity(-allVelocity);
      MTR_frontRight.moveVelocity(-allVelocity);
      MTR_backLeft.moveVelocity(-allVelocity);
      MTR_backRight.moveVelocity(-allVelocity);
      pros::delay(20);
    }
    MTR_frontLeft.moveVelocity(0);
    MTR_frontRight.moveVelocity(0);
    MTR_backLeft.moveVelocity(0);
    MTR_backRight.moveVelocity(0);
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
    if (distanceInTicks > 0){
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

            pros::delay(20);
        }
//     std::cout << "FrontLeft End: " << MTR_frontLeft.getPosition() << std::endl;
//     std::cout << "BackLeft End: " << MTR_backLeft.getPosition() << std::endl;
//     std::cout << "FrontRight End: " << MTR_frontRight.getPosition() << std::endl;
//     std::cout << "BackRight End: " << MTR_backRight.getPosition() << std::endl;
        MTR_frontLeft.moveVelocity(0);
        MTR_frontRight.moveVelocity(0);
        MTR_backLeft.moveVelocity(0);
        MTR_backRight.moveVelocity(0);
    } else if (distanceInTicks < 0) {
        double leftVelocity = -100;
        double rightVelocity = -100;

        MTR_frontLeft.moveVelocity(leftVelocity);
        MTR_frontRight.moveVelocity(rightVelocity);
        MTR_backLeft.moveVelocity(leftVelocity);
        MTR_backRight.moveVelocity(rightVelocity);

        while ( MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() > distanceInTicks*2) {

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

            pros::delay(20);
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
    pros::lcd::set_text(2, "RIGHT");

    pros::lcd::register_btn0_cb(on_left_button);
	  pros::lcd::register_btn1_cb(on_middle_button);
    pros::lcd::register_btn2_cb(on_right_button);

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
void disabled() {
    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn1_cb(on_middle_button);
    pros::lcd::register_btn2_cb(on_right_button);
}

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
/* our regional's auto
pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
MTR_shooter.moveVelocity(600);
drive->setMaxVelocity(150);
drive->moveDistance(23.5_in);
drive->turnAngle(-141_deg);
pickUpBalls();
drive->moveDistance(27.3_in);
MTR_pushup.moveVelocity(-600);
MTR_shooter.moveVelocity(-600);
pros::delay(400);
MTR_rollerLeft.moveVelocity(0);
MTR_rollerRight.moveVelocity(0);
pros::delay(2000);
MTR_shooter.moveVelocity(0);
MTR_pushup.moveVelocity(0);
drive->moveDistance(-27.3_in);
*/
    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
//    MTR_shooter.moveVelocity(600);
    drive->setMaxVelocity(200);
    pickUpBalls();
    drive->moveDistance(55_in);
    pros::delay(600);
    stopIntake();
    turnAngleRIGHT(135);
/*
    drive->moveDistance(49.5_in);
    turnAngleRIGHT(45);
    drive->moveDistance(20_in);
    pickUpBalls();
    MTR_pushup.moveVelocity(-600);
    MTR_shooter.moveVelocity(-600);
    pros::delay(1200);
    MTR_rollerLeft.moveVelocity(0);
    MTR_rollerRight.moveVelocity(0);
    pros::delay(2000);
    MTR_shooter.moveVelocity(0);
    MTR_pushup.moveVelocity(0);
  */
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
  /*
    double Pi = 3.14159265358979323846;
    turnAngleRIGHT(3.14);
    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    drive->setMaxVelocity(200);

    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    drive->turnAngle(360_deg);

    std::cout << "Frontleft =" <<  MTR_frontLeft.getPosition() << std::endl;
    std::cout << "frontRight =" << MTR_frontRight.getPosition() << std::endl;
    std::cout << "backLeft =" <<  MTR_backLeft.getPosition() << std::endl;
    std::cout << "backRight =" <<  MTR_backRight.getPosition() << std::endl;
  */

	while(1){

//tank drive
		drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY),
                                    controller.getAnalog(ControllerAnalog::rightY));
		if (controller.getDigital(okapi::ControllerDigital::X))  {
			MTR_shooter.moveVelocity(-600);
		} else if (controller.getDigital(okapi::ControllerDigital::L2)) {
			MTR_shooter.moveVelocity(600);
		}else if (controller.getDigital(okapi::ControllerDigital::L1)) {
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
	        MTR_rollerRight.moveVelocity(0) ;
			if(!controller.getDigital(okapi::ControllerDigital::L1)){
				MTR_pushup.moveVelocity(0);
			}
		}

		pros::delay(10);
	}

}
