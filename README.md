# Automated Bottle Filler System


<p align="center">
  <strong>Arduino-based automatic bottle filling system using an IR sensor, relays, pump, lock, catch mechanism, actuator, and buzzer.</strong>
</p>


---


## Overview

This project is an **automatic bottle filler prototype** controlled by an Arduino. The system counts bottles using an IR sensor and starts the filling sequence after detecting the target number of bottles. Once triggered, it activates a lock/catch mechanism, moves an actuator, runs a pump for a fixed filling duration, and then resets for the next cycle.

The project is suitable for:

- Small-scale bottle filling automation
- Arduino relay-control projects
- Educational industrial automation demonstrations
- Prototype beverage, water, chemical, or liquid filling systems

---

## Features

- Counts bottles automatically using an IR sensor
- Starts the filling cycle after detecting **4 bottles**
- Uses relay outputs to control:
  - Pump
  - Lock mechanism
  - Catch mechanism
  - Actuator
- Startup buzzer indication
- Serial Monitor status logs
- Prevents double-triggering during an active sequence using `sequenceRunning`
- Resets automatically after each cycle

---

## Hardware Requirements

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno/Nano or compatible board | 1 | Main controller |
| IR sensor module | 1 | Bottle detection |
| 4-channel relay module | 1 | Controls pump, lock, catch, and actuator |
| DC pump / water pump | 1 | Liquid filling |
| Linear actuator / motor mechanism | 1 | Nozzle or bottle-position movement |
| Buzzer | 1 | Startup and cycle alert |
| External power supply | 1 | Powers pump, actuator, and relays |
| Tubing, frame, bottle holder, wiring | As needed | Mechanical setup |

> Use a relay module and power supply rated properly for your pump and actuator.

---

## Pin Configuration

| Arduino Pin | Code Name | Connected Device |
|---:|---|---|
| 12 | `RELAY1` | Pump |
| 6 | `RELAY2` | Lock |
| 3 | `RELAY3` | Catch |
| 9 | `RELAY4` | Actuator |
| 7 | `BUZZER` | Buzzer |
| 11 | `IR_PIN` | IR Sensor |

---

## How It Works

1. Arduino starts and beeps twice.
2. IR sensor detects bottles one by one.
3. Each rising edge from the IR sensor increases the bottle count.
4. When the count reaches **4 bottles**, the filling sequence starts.
5. Buzzer gives a short alert.
6. Lock and catch mechanism are activated.
7. Actuator moves into position.
8. Pump turns ON and fills the bottles.
9. Pump turns OFF after the configured filling time.
10. Actuator and catch mechanism return to idle state.
11. Counter resets and the system waits for the next 4 bottles.

---

## Sequence Timing

| Step | Action | Duration |
|---:|---|---:|
| 1 | Startup buzzer beep | 2 short beeps |
| 2 | Bottle detection debounce | 120 ms |
| 3 | Cycle alert buzzer | 100 ms |
| 4 | Actuator ON before filling | 1400 ms |
| 5 | Pump ON / filling time | 8000 ms |
| 6 | Delay before actuator OFF | 500 ms |
| 7 | Catch/lock reset delay | 1500 ms + 1000 ms |
| 8 | Final reset delay | 3500 ms |

---

## Installation

1. Install the Arduino IDE.
2. Connect the components according to the pin configuration table.
3. Open the Arduino sketch file, for example:

   ```text
   bottle_filler.ino
   ```

4. Select your Arduino board from:

   ```text
   Tools > Board
   ```

5. Select the correct COM port from:

   ```text
   Tools > Port
   ```

6. Upload the code.
7. Open Serial Monitor at **9600 baud** to view system messages.

---

## Repository Structure

```text
automatic-bottle-filler/
├── bottle_filler.ino
├── README.md
├── LICENSE
└── images/
    └── project-photo-placeholder.jpg
```

---

## Configuration

The default code starts the filling cycle after detecting 4 bottles:

```cpp
if (bottleCount >= 4) {
  // Start filling sequence
}
```

To change the number of bottles before starting the cycle, modify:

```cpp
if (bottleCount >= 4)
```

For example, to start after 6 bottles:

```cpp
if (bottleCount >= 6)
```

To change the pump filling time, modify this delay:

```cpp
delay(8000);
```

For example, for 5 seconds of filling:

```cpp
delay(5000);
```

---

## Important Notes

- Relay modules may be **active HIGH** or **active LOW**. If a relay works in reverse, adjust the `HIGH` and `LOW` values in the code.
- Use a separate external power supply for high-current devices such as pumps and actuators.
- Connect Arduino GND and external power supply GND together when required by your relay module.
- Test each relay output separately before running the full machine.
- Do not run pumps dry.
- Keep water/liquid away from the Arduino and exposed electrical wiring.
- Add fuses, emergency stop switches, and protective casing for real-world use.

---

## Serial Monitor Output

Example output:

```text
System Starting...
System Ready
Bottle Count: 1
Bottle Count: 2
Bottle Count: 3
Bottle Count: 4
4 Bottles Detected - Starting Relay Sequence
Relay2 (Lock) ON
Relay3 (Catch) ON
Relay4 (Actuator) ON
Relay1 (Pump) ON
Relay1 (Pump) OFF
Relay4 (Actuator) OFF
Relay3 (Catch) OFF
Relay2 (Lock) OFF
Cycle Complete. Resetting...
```

---


