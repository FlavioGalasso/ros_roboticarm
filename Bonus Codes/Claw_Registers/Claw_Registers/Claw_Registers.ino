void setup(){
  Serial.begin(115200);
  TCCR2A= ((1<<COM2B1) |(1<<WGM20)); 
  TCCR2B= (1<<WGM22) | (1<<CS22)| (1<<CS21) | (1<<CS20);
  OCR2A = 155;
  DDRD|=(1<<PD3);
}

void servo4_update_pos(int pos){
  double pos_to_us = double(pos)/90 + 0.4;
  double duty= (pos_to_us) / (((0.02) * 1000.0) / (155+1)); 
  OCR2B = int(duty);
  Serial.print(pos);
  Serial.print(",");
  Serial.print(pos_to_us);
    Serial.print(",");
  Serial.print(duty);
  Serial.print(",");
  Serial.println(OCR2B);
}

void loop(){
  for(int i = 30; i < 60; i++){
    servo4_update_pos(i);
    delay(15);
  }
    for(int i = 60; i > 30; i--){
    servo4_update_pos(i);
    delay(15);
  }
}
