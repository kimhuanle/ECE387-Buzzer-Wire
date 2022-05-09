void check_input() {
  switch(game_state) {
    case INIT:
      if(digitalRead(left)) {
        start_input = left;
        stop_input = right;
        show = true;
        game_state = GAME;
      } else if(digitalRead(right)) {
        start_input = right;
        stop_input = left;
        show = true;
        game_state = GAME;
      } else
        return INIT;
      break;
    case GAME:
      if(digitalRead(stop_input))
        game_state = WIN;
      break;
    default:
      break;
  }
}

void check_wire() {
  if(millis() - last_check >= 400 && digitalRead(wire)) {
    heart_count--;
    tone(buzzer, 600, 200);
    last_check = millis();
    show = true;
  }
  if(heart_count == 0) {
    show = true;
    game_state = LOST;
  }
}
