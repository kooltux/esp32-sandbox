#include "eeprom_config.h"

#include <EEPROM.h>

#define SSID_OFFSET 0
#define PASSWD_OFFSET (SSID_OFFSET + SSID_LEN)
#define HOSTNAME_OFFSET (PASSWD_OFFSET + PASSWD_LEN)

EEPROM_Config::EEPROM_Config(void) : _ssid(""),
                                     _passwd(""),
                                     _hostname("")
{
}

bool EEPROM_Config::_read(int startAdr, int maxLength, char *dest)
{
  if (!EEPROM.begin(512))
    return false;

  delay(10);
  for (int i = 0; i < maxLength; i++)
  {
    dest[i] = char(EEPROM.read(startAdr + i));
  }
  EEPROM.end();
  return true;
}

bool EEPROM_Config::_write(int startAdr, int len, char *src)
{
  if (!EEPROM.begin(512))
    return false;
  EEPROM.begin(512); //Max bytes of eeprom to use
  yield();

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(startAdr + i, src[i]);
  }
  EEPROM.commit();
  EEPROM.end();
  return true;
}

bool EEPROM_Config::load()
{
  return (
      _read(SSID_OFFSET, SSID_LEN, _ssid) &&
      _read(PASSWD_OFFSET, PASSWD_LEN, _passwd) &&
      _read(HOSTNAME_OFFSET, HOSTNAME_LEN, _hostname) &&
      true);
}

bool EEPROM_Config::save()
{
  return (
      _write(SSID_OFFSET, SSID_LEN, _ssid) &&
      _write(PASSWD_OFFSET, PASSWD_LEN, _passwd) &&
      _write(HOSTNAME_OFFSET, HOSTNAME_LEN, _hostname) &&
      true);
}

void EEPROM_Config::set_ssid(const char *s)
{
  if (strlen(s) <= SSID_LEN)
    strcpy(_ssid, s);
  else
  {
    strncpy(_ssid, s, SSID_LEN);
    _ssid[SSID_LEN] = '\0';
  }
}

void EEPROM_Config::set_password(const char *s)
{
  if (strlen(s) <= PASSWD_LEN)
    strcpy(_passwd, s);
  else
  {
    strncpy(_passwd, s, PASSWD_LEN);
    _passwd[PASSWD_LEN] = '\0';
  }
}

void EEPROM_Config::set_hostname(const char *s)
{
  if (strlen(s) <= HOSTNAME_LEN)
    strcpy(_hostname, s);
  else
  {
    strncpy(_hostname, s, HOSTNAME_LEN);
    _hostname[HOSTNAME_LEN] = '\0';
  }
}