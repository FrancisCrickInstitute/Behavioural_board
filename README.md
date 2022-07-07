# Behavioural_board

This piece of hardware is a Teensy 3.2, Teensy LC or Teensy 4 [1] breakout board with 4 valve controls and (capacitive) licking sensors and with the same amount of digital inputs/outputs (8 in total). This device pretends to be a tool for behavioural experiments which need to control up to four valves and sense 4 licking sensors. The board has eight digital pins with interrupt capability. These pins are connected to a BNC and they can be used to display digital signals or to trigger externally the valves for instance. The Teensy 3.2 performs very well on the capacitive sensor library [2] achieving sub-millisecond sampling periods while using one licking sensor at 120 MHz clock speed. All thought the licking frequency in mice is ~7 Hz, sub-millisecond resolution is required when accurate sensing of lick onset and offset is desired [3]. There is also an Incremental encoder connection for 5V Encoders with logic level shifters for phases A and B.


![Behavioural board v2](https://user-images.githubusercontent.com/54901317/177177025-56f0a11d-c3ec-42a9-9601-7cabe0dad406.png)

# R1-R8 resistor values (Capacitive sensor pins resistors)
The value of the capacitive sensor emitter is 1MΩ and the receiver digital pin has a 1kΩ resistance value to avoid an accidental electric shock [5]. The value of the high resistance value resistor can be changed to higher values in order to increase sensitivity.

# R9-R12 Calculation example (Transistor base current)
The solenoid valve used for the design is the Lee company model LHDA0533215H. The current needed on the transistor collector has been calculated using the power and the resistance from the manufacturer specifications [4].
 
P_valve=550 mW  R_valve=46 Ω

P_valve=I_valve^2*R_valve
I_valve=√(P_valve/R_valve )=√((550 mW)/(46 Ω))
I_valve=109 mA

Base-Ccollector 337 NPN Transistor

h_FE=100    I_C=100mA    V_(CE(ON))=1.2V   
I_B=I_C/h_FE =(100 mA)/100=1mA

Base-Emitter mesh

-TTL+I_B R+V_(CE(ON))=0
-3.3V+(1 mA)R+1.2V=0
R1=2.1V/1mA=2.1kΩ

Collector-Emitter mesh

-V_cc+R_valve I_C+V_CE=0
-3.3V+46Ω 100mA+V_CE=0
V_CE=1.3V

# Limitations

If you are using Teensy LC Pin 1 does not have interrupt capability, therefore Trigger 1 cannot be used using interrupts.

# References

[1] 	"https://www.pjrc.com/teensy/teensy31.html". 

[2] 	"https://github.com/PaulStoffregen/CapacitiveSensor". 

[3] 	B. Williams, A. Speed and B. Haider, "A novel device for real-time measurement and manipulation of licking behavior in head-fixed mice," Journal of Neurophisiology, vol. 120, pp. 2975-2987, 2018. 

[4] 	"https://www.theleeco.com/products/electro-fluidic-systems/solenoid-valves/control-valves/lhd-series/3-port/ported/". 

[5] 	"https://www.pjrc.com/teensy/td_libs_CapacitiveSensor.html". 


