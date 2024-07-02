# Stop Watch System

This project implements a Stop Watch system using an ATmega32 microcontroller. The system utilizes timer functionality, multiplexed common anode 7-segment displays, and external interrupts to provide accurate time measurement and control.

## Specifications

1. Microcontroller: ATmega32
   - Frequency: 1 MHz

2. Timer Configuration
   - Timer1 configured in CTC mode for precise time measurement.

3. Display
   - Six Common Anode 7-segment displays.

4. Multiplexing Technique
   - Utilize one 7447 decoder for all 7-segment displays.
   - Control enable/disable for each 7-segment display using an NPN BJT transistor connected to one of the MCU pins.

5. Multiplexing Method
   - Connect more than one 7-segment display using the multiplexing technique.
   - Switch displays using transistors, allowing only one display to be driven by the microcontroller at a time.
   - Persistence of vision creates the illusion of a continuous display.

6. Connection Details
   - Connect 7447 decoder 4 pins to the first 4 pins in PORTC.
   - Use the first 6 pins in PORTA as enable/disable pins for the six 7-segment displays.

7. Power-On Start
   - The Stop Watch counting should start automatically once power is connected to the microcontroller.

8. External Interrupt INT0 (Falling Edge)
   - Connect a push button with the internal pull-up resistor.
   - When a falling edge is detected, the Stop Watch time should be reset.

9. External Interrupt INT1 (Rising Edge)
   - Connect a push button with the external pull-down resistor.
   - When a rising edge is detected, the Stop Watch time should be paused.

10. External Interrupt INT2 (Falling Edge)
    - Connect a push button with the internal pull-up resistor.
    - When a falling edge is detected, the Stop Watch time should be resumed.

## Usage

To use the Stop Watch system:

1. Connect the ATmega32 microcontroller to the necessary components, including the 7-segment displays, 7447 decoder, and push buttons, based on the specified connections.

2. Program the microcontroller with the provided code to configure the timer, interrupts, and display multiplexing.

3. Power on the system, and the Stop Watch counting will start automatically.

4. Press the push buttons according to the defined interrupt configurations:
   - Pressing the reset button (INT0) will reset the Stop Watch time.
   - Pressing the pause button (INT1) will pause the Stop Watch time.
   - Pressing the resume button (INT2) will resume the Stop Watch time.

5. The time will be displayed on the six 7-segment displays using the multiplexing technique.

## Conclusion

The Stop Watch system implemented with the ATmega32 microcontroller provides accurate time measurement and control. By utilizing timer functionality, multiplexed common anode 7-segment displays, and external interrupts, the system allows users to measure time intervals and control the Stop Watch operation effectively.

