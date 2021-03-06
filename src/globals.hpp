#include "main.h"

// controllers
extern Controller controller;

extern bool team;
extern bool side;
extern bool restricted;

extern double ticksPerInch;
extern double kP;
extern double kI;
extern double kD;
extern int autoRoutine;

extern double chassisWidthInch;
extern double ticksPerInch2;
extern double gP;
extern double gI;
extern double gD;

// drive motors
extern int FRONT_LEFT_MOTOR_PORT;
extern int FRONT_RIGHT_MOTOR_PORT;
extern int BACK_LEFT_MOTOR_PORT;
extern int BACK_RIGHT_MOTOR_PORT;
extern Motor MTR_frontLeft;
extern Motor MTR_frontRight;
extern Motor MTR_backLeft;
extern Motor MTR_backRight;

// roller motors
extern int LEFT_ROLLER_MOTOR_PORT;
extern int RIGHT_ROLLER_MOTOR_PORT;
extern Motor MTR_rollerLeft;
extern Motor MTR_rollerRight;

// shooter
extern int SHOOTER_MOTOR_PORT;
extern Motor MTR_shooter;

// pushup
extern int PUSHUP_MOTOR_PORT;
extern Motor MTR_pushup;

// chassis
extern std::shared_ptr<ChassisController> drive;
