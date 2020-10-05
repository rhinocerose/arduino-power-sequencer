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
};

struct relay_switch synth = {SYNTH_SWITCH, SYNTH_RELAY};
struct relay_switch mixer = {MIXER_SWITCH, MIXER_RELAY};
struct relay_switch speaker = {SPEAKER_SWITCH, SPEAKER_RELAY};

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


}

/**
 * @brief
 *
 * @param Switch
 *
 * @return
 */
bool check_state(struct relay_switch Switch) {
    if ((digitalRead(Switch.u8_relay == HIGH) || digitalRead(Switch.u8_switch == HIGH))){
        return true;
    }
    else return false;
}

void turn_on_speakers(void) {
    digitalWrite(SPEAKER_RELAY, RELAY_ON);
}

void turn_on_mixer(void) {
    if (check_state(speaker)) {
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

void turn_on_synths(void) {
    if (check_state(speaker) || check_state(mixer)){
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
