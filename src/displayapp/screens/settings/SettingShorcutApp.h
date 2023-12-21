#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "displayapp/screens/ScreenList.h"
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/CheckboxList.h"
#include "displayapp/Apps.h"
#include "displayapp/UserApps.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingShorcutApp : public Screen {
      public:
        SettingShorcutApp(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingShorcutApp() override;

        bool OnTouchEvent(TouchEvents event) override;

      private:
        DisplayApp* app;
        auto CreateAppList() const;
        auto CreateScreenList() const;
        std::unique_ptr<Screen> CreateScreen(unsigned int screenNum) const;

        Controllers::Settings& settingsController;

        static constexpr const char* title = "Shortcut";
        static constexpr const char* symbol = Symbols::stepForward;

        static constexpr int itemsPerScreen = 4;
        
        static constexpr int nItems = ((int)(Pinetime::Applications::UserAppTypes::Count / itemsPerScreen) + 1) * itemsPerScreen;

        static constexpr int nScreens = nItems / itemsPerScreen;

        std::array<CheckboxList::Item, nItems> appList;
        ScreenList<nScreens> screens;
      };
    }
  }
}
