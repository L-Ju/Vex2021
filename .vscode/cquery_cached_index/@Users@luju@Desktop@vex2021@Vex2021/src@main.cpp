#include "main.h"
#include "globals.hpp"
#include <string>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

// void on_middle_button(){

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


//turn right *NO neagtive angle values *somehow only works within the range of 0 < x <= 180
void turnAngleRIGHT(double angleInDegrees){
    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    if(angleInDegrees == 180){
      double temp = ( (44.5/360.0)*angleInDegrees ) / 2.0;
      angleInDegrees = angleInDegrees + temp;
    }

    double angleinTicks = 0;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    while(angleinTicks < angleInDegrees){
      double allVelocity;
      double circleticks = MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() + MTR_frontRight.getPosition() + MTR_backRight.getPosition();
      circleticks  =  circleticks / 4.0;

      angleinTicks = circleticks /6.843738; //8.547499

      error = angleInDegrees - angleinTicks;
      integral = integral + error;
      derivative = error - lastError;

       allVelocity = 185 + (error * gP)
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

//*NO neagtive angle values *somehow only works within the range of 0 < x <= 180
void turnAngleLEFT(double angleInDegrees){
    MTR_frontLeft.tarePosition();
    MTR_frontRight.tarePosition();
    MTR_backLeft.tarePosition();
    MTR_backRight.tarePosition();

    if(angleInDegrees == 180){
      double temp = ( (44.5/360.0)*angleInDegrees ) / 2.0;
      angleInDegrees = angleInDegrees + temp;
    }

    double angleinTicks = 0;
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    while(angleinTicks < angleInDegrees){
      double allVelocity = 0;
      double circleticks = MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() + MTR_frontRight.getPosition() + MTR_backRight.getPosition();
      circleticks  =  circleticks / 4.0;

      angleinTicks = - 1 * (circleticks/6.843738); //7.7891

      error = angleInDegrees - angleinTicks;
      integral = integral + error;
      derivative = error - lastError;

      allVelocity = 190 + (error * gP)
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

    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;
    if (distanceInTicks > 0){
        double leftVelocity = 185;
        double rightVelocity = 185;

        MTR_frontLeft.moveVelocity(leftVelocity);
        MTR_frontRight.moveVelocity(rightVelocity);
        MTR_backLeft.moveVelocity(leftVelocity);
        MTR_backRight.moveVelocity(rightVelocity);

        while ( MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() < distanceInTicks*2) {
            error = (MTR_frontLeft.getPosition() + MTR_backLeft.getPosition()) - (MTR_frontRight.getPosition()*-1 + MTR_backRight.getPosition()*-1);
            integral = integral + error;
            derivative = error - lastError;

            rightVelocity = leftVelocity + (error * kP)
                                        + (integral * kI)
                                        + (derivative * kD);

            MTR_frontRight.moveVelocity(-rightVelocity);
            MTR_backRight.moveVelocity(-rightVelocity);

            pros::delay(20);
        }
        MTR_frontLeft.moveVelocity(0);
        MTR_frontRight.moveVelocity(0);
        MTR_backLeft.moveVelocity(0);
        MTR_backRight.moveVelocity(0);
    }
    else if (distanceInTicks < 0) {
        double leftVelocity = -100;
        double rightVelocity = -100;

        MTR_frontLeft.moveVelocity(leftVelocity);
        MTR_frontRight.moveVelocity(rightVelocity);
        MTR_backLeft.moveVelocity(leftVelocity);
        MTR_backRight.moveVelocity(rightVelocity);

        while ( MTR_frontLeft.getPosition() + MTR_backLeft.getPosition() > distanceInTicks*2) {

            error = (MTR_frontLeft.getPosition() + MTR_backLeft.getPosition()) - (MTR_frontRight.getPosition()*-1 + MTR_backRight.getPosition()*-1);
            integral = integral + error;
            derivative = error - lastError;

            rightVelocity = leftVelocity + (error * kP)
                                        + (integral * kI)
                                        + (derivative * kD);

            MTR_frontRight.moveVelocity(-rightVelocity);
            MTR_backRight.moveVelocity(-rightVelocity);


            pros::delay(20);
        }
        MTR_frontLeft.moveVelocity(0);
        MTR_frontRight.moveVelocity(0);
        MTR_backLeft.moveVelocity(0);
        MTR_backRight.moveVelocity(0);
    }
}

void driveInches (double distanceInInches) {
    driveFeet(distanceInInches/12);
}

void pickUpBalls() {
    MTR_rollerLeft.moveVelocity(-200);
    MTR_rollerRight.moveVelocity(200);
    MTR_pushup.moveVelocity(-600);
}

void ejectBalls() {
    MTR_rollerLeft.moveVelocity(200);
    MTR_rollerRight.moveVelocity(-200);
    MTR_pushup.moveVelocity(600);
}

void stopIntake() {
    MTR_rollerLeft.moveVelocity(0);
    MTR_rollerRight.moveVelocity(0);
    MTR_pushup.moveVelocity(0);
}

// LVGL FUNCTIONS

static lv_res_t teamAction(lv_obj_t * ddlist){
    uint8_t id = lv_obj_get_free_num(ddlist);

    char sel_str[32];
    lv_ddlist_get_selected_str(ddlist, sel_str);
    std::cout << "ddlist: " << sel_str << std::endl;

    if (std::string(sel_str) == "Red"){
        team = false;
        std::cout << "Team: " << team << std::endl;
    } else if (std::string(sel_str) == "Blue"){
        team = true;
        std::cout << "Team: " << team << std::endl;
    }


    return LV_RES_OK;
}

static lv_res_t sideAction(lv_obj_t * ddlist){
    uint8_t id = lv_obj_get_free_num(ddlist);

    char sel_str[32];
    lv_ddlist_get_selected_str(ddlist, sel_str);
    std::cout << "ddlist: " << sel_str << std::endl;

    if (std::string(sel_str) == "Left"){
        side = false;
    } else if (std::string(sel_str) == "Right"){
        side = true;
    }

    std::cout << "Side: " << side << std::endl;

    return LV_RES_OK;
}

static lv_res_t restrictionAction(lv_obj_t * ddlist){
    uint8_t id = lv_obj_get_free_num(ddlist);

    char sel_str[32];
    lv_ddlist_get_selected_str(ddlist, sel_str);
    std::cout << "ddlist: " << sel_str << std::endl;

    if (std::string(sel_str) == "Restricted"){
        restricted = true;
    } else if (std::string(sel_str) == "Unrestricted"){
        restricted = false;
    }

    std::cout << "Restricted: " << restricted << std::endl;

    return LV_RES_OK;
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


    // sidebar buttons
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);
    lv_obj_set_size(btn1, 140, 50);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 10);

    lv_obj_t * btn2 = lv_btn_create(scr, btn1);
    lv_obj_align(btn2, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t * btn3 = lv_btn_create(scr, btn1);
    lv_obj_align(btn3, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -10);

    lv_obj_t * label1 = lv_label_create(btn1, NULL);
    lv_label_set_text(label1, "Button 1");

    lv_obj_t * label2 = lv_label_create(btn2, NULL);
    lv_label_set_text(label2, "Button 2");

    lv_obj_t * label3 = lv_label_create(btn3, NULL);
    lv_label_set_text(label3, "Button 3");


    // dropdown auto selector
    lv_obj_t * dropdownTeam = lv_ddlist_create(lv_scr_act(), NULL);
    lv_ddlist_set_options(dropdownTeam, "Red\n" "Blue");
    lv_ddlist_set_hor_fit(dropdownTeam, false);
    lv_obj_set_width(dropdownTeam, 160);
    lv_obj_align(dropdownTeam, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_ddlist_set_draw_arrow(dropdownTeam, true);
    lv_ddlist_set_action(dropdownTeam, teamAction);


    // dropdown side selector
    lv_obj_t * dropdownSide = lv_ddlist_create(lv_scr_act(), NULL);
    lv_ddlist_set_options(dropdownSide, "Left\n" "Right");
    lv_ddlist_set_hor_fit(dropdownSide, false);
    lv_obj_set_width(dropdownSide, 160);
    lv_obj_align(dropdownSide, NULL, LV_ALIGN_IN_LEFT_MID, 10, 20);
    lv_ddlist_set_draw_arrow(dropdownSide, true);
    lv_ddlist_set_action(dropdownSide, sideAction);

    // dropdown restriction seelctor
    lv_obj_t * dropdownRestrict = lv_ddlist_create(lv_scr_act(), NULL);
    lv_ddlist_set_options(dropdownRestrict, "Restricted\n" "Unrestricted");
    lv_ddlist_set_hor_fit(dropdownRestrict, false);
    lv_obj_set_width(dropdownRestrict, 160);
    lv_obj_align(dropdownRestrict, NULL, LV_ALIGN_IN_TOP_MID, 15, 10);
    lv_ddlist_set_draw_arrow(dropdownRestrict, true);
    lv_ddlist_set_action(dropdownRestrict, restrictionAction);

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

    if (side == false) { // left side
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
        pros::delay(500);
        MTR_shooter.moveVelocity(0);
        pickUpBalls();
        driveFeet(4.666666666666666);
//         driveInches(56);
        pros::delay(600);
        turnAngleRIGHT(135);
        pros::delay(5);
        stopIntake();
        pros::delay(5);
//         driveFeet(6);
        driveFeet(3.8333);
//         driveInches(46);
        pros::delay(5);
        turnAngleRIGHT(45);
        pros::delay(5);
        driveFeet(2);
//         driveInches(20);
        pickUpBalls();
        MTR_pushup.moveVelocity(-400);
        MTR_shooter.moveVelocity(-600);
        pros::delay(1650);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);
        pros::delay(1000);
        MTR_shooter.moveVelocity(0);
        MTR_pushup.moveVelocity(0);
        MTR_rollerLeft.moveVelocity(150);
        MTR_rollerRight.moveVelocity(-150);
        pros::delay(200);
        driveFeet(-2);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);

        // new code
        turnAngleRIGHT(60);
//         pros::delay(5);
//         pickUpBalls();
//         driveInches(63);
//         MTR_pushup.moveVelocity(-400);
//         MTR_shooter.moveVelocity(-600);
//         pros::delay(1600);
//         MTR_rollerLeft.moveVelocity(0);
//         MTR_rollerRight.moveVelocity(0);
//         pros::delay(1000);
//         MTR_shooter.moveVelocity(0);
//         MTR_pushup.moveVelocity(0);
//         MTR_rollerLeft.moveVelocity(150);
//         MTR_rollerRight.moveVelocity(-150);
//         pros::delay(200);
//         driveFeet(-2);
    }

    else if (side == true) { // right side // regionals
        pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
        MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        MTR_shooter.moveVelocity(600);
        pros::delay(500);
        MTR_shooter.moveVelocity(0);

        drive->setMaxVelocity(400);
        // drive->moveDistance(23.5_in);
        // driveInches(20);
        drive->moveDistance(20_in);
        // drive->turnAngle(-141_deg);
        // turnAngleLEFT(145);
        drive->turnAngle(145_deg);
        pros::delay(10);
        pickUpBalls();
        // drive->moveDistance(27.3_in);
        drive->moveDistance(30_in);
        MTR_pushup.moveVelocity(-400);
        MTR_shooter.moveVelocity(-600);
        pros::delay(2100);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);
        pros::delay(1000);
        MTR_shooter.moveVelocity(0);
        MTR_pushup.moveVelocity(0);
        MTR_rollerLeft.moveVelocity(100);
        MTR_rollerRight.moveVelocity(-100);
        pros::delay(200);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);
/*
        MTR_pushup.moveVelocity(-600);
        MTR_shooter.moveVelocity(-600);
        pros::delay(400);
        MTR_rollerLeft.moveVelocity(0);
        MTR_rollerRight.moveVelocity(0);
        pros::delay(2000);
        MTR_shooter.moveVelocity(0);
        MTR_pushup.moveVelocity(0);
*/
      //  drive->moveDistance(-27.3_in);
        drive->moveDistance(-27.3_in);

    } else { // Lu's testing
/*
           pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
           MTR_5.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
           MTR_shooter.moveVelocity(600);
           pickUpBalls();
           driveInches(54.5);
           pros::delay(650);
           turnAngleRIGHT(151);
           pros::delay(5);
           stopIntake();
           driveInches(66);
           pros::delay(5);
           pickUpBalls();
           MTR_pushup.moveVelocity(-600);
           MTR_shooter.moveVelocity(-600);
           pros::delay(1600);
           MTR_rollerLeft.moveVelocity(0);
           MTR_rollerRight.moveVelocity(0);
           pros::delay(1000);
           MTR_shooter.moveVelocity(0);
           MTR_pushup.moveVelocity(0);
           MTR_rollerLeft.moveVelocity(100);
           MTR_rollerRight.moveVelocity(100);
           pros::delay(200);
           driveFeet(-2);
           MTR_rollerLeft.moveVelocity(0);
           MTR_rollerRight.moveVelocity(0);
           turnAngleRIGHT(62);
           pros::delay(5);
           pickUpBalls();
           driveInches(63);

           MTR_pushup.moveVelocity(-600);
           MTR_shooter.moveVelocity(-600);
           pros::delay(1600);
           MTR_rollerLeft.moveVelocity(0);
           MTR_rollerRight.moveVelocity(0);
           pros::delay(1000);
           MTR_shooter.moveVelocity(0);
           MTR_pushup.moveVelocity(0);
           MTR_rollerLeft.moveVelocity(100);
           MTR_rollerRight.moveVelocity(100);
           pros::delay(200);
           driveFeet(-2);
*/
        std::cout << "wtf bro" << std::endl;
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
    int testing = 0;
    if (testing) {
        MTR_frontLeft.tarePosition();
        MTR_frontRight.tarePosition();
        MTR_backLeft.tarePosition();
        MTR_backRight.tarePosition();

        while (1){
            drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY)/2,
                                        controller.getAnalog(ControllerAnalog::rightY)/2);
            std::cout << MTR_frontLeft.getPosition() << std::endl;
            std::cout << MTR_frontRight.getPosition() << std::endl;
            std::cout << MTR_backLeft.getPosition() << std::endl;
            std::cout << MTR_backRight.getPosition() << std::endl;
        }
    } else {
        while(1){

    //tank drive
            drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY),
                                        controller.getAnalog(ControllerAnalog::rightY));
            if (controller.getDigital(okapi::ControllerDigital::X))  {
                MTR_shooter.moveVelocity(-600);
            } else if (controller.getDigital(okapi::ControllerDigital::L2)) {
                MTR_shooter.moveVelocity(600);
            } else if (controller.getDigital(okapi::ControllerDigital::L1)) {
                MTR_shooter.moveVelocity(-600);
                MTR_pushup.moveVelocity(-400);
            } else {
                MTR_shooter.moveVelocity(0);
            }

            if (controller.getDigital(okapi::ControllerDigital::R1)) {
                pickUpBalls();
            } else if (controller.getDigital(okapi::ControllerDigital::R2)) {
                MTR_rollerLeft.moveVelocity(200);
                MTR_rollerRight.moveVelocity(-200);
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


}
