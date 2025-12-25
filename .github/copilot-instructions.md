# Copilot Instructions for kerbal-control

This repository is a hardware/software project for a custom Kerbal Space Program controller using an Arduino Pro Micro, WS2812 LEDs, and physical switches/buttons. The codebase is designed for iterative hardware prototyping, with a split workflow between a development host (Steamdeck) and a Raspberry Pi used for compiling and uploading to the Arduino.

## Architecture & Major Components
- **kerbal-controller.ino**: Main Arduino sketch. Handles button debouncing, toggle switch logic, LED animations, and USB keyboard output. All hardware logic is here.
- **3d/**: OpenSCAD models and STL files for 3D-printed enclosures, keycap holders, and test stands.
- **button-test/**, **button-test2/**, **fastled-test/**: Minimal Arduino sketches for hardware/feature prototyping.
- **plantuml/**: PlantUML diagrams for state/activity/dev pipeline, kept in sync with code and workflow.
- **docs/**: Generated documentation and HTML/PDF versions of the README.
- **github/INSTRUCTIONS.md**: Contributor and LLM guidelines.

## Development Workflow
- Edit code on the host (Steamdeck, VS Code).
- Transfer code to the Pi using `scp`:
  ```sh
  scp /path/to/kerbal-controller.ino sean@arduinoworkstation.fritz.box:/home/sean/kerbal-control/
  ```
- SSH to the Pi and compile/upload using Arduino CLI:
  ```sh
  ssh sean@arduinoworkstation.fritz.box
  cd /home/sean/kerbal-control
  /home/sean/bin/arduino-cli compile --fqbn arduino:avr:leonardo kerbal-control.ino
  /home/sean/bin/arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo kerbal-control.ino
  ```
- Monitor serial output for debugging:
  ```sh
  screen /dev/ttyACM0 9600
  ```
- See `README.asciidoc` for full pipeline and troubleshooting.

## Project-Specific Patterns
- **Always use INPUT_PULLUP for button/toggle pins.**
- **Debouncing** is handled in software using `millis()`-based logic, not `delay()`.
- **Toggle switch logic**: System always starts disarmed, regardless of switch position; only toggles armed state on first change after boot.
- **LEDs**: WS2812 controlled via FastLED; LED 0 is the toggle indicator (red/green), LEDs 6-10 animate or blink based on state.
- **No blocking code**: Avoid `delay()` in main logic except for brief flashes (e.g., stage LED feedback).
- **PlantUML diagrams**: State, activity, and dev pipeline diagrams are kept up to date in `plantuml/`.

## Integration & External Dependencies
- **FastLED** and **Keyboard** Arduino libraries are required.
- **Arduino CLI** is used for compiling/uploading on the Pi.
- **3D models** are for hardware prototyping and not required for code builds.

## Key Files/Directories
- `kerbal-controller.ino`: Main logic, always update this for hardware changes.
- `plantuml/`: Diagrams for logic and workflow.
- `README.asciidoc`: Full documentation, including hardware notes and workflow.
- `github/INSTRUCTIONS.md`: Contributor/LLM instructions.

## Coding Principles
- **No Magic**: All logic must be explicit and discoverable. Avoid hidden state, implicit flows, or unexplained behavior.
- **Hemingway Extreme**: Write code and comments in the simplest, clearest way possible. Use short sentences. Avoid jargon and ambiguity.
- **Dry**: Do not repeat yourself. Extract common logic. Prefer functions over copy-paste.
- **KISS (Keep It Simple, Stupid)**: Favor simple, direct solutions. Avoid cleverness. If in doubt, make it simpler.
- **MVP (Minimum Viable Product)**: Implement the smallest, testable version of a feature first. Iterate only as needed.

## Example: Adding a New Button
1. Define the pin at the top of `kerbal-controller.ino`.
2. Use `pinMode(PIN, INPUT_PULLUP)` in `setup()`.
3. Add debounced logic in the main loop or as a new handler function.
4. Update LED/status logic as needed.
5. Document changes in `README.asciidoc` and update diagrams if logic changes.

---

For more, see the README and PlantUML diagrams. Keep this file up to date with any new conventions or workflow changes.
