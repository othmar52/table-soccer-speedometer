# Table Soccer Speedometer
```
  ████████╗ █████╗ ██████╗ ██╗     ███████╗    ███████╗ ██████╗  ██████╗ ██████╗███████╗██████╗ 
  ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝    ██╔════╝██╔═══██╗██╔════╝██╔════╝██╔════╝██╔══██╗
     ██║   ███████║██████╔╝██║     █████╗      ███████╗██║   ██║██║     ██║     █████╗  ██████╔╝
     ██║   ██╔══██║██╔══██╗██║     ██╔══╝      ╚════██║██║   ██║██║     ██║     ██╔══╝  ██╔══██╗
     ██║   ██║  ██║██████╔╝███████╗███████╗    ███████║╚██████╔╝╚██████╗╚██████╗███████╗██║  ██║
     ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝    ╚══════╝ ╚═════╝  ╚═════╝ ╚═════╝╚══════╝╚═╝  ╚═╝

   ███████╗██████╗ ███████╗███████╗██████╗  ██████╗ ███╗   ███╗███████╗████████╗███████╗██████╗  
   ██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝██╔════╝██╔══██╗ 
   ███████╗██████╔╝█████╗  █████╗  ██║  ██║██║   ██║██╔████╔██║█████╗     ██║   █████╗  ██████╔╝ 
   ╚════██║██╔═══╝ ██╔══╝  ██╔══╝  ██║  ██║██║   ██║██║╚██╔╝██║██╔══╝     ██║   ██╔══╝  ██╔══██╗ 
   ███████║██║     ███████╗███████╗██████╔╝╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ███████╗██║  ██║ 
   ╚══════╝╚═╝     ╚══════╝╚══════╝╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ 
```



This Arduino (ESP32)-based project measures and displays the speed of a ball on a table soccer game. By using light barriers, it calculates the flight height of the ball and then determines its speed based on that information.

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
2. Connect the ESP32 Arduino board to the computer.
3. Upload the sketch to the board using the Arduino IDE.
4. Set up the light barriers and ensure they are properly aligned.
5. Power on the system and observe the speed and flight height measurements on the LCD screen.

## Libraries used
https://github.com/MajicDesigns/MD_Parola  
https://github.com/MajicDesigns/MD_MAX72XX  

## Components Used

- Arduino board ESP32
- Light barriers (e.g., SFH 309)
- Matrix display MAX7219
- Jumper wires

## wiring
### ESP32-S Dev Kit C
https://www.azdelivery.de/products/esp32-dev-kitc-v2-ai-thinker-soldered  
```
                                  ESP32
                         ┌────────────────────┐
                         │◎ 3V3          GND ◎│
                         │◎ EN           G23 ●│────> display MAX7219 MOSI [label:DIN]
       sensor input <────│● SVP/36       G22 ●│────> sensor input
       sensor input <────│● SVN/39       TXD ◎│
       sensor input <────│● G34          RXD ◎│
       sensor input <────│● G35          G21 ●│────> sensor input
       sensor input <────│● G32          GND ◎│
       sensor input <────│● G33          G19 ●│────> sensor input
       sensor input <────│● G25          G18 ●│────> display MAX7219 SCK [label:CLK]
       sensor input <────│● G26          G5  ●│────> display MAX7219 CS [label:CS]
       sensor input <────│● G27          G17 ●│────> sensor input
       sensor input <────│● G14          G16 ●│────> button input
       sensor input <────│● G12          G4  ●│────> button input
                         │◎ GND          G0  ◎│
       sensor input <────│● G13          G2  ●│────> button input
                         │◎ SD2          G15 ●│────> button input
                         │◎ SD3          SD1 ◎│
                         │◎ CMD          SD0 ◎│
                         │◎ 5V           CLK ◎│
                         └────────────────────┘

```
### Photo transistors SFH 309
https://www.conrad.at/de/p/osram-sfh-309-fototransistor-3-mm-1080-nm-12-sfh-309-153870.html
```
                                     SHORT       LONG
                                      LEG         LEG
                                           ◎  ◎
                ┌───────────┐            ◎      ◎
     3V3 ●──────┤    670K   ├─────┬─────◎ SFH309 ◎────────● GND
                └───────────┘     │      ◎      ◎
                                  │        ◎  ◎
                                  ●
                              to ESP32
                            digital pin
```

### circuit schematics
![image](https://github.com/othmar52/table-soccer-speedometer/assets/7056051/a0d9bf40-dd66-452d-9ae6-8fcefb3113f2)



## Troubleshooting
https://aur.archlinux.org/ch34x-dkms-git.git  


## Contributing

Contributions to this project are welcome! If you have any ideas, improvements, or bug fixes, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
