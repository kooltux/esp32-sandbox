#ifndef __eeprom_config_h__
#define __eeprom_config_h__

#define SSID_LEN 32
#define PASSWD_LEN 32
#define HOSTNAME_LEN 32

class EEPROM_Config {
    private:
        char _ssid[SSID_LEN+1];
        char _passwd[PASSWD_LEN+1];
        char _hostname[HOSTNAME_LEN+1];

        bool _read(int startAdr, int maxLength, char* dest);
        bool _write(int startAdr, int len, char* src);

    public:
        EEPROM_Config(void);
    
        bool load();
        bool save();

        const char* ssid() { return _ssid; }
        void set_ssid(const char*);

        const char* password() { return _passwd; }
        void set_password(const char*);

        const char* hostname() { return _hostname; }
        void set_hostname(const char*);
};

#endif
