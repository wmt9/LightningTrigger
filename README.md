# LightningTrigger


This is a simple arduino program that takes a reading from a Cadmium Selenide Light Detecting Resistor or LDR and triggers an opto isolator to trigger a camera connected to the optoisolator
3 potentiometers adjust the sensitivity, delay from detecting the lightning to opening shutter, and delay to when the shutter is then closed again. 

If the values of the time delays are changed on the pot, the new value is displayed on the tm1638 board, also if the light value detected is less than the amount required to trigger that value is displayed instead.




todo, try and find a way to display both delays on same line ( this should be easy)
      fine tune the "touchiness" of the pots (something like a debounce)
      display the light value and the sensivity value side by side when the value is not high enough to trigger the camera, allowing on to fine tune the sensitivity on the fly.
