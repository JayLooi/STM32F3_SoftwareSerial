# Interrupt-driven Software UART on STM32F3
This library uses Timer3 and GPIO port C pin 6 (tx) and pin 7 (rx). 

## Example (echo on serial terminal)

```
#include "SoftwareSerial.h"
int main(void)
{
  ssInit(9600);         // Initialise software UART and specify the baud rate
	while(1) {
		if(isRxAvailable()) {
			ssWriteByte(ssReadByte());
		}
	}

	return 0;
}
```

