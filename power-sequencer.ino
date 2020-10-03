#define TEST_MODE
#define __NANO__
//#define __UNO__

#if defined(__NANO__)
    #define SPEAKER_RELAY   3
    #define MIXER_RELAY     4
    #define SYNTH_RELAY     5
#elif defined(__UNO__)
    #define SPEAKER_RELAY   3
    #define MIXER_RELAY     4
    #define SYNTH_RELAY     5
#endif

#define RELAY_OFF       0
#define RELAY_ON        1

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

void turn_on_speakers(void) {
    digitalWrite(SPEAKER_RELAY, RELAY_ON);
}

void turn_on_mixer(void) {
    if (digitalRead(SPEAKER_RELAY) == HIGH) {
          digitalWrite(SPEAKER_RELAY, RELAY_OFF);
          delay(500);
          digitalWrite(MIXER_RELAY, RELAY_ON);
          delay(3000);
          turn_on_speakers();
    }
}

void turn_off_mixer(void) {
    digitalWrite(SPEAKER_RELAY, RELAY_OFF);
    delay(500);
    digitalWrite(MIXER_RELAY, RELAY_OFF);
    delay(500);
}

void turn_on_synths(void) {
    if ((digitalRead(MIXER_RELAY) == HIGH) || (digitalRead(SPEAKER_RELAY) == HIGH)) {
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
