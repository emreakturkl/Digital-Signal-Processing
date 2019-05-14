#define MicSamples (1024*2)
#define MicPin A0

void setup() {
  Serial.begin(115200);
}

void loop() {
  MeasureAnalog();
}

// measure basic properties of the input signal
// determine if analog or digital, determine range and average.
void MeasureAnalog()
{
  long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
  for (int i = 0; i < MicSamples; i++)
  {
    int k = analogRead(MicPin);
    #if 0
      Serial.println(k);
    #endif
    signalMin = min(signalMin, k);
    signalMax = max(signalMax, k);
    signalAvg += k;
  }
  signalAvg /= MicSamples;
  // print

#if 1
  Serial.print("Time: " + String(millis() - t0));
  Serial.print(" Min: " + String(signalMin));
  Serial.print(" Max: " + String(signalMax));
  Serial.print(" Avg: " + String(signalAvg));
  Serial.print(" Span: " + String(signalMax - signalMin));
  Serial.print(", " + String(signalMax - signalAvg));
  Serial.print(", " + String(signalAvg - signalMin));
  Serial.println("");
#endif
}
