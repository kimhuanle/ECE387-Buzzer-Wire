void lcd_init() {
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Welcome To");
  lcd.setCursor(2,1);
  lcd.print("Buzzer Wire Game");
  lcd.setCursor(1,2);
  lcd.print("Created by Huan Le");
  lcd.setCursor(0,3);
  lcd.print("Touch loop  to start");
  show = false;
}

void lcd_game() {
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Buzzer Wire Game");
  lcd.setCursor(5,1);
  for(int i = 0; i < heart_count; i++)
    lcd.write(0);
  for(int i = 0; i < 10-heart_count; i++)
    lcd.write(1);
  lcd.setCursor(0,2);
  lcd.print("Lose all  Hearts and");
  lcd.setCursor(2,3);
  lcd.print("You will lose!!!");
  if(game_state == LOST)
    delay(500);
  else
    show = false;
}

void lcd_win() {
  if(millis() - last_blink > 300) {
    if(blink_time == 0) {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Buzzer Wire Game");
      lcd.setCursor(5,1);
      for(int i = 0; i < heart_count; i++)
        lcd.write(0);
      for(int i = 0; i < 10-heart_count; i++)
        lcd.write(1);
      lcd.setCursor(5,2);
      lcd.print("You Win!!!");
      lcd.setCursor(1,3);
      lcd.print("Your time: ");
      lcd.print(float(timer)/10);
      lcd.print("s");
    }
    if(is_blink)
      lcd.display();
    else
      lcd.noDisplay();
    is_blink = !is_blink;
    blink_time++;
    last_blink = millis();
  }
  if(blink_time > 10) {
    is_blink = true;
    blink_time = 0;
    lcd.display();
    show = true;
    game_state = INIT;
  }
}

void lcd_lose() {
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Buzzer Wire Game");
  lcd.setCursor(5,1);
  for(int i = 0; i < heart_count; i++)
    lcd.write(0);
  for(int i = 0; i < 10-heart_count; i++)
    lcd.write(1);
  lcd.setCursor(5,2);
  lcd.print("You Lost!!!");
  lcd.setCursor(3,3);
  lcd.print("Let's try again");
  show = false;
}
