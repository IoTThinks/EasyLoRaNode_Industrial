// ====================================
// PREFERENCES
// ====================================
// To save preferences to flash (without SD card)
// https://github.com/espressif/arduino-esp32/blob/master/libraries/Preferences/examples/StartCounter/StartCounter.ino

void setupPreferences() {
  // Read-Write mode: set second parameter to false 
  // Note: Namespace name is limited to 15 chars */
  preferences.begin("easylora", false);
}

void setPrefs(const char* key, const char* value)
{
  String savedPrefs = getPrefs(key);

  // If not exist saved value 
  // or saved value and to-save value is different
  // Then save new value
  if(savedPrefs == "" || strcmp(value, string2Char(savedPrefs)) != 0 )
  {
    preferences.putString(key, value);
    log("[Prefs] Preference saved. Key : ", key, " , value: ", value);
  }
  else
  {
    log("[Prefs] Skip saving same preference. Key : ", key, " , value: ", value);
  }
}

String getPrefs(const char* key)
{
  return preferences.getString(key, "");
}

// Close the Preferences
void closePreferences()
{
  // When we need to close the preference?
  preferences.end();  
}
