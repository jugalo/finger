void getFinger() {
  uint8_t p = -1;
  ok();
  while (p != FINGERPRINT_OK) {
    Emprenta(0);
    p = finger.getImage();
  }
  p = finger.image2Tz();  
  p = finger.fingerFastSearch();
  if (p==FINGERPRINT_OK){
    ID=finger.fingerID;
    ok();
    #if DEBUG==1 
      Cap();
      Missatge("Enviant la emprenta..",0,32);
    #endif
    Enviar();
    Emprenta(5);
    delay(1000);
  }else{
    Emprenta(4);
    nak();
  }
}

void iniFinger(){
  finger.begin(57600); 
//  finger.emptyDatabase();
}

void Enviar(){
  if (ConnexioMysql()) {
    InsertMysql("Access");
    ConsultaMysql();
    #if DEBUG==1 
      delay(1000);
    #endif
  }
}

uint8_t enrollFinger() {
  uint8_t p = -1;
  uint8_t e = -1;
  ok();
  while (p != FINGERPRINT_OK) {
    Emprenta(0);
    p = finger.getImage();
  }
  p = finger.image2Tz(1);
  p = 0;
  ok();
  while (p != FINGERPRINT_NOFINGER) {
    Emprenta(1);
    p = finger.getImage();
  }
  p = -1;
  ok();
  while (p != FINGERPRINT_OK) {
    Emprenta(2);
    p = finger.getImage();
  }
  p = finger.image2Tz(2);
  p = finger.createModel();
  p = finger.storeModel(ID);
  if (p != FINGERPRINT_OK){
    Error("No es pot desar el   template.",1);
  }else{
    ok();
    #if DEBUG==1 
      Cap();
      Missatge("Desant la emprenta...",0,32);
    #endif
    //Grabar();
    Emprenta(3);
    delay(1000);
    //e=Template();
  }
 }
 void Grabar(){
  if (ConnexioMysql()) {
    InsertMysql("User");
    #if DEBUG==1 
      delay(1000);
    #endif
  }
}

/*
uint8_t Template(uint16_t ID){
uint8_t e = -1;
  Cap();
  Missatge("Generant model...",0,32);
  e=finger.loadModel(ID);  
  e=finger.getModel();
  if (e == FINGERPRINT_OK){
    e=GrabarTemplate();
  }
  return e;
}

uint8_t GrabarTemplate(){
  uint8_t bytesReceived[556]; 
  memset(bytesReceived, 0xff, 556);
  uint32_t starttime = millis();
  int i = 0;
  while (i < 556 && (millis() - starttime) < 20000) {
      if (mySerial.available()) {
          bytesReceived[i++] = mySerial.read();
      }
  }
  
  uint8_t fingerTemplate[512]; 
  memset(fingerTemplate, 0xff, 512);
  int uindx = 9, index = 0;
  while (index < 512) {
      fingerTemplate[index++] = bytesReceived[uindx++];
      if (index == 128) uindx += 11;
      if (index == 256) uindx += 11;
      if (index == 384) uindx += 11;
  }
  String fexa;
  for (int i = 0; i < 512; ++i) {
      fexa=fexa + printHex(fingerTemplate[i], 2);
  }

  if (!ConnexioMysql()) {
    return 0;
  }else{
    InsertMysql(fexa);
    delay(1000);
  }
  return FINGERPRINT_OK;
}

String printHex(int num, int precision) {
    char tmp[16];
    char format[128];
 
    sprintf(format, "%%.%dX", precision);
    sprintf(tmp, format, num);
    return tmp;
}

*/











