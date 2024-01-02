#include "SettingShortcutApp.h"
#include <lvgl/lvgl.h>
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Screen.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens;

constexpr const char* SettingShortcutApp::title;
constexpr const char* SettingShortcutApp::symbol;

auto SettingShortcutApp::CreateAppList() const {
  std::array<CheckboxList::Item, nItems> items;
  items[0] = {"None", true};
  int i = 1;
  for(auto& app : Pinetime::Applications::userApps) {
    items[i++] = {app.name, true};
  }
  while(i < nItems) {
    items[i++] = {"", false};
  }
  return items;
}

auto SettingShortcutApp::CreateScreenList() const {
  std::array<std::function<std::unique_ptr<Screen>()>, nScreens> screens;
  for (size_t i = 0; i < screens.size(); i++) {
    screens[i] = [this, i]() -> std::unique_ptr<Screen> {
      return CreateScreen(i);
    };
  }
  return screens;
}

SettingShortcutApp::SettingShortcutApp(Pinetime::Applications::DisplayApp* app,
                                   Pinetime::Controllers::Settings& settingsController)
  : app {app},
    settingsController {settingsController},
    appList {CreateAppList()},
    screens {app, 0, CreateScreenList(), Screens::ScreenListModes::UpDown} {
}

SettingShortcutApp::~SettingShortcutApp() {
  lv_obj_clean(lv_scr_act());
}

bool SettingShortcutApp::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}

std::unique_ptr<Screen> SettingShortcutApp::CreateScreen(unsigned int screenNum) const {
  std::array<Screens::CheckboxList::Item, itemsPerScreen> itemsOnThisScreen;
  for (int i = 0; i < itemsPerScreen; i++) {
    itemsOnThisScreen[i] = appList[screenNum * itemsPerScreen + i];
  }

  auto selectedApp = settingsController.GetShortcutApp();
  uint32_t selectedIndex = 0;
  for (size_t i = 0; i < UserAppTypes::Count; i++) {
    if (Pinetime::Applications::userApps[i].app == selectedApp) {
      selectedIndex = i + 1;
      break;
    }
  }

  return std::make_unique<Screens::CheckboxList>(
    screenNum,
    nScreens,
    title,
    symbol,
    selectedIndex,
    [&settings = settingsController](uint32_t index) {
      settings.SetShortcutApp(Pinetime::Applications::userApps[index-1].app);
      settings.SaveSettings();
    },
    itemsOnThisScreen);
}
