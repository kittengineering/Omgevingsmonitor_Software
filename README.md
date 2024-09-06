# Gadget Firmware
## 🛠️ Project status
**Still in development.**

Check ✅[Roadmap](#roadmap) for progress.

## 📇 Name
Beurs Gadget WoTS / MJSGadget environment monitor

## ❓ Description
This project is using the MJS PCB in combination with the added environment measurement PCB. 

The final product will include these functions:

**Environment monitoring**
- Microphone measurements.
- Humidity temperature measurements.
- VOC measurements.
- PM, NOx, VOC, RH & T measurements (Optional sensor upgrade).

**Communication**
- WiFi communication
- Sending the sensor and gps data to the sensor community server.
- Webpage to set parameters.
- Low power capabilities.

**Other**
- LED indication for Status, dB and VOC.

## ⚙️ Installation
Make sure you have the following installed:
- GDB server
- STM32CubeIDE
- STM32CuberMonitor-Power -> For debugging purposes.

- Generate code via .ioc file.
- Go to run -> Debug Configurations -> MJSGadget Debug -> Debugger -> Scan your ST-link serial number

Make sure the library paths link to your repository files.

In STM32CubeIDE change the paths under:
- Project -> Properties -> C/C++ General -> Paths and Symbols
- Repository default installation location: C:Users/YOURUSERNAME/STM32Cube/Repository.

## 📗 Usage
~~Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.~~

## ✅ Roadmap 
- [x] **Utilities**
  - [x] Add a logger function for debugging.
  - [x] Non blocking timer function.
- [ ] **Measurements**
  - [x] Callbacks to I2C, I2S and UART handlers.
  - [x] State machine to handle measurements logic.
    - [x] Ability to turn off / on measurements.
    - [ ] Check humidity is above a certain % and turn heater on if necessary.
    - [ ] De-init sensors function.
  - [ ] Microphone
    - [x] I2S Low level driver with DMA functionality.
    - [x] Init function.
    - [x] Ability to start a measurement with sample rate / amount of samples.
    - [x] Fix bug for flipping bits in I2S signal. 
    - [x] FFT conversion (use CMSIS libraries?)
    - [x] Measurement done function callback.
    - [ ] Returning sensor status (BUSY, IDLE, WAIT, FINISHED, ERROR)
  - [ ] Humidity / Temperature
    - [x] I2C Low level driver with DMA functionality.
    - [x] Init function.
    - [x] Start measurement function.
    - [ ] Measurement done function.
      - [x] Calculate the CRC to verify data integrity.
      - [x] Returning humidity and temperature values function (non-blocking).
      - [ ] Returning sensor status (BUSY, IDLE, WAIT, FINISHED, ERROR).
  - [ ] VOC
    - [x] Init function.
      - [x] Read serial to see if device is connected.
    - [x] Start measurement function.
      - [x] Wait for the heat-up to be done (non-blocking).
    - [x] Measurement done function.
      - [x] Calculate the CRC to verify data integrity.
      - [x] Calculate the VOC index using the provided sensor algorithm. 
      - [x] Use the humidity and temperature values from the humidity 
      temperature sensor to calculate the VOC index.
      - [x] Returning the VOC index (non-blocking).
      - [x] Wait for the measurement interval before starting another 
      - [ ] Returning sensor status (BUSY, IDLE, WAIT, FINISHED, ERROR).
  - [ ] Sensirion SEN5
    - [ ] I2C Low level driver.
    - [ ] Init function.
    - [ ] Start measurement function.
    - [ ] Measurement done function.
      - [ ] Calculate the CRC to verify data integrity.
      - [ ] Returning the PM, NOx, VOC, RH & T values (non-blocking).
      - [ ] Returning sensor status (BUSY, IDLE, WAIT, FINISHED, ERROR)
  - [ ] Re-init sensors function.
- [ ] **ESP32**
  - [ ] UART bridge mode for programming ESP
  - [x] Ability to turn on ESP32 using a GPIO.
  - [ ] UART Low level driver with DMA functionality.
  - [ ] Sending / receiving AT commands.
    - [ ] WiFi Access Point mode
    - [ ] Turn-off ESP
  - [ ] Settable sleep mode.
  - [ ] Read back from NTP server.
    - [ ] Parse reply to configure the RTC with correct date and time.
  - [ ] Sensor community interface.
    - [ ] Web page interface to set parameters. 
    - [ ] Web page interface to save parameters to EEPROM.
    - [ ] Parsed JSON file for sensor community.
  - [ ] Check for WiFi availability.  
- [ ] **Sleep mode**
  - [ ] Settable sleep interval parameter
  - [ ] Switching between clock frequencies.
  - [ ] Aware of idle time.
    - [ ] Utilising idle time.
- [ ] **EEPROM**
  - [ ] Low level driver to read / write / update the EEPROM values.
  - [ ] Default EEPROM values handler.
  - [ ] Settable EEPROM values handler.
- [ ] **Power Mode**
  - [ ] Check for grid power or battery power.
  - [ ] Set enabled sensors depening on power mode.
  - [ ] Set sleep interval depending on power mode.
  - [ ] Set measurement duration depending on power mode.
- [ ] **User Button**
  - [ ] User button pressed -> go to WiFi Access Point mode ESP.
- [ ] **LED indication**
  - [ ] LED indicator for the status
  - [ ] LED indicator for the dB (7 colours)
  - [ ] LED indicator for the temperature

- [ ]!IMPORTANT Turn RX and TX swapping off for final gadget.


## 🫂 Collaborate with your team
- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Set auto-merge](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## 🧪 Test and Deploy
Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing (SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

## 🤝 Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## ☎️ Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## ✍️ Authors and acknowledgment
Joris Blankestijn

## 🧾 License
[MIT](https://opensource.org/license/mit)
