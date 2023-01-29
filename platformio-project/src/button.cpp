#include <button.h>
#include <OneButton.h>
#include <EEPROMSetting.h>
#define HOLD_REPEAT_TIME 100

void button::yellow1ButtonLongPress() {
  minusHold = true;
}
void button::yellow2ButtonLongPress() {
  plusHold = true;
}
void button::yellow1ButtonLongStop() {
  minusHold = false;
}
void button::yellow2ButtonLongStop() {
  plusHold = false;
}

void button::greenButtonClick() {
  switch (getDisplayState())
  {
  case DisplayState::MainFrame:
    switch (getMainFrameSelector())
    {
    case MainFrameSelector::StartProgram:
      setDisplayState(DisplayState::SelectProgramFrame);
      break;
    
    case MainFrameSelector::Settings:
      setDisplayState(DisplayState::SettingFrame);
      break;
    }
    break;
  case DisplayState::SelectProgramFrame:
    switch (getProgramSelector())
    {
    case ProgramSelector::Cancel:
      setDisplayState(DisplayState::MainFrame);
      break;
      case ProgramSelector::Cure:
      setDisplayState(DisplayState::SelectCureSubprogramFrame);
      break;
      case ProgramSelector::Wash:
      setDisplayState(DisplayState::SelectWashingSubprogramFrame);
      break;
    }
    break;
  case DisplayState::RunProgramFrame:
    setDisplayState(DisplayState::MainFrame);
    setState(State::idle);
    break;
  case DisplayState::SelectCureSubprogramFrame:
    switch (getSubprogramSelector())
    {
    case SubprogramState::Cancel:
      setDisplayState(DisplayState::SelectProgramFrame);
      break;
    case SubprogramState::Infinity:
      setDisplayState(DisplayState::RunProgramFrame);
      startCure(getGlobalSettings().CureCycleTime, -1);
      break;
    case SubprogramState::Slot1:
      setDisplayState(DisplayState::RunProgramFrame);
      startCure(getGlobalSettings().CureCycleTime, getGlobalSettings().CureSlot1Time);
      break;
    case SubprogramState::Slot2:
      setDisplayState(DisplayState::RunProgramFrame);
      startCure(getGlobalSettings().CureCycleTime, getGlobalSettings().CureSlot2Time);
      break;
    case SubprogramState::Slot3:
      setDisplayState(DisplayState::RunProgramFrame);
      startCure(getGlobalSettings().CureCycleTime, getGlobalSettings().CureSlot3Time);
      break;
    case SubprogramState::Slot4:
      setDisplayState(DisplayState::RunProgramFrame);
      startCure(getGlobalSettings().CureCycleTime, getGlobalSettings().CureSlot4Time);
      break;
    }
    break;
  case DisplayState::SelectWashingSubprogramFrame:
    switch (getSubprogramSelector())
    {
    case SubprogramState::Cancel:
      setDisplayState(DisplayState::SelectProgramFrame);
      break;
    case SubprogramState::Infinity:
      setDisplayState(DisplayState::RunProgramFrame);
      startWashing(getGlobalSettings().WashingCycleTime, -1);
      break;
    case SubprogramState::Slot1:
      setDisplayState(DisplayState::RunProgramFrame);
      startWashing(getGlobalSettings().WashingCycleTime, getGlobalSettings().WashingSlot1Time);
      break;
    case SubprogramState::Slot2:
      setDisplayState(DisplayState::RunProgramFrame);
      startWashing(getGlobalSettings().WashingCycleTime, getGlobalSettings().WashingSlot2Time);
      break;
    case SubprogramState::Slot3:
      setDisplayState(DisplayState::RunProgramFrame);
      startWashing(getGlobalSettings().WashingCycleTime, getGlobalSettings().WashingSlot3Time);
      break;
    case SubprogramState::Slot4:
      setDisplayState(DisplayState::RunProgramFrame);
      startWashing(getGlobalSettings().WashingCycleTime, getGlobalSettings().WashingSlot4Time);
      break;
    }
    break;
  case DisplayState::SettingFrame:
    switch (getSettingState())
    {
    case SettingsState::Cancel:
      setDisplayState(DisplayState::MainFrame);
      break;
    default:
      setDisplayState(DisplayState::SettingPropertyChangeFrame);
      break;
    }
    break;
  case DisplayState::SettingPropertyChangeFrame:
    setDisplayState(DisplayState::SettingFrame);
    break;
  }
}

void button::yellow1ButtonClick() {
  EEPROMSetting currentSettings = getGlobalSettings();
  switch (getDisplayState())
  {
  case DisplayState::MainFrame:
    switch (getMainFrameSelector())
    {
    case MainFrameSelector::StartProgram:
      setMainFrame(MainFrameSelector::Settings);
      break;
    case MainFrameSelector::Settings:
      setMainFrame(MainFrameSelector::StartProgram);
      break;
    }
    break;
  case DisplayState::SelectProgramFrame:
    switch (getProgramSelector())
    {
    case ProgramSelector::Cancel:
      setProgramSelector(ProgramSelector::Cure);
      break;
    case ProgramSelector::Wash:
      setProgramSelector(ProgramSelector::Cancel);
      break;
    case ProgramSelector::Cure:
      setProgramSelector(ProgramSelector::Wash);
      break;
    }
    break;
  case DisplayState::SelectCureSubprogramFrame:
  case DisplayState::SelectWashingSubprogramFrame:
    switch (getSubprogramSelector())
    {
    case SubprogramState::Cancel:
      setSubprogramSelector(SubprogramState::Slot4);
      break;
    case SubprogramState::Infinity:
      setSubprogramSelector(SubprogramState::Cancel);
      break;
    case SubprogramState::Slot1:
      setSubprogramSelector(SubprogramState::Infinity);
      break;
    case SubprogramState::Slot2:
      setSubprogramSelector(SubprogramState::Slot1);
      break;
    case SubprogramState::Slot3:
      setSubprogramSelector(SubprogramState::Slot2);
      break;
    case SubprogramState::Slot4:
      setSubprogramSelector(SubprogramState::Slot3);
      break;
    }
    break;
  case DisplayState::SettingFrame:
    switch (getSettingState())
    {
    case SettingsState::Cancel:
      setSettingState(SettingsState::Acceleration);
      break;
    case SettingsState::WashingSpeed:
      setSettingState(SettingsState::Cancel);
      break;
    case SettingsState::CureSpeed:
      setSettingState(SettingsState::WashingSpeed);
      break;
    case SettingsState::WashingCycleTime:
      setSettingState(SettingsState::CureSpeed);
      break;
    case SettingsState::CureCycleTime:
      setSettingState(SettingsState::WashingCycleTime);
      break;
    case SettingsState::WashingSlot1Time:
      setSettingState(SettingsState::CureCycleTime);
      break;
    case SettingsState::WashingSlot2Time:
      setSettingState(SettingsState::WashingSlot1Time);
      break;
    case SettingsState::WashingSlot3Time:
      setSettingState(SettingsState::WashingSlot2Time);
      break;
    case SettingsState::WashingSlot4Time:
      setSettingState(SettingsState::WashingSlot3Time);
      break;
    case SettingsState::CureSlot1Time:
      setSettingState(SettingsState::WashingSlot4Time);
      break;
    case SettingsState::CureSlot2Time:
      setSettingState(SettingsState::CureSlot1Time);
      break;
    case SettingsState::CureSlot3Time:
      setSettingState(SettingsState::CureSlot2Time);
      break;
    case SettingsState::CureSlot4Time:
      setSettingState(SettingsState::CureSlot3Time);
      break;
    case SettingsState::Acceleration:
      setSettingState(SettingsState::CureSlot4Time);
      break;
    }
    break;
  case DisplayState::SettingPropertyChangeFrame:
    switch (getSettingState())
    {
    case SettingsState::CureCycleTime:
      if(currentSettings.CureCycleTime > 1000) {
        currentSettings.CureCycleTime-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot1Time:
      if(currentSettings.CureSlot1Time > 1000) {
        currentSettings.CureSlot1Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot2Time:
      if(currentSettings.CureSlot2Time > 1000) {
        currentSettings.CureSlot2Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot3Time:
      if(currentSettings.CureSlot3Time > 1000) {
        currentSettings.CureSlot3Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot4Time:
      if(currentSettings.CureSlot4Time > 1000) {
        currentSettings.CureSlot4Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSpeed:
      if(currentSettings.CureSpeed > 2) {
        currentSettings.CureSpeed--;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingCycleTime:
      if(currentSettings.WashingCycleTime > 1000) {
        currentSettings.WashingCycleTime-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot1Time:
      if(currentSettings.WashingSlot1Time > 1000) {
        currentSettings.WashingSlot1Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot2Time:
      if(currentSettings.WashingSlot2Time > 1000) {
        currentSettings.WashingSlot2Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot3Time:
      if(currentSettings.WashingSlot3Time > 1000) {
        currentSettings.WashingSlot3Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot4Time:
      if(currentSettings.WashingSlot4Time > 1000) {
        currentSettings.WashingSlot4Time-=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSpeed:
      if(currentSettings.WashingSpeed > 2) {
        currentSettings.WashingSpeed--;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::Acceleration:
      if(currentSettings.Acceleration > 2) {
        currentSettings.Acceleration--;
        setGlobalSettings(currentSettings);
      }
      break;
    }
    break;
  }
}

void button::yellow2ButtonClick() {
  EEPROMSetting currentSettings = getGlobalSettings();
  switch (getDisplayState())
  {
  case DisplayState::MainFrame:
    switch (getMainFrameSelector())
    {
    case MainFrameSelector::StartProgram:
      setMainFrame(MainFrameSelector::Settings);
      break;
    case MainFrameSelector::Settings:
      setMainFrame(MainFrameSelector::StartProgram);
      break;
    }
    break;
  case DisplayState::SelectProgramFrame:
    switch (getProgramSelector())
    {
    case ProgramSelector::Cancel:
      setProgramSelector(ProgramSelector::Wash);
      break;
    case ProgramSelector::Wash:
      setProgramSelector(ProgramSelector::Cure);
      break;
    case ProgramSelector::Cure:
      setProgramSelector(ProgramSelector::Cancel);
      break;
    }
    break;
  case DisplayState::SelectCureSubprogramFrame:
  case DisplayState::SelectWashingSubprogramFrame:
    switch (getSubprogramSelector())
    {
    case SubprogramState::Cancel:
      setSubprogramSelector(SubprogramState::Infinity);
      break;
    case SubprogramState::Infinity:
      setSubprogramSelector(SubprogramState::Slot1);
      break;
    case SubprogramState::Slot1:
      setSubprogramSelector(SubprogramState::Slot2);
      break;
    case SubprogramState::Slot2:
      setSubprogramSelector(SubprogramState::Slot3);
      break;
    case SubprogramState::Slot3:
      setSubprogramSelector(SubprogramState::Slot4);
      break;
    case SubprogramState::Slot4:
      setSubprogramSelector(SubprogramState::Cancel);
      break;
    }
    break;
  case DisplayState::SettingFrame:
    switch (getSettingState())
    {
    case SettingsState::Cancel:
      setSettingState(SettingsState::WashingSpeed);
      break;
    case SettingsState::WashingSpeed:
      setSettingState(SettingsState::CureSpeed);
      break;
    case SettingsState::CureSpeed:
      setSettingState(SettingsState::WashingCycleTime);
      break;
    case SettingsState::WashingCycleTime:
      setSettingState(SettingsState::CureCycleTime);
      break;
    case SettingsState::CureCycleTime:
      setSettingState(SettingsState::WashingSlot1Time);
      break;
    case SettingsState::WashingSlot1Time:
      setSettingState(SettingsState::WashingSlot2Time);
      break;
    case SettingsState::WashingSlot2Time:
      setSettingState(SettingsState::WashingSlot3Time);
      break;
    case SettingsState::WashingSlot3Time:
      setSettingState(SettingsState::WashingSlot4Time);
      break;
    case SettingsState::WashingSlot4Time:
      setSettingState(SettingsState::CureSlot1Time);
      break;
    case SettingsState::CureSlot1Time:
      setSettingState(SettingsState::CureSlot2Time);
      break;
    case SettingsState::CureSlot2Time:
      setSettingState(SettingsState::CureSlot3Time);
      break;
    case SettingsState::CureSlot3Time:
      setSettingState(SettingsState::CureSlot4Time);
      break;
    case SettingsState::CureSlot4Time:
      setSettingState(SettingsState::Acceleration);
      break;
    case SettingsState::Acceleration:
      setSettingState(SettingsState::Cancel);
      break;
    }
    break;
  case DisplayState::SettingPropertyChangeFrame:
    switch (getSettingState())
    {
    case SettingsState::CureCycleTime:
      if(currentSettings.CureCycleTime < 1000 * 60 * 10) {
        currentSettings.CureCycleTime+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot1Time:
      if(currentSettings.CureSlot1Time < 1000 * 60 * 60 * 4) {
        currentSettings.CureSlot1Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot2Time:
      if(currentSettings.CureSlot2Time < 1000 * 60 * 60 * 4) {
        currentSettings.CureSlot2Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot3Time:
      if(currentSettings.CureSlot3Time < 1000 * 60 * 60 * 4) {
        currentSettings.CureSlot3Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSlot4Time:
      if(currentSettings.CureSlot4Time < 1000 * 60 * 60 * 4) {
        currentSettings.CureSlot4Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::CureSpeed:
      if(currentSettings.CureSpeed < 20000) {
        currentSettings.CureSpeed++;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingCycleTime:
      if(currentSettings.WashingCycleTime < 1000 * 60 * 10) {
        currentSettings.WashingCycleTime+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot1Time:
      if(currentSettings.WashingSlot1Time < 1000 * 60 * 60 * 4) {
        currentSettings.WashingSlot1Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot2Time:
      if(currentSettings.WashingSlot2Time < 1000 * 60 * 60 * 4) {
        currentSettings.WashingSlot2Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot3Time:
      if(currentSettings.WashingSlot3Time < 1000 * 60 * 60 * 4) {
        currentSettings.WashingSlot3Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSlot4Time:
      if(currentSettings.WashingSlot4Time < 1000 * 60 * 60 * 4) {
        currentSettings.WashingSlot4Time+=1000;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::WashingSpeed:
      if(currentSettings.WashingSpeed < 20000) {
        currentSettings.WashingSpeed++;
        setGlobalSettings(currentSettings);
      }
      break;
    case SettingsState::Acceleration:
      if(currentSettings.Acceleration < 20000) {
        currentSettings.Acceleration++;
        setGlobalSettings(currentSettings);
      }
      break;
    }
    break;
  }
}

void button::redButtonClick() {

}

button::button(getGlobalStateFunction getglobalState, getDisplayStateFunction getdisplayState, getProgramSelectorFunction getprogramSelector, 
    getMainFrameSelectorFunction getmainFrameSelector, StartProgramFunction startcure, StartProgramFunction startwashing, SetDisplayStateFunction setdisplayState,
    SetStateFunction setstate, SetMainFrameFunction setmainFrame, SetProgramSelectorFunction setprogramSelector, getSubprogramSelectorFunction getsubprogramSelector,
    SetSubprogramSelectorFunction setsubprogramSelector, getSettingStateFunction getsettingState, SetSettingStateFunction setsettingState, getGlobalSettingsFunction getglobalSettings,
    SetGlobalSettingsFunction setglobalSettings) {
    greenButton = OneButton(GPIO_NUM_27);
    yellowButton1 = OneButton(GPIO_NUM_26);
    yellowButton2 = OneButton(GPIO_NUM_25);
    redButton = OneButton(GPIO_NUM_35);
    getGlobalState = getglobalState;
    getDisplayState = getdisplayState;
    getProgramSelector = getprogramSelector;
    getMainFrameSelector = getmainFrameSelector;
    startCure = startcure;
    startWashing = startwashing;
    setDisplayState = setdisplayState;
    setState = setstate;
    setMainFrame = setmainFrame;
    setProgramSelector = setprogramSelector;
    getSubprogramSelector = getsubprogramSelector;
    setSubprogramSelector = setsubprogramSelector; 
    getSettingState = getsettingState;
    setSettingState = setsettingState;
    getGlobalSettings = getglobalSettings;
    setGlobalSettings = setglobalSettings;
    minusHold = false;
    plusHold = false;
}
void button::setup() {
  greenButton.attachClick(greenButtonClick);
  yellowButton1.attachClick(yellow1ButtonClick);
  yellowButton1.attachLongPressStart(yellow1ButtonLongPress);
  yellowButton1.attachLongPressStop(yellow1ButtonLongStop);
  yellowButton2.attachClick(yellow2ButtonClick);
  yellowButton2.attachLongPressStart(yellow2ButtonLongPress);
  yellowButton2.attachLongPressStop(yellow2ButtonLongStop);
  redButton.attachClick(redButtonClick);
}
void button::loop() {
  greenButton.tick();
  yellowButton1.tick();
  yellowButton2.tick();
  redButton.tick();
  if (millis() - repeatTimer >= HOLD_REPEAT_TIME) { 
    repeatTimer = millis();
    if (minusHold) {
      yellow1ButtonClick();
    }
    if (plusHold) {
      yellow2ButtonClick();
    }
  }
}