#pragma once

#include "wled.h"
#include <graph/Dodecahedron.h>
#include <graph/Graph.h>

class InfinityCubezUsermod : public Usermod
{

private:
  // set your config variables to their boot default value (this can also be done in readFromConfig() or a constructor if you prefer)
  struct
  {
    unsigned long ledsPerEdge = 25;
  } config;

  infc::Graph _graph;

  // string that are used multiple time (this will save some flash memory)
  static const char _name[];

public:
  /*
   * setup() is called once at boot. WiFi is not yet connected at this point.
   * readFromConfig() is called prior to setup()
   * You can use it to initialize variables, sensors or similar.
   */
  void setup()
  {
    
  }

  void loop() {

  }

  /*
   * addToConfig() can be used to add custom persistent settings to the cfg.json file in the "um" (usermod) object.
   * It will be called by WLED when settings are actually saved (for example, LED settings are saved)
   * If you want to force saving the current state, use serializeConfig() in your loop().
   *
   * CAUTION: serializeConfig() will initiate a filesystem write operation.
   * It might cause the LEDs to stutter and will cause flash wear if called too often.
   * Use it sparingly and always in the loop, never in network callbacks!
   *
   * addToConfig() will make your settings editable through the Usermod Settings page automatically.
   *
   * Usermod Settings Overview:
   * - Numeric values are treated as floats in the browser.
   *   - If the numeric value entered into the browser contains a decimal point, it will be parsed as a C float
   *     before being returned to the Usermod.  The float data type has only 6-7 decimal digits of precision, and
   *     doubles are not supported, numbers will be rounded to the nearest float value when being parsed.
   *     The range accepted by the input field is +/- 1.175494351e-38 to +/- 3.402823466e+38.
   *   - If the numeric value entered into the browser doesn't contain a decimal point, it will be parsed as a
   *     C int32_t (range: -2147483648 to 2147483647) before being returned to the usermod.
   *     Overflows or underflows are truncated to the max/min value for an int32_t, and again truncated to the type
   *     used in the Usermod when reading the value from ArduinoJson.
   * - Pin values can be treated differently from an integer value by using the key name "pin"
   *   - "pin" can contain a single or array of integer values
   *   - On the Usermod Settings page there is simple checking for pin conflicts and warnings for special pins
   *     - Red color indicates a conflict.  Yellow color indicates a pin with a warning (e.g. an input-only pin)
   *   - Tip: use int8_t to store the pin value in the Usermod, so a -1 value (pin not set) can be used
   *
   * See usermod_v2_auto_save.h for an example that saves Flash space by reusing ArduinoJson key name strings
   *
   * If you need a dedicated settings page with custom layout for your Usermod, that takes a lot more work.
   * You will have to add the setting to the HTML, xml.cpp and set.cpp manually.
   * See the WLED Soundreactive fork (code and wiki) for reference.  https://github.com/atuline/WLED
   *
   * I highly recommend checking out the basics of ArduinoJson serialization and deserialization in order to use custom settings!
   */
  void addToConfig(JsonObject &root)
  {
    JsonObject top = root.createNestedObject(FPSTR(_name));
    top["ledsPerEdge"] = config.ledsPerEdge;
  }

  /*
   * readFromConfig() can be used to read back the custom settings you added with addToConfig().
   * This is called by WLED when settings are loaded (currently this only happens immediately after boot, or after saving on the Usermod Settings page)
   *
   * readFromConfig() is called BEFORE setup(). This means you can use your persistent values in setup() (e.g. pin assignments, buffer sizes),
   * but also that if you want to write persistent values to a dynamic buffer, you'd need to allocate it here instead of in setup.
   * If you don't know what that is, don't fret. It most likely doesn't affect your use case :)
   *
   * Return true in case the config values returned from Usermod Settings were complete, or false if you'd like WLED to save your defaults to disk (so any missing values are editable in Usermod Settings)
   *
   * getJsonValue() returns false if the value is missing, or copies the value into the variable provided and returns true if the value is present
   * The configComplete variable is true only if the "exampleUsermod" object and all values are present.  If any values are missing, WLED will know to call addToConfig() to save them
   *
   * This function is guaranteed to be called on boot, but could also be called every time settings are updated
   */
  bool readFromConfig(JsonObject &root)
  {
    // default settings values could be set here (or below using the 3-argument getJsonValue()) instead of in the class definition or constructor
    // setting them inside readFromConfig() is slightly more robust, handling the rare but plausible use case of single value being missing after boot (e.g. if the cfg.json was manually edited and a value was removed)

    JsonObject top = root[FPSTR(_name)];

    bool configComplete = !top.isNull();

    configComplete &= getJsonValue(top["ledsPerEdge"], config.ledsPerEdge, 25);

    if (strip.getLength() <= 30*config.ledsPerEdge)
    {
      _graph.setDefinition(infc::makeInfinityCubeD12(config.ledsPerEdge));
    }

    return configComplete;
  }

  /*
   * getId() allows you to optionally give your V2 usermod an unique ID (please define it in const.h!).
   * This could be used in the future for the system to determine whether your usermod is installed.
   */
  uint16_t getId()
  {
    return USERMOD_ID_INFINITYCUBEZ;
  }

  // More methods can be added in the future, this example will then be extended.
  // Your usermod will remain compatible as it does not need to implement all methods from the Usermod base class!
};

// add more strings here to reduce flash memory usage
const char InfinityCubezUsermod::_name[] PROGMEM = "InfinityCubez";