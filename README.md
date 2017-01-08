# led_strip
Library for controlling LED strips that use the APA102 5050 RGB LED.

So far the following backends are complete:
* Linux SPI
  * To build, run make in the base directory
* Arduino SPI
  * To install as a library, run the createArduinoLibrary.sh script in arduino folder. This will create a LedStrip.zip file which can be imported via the Arduino GUI under Sketch->Include Library->Add .ZIP Library. You can then find examples under File->Examples->LedStrip.


TODO:
* Migrate to CMake with build options for each backend
* Create Linux bit-bang backend
* Organize files into folders
