# 1 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"


//#define __UNO__
# 21 "/home/arch/Projects/arduino/power-sequencer/power-sequencer.ino"
void setup() {
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 0);

        pinMode(13, 0x1);


    pinMode(3, 0x1);
    pinMode(4, 0x1);
    pinMode(5, 0x1);
}

void turn_on_speakers(void) {
    digitalWrite(3, 1);
}

void turn_on_mixer(void) {
    if (check_speakers()) {
          digitalWrite(3, 0);
          delay(500);
          digitalWrite(4, 1);
          delay(3000);
          turn_on_speakers();
    }
}

void turn_off_mixer(void) {
    digitalWrite(3, 0);
    delay(500);
    digitalWrite(4, 0);
    delay(500);
}

bool check_mixer(void) {
    if ((digitalRead(4 == 0x1) || digitalRead(7 == 0x1))){
        return true;
    }
    else return false;
}

bool check_speakers(void) {
    if ((digitalRead(3 == 0x1) || digitalRead(6 == 0x1))){
        return true;
    }
    else return false;
}

void turn_on_synths(void) {
    if (check_speakers() || check_mixer()){
        turn_off_mixer();
        delay(500);
        digitalWrite(5, 1);
        turn_on_speakers();
    }
}

void turn_off_synths(void) {
    turn_off_mixer();
    digitalWrite(5, 0);
}

void loop() {
    digitalWrite(13, 0x1);
    delay(1000);
    digitalWrite(13, 0x0);
    delay(1000);
}
