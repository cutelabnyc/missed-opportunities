# Missed Opportunities

[![Build Status](https://travis-ci.com/cutelabnyc/missed-opportunities.svg?branch=master)](https://travis-ci.com/cutelabnyc/missed-opportunities)

_Keep on missing each other, Our world's out of order, All I see is Missed Opportunity_

— Daryl Hall & John Oates 🌻🌺🌻🌺

## Installation

Make sure platform io command line tools are installed

```
brew install platformio
```

In the `missed-opportunities` project directory, install the external libraries

```
pio lib install
```

## Production Usage

Make sure the Pocket Programmer is connected
```
avrdude -c usbtiny -p t84
```

Upload the code using the Pocket Programmer
```
pio run -t upload -e avr-328pb # or avr-168pa depending on chip
```

## Development

After creating a feature branch and making your changes, you can build locally without the board plugged in to make sure the code can compile. There are two building environments specified in `platform.ini`:

-   `[env:uno]` is the default environment, for uploading and onboard integration testing
-   `[env:native]` is for building, uploading, and unit testing

To perform unit testing and building without the board plugged in you can simply run

```
pio test -e native && pio run
```

Then plug the prototype board into your computer to perform integration tests

```
pio test -e uno
```

Finally, upload the code with the optional `monitor` flag to view the output of any Serial printing put in the code for debugging.

```
pio run --target upload --target monitor
```

After pull requesting, Travis CI will make sure that the code is able to compile and perform integration testing in order to make sure everything is squeaky clean before merging

## Clock Settings

### Atmega328P

Internal crystal: 
  -Ulfuse:w:0xe2:m
  -Uhfuse:w:0xd9:m
  -Uefuse:w:0xf3:m

External crystal: (up to 20MHz)
  -Ulfuse:w:0xff:m
  -Uhfuse:w:0xd9:m
  -Uefuse:w:0xff:m

### Atmega328PB

Internal crystal: 
  -Ulfuse:w:0xe2:m
  -Uhfuse:w:0xd9:m
  -Uefuse:w:0xf7:m

External crystal: (up to 16MHz)
  -Ulfuse:w:0xff:m
  -Uhfuse:w:0xd9:m
  -Uefuse:w:0xf7:m
