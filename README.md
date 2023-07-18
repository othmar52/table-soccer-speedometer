# Table Soccer Speedometer

This Arduino-based project measures and displays the speed of a ball on a table soccer game. By using light barriers, it calculates the flight height of the ball and then determines its speed based on that information.

## Features

- Calculates ball speed based on flight height
- Uses light barriers to measure the interruption time
- Displays speed and flight height on an LCD screen

## Assumptions

- The ball is assumed to approach the goal surface at a 90-degree angle, disregarding different impact angles such as left, right, ascending, or descending.
- Acceleration or deceleration of the ball during the measurement process is ignored.

## Prototype Image

![Prototype Image](https://github.com/othmar52/table-soccer-speedometer/assets/7056051/3d830197-5aec-4e9f-9297-603be98f3aab)

## Getting Started

To build and run this project, follow these steps:

1. Clone the repository: `git clone https://github.com/othmar52/table-soccer-speedometer.git`
2. Connect the Arduino board to the computer.
3. Upload the sketch to the Arduino board using the Arduino IDE.
4. Set up the light barriers and ensure they are properly aligned.
5. Power on the system and observe the speed and flight height measurements on the LCD screen.

## Components Used

- Arduino board (e.g., Arduino Uno, ESP32)
- Light barriers (e.g., SFH 203)
- LCD screen (compatible with your Arduino board)
- Jumper wires

## Contributing

Contributions to this project are welcome! If you have any ideas, improvements, or bug fixes, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
