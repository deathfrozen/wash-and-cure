
#include <Adafruit_SSD1306.h>
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
typedef uint32_t (*getProgramDurationSettingFunction)(void);
}

class display
{
private:
    Adafruit_SSD1306 oledDisplay;
    uint32_t frameTimer;
    getGlobalStateFunction getGlobalState;
    getDisplayStateFunction getDisplayState;
    getProgramDurationTimerFunction getProgramDurationTimer;
    getProgramSelectorFunction getProgramSelector;
    getMainFrameSelectorFunction getMainFrameSelector;
    getSubprogramSelectorFunction getSubprogramSelector;
    getSettingStateFunction getSettingState;
    getProgramDurationSettingFunction getProgramDurationSetting;
    getGlobalSettingsFunction getGlobalSettings;
    void showFrame();
    void mainFrame();
    void settingFrame();
    void selectProgramFrame();
    void runProgramFrame();
    void selectSubprogramFrame();
    void changeSettingPropFrame();
    void printEstimateTime();
    String getTimeString(unsigned int ms);
public:
    display(getGlobalStateFunction getglobalState, getDisplayStateFunction getdisplayState, getProgramDurationTimerFunction getprogramDurationTimer, 
        getProgramSelectorFunction getprogramSelector, getMainFrameSelectorFunction getmainFrameSelector, getSubprogramSelectorFunction getsubprogramSelector,
        getSettingStateFunction getsettingState, getProgramDurationSettingFunction getprogramDurationSetting, getGlobalSettingsFunction getglobalSettings);
    void setup();
    void loop();
    void slow_time();
    void wifi_connected();
};