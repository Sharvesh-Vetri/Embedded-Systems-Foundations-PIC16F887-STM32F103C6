# Embedded Systems Foundations – PIC16F887 & STM32F103C6

This repository contains foundational embedded systems implementations using **PIC16F887** and **STM32F103C6** microcontrollers.

The work focuses on **bare-metal C programming** and understanding **core MCU peripherals** through datasheet-driven development.

---

## Contents
- GPIO (input/output, pull-ups, debouncing)
- Timers (delay generation, interrupt-based timing)
- External and timer interrupts
- UART communication (polling and interrupt-driven)
- ADC (polling and interrupt-based)
- PWM using timers

Each implementation is peripheral-focused and self-contained.

---

## Tools Used
- **MPLAB X IDE** (PIC16F887)
- **Keil µVision** (STM32F103C6)
- **Proteus** for functional simulation and validation

---

## About the `circuit` Files
Each implementation directory contains a file named `circuit`, which is a **Proteus simulation project** corresponding to the firmware in that directory.

Proteus simulations are used **only for functional verification**.  
All firmware is written to be **hardware-ready** and not dependent on simulator-specific behavior.

---

## How to Use
1. Navigate to the required microcontroller and peripheral folder
2. Review the source code for configuration and logic flow
3. (Optional) Open the `circuit` file in Proteus
4. Load the compiled HEX/ELF file
5. Run the simulation to observe expected behavior

---

## Purpose
This repository represents **junior embedded firmware engineer–level work**, intended to build and demonstrate:
- Register-level understanding
- Interrupt handling
- Hardware-oriented firmware design

This is a learning and reference repository, not production firmware.

---

