#include <Arduino.h>

// Define hardware pin assignments on the microcontroller
const int LIGHT_SENSOR_PIN = 34; // Analog pin for light monitoring
const int SMART_LAMP_PIN   = 23; // Digital pin driving the lighting relay
const int COOLING_FAN_PIN  = 22; // Digital pin driving the ventilation relay

// Environmental control thresholds
const int DARKNESS_THRESHOLD = 1500; // Sensor value below which lights turn on
const float TEMP_THRESHOLD   = 28.0;  // Celsius threshold to activate fan

void setup() {
    // Initialize serial communication channel for data telemetry
    Serial.begin(115200);
    
    // Configure pin behaviors
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(SMART_LAMP_PIN, OUTPUT);
    pinMode(COOLING_FAN_PIN, OUTPUT);
    
    Serial.println("--- Smart Home IoT Node Initialized Successfully ---");
}

void loop() {
    // Read raw sensor data from environmental inputs
    int ambientLight = analogRead(LIGHT_SENSOR_PIN);
    
    // Simulate a temperature calculation (Mapping variable voltage to degrees)
    float currentTemp = 24.0 + (analogRead(35) * 0.002); 

    // System Telemetry Log Output
    Serial.print("Telemetry Data -> Light Lux: ");
    Serial.print(ambientLight);
    Serial.print(" | Temperature: ");
    Serial.print(currentTemp);
    Serial.println(" C");

    // Automation Logic Block 1: Smart Lighting System
    if (ambientLight < DARKNESS_THRESHOLD) {
        digitalWrite(SMART_LAMP_PIN, HIGH); // Turn on the light
        Serial.println("[SYSTEM ALERT]: Low Light Detected. Smart Lamp ACTIVATED.");
    } else {
        digitalWrite(SMART_LAMP_PIN, LOW);  // Turn off the light
    }

    // Automation Logic Block 2: Climate Ventilation Control
    if (currentTemp > TEMP_THRESHOLD) {
        digitalWrite(COOLING_FAN_PIN, HIGH); // Turn on cooling fan
        Serial.println("[SYSTEM ALERT]: High Temperature Detected. Cooling Fan RUNNING.");
    } else {
        digitalWrite(COOLING_FAN_PIN, LOW);  // Shut off fan
    }

    delay(2000); // Wait 2 seconds before running the calculation loop again
}
