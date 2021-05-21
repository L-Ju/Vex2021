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

void shoot() {
    MTR_shooter.moveVelocity(-600);
    pros::delay(10);
    MTR_pushup.moveVelocity(-400);
}

void justShoot() {
    MTR_shooter.moveVelocity(-600);
}

void afterShoot() {
    MTR_rollerLeft.moveVelocity(85);
    MTR_rollerRight.moveVelocity(-85);
    MTR_pushup.moveVelocity(-40);
    MTR_shooter.moveVelocity(0);
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

    MTR_backRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_backLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

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

    MTR_backRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_backLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    pros::Motor MTR_5(SHOOTER_MOTOR_PORT);
    

    std::cout << "cock" << std::endl;

    profileController->generatePath(
        {
        {0_ft, 0_ft, 0_deg},
        {5.4_ft, 0_ft, 0_deg}
        },
        "D" // Profile name
    ); 
    // OLD

    

    

    pros::delay(10);
    profileController->generatePath(
        {
        {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
        {1.5_ft, -0.1_ft, 135_deg}
        },
        "A" // Profile name
    ); profileController->setTarget("A"); 

    MTR_rollerLeft.moveVelocity(-300);
    MTR_rollerRight.moveVelocity(300);
    MTR_pushup.moveVelocity(-400);
    MTR_shooter.moveVelocity(600);
    pros::delay(50);
    
    profileController->waitUntilSettled();
    
    MTR_shooter.moveVelocity(0);
    pros::delay(375);
    stopIntake();
    pros::delay(10);
    
    profileController->generatePath(
        {
        {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
        {0.6_ft, 0_ft, 0_deg}
        },
        "A" // Profile name
    ); 
    
    profileController->setTarget("A"); 
    profileController->generatePath(
        {
        {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
        {4.4_ft, 0_ft, 0_deg}
        },
        "B" // Profile name
    );
    profileController->generatePath(
        {
        {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
        {1.45_ft, 0_ft, 0_deg}
        },
        "C" // Profile name
    );
    profileController->waitUntilSettled();

    shoot();
    pros::delay(300);
    afterShoot();
    
    drive->setMaxVelocity(500);

    drive->moveDistance(-2_ft);
    stopIntake();
    drive->setMaxVelocity(300);
    
    drive->turnAngle(116_deg);

    drive->setMaxVelocity(600);
    
    profileController->setTarget("B"); profileController->waitUntilSettled();

    drive->turnAngle(-90_deg);

    
    
    profileController->setTarget("C"); profileController->waitUntilSettled();

    shoot();
    pros::delay(600);
    afterShoot();

    drive->moveDistance(-2_ft);
    drive->turnAngle(67_deg);
    pickUpBalls();
    

    
    shoot();
    profileController->setTarget("D"); 
    
    profileController->waitUntilSettled();
    MTR_rollerLeft.moveVelocity(0);
    MTR_rollerRight.moveVelocity(0);
    
    pros::delay(600);
    afterShoot();
     
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

    MTR_backRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_backLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontRight.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    MTR_frontLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
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
            MTR_shooter.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    //tank drive
            drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY),
                                        controller.getAnalog(ControllerAnalog::rightY));
            if (controller.getDigital(okapi::ControllerDigital::X))  {
                MTR_shooter.moveVelocity(-600);
            } else if (controller.getDigital(okapi::ControllerDigital::L2)) {
                MTR_shooter.moveVelocity(600);
            } else if (controller.getDigital(okapi::ControllerDigital::L1)) {
                MTR_shooter.moveVelocity(-600);
                pros::delay(100);
                MTR_pushup.moveVelocity(-400);
            } else if (controller.getDigital(okapi::ControllerDigital::Y)) {
                MTR_shooter.moveVelocity(600);
                MTR_pushup.moveVelocity(400);
                MTR_rollerLeft.moveVelocity(200);
                MTR_rollerRight.moveVelocity(-200);
            }  else {
                MTR_shooter.moveVelocity(0);
            }

            if (controller.getDigital(okapi::ControllerDigital::R1)) {
                pickUpBalls();
            } else if (controller.getDigital(okapi::ControllerDigital::R2)) {
                MTR_rollerLeft.moveVelocity(200);
                MTR_rollerRight.moveVelocity(-200);
            } else {
                if(!controller.getDigital(okapi::ControllerDigital::Y)){
                    MTR_rollerLeft.moveVelocity(0);
                    MTR_rollerRight.moveVelocity(0) ;
                    if(!controller.getDigital(okapi::ControllerDigital::L1)){
                        MTR_pushup.moveVelocity(0);
                    }
                }
            }

            pros::delay(10);
        }
    }


}
