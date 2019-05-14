void setup()
{
  Serial.begin(115200);
  pinMode(A0, INPUT);
}
void loop()
{
  long t0, t;
  t0 = micros();
  for(int i=0; i<1000; i++) {
    analogRead(A0);
  }
  t = micros()-t0; // calculate elapsed time
  Serial.print("Time per sample: ");
  Serial.println((float)t/1000);
  Serial.print("Frequency: ");
  Serial.println((float)1000*1000000/t);
  Serial.println();
  delay(2000);
}
