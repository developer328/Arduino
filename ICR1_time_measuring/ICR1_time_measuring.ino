/*
 * 6-APR-2024
 */

volatile uint16_t t0 = 0, t1 = 0, res = 0;

volatile uint8_t pulse_cnt = 0;

volatile uint8_t icrLed = 0, ovfLed = 0;

void setup(){
  Serial.begin(115200);
  cli();
  DDRB |= (1<<1) | (1<<5);
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  ICR1 = 50;
  TCNT1 = 0;

  TCCR1A |= (0<<COM1A0) | (1<<WGM13) | (1<<WGM12);
  TCCR1B |= (1<<CS12) | (1<<CS10) | (1<<ICNC1);
  TIMSK1 |= (1<<ICIE1) | (1<<TOIE1);

  sei();
}
void loop(){ 
  float second = (float)1/15625*res;
  Serial.print(second,4);
  Serial.print('\t');
  Serial.println("s");
}

ISR(TIMER1_CAPT_vect){
  pulse_cnt += 1;
  if(pulse_cnt == 1){
    t0 = ICR1;
  }
  if(pulse_cnt == 2){
    t1 = ICR1;
    res = t1-t0;
    pulse_cnt = 0;
  }
  
  icrLed = !icrLed;
  PORTB = (icrLed<<5) | (PORTB & ~(1<<5));
}

ISR(TIMER1_OVF_vect){
  t0 = 0, t1 = 0, pulse_cnt = 0;
  ovfLed = !ovfLed;
  PORTB = (ovfLed<<1) | (PORTB & ~(1<<1));
}
