# MIDI Foot Controller and Expression Pedal with Arduino

Here is a pretty hands-on but relatively straightforward MIDI project for Arduino! 
The board contains 6 3PDT switches, each with a dedicated LED and a quarter inch jack for an expression pedal. Each button sends a Note On message (C-1 to F-1 chromatically), and the pedal sends Control Change (CC) messages. These can be mapped to serve whatever purpose is desired within your DAW. 

![Image](https://i.imgur.com/cPsbfmu.jpg)

# Components
This project can be very adaptable to your specific needs, so some of these parts may be swapped out or left out. 
* Arduino Uno
* [6x 3PDT Latching Footswitch](https://guitarpedalparts.com/products/3pdt-latching-foot-switch-solder-lugs-blue?variant=18956215910500&currency=USD&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&gclid=CjwKCAiA_9r_BRBZEiwAHZ_v13TFxLFq4LA3L778E7HzhQMTSmOJOai6v7dpBIHWe3kPP3nutgcR-xoCDP0QAvD_BwE) (other types of buttons can be used, but use these for a satisfying, punchy click)
* [TRS 1/4" jack](https://www.sweetwater.com/store/detail/TRSFPanCon--pro-co-ftrspanelconnector?mrkgadid=3274408732&mrkgcl=28&mrkgen=gpla&mrkgbflag=0&mrkgcat=accessories&acctid=21700000001645388&dskeywordid=92700046938453127&lid=92700046938453127&ds_s_kwgid=58700005283136159&ds_s_inventory_feed_id=97700000007215323&dsproductgroupid=411460338691&product_id=TRSFPanCon&prodctry=US&prodlang=en&channel=online&storeid=&device=c&network=g&matchtype=&locationid=9004733&creative=249895767051&targetid=aud-994727060045%3Apla-411460338691&campaignid=1055581119&gclid=CjwKCAiAouD_BRBIEiwALhJH6D8kL3EXj7u44ZqF8clnO2sOm4Gy_tok48gRuFp2nhKbZd17rSE0ZRoCZGYQAvD_BwE&gclsrc=aw.ds) (also known as a stereo jack. A mono jack will **not** work for this purpose. Learned from experience)
* MIDI Jack
* Generic expression pedal with 1/4" output
* MIDI Cable 
* (Optional) 6x LEDs
* (Optional) 6x 220 ohm resistors

Plus, of course, all the usual suspects in Arduino projects. Power source, breadboard, hookup wire, soldering equipment, a drill, and an enclosure. I just used a spray painted cake pan and used a power drill to create holes which worked surprisingly well (most switches and jacks come with washers which allows them to easily be affixed to the drilled holes). As you can tell, I'm just using a MIDI cable. While MIDI-to-USB is convenient, this isn't possible on a stand-alone Arduino Uno, and it keeps things pretty simple. 

# Construction
*Please excuse this absolute mess of wires, I am no electrical engineer*

![Image](https://i.imgur.com/gC7Mecol.jpg)

The advantage of the 3PDT switches (more info [here](https://www.stewmac.com/video-and-ideas/online-resources/learn-about-guitar-pickups-and-electronics-and-wiring/3pdt-stomp-switch-instructions.html)) is that we can hookup the LEDs without communicating with the Arduino at all. On the left most pole of each switch (from top to bottom) is the power source, the digital input to the Arduino, and ground. In the middle pole, the power source is soldered to the top lug and the middle lug is soldered to the positive lead of the LED (which of course must be grounded through a resistor). 
As for the expression pedal jack, connect the tip to positive, the ring to an analog input (I used pin A0), and the sleeve to ground. 
![Image](https://www.circuitbasics.com/wp-content/uploads/2015/03/TRS-Pinout.png)

Lastly is the hooking up the MIDI jack. We only need 3 of the 5 pins in a MIDI jack. Be sure to take note of the slightly odd way the pins are numbered. Pin 5 goes to the Arduino's serial communication port (1), pin 4 goes to the power source, and pin 2 goes to ground. 

![Image](https://www.arduino.cc/en/uploads/Tutorial/MIDI_schem.png) 

It can get messy if you're not very good with your hands like me, but it's at least conceptually straightforward. Now onto the code...

# Coding

The MIDI messages we're sending are simple, so this was easily coded without importing any MIDI libraries. The baud rate is set to 31250, as this is the rate MIDI communicates over. Unfortunately, the serial monitor built into the Arduino IDE doesn't support this rate at the moment, so if you attempt to use the serial monitor, you're going to see some bizarre output. If you're having trouble and need to debug, change the Serial.begin(31250) to any supported baud rate (you will be unable to send MIDI messages properly, but you can monitor the input the Arduino is getting which is a good start). I'm sending Note On messages over channel 11. To change this, replace A in 0x9A (A is 11 in decimal notation) to your desired channel. CC messages are sent over CC1, which is defined by the MIDI standard as a Mod Wheel. This is typical for generic modulation that doesn't have a dedicated purpose, but if you're simultaneously using a controller with a mod wheel, these may conflict. If you desire, change CCnum to 0x0E (this CC number is undefined, as are many others. Find the assignments of all CC numbers [here](https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2)). The code loops every 10ms, so that's the frequency at which messages are sent, which could be changed but shouldn't be necessary. Button 5 also acts as on On/Off switch for the expression pedal. This is because the analog input ranges from 0-1023, which means that even the slightest movements (or no movement at all) will send a MIDI message. This noise can make it difficult to assign buttons in DAWs like Ableton (which asks you to push/move the desired button/mod wheel/etc. to assign MIDI, and if the expression pedal is constantly sending messages, this will interfere with your assignments). This button also sends a Note On message like all the others, so you can enable the expression pedal and the corresponding digital effect in one click. You can remove the "&& lastButton5State==1" from the code if you'd like the expression pedal to always be on. 

Feel free to reach out if you have any questions!

Nick Dombroski
nick.m.dombroski@gmail.com



# Demo
[![Click here to see a demo](https://img.youtube.com/vi/BqbcW5VHuI8/0.jpg)](https://www.youtube.com/watch?v=BqbcW5VHuI8)

[Check out my music here](https://www.youtube.com/channel/UCnHnk0IhTvzKCuTdqNcnDNg)
