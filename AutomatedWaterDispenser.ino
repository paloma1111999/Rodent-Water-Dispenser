/*
 * AUTOMATED RODENT WATER DISPENSER
 * 
 * Logic:
 * - Manual Button (Pin 3): Always active. Dispenses water for the set duration.
 * - Master Switch (Pin 2): When ON (LOW), starts the countdown for the 24h cycle.
 */

// --- USER CONFIGURATION ---
const unsigned long INTERVAL_HOURS = 24;          
const unsigned long PUMP_DURATION_MS = 1000; // Calibrate this to reach desired volume (e.g., 1ml)

// --- PIN DEFINITIONS ---
const uint8_t pinPump = 7;        // To MOSFET Gate or Relay
const uint8_t pinSwitch = 2;      // To Toggle Switch (Pin 2 to GND)
const uint8_t pinManualBtn = 3;   // To Push Button (Pin 3 to GND)

// --- INTERNAL VARIABLES ---
const unsigned long msPerHour = 3600000; 
unsigned long intervalMs = INTERVAL_HOURS * msPerHour;
unsigned long lastActivationTime = 0;
bool systemActive = false;

void setup() {
  pinMode(pinPump, OUTPUT);
  digitalWrite(pinPump, LOW); // Ensure pump is OFF on startup
  
  // Internal Pull-ups remove the need for external resistors
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinManualBtn, INPUT_PULLUP);
}

void loop() {
  
  // --- 1. MANUAL OVERRIDE ---
  // Works regardless of the master switch state.
  if (digitalRead(pinManualBtn) == LOW) {
    dispenseWater();
    delay(200); // Debounce delay
  }

  // --- 2. AUTOMATIC SYSTEM ---
  if (digitalRead(pinSwitch) == LOW) {
    
    // If the switch was just turned ON
    if (!systemActive) {
      systemActive = true;
      lastActivationTime = millis(); // Start counting from this moment
    }

    unsigned long currentTime = millis();
    
    // Check if the interval has passed
    if (currentTime - lastActivationTime >= intervalMs) {
      dispenseWater();
      lastActivationTime = currentTime; // Reset the cycle timer
    }

  } else {
    // If the switch is OFF, the automatic timer is reset
    systemActive = false;
  }
}

// Function to activate the pump
void dispenseWater() {
  digitalWrite(pinPump, HIGH);
  delay(PUMP_DURATION_MS); 
  digitalWrite(pinPump, LOW);
}
