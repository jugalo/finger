void iniDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.display();
  delay(1000);
}

void Emprenta(int posar){ // 0 posar 1 treure 2 tornar a posar 3 OK
char * user;
char names[50];
    Cap();
    display.fillRect(0, 20, 32, 45, WHITE);
    display.drawXBitmap(0, 21,  finger_bits, finger_width, finger_height, 0);
    display.setFont(&FreeSerifBold8pt7b);
    display.drawRect(34, 21, 93, 42, WHITE);
    display.setTextColor(WHITE);
    switch (posar) {
    case 0:
      display.setCursor(62,37);
      display.print("POSI");
      display.setCursor(54,55);
      display.print("EL DIT");
      break;
    case 1:
      display.setCursor(47,37);
      display.print("TREGUI");      
      display.setCursor(54,55);
      display.print("EL DIT");
      break;
    case 2:
      display.setCursor(49,33);
      display.print("POSI EL");      
      display.setCursor(47,46);
      display.print("MATEIX");      
      display.setCursor(67,59);
      display.print("DIT");
      break;
    case 3:
/*      display.setCursor(70,46);
      display.print("OK");*/
      display.setCursor(35,37);
      display.print("EMPRENTA");      
      display.setCursor(45,55);
      display.print("AFEGIDA");
      break;
    case 4:
      display.setCursor(47,33);
      display.print("USUARI");      
      display.setCursor(67,46);
      display.print("NO");      
      display.setCursor(47,59);
      display.print("TROBAT");
      break;
    case 5:
      display.setCursor(46,33);
      display.print("Benvingut");      
      display.setCursor(37,46);
      int pos=name.indexOf(" ");
      display.print(name.substring(0,pos));      
      display.setCursor(37,57);
      display.print(name.substring(pos+1));      
      break;
    }
    display.setFont();
    display.display();
    delay(500);
    display.invertDisplay(true);
    delay(500); 
    display.invertDisplay(false);
}
void Cap(){
char sid[3];
    display.clearDisplay();
    display.drawXBitmap(0, 0,  wifi_bits, wifi_width, wifi_height, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(29,1);
    display.print("AULA");
    display.setCursor(34,10);
    display.print(AULA);
    display.fillRoundRect(62, 1, 65, 18, 3, WHITE);
    display.setTextColor(BLACK,WHITE);
    if (PROGRAMA==1){
      display.setCursor(65,6);
      display.print("AFEGIR ");
      sprintf(sid,"%03u",ID);
      display.print(sid);
    }else{
      display.setCursor(74,6);
      display.print("CONTROL");
    }
    display.setTextColor(WHITE);
}
void Missatge(String missatge, int x, int y){
  display.setCursor(x,y);
  display.println(missatge);
  display.display();
}

void Error(String missatge, int c){
  if (c==1) {
    Cap();
    display.setCursor(0,30);
  }else{
    display.clearDisplay();
    display.setCursor(0,20);
  }
  display.setTextSize(2);
  display.setTextColor(BLACK,WHITE);
  display.println("  ERROR:  ");
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println(missatge);  
  display.display();
  delay(500);
  display.invertDisplay(true);
  delay(500); 
  display.invertDisplay(false);
  nak();
  display.invertDisplay(true);
  delay(500); 
  display.invertDisplay(false);
}
