#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_IMGUIWIDGETS
    #define IMGUIWIDGETS_PUBLIC __declspec(dllexport)
  #else
    #define IMGUIWIDGETS_PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_IMGUIWIDGETS
      #define IMGUIWIDGETS_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define IMGUIWIDGETS_PUBLIC
  #endif
#endif

namespace imguiwidgets {

class IMGUIWIDGETS_PUBLIC Imguiwidgets {

public:
  Imguiwidgets();
  int get_number() const;

private:

  int number;

};

}

