
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <display.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define FRAME_PERIOD 333

const unsigned char washerIcon[] PROGMEM = {
  0x3f, 0xff, 0xc0, 0x6d, 0x9f, 0x60, 0x5f, 0x99, 0x20, 0x4d, 0x9f, 0x20, 0x7f, 0xff, 0xe0, 0x7f, 
  0xff, 0xe0, 0x41, 0xf8, 0x20, 0x41, 0xfc, 0x20, 0x47, 0x9e, 0x20, 0x47, 0x0e, 0x20, 0x4e, 0x07, 
  0x20, 0x4f, 0xff, 0x20, 0x4e, 0x07, 0x20, 0x47, 0x0e, 0x20, 0x47, 0xfe, 0x20, 0x43, 0xfc, 0x20, 
  0x40, 0xf0, 0x20, 0x7f, 0xff, 0xe0, 0x60, 0x00, 0x60, 0x3f, 0xff, 0xc0
};

const unsigned char cureIcon[] PROGMEM = {
  0x00, 0x60, 0x00, 0x04, 0x62, 0x00, 0x07, 0xff, 0x00, 0x07, 0x0f, 0x00, 0x3c, 0x03, 0x00, 0x78, 
  0x01, 0xe0, 0x30, 0x00, 0xc0, 0x34, 0x92, 0xc0, 0x26, 0xb6, 0x40, 0xe6, 0xb6, 0x70, 0xe6, 0xb6, 
  0x70, 0x27, 0x9e, 0x00, 0x37, 0x9c, 0x00, 0x30, 0x00, 0x80, 0x78, 0x01, 0xe0, 0x0c, 0x03, 0xc0, 
  0x0f, 0x0e, 0x00, 0x0f, 0xfe, 0x00, 0x04, 0x62, 0x00, 0x00, 0x60, 0x00
};

display::display(getGlobalStateFunction getglobalState, getDisplayStateFunction getdisplayState, getProgramDurationTimerFunction getprogramDurationTimer, 
  getProgramSelectorFunction getprogramSelector, getMainFrameSelectorFunction getmainFrameSelector, getSubprogramSelectorFunction getsubprogramSelector,
  getSettingStateFunction getsettingState, getProgramDurationSettingFunction getprogramDurationSetting, getGlobalSettingsFunction getglobalSettings)
{
    oledDisplay = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    getGlobalState = getglobalState;
    getDisplayState = getdisplayState;
    getProgramDurationTimer = getprogramDurationTimer;
    getProgramSelector = getprogramSelector;
    getMainFrameSelector = getmainFrameSelector;
    getSubprogramSelector = getsubprogramSelector;
    getSettingState = getsettingState;
    getProgramDurationSetting = getprogramDurationSetting;
    getGlobalSettings = getglobalSettings;
}

void display::printEstimateTime() {
  if(getProgramDurationSetting() == -1) {
    oledDisplay.print("infinity");
    return;
  }
  if((((getProgramDurationSetting() - (millis() - getProgramDurationTimer())) / 1000)/60 )/ 60 > 1) {
    oledDisplay.printf("%.2d", (((getProgramDurationSetting() - (millis() - getProgramDurationTimer())) / 1000)/60)/60);
    oledDisplay.print(":");
    oledDisplay.printf("%.2d", (((getProgramDurationSetting() - (millis() - getProgramDurationTimer()))/1000)/60)%60);
    oledDisplay.print(":");  
  } else {
    oledDisplay.printf("%.2d", ((getProgramDurationSetting() - (millis() - getProgramDurationTimer()))/1000)/60);
    oledDisplay.print(":");      
  }
  oledDisplay.printf("%.2d", ((getProgramDurationSetting() - (millis() - getProgramDurationTimer()))/1000)%60);
}

String display::getTimeString(unsigned int ms) {
  String result = "";
  if(((ms / 1000) / 60) / 60 > 1) {
    result += ((ms / 1000) / 60) / 60;
    result += ":";
    result += ((ms / 1000) / 60) % 60;
    result += ":";
  } else {
    result += (ms / 1000) / 60;
    result += ":";
  }
  result += (ms / 1000) % 60;
  return result;
}

void display::mainFrame() {
  oledDisplay.setCursor(0,16);
  switch (getMainFrameSelector())
  {
  case MainFrameSelector::StartProgram:
    oledDisplay.println(" Settings");
    oledDisplay.println(">Start program");
    break;
  case MainFrameSelector::Settings:
    oledDisplay.println(" Start program");
    oledDisplay.println(">Settings");
    break;
  }
}

void display::runProgramFrame() {
  oledDisplay.setCursor(0,0);
  switch (getGlobalState())
  {
  case State::washing:
    oledDisplay.println("Washing");
    oledDisplay.drawBitmap(0, 30, washerIcon, 20, 20, WHITE);
    oledDisplay.setCursor(30,30);
    printEstimateTime();
    break;
  case State::cure:
    oledDisplay.println("Cure");
    oledDisplay.drawBitmap(0, 30, cureIcon, 20, 20, WHITE);
    oledDisplay.setCursor(30,30);
    printEstimateTime();
    break;
  }
}

void display::selectProgramFrame() {
  oledDisplay.setCursor(0,16);
  switch (getProgramSelector())
  {
  case ProgramSelector::Cancel:
    oledDisplay.println(" Cure");
    oledDisplay.println(">Cancel");
    oledDisplay.println(" Wash");
    break;
  case ProgramSelector::Wash:
    oledDisplay.println(" Cancel");
    oledDisplay.println(">Wash");
    oledDisplay.println(" Cure");
    break;
  case ProgramSelector::Cure:
    oledDisplay.println(" Wash");
    oledDisplay.println(">Cure");
    oledDisplay.println(" Cancel");
    break;
  }
}

void display::selectSubprogramFrame() {
  oledDisplay.setCursor(0,16);
  switch (getSubprogramSelector())
  {
  case SubprogramState::Cancel:
    oledDisplay.println(" Slot 3");
    oledDisplay.println(" Slot 4");
    oledDisplay.println(">Cancel");
    oledDisplay.println(" Infinity");
    oledDisplay.println(" Slot 1");
    oledDisplay.println(" Slot 2");
    break;
  case SubprogramState::Infinity:
    oledDisplay.println(" Slot 4");
    oledDisplay.println(" Cancel");
    oledDisplay.println(">Infinity");
    oledDisplay.println(" Slot 1");
    oledDisplay.println(" Slot 2");
    oledDisplay.println(" Slot 3");
    break;
  case SubprogramState::Slot1:
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Infinity");
    oledDisplay.println(">Slot 1");
    oledDisplay.println(" Slot 2");
    oledDisplay.println(" Slot 3");
    oledDisplay.println(" Slot 4");
    break;
  case SubprogramState::Slot2:
    oledDisplay.println(" Infinity");
    oledDisplay.println(" Slot 1");
    oledDisplay.println(">Slot 2");
    oledDisplay.println(" Slot 3");
    oledDisplay.println(" Slot 4");
    oledDisplay.println(" Cancel");
    break;
  case SubprogramState::Slot3:
    oledDisplay.println(" Slot 1");
    oledDisplay.println(" Slot 2");
    oledDisplay.println(">Slot 3");
    oledDisplay.println(" Slot 4");
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Infinity");
    break;
  case SubprogramState::Slot4:
    oledDisplay.println(" Slot 2");
    oledDisplay.println(" Slot 3");
    oledDisplay.println(">Slot 4");
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Infinity");
    oledDisplay.println(" Slot 1");
    break;
  }
}

void display::settingFrame() {
  oledDisplay.setCursor(0,16);
  switch (getSettingState())
  {
  case SettingsState::Cancel:
    oledDisplay.println(" Cure Slot4 time");
    oledDisplay.println(" Acceleration");
    oledDisplay.println(">Cancel");
    oledDisplay.println(" Wash speed");
    oledDisplay.println(" Cure speed");
    oledDisplay.println(" Wash cycle time");
    break;
  case SettingsState::WashingSpeed:
    oledDisplay.println(" Acceleration"); 
    oledDisplay.println(" Cancel");
    oledDisplay.println(">Wash speed");
    oledDisplay.println(" Cure speed");
    oledDisplay.println(" Wash cycle time");
    oledDisplay.println(" Cure cycle time");
    break;
  case SettingsState::CureSpeed:   
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Wash speed");
    oledDisplay.println(">Cure speed");
    oledDisplay.println(" Wash cycle time");
    oledDisplay.println(" Cure cycle time");
    oledDisplay.println(" Wash Slot1 time");
    break;
  case SettingsState::WashingCycleTime:
    oledDisplay.println(" Wash speed");
    oledDisplay.println(" Cure speed");
    oledDisplay.println(">Wash cycle time");
    oledDisplay.println(" Cure cycle time");
    oledDisplay.println(" Wash Slot1 time");
    oledDisplay.println(" Wash Slot2 time");
    break;
  case SettingsState::CureCycleTime:
    oledDisplay.println(" Cure speed");
    oledDisplay.println(" Wash cycle time");
    oledDisplay.println(">Cure cycle time");
    oledDisplay.println(" Wash Slot1 time");
    oledDisplay.println(" Wash Slot2 time");
    oledDisplay.println(" Wash Slot3 time");
    break;
  case SettingsState::WashingSlot1Time:
    oledDisplay.println(" Wash cycle time");
    oledDisplay.println(" Cure cycle time");
    oledDisplay.println(">Wash Slot1 time");
    oledDisplay.println(" Wash Slot2 time");
    oledDisplay.println(" Wash Slot3 time");
    oledDisplay.println(" Wash Slot4 time");
    break;
  case SettingsState::WashingSlot2Time:
    oledDisplay.println(" Cure cycle time");
    oledDisplay.println(" Wash Slot1 time");
    oledDisplay.println(">Wash Slot2 time");
    oledDisplay.println(" Wash Slot3 time");
    oledDisplay.println(" Wash Slot4 time");
    oledDisplay.println(" Cure Slot1 time");
    break;
  case SettingsState::WashingSlot3Time:
    oledDisplay.println(" Wash Slot1 time");
    oledDisplay.println(" Wash Slot2 time");
    oledDisplay.println(">Wash Slot3 time");
    oledDisplay.println(" Wash Slot4 time");
    oledDisplay.println(" Cure Slot1 time");
    oledDisplay.println(" Cure Slot2 time");
    break;
  case SettingsState::WashingSlot4Time:
    oledDisplay.println(" Wash Slot2 time");
    oledDisplay.println(" Wash Slot3 time");
    oledDisplay.println(">Wash Slot4 time");
    oledDisplay.println(" Cure Slot1 time");
    oledDisplay.println(" Cure Slot2 time");
    oledDisplay.println(" Cure Slot3 time");
    break;
  case SettingsState::CureSlot1Time:
    oledDisplay.println(" Wash Slot3 time");
    oledDisplay.println(" Wash Slot4 time");
    oledDisplay.println(">Cure Slot1 time");
    oledDisplay.println(" Cure Slot2 time");
    oledDisplay.println(" Cure Slot3 time");
    oledDisplay.println(" Cure Slot4 time");
    break;
  case SettingsState::CureSlot2Time:
    oledDisplay.println(" Wash Slot4 time");
    oledDisplay.println(" Cure Slot1 time");
    oledDisplay.println(">Cure Slot2 time");
    oledDisplay.println(" Cure Slot3 time");
    oledDisplay.println(" Cure Slot4 time");  
    oledDisplay.println(" Acceleration");
    break;
  case SettingsState::CureSlot3Time:
    oledDisplay.println(" Cure Slot1 time");
    oledDisplay.println(" Cure Slot2 time");
    oledDisplay.println(">Cure Slot3 time");
    oledDisplay.println(" Cure Slot4 time");   
    oledDisplay.println(" Acceleration"); 
    oledDisplay.println(" Cancel");
    break;
  case SettingsState::CureSlot4Time:
    oledDisplay.println(" Cure Slot2 time");
    oledDisplay.println(" Cure Slot3 time");
    oledDisplay.println(">Cure Slot4 time");
    oledDisplay.println(" Acceleration");
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Wash speed");
    break;
  case SettingsState::Acceleration:
    oledDisplay.println(" Cure Slot3 time");
    oledDisplay.println(" Cure Slot4 time");
    oledDisplay.println(">Acceleration");
    oledDisplay.println(" Cancel");
    oledDisplay.println(" Wash speed");
    oledDisplay.println(" Cure speed");
    break;
  }
}

void display::changeSettingPropFrame() {
  oledDisplay.setCursor(0,16);
  EEPROMSetting currentSettings = getGlobalSettings();
  String PropName;
  String PropValue;
  switch (getSettingState())
  {
  case SettingsState::WashingSpeed:
    PropName = "Washing speed";
    PropValue = currentSettings.WashingSpeed;
    break;
  case SettingsState::CureSpeed:
    PropName = "Cure speed";
    PropValue = currentSettings.CureSpeed;
    break;
  case SettingsState::WashingCycleTime:
    PropName = "Washing cycle time";
    PropValue = getTimeString(currentSettings.WashingCycleTime);
    break;
  case SettingsState::CureCycleTime:
    PropName = "Cyre cycle time";
    PropValue = getTimeString(currentSettings.CureCycleTime);
    break;
  case SettingsState::WashingSlot1Time:
    PropName = "Washing Slot1 time";
    PropValue = getTimeString(currentSettings.WashingSlot1Time);
    break;
  case SettingsState::WashingSlot2Time:
    PropName = "Washing Slot2 time";
    PropValue = getTimeString(currentSettings.WashingSlot2Time);
    break;
  case SettingsState::WashingSlot3Time:
    PropName = "Washing Slot3 time";
    PropValue = getTimeString(currentSettings.WashingSlot3Time);
    break;
  case SettingsState::WashingSlot4Time:
    PropName = "Washing Slot4 time";
    PropValue = getTimeString(currentSettings.WashingSlot4Time);
    break;
  case SettingsState::CureSlot1Time:
    PropName = "Cure Slot1 time";
    PropValue = getTimeString(currentSettings.CureSlot1Time);
    break;
  case SettingsState::CureSlot2Time:
    PropName = "Cure Slot2 time";
    PropValue = getTimeString(currentSettings.CureSlot2Time);
    break;
  case SettingsState::CureSlot3Time:
    PropName = "Cure Slot3 time";
    PropValue = getTimeString(currentSettings.CureSlot3Time);
    break;
  case SettingsState::CureSlot4Time:
    PropName = "Cure Slot4 time";
    PropValue = getTimeString(currentSettings.CureSlot4Time);
    break;
  case SettingsState::Acceleration:
    PropName = "Acceleration";
    PropValue = currentSettings.Acceleration;
    break;
  }
  oledDisplay.println(PropName);
  oledDisplay.println(PropValue);
}

void display::setup() {
  Wire.begin(GPIO_NUM_33, GPIO_NUM_32);
  oledDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  oledDisplay.display();
}

void display::wifi_connected() {
  oledDisplay.clearDisplay();
  oledDisplay.display();
}
void display::showFrame(){
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(1);
  oledDisplay.setTextColor(WHITE);
  switch (getDisplayState())
  {
  case DisplayState::MainFrame:
    mainFrame();
    break;
  case DisplayState::SelectProgramFrame:
    selectProgramFrame();
    break;
  case DisplayState::SettingFrame:
    settingFrame();
    break;
  case DisplayState::RunProgramFrame:
    runProgramFrame();
    break;
  case DisplayState::SelectCureSubprogramFrame:
  case DisplayState::SelectWashingSubprogramFrame:
    selectSubprogramFrame();
    break;
  case DisplayState::SettingPropertyChangeFrame:
    changeSettingPropFrame();
    break;
  }
  oledDisplay.display();
}
void display::slow_time() {
  showFrame();
}

void display::loop() {
  if(millis() - frameTimer >= FRAME_PERIOD) {
    frameTimer = millis();
    showFrame();
  }
}