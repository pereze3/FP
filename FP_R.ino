// PEREZE3
// FINAL PROJECT
// WIRELESS TRANSMITTER RECEIVER PAIR
// TRANSMITTING CO2 AND TEMP TO REMOTE LCD
// 04/25/16

// FP - Temp/humidity sensor and LCD Integration over Wirless RF.
// This is the parent code for the FP.
// In this code we read temp and humidity sensor data
// and output the results to an LCD over Wireless RF.

// BELOW ARE CREDITS WHERE DUE TO ORIGINATORS OF PART OF THIS CODE

// Thanks to Robert Tillart for providing base code on the combo
// sensor read values

// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

// Designate digital pin #6 for LCD serial communication
const int TxPin = 6;

// Include “SoftwareSerial” header file from the Arduino Library
#include <SoftwareSerial.h>

// Creating a “SoftwareSerial” object
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

// Include the Virtual Wire header file needed for the receiver
#include "VirtualWire.h"

// Declare a local variable needed for the receiver
int count;

// The following void setup method prints to the serial monitor
// This is used for testing sensor readings
void setup()
{
  // The folowing code is for debugging only
  Serial.begin(9600);
  // Prints "Setup" to the serial monitor
  Serial.println("setup");
  // Sets pin D12 as the RX Pin
  vw_set_rx_pin(12);
  // Required for DR3100
  vw_set_ptt_inverted(true);
  // Bits per sec
  vw_setup(4000);
  // Start the receiver PLL running
  vw_rx_start();
}

// This is the main loop for checking the validity of the data from the sensor
// as well as reading and reporting the data from the sensor and writing it to the LCD
void loop()
{
  // This is the main loop for the RF Receiver
  // The following writes from the transmitter to the buffer
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    // Flash a light to show received good message
    int i;
    // Write to the onboard LED
    digitalWrite(13, true);
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");

    // Iterate through the buffer
    for (i = 0; i < buflen; i++)
    {
      // One by one print the chracters
      char c = (buf[i]);
      Serial.print(c);
      Serial.print(" ");
      
      // The following iterates through to display the transmitter data to LCD
      // Set baud rate and begin serial port communication to LCD
      mySerial.begin(9600);
      // Sending turn backlight on command to screen
      mySerial.write(17);
      // Print the character
      mySerial.print(c);
    }
    // Increase the conter for the iteration
    count++;
    // Short delay
    delay(2100);
    // Turn off the onbboard LED
    Serial.println("");
    digitalWrite(13, false);
    // Sending clear command to screen
    mySerial.write(12);
  }
}
