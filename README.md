(Very) small program to control a [Noctua 5V PWM fan](https://noctua.at/en/products/fan?connector=12&voltage=5) with an [Adafruit Trinket 5V](https://learn.adafruit.com/introducing-trinket) and a potentiometer. Thanks be to the below for explaining how some of these things work:

+ [Newbie's Guide to AVR Timers](https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?name=PNphpBB2&file=viewtopic&t=50106)
+ [Trinket Timer notes](https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?name=PNphpBB2&file=viewtopic&t=50106)

# Datasheets:

 + [Fan](https://noctua.at/pub/media/wysiwyg/Noctua_PWM_specifications_white_paper.pdf)
 + [ATtiny85](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)

# Program

Timer 0 on the ATtiny85 is used, as it allows for Phase Correct PWM mode which is important to use for motor control (according to the internet).

We need to select the PWM frequency (25KHz for the fan), and be able to set the duty cycle based on a potentiometer reading. OutputCompare A (OCA) is used to set the frequency, OutputCompare B (OCB) to control the duty cycle. The PWM frequncy is given by the below equation:

Frequency = CPU frequency / prescaler / (OCR0A + 1) / 2

The CPU frequency is 8MHz, and the available prescalers are listed in the ATTiny85 datasheet. From these, we calculate that we use no prescaler and a value of OCR0A of 159.

The duty cycle of the PWM signal is given by:

Duty cycle = (OCR0B + 1) / (OCR0A + 1)

The values of the TCCR0 configuration registers uses are below. See the documentation above for what the values mean.

TCCR0A:

| COM0A1 | COM0A0 | COM0B1 | COM0B0 | xxxxxx | xxxxxx | WGM01  | WGM00 |
------------------------------------------------------------------------
| 0      | 0      | 1      | 0      | 0      | 0      | 0      | 1     |

TCCR0B:

| FOC0A  | FOC0B  | xxxxxx | xxxxxx | WGM02  | CS02   | CS01   | CS00  |
------------------------------------------------------------------------
| 0      | 0      | 0      | 0      | 1      | 0      | 0      | 1     |

# Hardware
