#pragma once
#include "Apps.h"
#include "Controllers.h"

#include "displayapp/screens/Tile.h"
#include "displayapp/screens/ApplicationList.h"
#include "displayapp/screens/Clock.h"
#include "displayapp/screens/StopWatch.h"
#include "displayapp/screens/Alarm.h"
#include "displayapp/screens/Timer.h"
#include "displayapp/screens/Steps.h"
#include "displayapp/screens/HeartRate.h"
#include "displayapp/screens/Music.h"
#include "displayapp/screens/InfiniPaint.h"
#include "displayapp/screens/Paddle.h"
#include "displayapp/screens/Twos.h"
#include "displayapp/screens/Metronome.h"
#include "displayapp/screens/Navigation.h"
// #include "displayapp/screens/Weather.h"
// #include "displayapp/screens/Motion.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class Screen;
    }

    struct AppDescription {
      Apps app;
      const char* icon;
      const char* name;
      Screens::Screen* (*create)(AppControllers& controllers);
    };

    template <Apps t>
    consteval AppDescription CreateAppDescription() {
      return {AppTraits<t>::app, AppTraits<t>::icon, AppTraits<t>::name, &AppTraits<t>::Create};
    }

    template <template <Apps...> typename T, Apps... ts>
    consteval std::array<AppDescription, sizeof...(ts)> CreateAppDescriptions(T<ts...>) {
      return {CreateAppDescription<ts>()...};
    }

    constexpr auto userApps = CreateAppDescriptions(UserAppTypes {});
  }
}
