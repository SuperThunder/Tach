# Tach
 Simple tachometer class for Mbed OS6 based on InterruptIn with a Ticker to calculate RPM at a given interval. Uses a to track the actual time elapsed between RPM calculations.

# Installation
Navigate to your project directory, and enter the command:
`mbed add https://github.com/SuperThunder/Tach.git`

# Usage
```C++
//Tach starts automatically when object created
Tach fan_tach(TACH_PIN);
...
void print_tach()
{
    printf("Tach reading (RPM): %d\n", fan_tach.getRPM());
}

//Functions available
uint32_t getRPM();
void setCalculationInterval(chrono::milliseconds t);

void reset();
void start();
void stop();
```