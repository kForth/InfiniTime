#include "displayapp/screens/settings/SettingShorcutApp.h"
#include <lvgl/lvgl.h>
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Screen.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens;

constexpr const char* SettingShorcutApp::title;
constexpr const char* SettingShorcutApp::symbol;

auto SettingShorcutApp::CreateScreenList() const {
  std::array<std::function<std::unique_ptr<Screen>()>, nScreens> screens;
  for (size_t i = 0; i < screens.size(); i++) {
    screens[i] = [this, i]() -> std::unique_ptr<Screen> {
      return CreateScreen(i);
    };
  }
  return screens;
}

SettingShorcutApp::SettingShorcutApp(Pinetime::Applications::DisplayApp* app,
                                   Pinetime::Controllers::Settings& settingsController)
  : app {app},
    settingsController {settingsController},
    screens {app, 0, CreateScreenList(), Screens::ScreenListModes::UpDown} {
}

SettingShorcutApp::~SettingShorcutApp() {
  lv_obj_clean(lv_scr_act());
}

bool SettingShorcutApp::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}

std::unique_ptr<Screen> SettingShorcutApp::CreateScreen(unsigned int screenNum) const {
  std::array<Screens::CheckboxList::Item, itemsPerScreen> itemsOnThisScreen;
  for (int i = 0; i < itemsPerScreen; i++) {
    itemsOnThisScreen[i] = appList[screenNum * itemsPerScreen + i];
  }

  auto selectedApp = settingsController.GetShortcutApp();
  uint32_t selectedIndex = 0;
  for (int i = 0; i < nItems; i++) {
    if (apps[i] == selectedApp) {
      selectedIndex = i;
      break;
    }
  }

  return std::make_unique<Screens::CheckboxList>(
    screenNum,
    nScreens,
    title,
    symbol,
    selectedIndex,
    [&settings = settingsController, apps = apps](uint32_t index) {
      settings.SetShortcutApp(apps[index]);
      settings.SaveSettings();
    },
    itemsOnThisScreen);
}
