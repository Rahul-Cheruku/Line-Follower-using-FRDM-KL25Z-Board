#include <MKL25Z4.H>

// Define LED pins
#define LED_PIN_0 (1U << 0)
#define LED_PIN_1 (1U << 1)
#define LED_PIN_2 (1U << 2)
#define LED_PIN_3 (1U << 3)

// Define sensor pins
#define SENSOR_LEFT_PIN (1U << 5)
#define SENSOR_RIGHT_PIN (1U << 4)

int main(void) {
    // Enable clock for PORTB and PORTC
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;

    // Set LED pins as outputs
    PORTB->PCR[0] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; // LED on PORTB pin 0
    PORTB->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; // LED on PORTB pin 1
    PORTB->PCR[2] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; // LED on PORTB pin 2
    PORTB->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; // LED on PORTB pin 3

    // Set sensor pins as inputs
    PORTC->PCR[5] = PORT_PCR_MUX(1); // Sensor left on PORTC pin 5
    PORTC->PCR[4] = PORT_PCR_MUX(1); // Sensor right on PORTC pin 4

    // Set LED pins as outputs
    PTB->PDDR |= LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3;

    while (1) {
        // Read sensor inputs
        uint32_t sensorLeftValue = (PTC->PDIR & SENSOR_LEFT_PIN) >> 5;
        uint32_t sensorRightValue = (PTC->PDIR & SENSOR_RIGHT_PIN) >> 4;
        uint32_t case_value = (sensorLeftValue << 1) | sensorRightValue;

        switch (case_value) {
            case 0:
                // Forward
                PTB->PSOR = LED_PIN_0;
                PTB->PCOR = LED_PIN_1;
                PTB->PSOR = LED_PIN_2;
                PTB->PCOR = LED_PIN_3;
                break;
            case 1:
                // Turn right
                PTB->PSOR = LED_PIN_0;
                PTB->PCOR = LED_PIN_1;
                PTB->PCOR = LED_PIN_2;
                PTB->PSOR = LED_PIN_3;
                break;
            case 2:
                // Turn left
                PTB->PCOR = LED_PIN_0;
                PTB->PSOR = LED_PIN_1;
                PTB->PSOR = LED_PIN_2;
                PTB->PCOR = LED_PIN_3;
                break;
            case 3:
                // Stop
                PTB->PCOR = LED_PIN_0;
                PTB->PCOR = LED_PIN_1;
                PTB->PCOR = LED_PIN_2;
                PTB->PCOR = LED_PIN_3;
                break;
        }
    }
}
