# ESP8266 Remote Power Switch

Zdalne włączanie i wymuszanie wyłączania komputera za pomocą ESP8266 i przekaźnika, z interfejsem webowym.

## Opis działania

Projekt umożliwia zdalne sterowanie włączaniem komputera poprzez podłączenie ESP8266 do przycisku Power w obudowie komputera. Dzięki odczytowi napięcia z diody LED zasilania (Power LED), możliwe jest monitorowanie stanu komputera (włączony/wyłączony).

## Funkcje

- **Włączanie komputera** – symulacja krótkiego naciśnięcia przycisku POWER (400 ms)
- **Wymuszone wyłączanie** – przytrzymanie przycisku POWER przez 5,2 sekundy (awaryjne wyłączenie)
- **Interfejs webowy** – responsywny panel sterowania dostępny przez przeglądarkę
- **Automatyczne odświeżanie** – odświeżanie stanu co 3 sekundy

## Wymagania sprzętowe

- ESP8266 (NodeMCU, Wemos D1 mini lub podobny)
- Przekaźnik 5V (moduł przekaźnika 1-kanałowy)
- Rezystor (opcjonalnie, do odczytu stanu LED)

## Schemat podłączenia

| ESP8266 | Komputer                 |
|---------|--------------------------|
| D2 (GPIO4) | Przekaźnik – styki równolegle do przycisku POWER |
| D1 (GPIO5) | Dioda POWER LED (odczyt stanu) |
| GND     | Masa komputera           |

### Uwagi:
- Przekaźnik podłączamy **równolegle** do przycisku POWER na płycie głównej (NO i COM).
- Odczyt stanu komputera realizujemy przez podpięcie do nóżki diody POWER LED (sygnał HIGH = komputer wyłączony, LOW = włączony – zależnie od polaryzacji).

## Konfiguracja oprogramowania

1. Zainstaluj Arduino IDE lub PlatformIO.
2. Dodaj obsługę płytki ESP8266 (Board URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`).
3. Zainstaluj biblioteki:
   - `ESP8266WiFi`
   - `ESP8266WebServer`
4. W pliku `.ino` zmień dane Wi-Fi:
   ```cpp
   const char* ssid = "NAZWA_TWOJEJ_SIECI";
   const char* password = "TWOJE_HASŁO";

## Uruchomienie

Po uruchomieniu ESP8266 połączy się z Wi-Fi i wyświetli adres IP w monitorze szeregowym (prędkość 115200 bps).
Wejdź w przeglądarce pod adres:http://192.168.1.203/

## Interfejs użytkownika

Włącz – włącza komputer (impuls 0,4 s)
Wymuś wyłączenie – wyłącza komputer (przytrzymanie 5,2 s)
Odśwież teraz – ręczne odświeżenie strony

## Autor

Projekt open-source – możesz dowolnie modyfikować i dostosowywać do własnych potrzeb.

## Licencja

MIT
Możesz dostosować sekcję autora i licencji według własnych potrzeb.
