volatile uint16_t count = 0;
float time1 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW); 
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCCR1B |= (1<<CS10);//16000000hz
  sei();

  TCNT1 = 0;
  PORTB |= (1<<1);
  count = TCNT1;

  time1 = (1.0/16000.0)*(float)count;

  Serial.print("count: ");
  Serial.print(count);
  Serial.print('\t');
  Serial.print("Milliseconds: ");
  Serial.println(time1, 5);
}

void loop() {

}
