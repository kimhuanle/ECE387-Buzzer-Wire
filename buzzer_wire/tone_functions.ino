void tone_win() {
  if(tone_index < 10 && millis() - last_tone >= win_duration[tone_index]) {
    tone(buzzer, win_tone[tone_index], win_duration[tone_index+1]);
    tone_index++;
    last_tone = millis();
  }
}

void tone_lose() {
  if(tone_index < 8 && millis() - last_tone >= lose_duration[tone_index]) {
    tone(buzzer, lose_tone[tone_index], lose_duration[tone_index+1]);
    tone_index++;
    last_tone = millis();
  }
  if(tone_index >= 8) {
    show = true;
    game_state = INIT;
  }
}
