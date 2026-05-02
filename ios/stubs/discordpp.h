// BionicSX2 iOS stub
#pragma once
#include <string>
#include <functional>
namespace discord {
  struct Activity {};
  struct User {};
  struct ActivityManager {
    void UpdateActivity(const Activity&, std::function<void(int)> cb) { if(cb) cb(0); }
    void ClearActivity(std::function<void(int)> cb) { if(cb) cb(0); }
  };
  class Core {
  public:
    static int Create(long, uint64_t, Core**) { return 0; }
    void RunCallbacks() {}
    ActivityManager& GetActivityManager() { static ActivityManager am; return am; }
  };
}
