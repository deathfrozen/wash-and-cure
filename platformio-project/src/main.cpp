#include "FastAccelStepper.h"
#include <EEPROM.h>
#include <display.h>
#include <state.h>
#include <displayState.h>
#include <programSelector.h>
#include <mainFrameSelector.h>
#include <subprogramState.h>
#include <settingsState.h>
#include <button.h>
#include <EEPROMSetting.h>
#define stepPinStepper GPIO_NUM_13
#define dirPinStepper GPIO_NUM_12
#define enablePinStepper GPIO_NUM_14

#define settingsSaveTimeout 5000

EEPROMSetting globalSettings;
uint32_t saveGlobalSettingsTimer;

uint32_t washCycleTimer;
uint32_t programTimer;
int dir = 1;

uint32_t cycleDuration;
uint32_t programDuration;

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;
State mode = State::idle;
DisplayState displayState = DisplayState::MainFrame;
ProgramSelector programSelector = ProgramSelector::Cancel;
MainFrameSelector mainFrameSelector = MainFrameSelector::StartProgram;
SubprogramState subprogramState = SubprogramState::Cancel;
SettingsState settingState = SettingsState::Cancel;

hw_timer_t *My_timer = NULL;

State getState() {
  return mode;
}

DisplayState getDisplayState() {
  return displayState;
}

ProgramSelector getProgramSelector() {
  return programSelector;
}

MainFrameSelector getMainFrameSelector() {
  return mainFrameSelector;
}

SubprogramState getSubprogramState() {
  return subprogramState;
}

SettingsState getSettingState() {
  return settingState;
}

uint32_t getProgramTimer() {
  return programTimer;
}

EEPROMSetting getGlobalSettings() {
  return globalSettings;
}

uint32_t getProgramDuration() {
  return programDuration;
}

void setDisplayState(DisplayState state) {
  displayState = state;
}

void setState(State programState) {
  mode = programState;
}

void setMainFrame(MainFrameSelector selector) {
  mainFrameSelector = selector;
}

void setProgramSelector(ProgramSelector selector) {
  programSelector = selector;
}

void setSubprogramState(SubprogramState state) {
  subprogramState = state;
}

void setSettingState(SettingsState state) {
  settingState = state;
}

void setGlobalSettings(EEPROMSetting settings) {
  globalSettings = settings;
  saveGlobalSettingsTimer = millis();
}

display oled = display(getState, getDisplayState, getProgramTimer, getProgramSelector, getMainFrameSelector, getSubprogramState, getSettingState, getProgramDuration, 
  getGlobalSettings);


void startWashing(int cycleduration, int programduration) {
  cycleDuration = cycleduration;
  programDuration = programduration;
  mode = State::washing;
  washCycleTimer = millis();
  programTimer = millis();
  stepper->setSpeedInHz(globalSettings.WashingSpeed);
  stepper->setAcceleration(globalSettings.Acceleration);
  stepper->stopMove();
}

void startCure(int cycleduration, int programduration) {
  cycleDuration = cycleduration;
  programDuration = programduration;
  mode = State::cure;
  washCycleTimer = millis();
  programTimer = millis();
  stepper->setSpeedInHz(globalSettings.CureSpeed);
  stepper->setAcceleration(globalSettings.Acceleration);
  stepper->stopMove();
}

button buttons = button(getState, getDisplayState, getProgramSelector, getMainFrameSelector, startCure, startWashing, setDisplayState, setState, setMainFrame, setProgramSelector,
  getSubprogramState, setSubprogramState, getSettingState, setSettingState, getGlobalSettings, setGlobalSettings);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(sizeof(globalSettings));
  EEPROM.get(0, globalSettings);
  Serial.println(globalSettings.CureCycleTime);
  Serial.println(globalSettings.CureSlot1Time);
  Serial.println(globalSettings.CureSlot2Time);
  Serial.println(globalSettings.CureSlot3Time);
  Serial.println(globalSettings.CureSlot4Time);
  Serial.println(globalSettings.CureSpeed);
  Serial.println(globalSettings.WashingCycleTime);
  Serial.println(globalSettings.WashingSlot1Time);
  Serial.println(globalSettings.WashingSlot2Time);
  Serial.println(globalSettings.WashingSlot3Time);
  Serial.println(globalSettings.WashingSlot4Time);
  Serial.println(globalSettings.WashingSpeed);
  if(globalSettings.WashingSpeed == 0 || globalSettings.WashingSpeed == 4294967295) {
    Serial.println("restore default settings");
    EEPROMSetting initValues;
    globalSettings = initValues;
    EEPROM.put(0, globalSettings);
    EEPROM.commit();
  }
  oled.setup();
  oled.wifi_connected();
  buttons.setup();
  engine.init();
  stepper = engine.stepperConnectToPin(stepPinStepper);
   if (stepper) {
      stepper->setDirectionPin(dirPinStepper);
      stepper->setEnablePin(enablePinStepper);
      stepper->setAutoEnable(true);
   }
}

void washProgram () { 
  if (mode != State::idle && !stepper->isRunning()) {
    if(dir > 0) {
      stepper->runForward();
    } else {
      stepper->runBackward();
    }
    stepper->keepRunning();
  }
  if (millis() - washCycleTimer >= cycleDuration) { 
    washCycleTimer = millis();
    dir = dir * -1;
    Serial.print(dir);
    stepper->stopMove();
  }
  if(millis() - programTimer >= programDuration) {
    mode = State::idle;
    displayState = DisplayState::MainFrame;
  }
}

void loop() {
  if(millis() - saveGlobalSettingsTimer == settingsSaveTimeout) {
    EEPROM.put(0, globalSettings);
    EEPROM.commit();
  }
  switch (mode)
  {
  case State::idle:
    stepper->stopMove();
    break;
  case State::washing:
    washProgram();
    break;
  case State::cure:
    washProgram();
    break;
  }
  buttons.loop();
  oled.loop();
}