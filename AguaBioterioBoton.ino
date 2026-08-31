/*
 * SISTEMA DE AGUA PARA ROEDORES - VERSIÓN FINAL
 * Botón manual (Pin 3) -> Funciona siempre.
 * Switch (Pin 2) -> Activa/Desactiva el ciclo automático de 24hs.
 */

// --- CONFIGURACIÓN DE USUARIO ---
const unsigned long INTERVALO_HORAS = 24;          
const unsigned long DURACION_BOMBA_MS = 1000; // Ajustar según calibración (1000ms = 1ml aprox)

// --- PINES ---
const uint8_t pinBomba = 7;       // A la compuerta (Gate) del MOSFET
const uint8_t pinSwitch = 2;      // Al interruptor de ciclo (Pata A a Pin 2, Pata B a GND)
const uint8_t pinBotonManual = 3; // Al pulsador manual (Pata A a Pin 3, Pata B a GND)

// --- VARIABLES INTERNAS ---
const unsigned long msPorHora = 3600000; 
unsigned long intervaloMs = INTERVALO_HORAS * msPorHora;
unsigned long tiempoUltimaActivacion = 0;
bool sistemaActivo = false;

void setup() {
  pinMode(pinBomba, OUTPUT);
  digitalWrite(pinBomba, LOW); // Asegurar bomba apagada al inicio
  
  // Activamos resistencias internas para que los botones no necesiten resistencias externas
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinBotonManual, INPUT_PULLUP);
}

void loop() {
  
  // --- 1. ENTREGA MANUAL (Siempre disponible) ---
  // Si el pulsador une el Pin 3 con GND, leemos LOW
  if (digitalRead(pinBotonManual) == LOW) {
    entregarAgua();
    delay(200); // Pequeño rebote para no activar dos veces por error
  }

  // --- 2. SISTEMA AUTOMÁTICO (Depende del Switch) ---
  if (digitalRead(pinSwitch) == LOW) {
    
    // Si el switch acaba de ser encendido
    if (!sistemaActivo) {
      sistemaActivo = true;
      tiempoUltimaActivacion = millis(); // Empezar a contar desde este momento
    }

    unsigned long tiempoActual = millis();
    
    // Si transcurrió el tiempo configurado
    if (tiempoActual - tiempoUltimaActivacion >= intervaloMs) {
      entregarAgua();
      tiempoUltimaActivacion = tiempoActual; // Reiniciar el reloj para las próximas 24hs
    }

  } else {
    // Si el switch está en OFF, el cronómetro se resetea
    sistemaActivo = false;
  }
}

// Función estandarizada para activar la bomba
void entregarAgua() {
  digitalWrite(pinBomba, HIGH);
  delay(DURACION_BOMBA_MS); 
  digitalWrite(pinBomba, LOW);
}
