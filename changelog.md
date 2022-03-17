# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.2.0] - 2022-03-17

### Added
- _env:avr-168pa_ environment lets us export to the atmega168pa
- _ANALOG_READ_ compile flag chooses between reading input CV pins using analog or digital read 

### Changed
- _cutesynth low memory_ using the low memory version of the code required changes to the spec

## [1.1.0] - 2022-03-04
### Added
- _time_dilation_ variable lets us adjust the time step to account for different clock speeds
- _env:avr-328pb_ environment lets us export to the atmega328pb
