# Missed Opportunities

[![Build Status](https://travis-ci.com/cutelabnyc/missed-opportunities.svg?branch=master)](https://travis-ci.com/cutelabnyc/missed-opportunities)

_Keep on missing each other, Our world's out of order, All I see is Missed Opportunity_

— Daryl Hall & John Oates 🌻🌺

## Installation

Make sure platform io command line tools are installed

```
brew install platformio
```

## Development

After creating a feature branch and making your changes, you can build locally without the board plugged in to make sure the code can compile. There are two building environments specified in `platform.ini`:

- `[env:uno]` is the default environment, for uploading and onboard integration testing
- `[env:native]` is for building, uploading, and unit testing

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

## Notes

General To-Dos:

- Make sure CI cycle is working
- Structure a basic outline from diagram on new branch
- Write unit tests and integration tests
  1. Add a unit test for a full input range on the atmega's analogIn function (0-1023)
- Structure the main loop to integrate a debugging mode where the Serial monitor is turned on
