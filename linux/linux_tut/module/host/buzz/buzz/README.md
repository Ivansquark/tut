# Buzz Driver for Zynq7010 Platform Using AXI GPIO

## Overview

This Linux kernel driver controls a PWM output on a GPIO pin using the AXI 
GPIO interface on the Zynq7010 platform. The driver is designed to operate 
through a device tree configuration and provides the following functionalities:
- PWM signal generation based on user input (frequency and time).
- Sysfs interface for reading and writing frequency and time values.
- Safe access to GPIO with synchronization using spinlocks to prevent 
  concurrent access.

## Features

- **PWM Control**: The driver generates a PWM signal on the GPIO pin with 
  a given frequency and time duration.
- **Sysfs Interface**: The driver exposes the `frequency`, `time`, and 
  `start` settings via sysfs for easy access from user space.
- **Thread-Safety**: The use of spinlocks ensures safe access to the GPIO 
  resources, preventing race conditions in multi-threaded environments.
- **Device Tree Integration**: The driver automatically detects the GPIO 
  base address and other necessary resources from the device tree.

## Functionality

- **write() Operation**: User space can write the frequency (in Hz) and 
  time (in milliseconds) to `/dev/buzz` as a comma-separated string 
  (`frequency,time`).
- **Sysfs Interface**:
  - **/sys/kernel/buzz/frequency**: Get or set the frequency of the PWM 
    signal.
  - **/sys/kernel/buzz/time**: Get or set the time duration of the PWM 
    signal.
  - **/sys/kernel/buzz/start**: Trigger the PWM signal generation by 
    writing `1` to start PWM, or `0` to stop it.

### Example Usage

1. **Writing to `/dev/buzz`**:
   Write the frequency and time to control the PWM signal:
   ```sh
   echo "1000,500" > /dev/buzz

