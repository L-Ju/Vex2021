 #include "main.h"

// controllers
Controller controller;

bool team = true; // true = blue
bool side = false; // false = left
bool restricted = true; // true = can't go over the line

double ticksPerInch = 87.7604166667; // final tuned value = 86
double kP = 0.09; // final tuned value = 0.09
double kI = 0;
double kD = 0;
int autoRoutine = 1;

double gP = 0.9; 
double gI = 0.0042;
double gD = 0.00001;

// drive motors
int FRONT_LEFT_MOTOR_PORT  =  -13;
int FRONT_RIGHT_MOTOR_PORT  =  -20;
int BACK_LEFT_MOTOR_PORT  =  -14;
int BACK_RIGHT_MOTOR_PORT  =  -19;
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
  .withDimensions({AbstractMotor::gearset::blue, (5.0/3.0)}, {{3.25_in, 10_in}, imev5BlueTPR})
  .build();

std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.9, // Maximum linear velocity of the Chassis in m/s
      1.75, // Maximum linear acceleration of the Chassis in m/s/s
      35.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(drive)
    .buildMotionProfileController();


std::shared_ptr<AsyncVelocityController<double, double>> rollerController = 
  AsyncVelControllerBuilder()
    .withMotor({-LEFT_ROLLER_MOTOR_PORT, RIGHT_ROLLER_MOTOR_PORT}) // lift motor port 3
    .build();