#ifndef WiFiSetup
#define WiFiSetup

#include <WiFi.h>
#include <Preferences.h>
#include <ESPmDNS.h>

/// @brief default setup ssid:"Setup"; default setup password:"12345678"
class WlanSetup{
    public:
        /// @brief Creates Setup with needed ssid an password
        /// @param ledPin the pin of the LED indicator(default: 2)
        /// @param ssid type in SSID if dont want to save the credentials
        /// @param pass type in password if dont want to save the credentials
        /// @param setupSsid name for the Setup Wlan(default:"Setup")
        /// @param setupPass Password for the Setup Wlan(default:"12345678")
        WlanSetup(int ledPin = 2,const char*ssid="",const char*pass="",const char*setupSsid="Setup",const char*setupPass="12345678");

        /// @brief Trying to connect to the saved/given credentials
        /// @param connect try to connect when calling this function and switchig to setup(default: true)
        /// @param save Want to save the credentials in EEPROM/use stored credentials on start; If not type in credentials in the class object(default: true)
        /// @param led Want LED(on pin 2) to be an indicator of the connecting State(default: true)
        /// @param tries how many times the ESP should try to connect to the stored SSID(default: 5)
        /// @param interval the delay(in ms) in between the tries of connecting to the WiFi(default: 1000)
        /// @return true if connected to stored SSID; false if starting in setup mode
        bool begin(bool connect = true,bool save = true,bool led = true,int tries = 5,int interval = 1000);

        /// @brief try to connect to the given SSID
        /// @param ssid ssid to try to connect to
        /// @param pass password to try to connect to
        /// @param setup if it should go in setup mode when failing to connect(default: true)
        /// @return true if connected to stored SSID; false if starting in setup mode or doing nothing instead of initialising
        bool tryConnect(const char*ssid,const char*pass,bool setup = "true");
    private:
        Preferences prefs;
        void saveCredentials(const char* ssid,const char*pass);
        void setupMode();
        bool _setupMode = false;
        bool _save;
        char* _setupSsid; 
        char* _setupPass; 
        String _ssid;
        String _pass;
        int _ledPin;
        int _tries;
        int _interval;
        bool _led;
    };

#endif