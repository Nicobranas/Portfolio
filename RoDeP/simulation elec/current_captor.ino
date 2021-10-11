const int SENSOR_PIN = A0;  // Input pin for measuring Vout
const float RS = 0.1;           // Shunt resistor value (in ohms)
const long int RL = 10000;
const int VOLTAGE_REF = 12;  // Reference voltage for analog read

float sensorValue;          // Variable to store value from analog read
float current;              // Calculated current value
long temps;

void setup()
{
        Serial.begin(115200);
        while (!Serial);
        temps=11;
}

static unsigned long last_time = 0;
static unsigned long last_print_time = 0;
static int16_t id = 0;

void loop(){

        long t0=millis();
        delay(1);
        
        if (temps>50){
          // Read a value from the INA169 board
          sensorValue = analogRead(SENSOR_PIN);
        
          // Remap the ADC value into a voltage number (5V reference)
          sensorValue = (sensorValue * VOLTAGE_REF) / 1023;
        
          // Follow the equation given by the INA169 datasheet to
          // determine the current flowing through RS. Assume RL = 10k
          // Is = (Vout) / (RS x RL *1000)
          // Is = Vout
          //current = (sensorValue) / (RS*RL*1000);
          current = (sensorValue*1000) / (RS*RL);
        
          // Output value (in amps) to the serial monitor to 3 decimal
          // places
          Serial.println(current, 4);
          //Serial.println(" A");
          temps=0;
        }
        temps+=millis()-t0;

}
