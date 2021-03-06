#pragma once
#include <FEHLCD.h>
#include <FEHBattery.h>
#include <FEHSD.h>

#define ICE_CREAM_ERROR 0.3
#define RPS_FRONT_ANGLE 90.0
#define RIGHT_ANGLE 90.0
#define FRONT_ANGLE 0.0
#define LEFT_ANGLE 270.0
#define BACK_ANGLE 180.0
#define SPEED 80
#define SLOW_SPEED 25
#define FAST_SPEED 60
#define IPS_SPEED 8.10
#define DPS_SPEED 138.462
#define BUTTON_DISTANCE 2.0
#define DEFAULT_X_SINK 4.4
#define DEFAULT_Y_SINK 45.8
#define DEFAULT_X_TICKET 33.1 // 33.2
#define DEFAULT_Y_TICKET 29.5
#define DEFAULT_X_BURGER 33.5
#define DEFAULT_Y_BURGER 64.6
#define DEFAULT_X_JUKEBOX 3.0
#define DEFAULT_Y_JUKEBOX 8.5

// OmniMotor constants
#define VOLTAGE 6.0
#define PI 3.141592
#define MOTOR_FRONT_ANGLE 270.0
#define MOTOR_LEFT_ANGLE 150.0
#define MOTOR_RIGHT_ANGLE 30.0
#define NEG_FRONT_FACTOR 1.0
#define NEG_LEFT_FACTOR 1.0
#define NEG_RIGHT_FACTOR 1.0
#define POS_FRONT_FACTOR 0.9
#define POS_LEFT_FACTOR 0.95
#define POS_RIGHT_FACTOR 0.95
#define RAMP_DOOR_MIN 500
#define RAMP_DOOR_MAX 2300
#define ROBOARM_MIN 500
#define ROBOARM_MAX 2300

//OmniSensors constants
#define RED_LIGHT_CUTOFF 0.4
#define BLUE_LIGHT_CUTOFF 1.0
#define RED_LIGHT 1
#define BLUE_LIGHT 2
#define NO_LIGHT 0
#define LINE_CUTOFF 2.0

//Utility constants
#define LCD_LEFT_MOTOR 0
#define LCD_RIGHT_MOTOR 1
#define LCD_FRONT_MOTOR 2

// variable storing the current column that the actions are at.
int currentRow = 5;
FEHFile *fptr;

void setLCD();
void reportSpeed(int, float);
void reportMessage(char const *);
void beginDebug();
void ceaseDebug();

/**
 * @brief Opens file for debug output.
 * 
 */
void beginDebug() {
    fptr = SD.FOpen("debug.txt", "w");
}

void ceaseDebug() {
    SD.FClose(fptr);
}

/**
 * @brief Sets the inital screen.
 * 
 */
void setLCD() {
    LCD.Clear();
    LCD.WriteRC(" Left Motor:",0,0);
    LCD.WriteRC("Right Motor:",1,0);
    LCD.WriteRC("Front Motor:",2,0);
    LCD.WriteRC("    Battery:",3,0);
    LCD.WriteRC("Messages:",4,0);

    LCD.WriteRC(Battery.Voltage(), 3, 13);
}

/**
 * @brief Reports the specified speed for the specified motor to the screen.
 * Also updates the battery voltage.
 * 
 * @param motor The motor: 0 is left, 1 is right, 2 is front.
 * @param speed The speed at which the motor is running.
 */
void reportSpeed(int motor, float speed) {
    LCD.WriteRC("             ", motor, 13);
    LCD.WriteRC(speed, motor, 13);

    // updates the voltage
    LCD.WriteRC(Battery.Voltage(), 3, 13);
}

/**
 * @brief Reports the specified message to the screen.
 * 
 * @param message the message to be reported.
 */
void reportMessage(char const * message) {
    if (currentRow < 15) {
        LCD.WriteRC("                          ", currentRow, 0);
        LCD.WriteRC(message, currentRow, 0);
        if (fptr != NULL) {
            SD.FPrintf(fptr, message);
            SD.FPrintf(fptr, "\n");
        }
        currentRow++;
    } else {
        currentRow = 5;
        reportMessage(message);
    }
}
