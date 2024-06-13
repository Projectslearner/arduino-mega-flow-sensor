/*
    Project name : Flow Sensor
    Modified Date: 13-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-mega-flow-sensor
*/

const int flowSensorPin = 2;  // Digital pin connected to the flow sensor output
unsigned int pulseCount = 0;  // Variable to count pulses from the flow sensor
float flowRate;               // Variable to store calculated flow rate
float flowMilliLitres;        // Variable to store calculated flow in milliliters
unsigned long startTime;      // Variable to store start time for flow measurement
unsigned long elapsedTime;    // Variable to store elapsed time for flow measurement

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  pinMode(flowSensorPin, INPUT); // Set flow sensor pin as INPUT
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, RISING); // Attach interrupt on rising edge
  startTime = millis();       // Start time for flow measurement
}

void loop() {
  elapsedTime = millis() - startTime; // Calculate elapsed time since last measurement
  
  // If elapsed time is greater than 1000 milliseconds (1 second), calculate flow rate
  if (elapsedTime > 1000) {
    detachInterrupt(digitalPinToInterrupt(flowSensorPin)); // Detach interrupt during calculation
    
    // Calculate flow rate based on pulse count and elapsed time
    flowRate = (1000.0 / (float(elapsedTime) / float(pulseCount)));
    flowMilliLitres = (flowRate / 60.0) * 1000.0; // Convert flow rate to milliliters per minute
    
    // Print flow rate and flow in milliliters to Serial Monitor
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min\t");
    Serial.print("Flow: ");
    Serial.print(flowMilliLitres);
    Serial.println(" ml");
    
    pulseCount = 0; // Reset pulse count for next measurement
    startTime = millis(); // Reset start time for next measurement
    
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, RISING); // Attach interrupt again
  }
}

// Interrupt Service Routine (ISR) for pulse counting
void pulseCounter() {
  pulseCount++; // Increment pulse count
}
