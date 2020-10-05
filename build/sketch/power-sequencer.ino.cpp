#include <Arduino.h>
#line 1 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
#define TEST_MODE
#define __NANO__
//#define __UNO__

#if defined(__NANO__)
    #define SPEAKER_RELAY   3
    #define SPEAKER_SWITCH  6
    #define MIXER_RELAY     4
    #define MIXER_SWITCH    7
    #define SYNTH_RELAY     5
    #define SYNTH_SWITCH    8
#elif defined(__UNO__)
    #define SPEAKER_RELAY   3
    #define SPEAKER_SWITCH  6
    #define MIXER_RELAY     4
    #define MIXER_SWITCH    7
    #define SYNTH_RELAY     5
    #define SYNTH_SWITCH    8
#endif

#define RELAY_OFF       0
#define RELAY_ON        1

struct relay_switch {
    int u8_switch;
    int u8_relay;
}

#line 29 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void setup();
#line 45 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void turn_on_speakers(void);
#line 49 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void turn_on_mixer(void);
#line 62 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void turn_off_mixer(void);
#line 69 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
bool check_mixer(void);
#line 76 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
bool check_speakers(void);
#line 83 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void turn_on_synths(void);
#line 92 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void turn_off_synths(void);
#line 97 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void loop();
#line 29 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void setup() {
    digitalWrite(SPEAKER_RELAY, RELAY_OFF);
    digitalWrite(MIXER_RELAY, RELAY_OFF);
    digitalWrite(SYNTH_RELAY, RELAY_OFF);
    #if defined(TEST_MODE)
        pinMode(LED_BUILTIN, OUTPUT);
    #endif

    pinMode(SPEAKER_RELAY, OUTPUT);
    pinMode(MIXER_RELAY, OUTPUT);
    pinMode(SYNTH_RELAY, OUTPUT);

    struct relay_switch synth = {SYNTH_SWITCH, SYNTH_RELAY};

}

void turn_on_speakers(void) {
    digitalWrite(SPEAKER_RELAY, RELAY_ON);
}

void turn_on_mixer(void) {
    if (check_speakers()) {
          digitalWrite(SPEAKER_RELAY, RELAY_OFF);
          delay(500);
          digitalWrite(MIXER_RELAY, RELAY_ON);
          delay(3000);
          turn_on_speakers();
    }
    else {
        digitalWrite(MIXER_RELAY, RELAY_ON);
    }
}

void turn_off_mixer(void) {
    digitalWrite(SPEAKER_RELAY, RELAY_OFF);
    delay(500);
    digitalWrite(MIXER_RELAY, RELAY_OFF);
    delay(500);
}

bool check_mixer(void) {
    if ((digitalRead(MIXER_RELAY == HIGH) || digitalRead(MIXER_SWITCH == HIGH))){
        return true;
    }
    else return false;
}

bool check_speakers(void) {
    if ((digitalRead(SPEAKER_RELAY == HIGH) || digitalRead(SPEAKER_SWITCH == HIGH))){
        return true;
    }
    else return false;
}

void turn_on_synths(void) {
    if (check_speakers() || check_mixer()){
        turn_off_mixer();
        delay(500);
        digitalWrite(SYNTH_RELAY, RELAY_ON);
        turn_on_speakers();
    }
}

void turn_off_synths(void) {
    turn_off_mixer();
    digitalWrite(SYNTH_RELAY, RELAY_OFF);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

