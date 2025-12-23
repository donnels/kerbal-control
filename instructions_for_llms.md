# Instructions for LLMs: Building Kerbal Space Program Controller

## Core Principles
- NO MAGIC: Every line of code must be explained. No unexplained constants, functions, or logic.
- Extreme Hemingway: Write concisely. Cut every unnecessary word. Be direct.
- DRY: Eliminate repetition. Reuse code where possible.
- KISS: Simplify everything. Avoid complexity.
- MVP: Deliver minimum viable product first. Core features only.

## Project Scope
Build Arduino Pro Micro controller for Kerbal Space Program.
- Emulate keyboard inputs.
- Use WS2812 LEDs for status.
- Debounced buttons for actions.
- Start with staging (spacebar) and arm/disarm toggle.

## Code Structure
- Single .ino file for MVP.
- Clear comments for every block.
- Pin definitions at top.
- Setup and loop functions only.
- Use millis for timing, no delays in loop.

## Hardware
- Arduino Pro Micro (ATmega32u4).
- WS2812 LEDs on pin 7.
- Button on pin 8 (arm/disarm).
- Stage button on pin 9.

## Key Bindings (KSP)
- Space: Stage
- T: SAS toggle
- G: Gear toggle
- .: Time warp increase
- ,: Time warp decrease

## Next Steps
1. Integrate existing prototypes.
2. Add keyboard emulation.
3. Test on Pro Micro.
4. Add more buttons iteratively.</content>
<parameter name="filePath">/home/deck/Documents/Github/donnels/kerbal-control/instructions_for_llms.md