#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "displayapp/screens/ScreenList.h"
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/CheckboxList.h"

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
        auto CreateScreenList() const;
        std::unique_ptr<Screen> CreateScreen(unsigned int screenNum) const;

        Controllers::Settings& settingsController;

        static constexpr const char* title = "Shortcut";
        static constexpr const char* symbol = Symbols::stepForward;

        static constexpr int itemsPerScreen = 4;

        // Increment this when more space is needed
        static constexpr int nScreens = 3;
        
        static constexpr int nItems = itemsPerScreen * itemsPerScreen;

        // Order of apps must match page order below
        std::array<Pinetime::Applications::Apps, nItems> apps {
            Apps::None,
            Apps::StopWatch,
            Apps::Alarm,
            Apps::Timer,

            Apps::Steps,
            Apps::HeartRate,
            Apps::Music,
            Apps::Paint,

            Apps::Paddle,
            Apps::Twos,
            Apps::Metronome,
            Apps::Navigation

            // Apps::Weather,
            // Apps::Motion,
            // Apps::QuickSettings,
            // Apps::None
        };

        // Order of apps must match list above
        std::array<Screens::CheckboxList::Item, nItems> appList {
          {
            {"None", true},
            {"StopWatch", true},
            {"Alarm", true},
            {"Timer", true},

            {"Steps", true},
            {"HeartRate", true},
            {"Music", true},
            {"Paint", true},

            {"Paddle", true},
            {"Twos", true},
            {"Metronome", true},
            {"Navigation", true}

            // {"Weather", true},
            // {"Motion", true},
            // {"QuickSettings", true},
            // {"", false}
            }
        };
        ScreenList<nScreens> screens;
      };
    }
  }
}
