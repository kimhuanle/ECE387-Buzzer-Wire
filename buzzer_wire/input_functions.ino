/**
 * Checking inputs from 2 wire loops on two ends to start and stop the game
 */
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
      if(digitalRead(stop_input)){
        game_state = WIN;
        delay(500/4);
      }
      break;
    default:
      break;
  }
}

/**
 * Checking for wire touch to reduce the number of hearts or end the game
 */
void check_wire() {
  if(millis() - last_check >= 400/4 && digitalRead(wire)) {
    heart_count--;
    tone(buzzer, 600, 200/4);
    last_check = millis();
    show = true;
  }
  if(heart_count == 0) {
    show = true;
    game_state = LOST;
  }
}
