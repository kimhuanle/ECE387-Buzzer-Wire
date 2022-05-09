void display_lose() {
  for(int i = 0; i < 4; i++)
    digitalWrite(digits[i], HIGH);
  for(int i = 0; i < 6; i++)
    digitalWrite(segments[i], HIGH);
  digitalWrite(segments[6], LOW);
}

void display_win() {
  if(!is_blink)
    display_num(timer);
  else
    clear_display();
}
void display_num(int num) {
  display_digit(-1, false);
  select_digit(4);
  display_digit(num/1000, false);
  display_digit(-1, false);
  select_digit(3);
  display_digit(num%1000/100, false);
  display_digit(-1, false);
  select_digit(2);
  display_digit(num%100/10, true);
  display_digit(-1, false);
  select_digit(1);
  display_digit(num%10/1, false);
}

// Clear display before update
void clear_display() {
  for (int i = 1; i <= 4; i++) {
    select_digit(i);
    for (int j = 0; j < 7; j++)
      digitalWrite(segments[j], HIGH);
  }
}

void select_digit(int digit) {
  switch (digit) {
    case 1:
      digitalWrite(digits[0], HIGH);
      digitalWrite(digits[1], LOW);
      digitalWrite(digits[2], LOW);
      digitalWrite(digits[3], LOW);
      break;
    case 2:
      digitalWrite(digits[0], LOW);
      digitalWrite(digits[1], HIGH);
      digitalWrite(digits[2], LOW);
      digitalWrite(digits[3], LOW);
      break;
    case 3:
      digitalWrite(digits[0], LOW);
      digitalWrite(digits[1], LOW);
      digitalWrite(digits[2], HIGH);
      digitalWrite(digits[3], LOW);
      break;
    case 4:
      digitalWrite(digits[0], LOW);
      digitalWrite(digits[1], LOW);
      digitalWrite(digits[2], LOW);
      digitalWrite(digits[3], HIGH);
      break;
  }
}

// Display one digit
void display_digit(int num, bool decimal) {
  if (decimal)
    digitalWrite(segments[7], LOW);
  else
    digitalWrite(segments[7], HIGH);
  switch (num) {
    case 0:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], LOW);
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], HIGH);
      break;
    case 1:
      digitalWrite(segments[0], HIGH);    
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], HIGH);   
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], HIGH);   
      digitalWrite(segments[6], HIGH);   
      break;
    case 2:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], HIGH);    
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], LOW);
      digitalWrite(segments[5], HIGH);   
      digitalWrite(segments[6], LOW);
      break;
    case 3:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], HIGH);   
      digitalWrite(segments[6], LOW);
      break;
    case 4:
      digitalWrite(segments[0], HIGH);   
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], HIGH);   
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], LOW);
      break;
    case 5:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], HIGH);   
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], LOW);
      break;
    case 6:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], HIGH);   
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], LOW);
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], LOW);
      break;
    case 7:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], HIGH);   
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], HIGH);   
      digitalWrite(segments[6], HIGH);     
      break;
    case 8:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], LOW);
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], LOW);
      break;
    case 9:
      digitalWrite(segments[0], LOW);
      digitalWrite(segments[1], LOW);
      digitalWrite(segments[2], LOW);
      digitalWrite(segments[3], LOW);
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], LOW);
      digitalWrite(segments[6], LOW);
      break;
    case -1:  
      digitalWrite(segments[0], HIGH);
      digitalWrite(segments[1], HIGH);
      digitalWrite(segments[2], HIGH);
      digitalWrite(segments[3], HIGH);
      digitalWrite(segments[4], HIGH);   
      digitalWrite(segments[5], HIGH);
      digitalWrite(segments[6], HIGH);
      break;
    default:
      break;
  }
}
