#include <Arduino.h> // Include the Arduino core library

// Target date and time for the countdown 
int targetYear = 2026;   // Set for 2026
int targetMonth = 1; 
int targetDay = 1;   
int targetHour = 0;  
int targetMinute = 0;

unsigned long previousMillis = 0; // Store the last time the counter was updated

// Variables to hold the current date and time
int currentYear = 0;
int currentMonth = 0;
int currentDay = 0;
int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;

// Variables to hold the remaining time
unsigned long hours;
unsigned long minutes;
unsigned long seconds;

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to return the number of days in a given month
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31; // Months with 31 days
        case 4: case 6: case 9: case 11:
            return 30; // Months with 30 days
        case 2:
            return isLeapYear(year) ? 29 : 28; // February, check for leap year
        default:
            return 0; // Invalid month
    }
}

// Function to calculate the total seconds since epoch (1970-01-01)
unsigned long calculateEpochTime(int year, int month, int day, int hour, int minute, int second) {
    unsigned long days = 0;

    // Count days from 1970 to the target year
    for (int y = 1970; y < year; y++) {
        days += (isLeapYear(y) ? 366 : 365);
    }
    // Count days in the months leading up to the target month
    for (int m = 1; m < month; m++) {
        days += daysInMonth(m, year);
    }
    days += day - 1; // Subtract 1 to account for zero-based counting

    // Calculate total seconds
    unsigned long totalSeconds = days * 86400 + hour * 3600 + minute * 60 + second;
    return totalSeconds;
}

// Function to initialize the countdown based on the current time string
void counterBegin(String currentTimeString) {
    // Parse the current time string into individual components
    currentYear = currentTimeString.substring(0, 4).toInt();
    currentMonth = currentTimeString.substring(5, 7).toInt();
    currentDay = currentTimeString.substring(8, 10).toInt();
    currentHour = currentTimeString.substring(11, 13).toInt();
    currentMinute = currentTimeString.substring(14, 16).toInt();
    currentSecond = currentTimeString.substring(17, 19).toInt();

    // Calculate current and target times in seconds since epoch
    unsigned long currentTimeInSeconds = calculateEpochTime(currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    unsigned long targetTimeInSeconds = calculateEpochTime(targetYear, targetMonth, targetDay, targetHour, targetMinute, 0);

    // Calculate the remaining time
    long remainingTime = targetTimeInSeconds - currentTimeInSeconds;

    // Display the remaining time or indicate that the countdown is finished
    if (remainingTime > 0) {
        unsigned long hours = remainingTime / 3600;
        unsigned long minutes = (remainingTime % 3600) / 60;
        unsigned long seconds = remainingTime % 60;

        Serial.print("Time remaining: ");
        Serial.print(hours);
        Serial.print(" hours, ");
        Serial.print(minutes);
        Serial.print(" minutes, ");
        Serial.print(seconds);
        Serial.println(" seconds");
    } else {
        hours = 0;
        minutes = 0;
        seconds = 0;
        Serial.println("Countdown finished!");
    }
}

// Function to increment the current time by one second
void refreshCurrentTime() {
    currentSecond++;
    if (currentSecond >= 60) {
        currentSecond = 0;
        currentMinute++;
        if (currentMinute >= 60) {
            currentMinute = 0;
            currentHour++;
            if (currentHour >= 24) {
                currentHour = 0;
                currentDay++;
                if (currentDay > daysInMonth(currentMonth, currentYear)) {
                    currentDay = 1;
                    currentMonth++;
                    if (currentMonth > 12) {
                        currentMonth = 1;
                        currentYear++;
                    }
                }
            }
        }
    }
}

// Function to manage the countdown logic
void count() {
    unsigned long currentMillis = millis();

    // Update the countdown every second
    if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis; // Save the last update time
        refreshCurrentTime(); // Update the current time

        // Calculate current and target times in seconds since epoch
        unsigned long currentTimeInSeconds = calculateEpochTime(currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
        unsigned long targetTimeInSeconds = calculateEpochTime(targetYear, targetMonth, targetDay, targetHour, targetMinute, 0);

        // Calculate the remaining time
        long remainingTime = targetTimeInSeconds - currentTimeInSeconds;

        // Display the remaining time or indicate that the countdown is finished
        if (remainingTime > 0) {
            hours = remainingTime / 3600;
            minutes = (remainingTime % 3600) / 60;
            seconds = remainingTime % 60;

            Serial.print("Time remaining: ");
            Serial.print(hours);
            Serial.print(" hours, ");
            Serial.print(minutes);
            Serial.print(" minutes, ");
            Serial.print(seconds);
            Serial.println(" seconds");
        } else {
            hours = 0;
            minutes = 0;
            seconds = 0;
            Serial.println("Countdown finished!");
        }
    }
}
