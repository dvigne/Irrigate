<p align="center"><img src="https://raw.githubusercontent.com/dvigne/Irrigate/master/media/irrigate.io_color.png" width=350></p>

# Irrigate
Opensource Irrigaton Controller and Software

### About
Irrigate is a project that consists of two parts. The hardware based valve controller and the microcode software that was primarily written for the NodeMCU ESP8266 microcontroller platform.

It was built and designed to operate up to 4 distinct zones and provide an easy to use web interface for controlling it. Through the web interface you can change and set the time, change or add times when each zone activates, manually activate a given zone, and modify global system settings.

### Setup and Installation
Requirements:
 - NodeJS
 - Python3
 - Virtualenv (optional)

This project designed around the Platformio framework. To get started you must first install `virtualenv` or install the requirements straight to your computer.

*Optional*:
```
sudo apt install virtualenv
virtualenv -p python3 env
```

Install the necessary requirements to compile and upload this project to the ESP8266

```
pip install -r requirements.txt
```

Next install the NPM modules required to compile the front-end assets

```
npm install
```

Then build, compile, and upload to the ESP8266

```
npm run prod && pio run -t uploadfs && pio run -t upload
```

After that, the blue light on the front of your ESP8266 should turn on once the system is ready and there should be a WiFi Network named `Irrigate` with no password that you can connect to. Once connected you can navigate to http://irrigate.io or http://192.168.4.1 to view the web interface.

All of the settings mentioned above are configurable in the `include.configuration.h` file along with many more settings. Don't forget to build, compile, and upload again once you've changed the settings to your satisfaction

### Contributers
- Derick Vigne
  - PCB Design and Software Design
- Christopher Medrano
  - Software Design and Hardware Design
- Selina Bostic
  - Logos and Digital Design
