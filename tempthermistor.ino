int count = 0;

// High Thermistor parameters
const double thermistorNominal = 10100.0;  // Nominal resistance of the thermistor
const double temperatureNominal = 25.0;    // Nominal temperature in degrees Celsius
const double betaCoefficient = 3910.5;     // Beta coefficient of the thermistor


// Analog pin connected to the thermistor
const int thermistorPin = A0;

void setup() {
  Serial.begin(115200);
  Serial.println("new measurement");
}

void loop() {
  int rawValue = analogRead(thermistorPin);
  Serial.println(rawValue);
  // Convert raw value to resistance
  double resistance = (1023.0 / rawValue) - 1.0;
  Serial.println(resistance);
  resistance = thermistorNominal / resistance;
  
  // Calculate temperature using the Steinhart-Hart equation
  double steinhart;
  steinhart = resistance / thermistorNominal;                // (R/Ro)
  steinhart = log(steinhart);                                // ln(R/Ro)
  steinhart /= betaCoefficient;                              // (1/B) * ln(R/Ro)
  steinhart += 1.0 / (temperatureNominal + 273.15);          // + (1/To)
  steinhart = 1.0 / steinhart;                               // Invert
  double temperature = steinhart - 273.15;                   // Convert to Celsius
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  delay(10000);
}
