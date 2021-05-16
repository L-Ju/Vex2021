
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

        drive->setMaxVelocity(150);
        // drive->moveDistance(23.5_in);
        driveInches(20);
        // drive->turnAngle(-141_deg);
        turnAngleLEFT(145);
        pros::delay(10);
        pickUpBalls();
        // drive->moveDistance(27.3_in);
        driveInches(30);
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
        driveInches(-27.3);

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
