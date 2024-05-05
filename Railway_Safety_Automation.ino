#include <Servo.h>

// Define pin numbers for IR sensors
const int IR_sensor1_pin = 2;
const int IR_sensor2_pin = 3;
const int IR_sensor3_pin = 4;
const int IR_sensor4_pin = 5;

// Define pin numbers for servo motors
const int servo1_pin = 6;
const int servo2_pin = 9;
const int servo3_pin = 10;
const int servo4_pin = 11;

// Define pin numbers for LEDs
const int red_led1_pin = 13;
const int yellow_led1_pin = 12;
const int green_led1_pin = 7;
const int red_led2_pin = A2;
const int yellow_led2_pin = A1;
const int green_led2_pin = A0;

// Define pin number for reed sensor
const int reed_sensor_pin = 8;

// Define pin number for buzzer
const int buzzer_pin = A3;

int delay_time = 100;

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize IR sensors
  pinMode(IR_sensor1_pin, INPUT);
  pinMode(IR_sensor2_pin, INPUT);
  pinMode(IR_sensor3_pin, INPUT);
  pinMode(IR_sensor4_pin, INPUT);

  // Initialize servo motors
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);
  servo4.attach(servo4_pin);

  // Initialize LEDs
  pinMode(red_led1_pin, OUTPUT);
  pinMode(yellow_led1_pin, OUTPUT);
  pinMode(green_led1_pin, OUTPUT);
  pinMode(red_led2_pin, OUTPUT);
  pinMode(yellow_led2_pin, OUTPUT);
  pinMode(green_led2_pin, OUTPUT);

  // Initialize reed sensor
  pinMode(reed_sensor_pin, INPUT);

  // Initialize buzzer
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  // Read IR sensors
  int IR_sensor1_state = digitalRead(IR_sensor1_pin);
  int IR_sensor2_state = digitalRead(IR_sensor2_pin);
  int IR_sensor3_state = digitalRead(IR_sensor3_pin);
  int IR_sensor4_state = digitalRead(IR_sensor4_pin);

  // Read reed sensor
  int reed_sensor_state = digitalRead(reed_sensor_pin);

  // Print sensor values to serial monitor
  Serial.print("IR Sensor 1: ");
  Serial.print(IR_sensor1_state);
  Serial.print(", IR Sensor 2: ");
  Serial.print(IR_sensor2_state);
  Serial.print(", IR Sensor 3: ");
  Serial.print(IR_sensor3_state);
  Serial.print(", IR Sensor 4: ");
  Serial.print(IR_sensor4_state);
  Serial.print(", Reed Sensor: ");
  Serial.println(reed_sensor_state);

  // Control servo motors and LEDs based on IR sensor readings
  if (IR_sensor1_state == 0 || IR_sensor2_state == 0) {
    servo1.write(0);
    servo2.write(0);
    Serial.println("Gate 1 and 2 closed!");

    digitalWrite(red_led1_pin, HIGH);
    Serial.println("RED LED ON!");

    digitalWrite(yellow_led1_pin, LOW);
    digitalWrite(green_led1_pin, LOW);

    delay(delay_time);

    if (IR_sensor1_state == 0 && IR_sensor2_state == 0) {
      digitalWrite(red_led1_pin, LOW);

      digitalWrite(yellow_led1_pin, HIGH);
      Serial.println("YELLOW LED ON!");

      digitalWrite(green_led1_pin, LOW);
      delay(delay_time);
    }
  } else {
    servo1.write(90);
    servo2.write(90);
    Serial.println("Gate 1 and 2 Opened!");

    digitalWrite(red_led1_pin, LOW);
    digitalWrite(yellow_led1_pin, LOW);

    digitalWrite(green_led1_pin, HIGH);
    Serial.println("GREEN LED ON!");
  }

  if (IR_sensor3_state == 0 || IR_sensor4_state == 0) {
    servo3.write(0);
    servo4.write(0);
    Serial.println("Gate 3 and 4 closed!");

    digitalWrite(red_led2_pin, HIGH);
    Serial.println("RED LED ON!");

    digitalWrite(yellow_led2_pin, LOW);
    digitalWrite(green_led2_pin, LOW);

    delay(delay_time);

    if (IR_sensor3_state == 0 && IR_sensor4_state == 0) {
      digitalWrite(red_led2_pin, LOW);

      digitalWrite(yellow_led2_pin, HIGH);
      Serial.println("YELLOW LED ON!");

      digitalWrite(green_led2_pin, LOW);

      delay(delay_time);
    }
  } else {
    servo3.write(90);
    servo4.write(90);
    Serial.println("Gate 3 and 4 Opene!");

    digitalWrite(red_led2_pin, LOW);
    digitalWrite(yellow_led2_pin, LOW);

    digitalWrite(green_led2_pin, HIGH);
    Serial.println("GREEN LED ON!");
  }

  // Control buzzer based on reed sensor reading
  if (reed_sensor_state == 0) {
    digitalWrite(buzzer_pin, HIGH);
    Serial.println("Buzzer ON!");
    delay(delay_time);
  } else {
    digitalWrite(buzzer_pin, LOW);
    Serial.println("Buzzer OFF!");
  }

  // Delay for stability
  delay(300);
}
