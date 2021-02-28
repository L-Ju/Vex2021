#include "main.h"
#include "globals.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


// void on_left_button()
// {
//     autoRoutine = 1;
//     pros::lcd::print(2, "LEFT");
// }
// 
// void on_middle_button(){
//     autoRoutine = 2;
//     pros::lcd::print(2, "MIDDLE");
// }
// 
// void on_right_button(){
//     autoRoutine = 3;
//     pros::lcd::print(2, "RIGHT");
// }

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
// 	pros::lcd::initialize();
// 	pros::lcd::set_text(1, "Hello OperationNightFury!");
//     pros::lcd::set_text(2, "RIGHT");
// 
//     pros::lcd::register_btn0_cb(on_left_button);
// 	pros::lcd::register_btn1_cb(on_middle_button);
//     pros::lcd::register_btn2_cb(on_right_button);
    
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);
    
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);
<<<<<<< HEAD
    lv_btn_set_fit(btn1, true); // auto set size according to content
    lv_obj_set_pos(btn1, 340, 0);
=======
    lv_btn_set_fit(btn1, true, true); // auto set size according to content
    lv_obj_set_pos(btn1, 60, 40);
>>>>>>> parent of bbdcf2b (new lvgl)
    
    lv_obj_t * btn2 = lv_btn_create(scr, btn1);
    lv_obj_set_pos(btn2, 180, 80);
    
    lv_obj_t * label1 = lv_label_create(btn1, NULL);
    lv_label_set_text(label1, "Button 1");
    
    lv_obj_t * label2 = lv_label_create(btn2, NULL);
    lv_label_set_text(label2, "Button 2");
    
    lv_obj_del(label2);
    
    
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
    
//     pros::lcd::register_btn0_cb(on_left_button);
// 	pros::lcd::register_btn1_cb(on_middle_button);
//     pros::lcd::register_btn2_cb(on_right_button);
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
    // 0 = move a metre
    // 1 = original auto plan (back of notebook)
    // 2 = Jem's youtube video
   
    if (autoRoutine == 0){
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
        drive->turnAngle(90_deg); 
    } else if (autoRoutine == 1) {
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
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
    } else if (autoRoutine == 2){
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
        drive->setMaxVelocity(150);
        drive->moveDistance(23.5_in);
        drive->turnAngle(141_deg);
        pickUpBalls();
        drive->moveDistance(27.3_in);
        MTR_shooter.moveVelocity(-600);
        MTR_pushup.moveVelocity(-600);
        pros::delay(400);
        stopIntake();
        pros::delay(2000);
        MTR_shooter.moveVelocity(0);
        MTR_pushup.moveVelocity(0);
        drive->moveDistance(-27.3_in);
        drive->turnAngle(141_deg);
        drive->moveDistance(41.5_in);
        drive->turnAngle(-90_deg);
        pickUpBalls();
        drive->moveDistance(30_in);
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);
        pros::delay(2);
        MTR_pushup.moveVelocity(0);
        MTR_shooter.moveVelocity(0);
        drive->setMaxVelocity(50);
        drive->moveDistance(-20_in);
//         drive->turnAngle(57_deg);
//         pickUpBalls();
//         drive->moveDistance(83.5_in);
//         pros::delay(500);
//         stopIntake();
//         MTR_pushup.moveVelocity(-600);
//         MTR_shooter.moveVelocity(-600);
//         pros::delay(1000);
//         MTR_pushup.moveVelocity(0);
//         MTR_shooter.moveVelocity(0);
//         drive->moveDistance(-12_in);
    } else if (autoRoutine == 3){ // left side
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
//         drive->turnAngle(-141_deg);
//         drive->moveDistance(41.5_in);
//         drive->turnAngle(90_deg);
//         pickUpBalls();
//         drive->moveDistance(30_in);
//         MTR_pushup.moveVelocity(-600);
//         stopIntake();
//         MTR_shooter.moveVelocity(-600);
//         pros::delay(500);
//         MTR_pushup.moveVelocity(0);
//         MTR_shooter.moveVelocity(0);
//         drive->setMaxVelocity(50);
//         drive->moveDistance(-20_in);
//         drive->turnAngle(57_deg);
//         pickUpBalls();
//         drive->moveDistance(83.5_in);
//         pros::delay(500);
//         stopIntake();
//         MTR_pushup.moveVelocity(-600);
//         MTR_shooter.moveVelocity(-600);
//         pros::delay(1000);
//         MTR_pushup.moveVelocity(0);
//         MTR_shooter.moveVelocity(0);
//         drive->moveDistance(-12_in);
    } else if (autoRoutine == 4) { // emilshit
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
        pros::delay(500);
        MTR_shooter.moveVelocity(0);
        driveFeet(1.9583333333333333);
        drive->turnAngle(135_deg);
        pickUpBalls();
        driveFeet(2.275);
        MTR_shooter.moveVelocity(-600);
        pros::delay(500);
        MTR_shooter.moveVelocity(0);
        pros::delay(500);
        stopIntake();
        driveFeet(-2.275);
        drive->turnAngle(135_deg);
        driveFeet(3.4583333333333335);
        drive->turnAngle(-90_deg);
        driveFeet(1.075);
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        pros::delay(500);
        MTR_pushup.moveVelocity(0);
        MTR_shooter.moveVelocity(0);
        driveFeet(-4.3166666666666655);
        drive->turnAngle(56_deg);
        pickUpBalls();
        driveFeet(6.958333333333332);
        pros::delay(500);
        stopIntake();
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        pros::delay(1000);
        MTR_pushup.moveVelocity(0);
        MTR_shooter.moveVelocity(0);
        driveFeet(-1);
    }  else {
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
    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    drive->setMaxVelocity(200);

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
