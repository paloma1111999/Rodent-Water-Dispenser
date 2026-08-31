# Rodent-Water-Dispenser

# Automated Rodent Water Delivery System

This project provides an autonomous, Arduino-based solution for delivering controlled amounts of water to rodents at specific intervals. It is designed for laboratory or home-care environments where a computer connection is not available after setup.
<img width="963" height="1280" alt="WhatsApp Image 2026-08-31 at 12 38 45" src="https://github.com/user-attachments/assets/bc85b6d3-e8da-48b4-a8d3-db2e4a77e178" />

## Features
- **Standalone Operation:** Runs on a 12V power supply without a PC.
- **Automatic Cycle:** Dispenses water every X hours (user-configurable, default 24h).
- **Manual Override:** A physical button allows for manual dispensing (priming or extra hydration) without affecting the automated timer.
- **Safety Switch:** A master toggle switch to enable or disable the automatic schedule.

## Hardware Components
- **Microcontroller:** Arduino Uno.
- **Actuator:** 12V Micro-pump or Solenoid Valve.
- **Power:** 12V DC Power Supply.
- **Switching:** N-Channel MOSFET (e.g., IRFZ44N) or Relay Module.
- **Protection:** 1N4007 Diode (Flyback diode for the pump).
- **Inputs:** 1x Toggle Switch (Automatic mode), 1x Momentary Push-button (Manual delivery).
- **Delivery:** Check the PrintableWaterDelivery.3mf file. I glued it tu a tupper with a screw and a needle as seen in the image.
  <img width="963" height="1280" alt="WhatsApp Image 2026-08-31 at 12 38 45 (1)" src="https://github.com/user-attachments/assets/4946f361-fed7-4ca4-93fb-546a2569782b" />


## Wiring Diagram
I used this diagram: https://forum.arduino.cc/t/how-to-control-a-motor-with-external-power/357324
### Power
- **12V (+)** -> Arduino `VIN` pin AND Pump (+) terminal.
- **12V (-)** -> Arduino `GND` pin AND MOSFET `Source`.

### Controls
- **Toggle Switch:** Connected between **Pin 2** and **GND**.
- **Push Button:** Connected between **Pin 3** and **GND**.
- **MOSFET Gate:** Connected to **Pin 7**.

### Pump/Solenoid
- **Pump (-)** -> MOSFET `Drain`.
- **Flyback Diode:** Place across the pump terminals (Anode to Negative, Cathode/Striped end to Positive).
- I used this one: https://www.harfington.com/products/p-1035329?srsltid=AfmBOoq4zBB5QLnGf7daASw75qGxCNdbWW8ioFcCodandrWTnTUKmcIR

## Installation
1. Clone this repository.
2. Open `AutomatedWaterDispenser.ino` in the Arduino IDE.
3. Adjust `INTERVALO_HORAS` and `DURACION_BOMBA_MS` according to your specific needs and pump calibration.
4. Upload the code to your Arduino.
5. Disconnect the USB and power the system via the 12V source.

## Calibration Tip
To deliver exactly 1ml, measure the output of your pump 10 times. Divide the time (10,000ms) by the volume delivered to find the `DURACION_BOMBA_MS` required for 1ml.
