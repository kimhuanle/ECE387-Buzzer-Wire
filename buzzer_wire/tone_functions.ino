/**
 * Playing win melody
 */
void tone_win() {
  if(tone_index < 10 && millis() - last_tone >= win_duration[tone_index]/4) {
    tone(buzzer, win_tone[tone_index], win_duration[tone_index+1]/4);
    tone_index++;
    last_tone = millis();
  }
}

/**
 * Playing loss melogy
 */
void tone_lose() {
  if(tone_index < 8 && millis() - last_tone >= lose_duration[tone_index]/4) {
    tone(buzzer, lose_tone[tone_index], lose_duration[tone_index+1]/4);
    tone_index++;
    last_tone = millis();
  }
  if(tone_index >= 8) {
    show = true;
    interrupt = millis();
    game_state = INIT;
  }
}
