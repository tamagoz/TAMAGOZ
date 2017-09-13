//--------------READ_PLC-------------------------

int i0 = 7;
int i1 = 6;
int i2 = 5;
int i3 = 4;
int i4 = 3;
int i5 = 2;

int state0;
int state1;
int state2;
int state3;
int state4;
int state5;

int value;

void setup()
{
  delay(2000);

  pinMode(i0, INPUT_PULLUP);
  pinMode(i1, INPUT_PULLUP);
  pinMode(i2, INPUT_PULLUP);
  pinMode(i3, INPUT_PULLUP);
  pinMode(i4, INPUT_PULLUP);
  pinMode(i5, INPUT_PULLUP);
}

void loop()
{
  state0 = digitalRead(i0);
  state1 = digitalRead(i1);
  state2 = digitalRead(i2);
  state3 = digitalRead(i3);
  state4 = digitalRead(i4);
  state5 = digitalRead(i5);

  value = 0;
  value = value + (state0);  //Most significant bit
  value = (value * 2) + (state1);
  value = (value * 2) + (state2);
  value = (value * 2) + (state3);
  value = (value * 2) + (state4);
  value = (value * 2) + (state5); //Least significant bit

  //Serial.println(value);
  //Serial.println(value, BIN);

  switch (value)
  {
    case 0:    // Do something
      Serial.println("input is 0");
      break;
    case 1:    // Do something    //  เป็นนาฬิกา
      Serial.println("1");
      break;
    case 2:    // Do something
      Serial.println("B-01");
      break;
    case 3:    // Do something
      Serial.println("B-02");
      break;
    case 4:    // Do something
      Serial.println("B-03");
      break;
    case 5:    // Do something
      Serial.println("B-04");
      break;
    case 6:    // Do something
      Serial.println("B-05");
      break;
    case 7:    // Do something
      Serial.println("B-08");
      break;
    case 8:    // Do something
      Serial.println("B-05");
      break;
    case 9:    // Do something
      Serial.println("B-07");
      break;
    case 16:    // Do something
      Serial.println("B-09");
      break;
    case 17:    // Do something
      Serial.println("B-10");
      break;
    case 18:    // Do something
      Serial.println("B-11");
      break;
    case 19:    // Do something
      Serial.println("B-12");
      break;
    case 20:    // Do something
      Serial.println("B-13");
      break;
    case 21:    // Do something
      Serial.println("B-14");
      break;
    case 22:    // Do something
      Serial.println("B-15");
      break;
    case 23:    // Do something
      Serial.println("B-16");
      break;
    case 24:    // Do something
      Serial.println("B-17");
      break;
    case 25:    // Do something
      Serial.println("B-18");
      break;
    case 32:    // Do something
      Serial.println("B-19");
      break;
    case 33:    // Do something
      Serial.println("B-20");
      break;
    case 34:    // Do something
      Serial.println("B-21");
      break;
    case 35:    // Do something
      Serial.println("B-22");
      break;
    case 36:    // Do something
      Serial.println("B-23");
      break;
    case 37:    // Do something
      Serial.println("A-01");
      break;
    case 38:    // Do something
      Serial.println("A-02");
      break;
    case 39:    // Do something
      Serial.println("A-03");
      break;
    case 40:    // Do something
      Serial.println("A-04");
      break;
    case 41:    // Do something
      Serial.println("A-05");
      break;
    case 48:    // Do something
      Serial.println("A-06");
      break;
    case 49:    // Do something
      Serial.println("FL01");
      break;
    case 50:    // Do something
      Serial.println("FL03");
      break;
    case 51:    // Do something
      Serial.println("FL02");
      break;
    case 52:    // Do something
      Serial.println("FL04");
      break;
    case 53:    // Do something
      Serial.println("K720");   //------------------------------final--
      break;

/*    
    case 54:    // Do something
      Serial.println("input is 36");
      break;
    case 55:    // Do something
      Serial.println("input is 37");
      break;
    case 56:    // Do something
      Serial.println("input is 38");
      break;
    case 57:    // Do something
      Serial.println("input is 39");
      break;
    case 58:    // Do something
      Serial.println("input is 40");
      break;
    case 59:    // Do something
      Serial.println("input is 41");
      break;
    case 60:    // Do something
      Serial.println("input is 42");
      break;
    case 61:    // Do something
      Serial.println("input is 43");
      break;
    case 62:    // Do something
      Serial.println("input is 44");
      break;
    case 63:    // Do something
      Serial.println("input is 45");
      break;
    case 64:    // Do something
      Serial.println("input is 46");
      break;
    case 65:    // Do something
      Serial.println("input is 47");
      break;
    case 66:    // Do something
      Serial.println("input is 48");
      break;
    case 67:    // Do something
      Serial.println("input is 49");
      break;
    case 68:    // Do something
      Serial.println("input is 50");
      break;
    case 69:    // Do something
      Serial.println("input is 51");
      break;
    case 70:    // Do something
      Serial.println("input is 52");
      break;
      case 71:    // Do something
      Serial.println("input is 53");
      break;
      case 72:    // Do something
      Serial.println("input is 54");
      break;
      case 73:    // Do something
      Serial.println("input is 55");
      break;
      case 74:    // Do something
      Serial.println("input is 56");
      break;
      case 75:    // Do something
      Serial.println("input is 57");
      break;
      case 76:    // Do something
      Serial.println("input is 58");
      break;
      case 77:    // Do something
      Serial.println("input is 59");
      break;
      case 78:    // Do something
      Serial.println("input is 60");
      break;
      case 79:    // Do something
      Serial.println("B-03");
      break;
      case 80:    // Do something
      Serial.println("B-02");
      break;
      case 81:    // Do something
      Serial.println("B-01");
      break;
*/
  }
  delay (3000);
}

/*
  value = 0;
  value = value + (digitalRead(pin8));  //Most significant bit
  value = (value*2) + (digitalRead(pin7));
  value = (value*2) + (digitalRead(pin6));
  value = (value*2) + (digitalRead(pin5));   //Least significant bit
*/


