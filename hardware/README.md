# Group 17 schematic

The submitted schematic keeps the required **16 sensor channels** and the
**CD74HC4067** multiplexer.

The physical prototype uses **8 sensors** and a **CD4051BE** multiplexer.
The prototype and the required schematic therefore have different channel counts
and multiplexer pinouts.

- `ProjectSchematic.SchDoc` is the editable Altium source.
- `ProjectSchematic.pdf` is the printable schematic.

The resistor values are 1k ohm for each sensor and the LED, 330 ohm at the MOSFET
gate, 100k ohm for the gate pull-down, and 4.7k ohm for each I2C pull-up.
