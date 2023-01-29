
#include <OneButton.h>
#include <state.h>
#include <displayState.h>
#include <programSelector.h>
#include <mainFrameSelector.h>
#include <subprogramState.h>
#include <settingsState.h>
#include <EEPROMSetting.h>

extern "C" {
typedef State (*getGlobalStateFunction)(void);
typedef DisplayState (*getDisplayStateFunction)(void);
typedef ProgramSelector (*getProgramSelectorFunction)(void);
typedef MainFrameSelector (*getMainFrameSelectorFunction)(void);
typedef SubprogramState (*getSubprogramSelectorFunction)(void);
typedef SettingsState (*getSettingStateFunction)(void);
typedef EEPROMSetting (*getGlobalSettingsFunction)(void);
typedef uint32_t (*getProgramDurationTimerFunction)(void);
typedef void (*StartProgramFunction)(int cycleduration, int programduration);
typedef void (*SetDisplayStateFunction)(DisplayState);
typedef void (*SetStateFunction)(State);
typedef void (*SetMainFrameFunction)(MainFrameSelector);
typedef void (*SetProgramSelectorFunction)(ProgramSelector);
typedef void (*SetSubprogramSelectorFunction)(SubprogramState);
typedef void (*SetSettingStateFunction)(SettingsState);
typedef void (*SetGlobalSettingsFunction)(EEPROMSetting);
}

class button
{
private:
    OneButton greenButton;
    OneButton yellowButton1;
    OneButton yellowButton2;
    OneButton redButton;
    inline static bool minusHold;
    inline static bool plusHold;
    inline static uint32_t repeatTimer;
public:
    button(getGlobalStateFunction getglobalState, getDisplayStateFunction getdisplayState, getProgramSelectorFunction getprogramSelector, 
        getMainFrameSelectorFunction getmainFrameSelector, StartProgramFunction startcure, StartProgramFunction startwashing, SetDisplayStateFunction setdisplayState,
        SetStateFunction setstate, SetMainFrameFunction setmainFrame, SetProgramSelectorFunction setprogramSelector, getSubprogramSelectorFunction getsubprogramSelector,
        SetSubprogramSelectorFunction setsubprogramSelector, getSettingStateFunction getsettingState, SetSettingStateFunction setsettingState, getGlobalSettingsFunction getglobalSettings,
        SetGlobalSettingsFunction setglobalSettings);
    void setup();
    void loop();
    static void greenButtonClick();
    static void yellow1ButtonClick();
    static void yellow2ButtonClick();
    static void redButtonClick();
    static void yellow1ButtonLongPress();
    static void yellow2ButtonLongPress();
    static void yellow1ButtonLongStop();
    static void yellow2ButtonLongStop();
    inline static getGlobalStateFunction getGlobalState;
    inline static getDisplayStateFunction getDisplayState;
    inline static getProgramDurationTimerFunction getProgramDurationTimer;
    inline static getProgramSelectorFunction getProgramSelector;
    inline static getMainFrameSelectorFunction getMainFrameSelector;
    inline static getSubprogramSelectorFunction getSubprogramSelector;
    inline static getSettingStateFunction getSettingState;
    inline static getGlobalSettingsFunction getGlobalSettings;
    inline static StartProgramFunction startCure;
    inline static StartProgramFunction startWashing;
    inline static SetDisplayStateFunction setDisplayState;
    inline static SetStateFunction setState;
    inline static SetMainFrameFunction setMainFrame;
    inline static SetProgramSelectorFunction setProgramSelector;
    inline static SetSubprogramSelectorFunction setSubprogramSelector;
    inline static SetSettingStateFunction setSettingState;
    inline static SetGlobalSettingsFunction setGlobalSettings;
};