#include <wiringPi.h>
#include <wiringSerial.h>

#define MAX485_DE_RE_PIN 4 // GPIO pin connected to MAX485 DE/RE pin

int main() {
    // Initialize WiringPi and serial communication
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Unable to initialize WiringPi\n");
        return 1;
    }

    int serialPort = serialOpen("/dev/ttyS0", 9600); // Use the appropriate serial port

    if (serialPort < 0) {
        fprintf(stderr, "Unable to open serial port\n");
        return 1;
    }

    // Setup DE/RE pin for MAX485
    pinMode(MAX485_DE_RE_PIN, OUTPUT);
    digitalWrite(MAX485_DE_RE_PIN, LOW); // Set to receive mode initially

    // Send data to Arduino
    const char* dataToSend = "Hello, Arduino!\n";
    printf("Sending: %s", dataToSend);

    digitalWrite(MAX485_DE_RE_PIN, HIGH); // Set to transmit mode
    serialPuts(serialPort, dataToSend);
    serialFlush(serialPort);

    // Wait for data to be transmitted
    delay(100);

    digitalWrite(MAX485_DE_RE_PIN, LOW); // Set back to receive mode

    // Close serial port
    serialClose(serialPort);

    return 0;
}
