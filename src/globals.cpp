 #include "main.h"
 
// controllers
Controller controller;

// drive motors
int FRONT_LEFT_MOTOR_PORT  =  13;
int FRONT_RIGHT_MOTOR_PORT  =  20;
int BACK_LEFT_MOTOR_PORT  =  14;
int BACK_RIGHT_MOTOR_PORT  =  19;
Motor MTR_frontLeft(FRONT_LEFT_MOTOR_PORT);
Motor MTR_frontRight(FRONT_RIGHT_MOTOR_PORT);
Motor MTR_backLeft(BACK_LEFT_MOTOR_PORT);
Motor MTR_backRight(BACK_RIGHT_MOTOR_PORT);

// roller motors
int LEFT_ROLLER_MOTOR_PORT = 3;
int RIGHT_ROLLER_MOTOR_PORT = 9;
Motor MTR_rollerLeft(LEFT_ROLLER_MOTOR_PORT);
Motor MTR_rollerRight(RIGHT_ROLLER_MOTOR_PORT);

// shooter
int SHOOTER_MOTOR_PORT = 1;
Motor MTR_shooter(SHOOTER_MOTOR_PORT);

// pushup
int PUSHUP_MOTOR_PORT = 2;
Motor MTR_pushup(PUSHUP_MOTOR_PORT);

// chassis
std::shared_ptr<ChassisController> drive =
ChassisControllerBuilder()
  .withMotors({FRONT_LEFT_MOTOR_PORT, BACK_LEFT_MOTOR_PORT},{-FRONT_RIGHT_MOTOR_PORT, -BACK_RIGHT_MOTOR_PORT})
  .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 10_in}, imev5GreenTPR}).build();
