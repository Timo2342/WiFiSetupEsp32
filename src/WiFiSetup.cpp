#include "WiFiSetup.h"

WlanSetup::WlanSetup(int ledPin,const char*ssid,const char*pass,const char*setupSsid,const char*setupPass){
_ledPin = ledPin;
_ssid = ssid;
_pass = pass;
_setupSsid = (char*)setupSsid;
_setupPass = (char*)setupPass;
}

bool WlanSetup::begin(bool connect,bool save,bool led,int tries,int interval){
    _save = save;
    _led = led;
    _tries = tries;
    _interval = interval;
    if(save){
        prefs.begin("WiFi-Cred", false); 
        _ssid = prefs.getString("_ssid","");
        _pass = prefs.getString("_pass","");
        if(connect==true && _ssid == ""){
            setupMode();
            return false;
        }
    }
    if(connect){
        if(led){
            pinMode(_ledPin,OUTPUT);
        }
        return(tryConnect((char*)_ssid.c_str(),(char*)_pass.c_str()));
    }
    return false;
}

bool WlanSetup::tryConnect(const char*ssid,const char*pass,bool setup){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,pass);
    bool ledState = false;
    for(int i = 0;i<_tries;i++){
        if(WiFi.status() == WL_CONNECTED){
            digitalWrite(_ledPin,LOW);
            _setupMode = false;
            if(_save){
                saveCredentials(ssid,pass);
            }
            return true;
        }
        if(_led){
            ledState = !ledState;
            digitalWrite(_ledPin,ledState);
        }
        delay(_interval);
    }
    if(setup){
        setupMode();
    }
    return false;
}

void WlanSetup::setupMode(){
    WiFi.mode(WIFI_AP);
    Serial.println(_setupSsid);
    Serial.println(_setupPass);
    if (!WiFi.softAP(_setupSsid, _setupPass)) {
    log_e("Soft AP creation failed.");
    while (1);
    }
    _setupMode = true;
    digitalWrite(_ledPin,HIGH);
}

void WlanSetup::saveCredentials(const char* ssid,const char*pass){
    prefs.putString("_ssid",ssid);
    prefs.putString("_pass",pass);
}