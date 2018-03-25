void iniBuzzer(){
   pinMode(buzzer, OUTPUT);
}

void beep(int delayms){
  analogWrite(buzzer, 255); 
  delay(delayms);
  analogWrite(buzzer,0);
  delay(delayms);
}

void ok(){
  beep(100);
  beep(100);
}

void nak(){
  beep(200);
  beep(400);
  beep(600);
  beep(800);
}

int potenciometro(){
  int valor;
  valor = analogRead(A0);
  if (valor>512){
    return 1;
  }else{
    return 0;
  }
  display.println(valor);
  display.display();
  delay(1000);
}
