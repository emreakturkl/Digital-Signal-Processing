#include <math.h>
#include <LCD5110_Basic.h>

#define SAMPLE     10000
#define PTP        250

extern uint8_t SmallFont[];
extern uint8_t icons[];
static char text[] = "Degree: ";

LCD5110 myGLCD(8,9,10,11,12);

static double data = 0;
static int channel = 0;

//double mic1[SAMPLE], mic2[SAMPLE];
long t1 , t2; 
long t = 0;
unsigned int count1 = 0, count2 = 0;

static int signalAvg[2] = {0, 0}, signalMax[2] = {0, 0}, signalMin[2] = {679, 679}, peak[2] = {0, 0};

void setup() {
  
  Serial.begin(115200); 
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  DDRD |= B11100000;
  
  cli();
  ADCSRA = 0;             // clear ADCSRA register
  ADCSRB = 0;             // clear ADCSRB register
  ADMUX |= 0x00;          // set A0-A1 analog input pin
  
  ADMUX |= (1 << REFS0);  // set reference voltage
  //ADMUX |= (1 << ADLAR);  // left align ADC value to 8 bits from ADCH register

  // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
  // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles

  //ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescaler for 9.6 KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);                 // 32 prescaler for 38.5 KHz
  //ADCSRA |= (1 << ADPS2);                                // 16 prescaler for 76.9 KHz
  //ADCSRA |= (1 << ADPS1) | (1 << ADPS0);                 // 8 prescaler for 153.8 KHz

  //ADCSRA |= (1 << ADATE); // enable auto trigger
  ADCSRA |= (1 << ADIE);  // enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN);  // enable ADC
  sei();
  
  ADCSRA |= (1 << ADSC);  // start ADC measurements
  t = micros();
}

ISR(ADC_vect)
{      
    data = (int)ADC;
    //Serial.println(data); 
    
    switch(ADMUX)
    {
      case 0x40:
        if(count1 < SAMPLE)
        {
          count1++;
          //mic1[count1++] = data;
          signalMin[0] = min(signalMin[0], data);
          signalMax[0] = max(signalMax[0], data);
          signalAvg[0] += data;
          if((peak[0] < signalMax[0] - signalMin[0]) && (signalMax[0] - signalMin[0] > PTP))
          {
            peak[0] = signalMax[0] - signalMin[0];
            t1 = micros() - t;
          }
        }       
        ADMUX = 0x43;
        break;
      case 0x43:
        if(count2 < SAMPLE)
        {
          count2++;
          //mic2[count2++] = data;
          signalMin[1] = min(signalMin[1], data);
          signalMax[1] = max(signalMax[1], data);
          signalAvg[1] += data;
          if((peak[1] < signalMax[1] - signalMin[1]) && (signalMax[1] - signalMin[1] > PTP))
          {
            peak[1] = signalMax[1] - signalMin[1];
            t2 = micros() - t;
          }
        }
        ADMUX = 0x40;
        break;
      default:
        // Default Code
        break;
    }
    ADCSRA |= (1 << ADSC);
}
void loop()
{ 
  if(count1 >= SAMPLE && count2 >= SAMPLE)
  { 
    /*
    for(int i=0; i<SAMPLE; i++)
    {
      Serial.println(mic1[i]);
      Serial.println(mic2[i]);
    }
    */
    
    int x = 0;
    PORTD &= B00000011;
    
    if(t1 == 0 && t2 == 0)
    {
      PORTD |= B01000000;
    }
    else if((t1 < t2 || (t2 == 0)) && t1 > 0)
    {
      x = -1;
      PORTD |= B10000000;
    }
    else
    {
      x = 1;
      PORTD |= B00100000;
    }

    /*
    Serial.print(t1);
    Serial.print("\t");
    Serial.println(t2);
    */
    
    //double tD =  (t1-t2) / (double)1000000;
    //double degree = acos((tD * 340.0) / 0.16) * (180.0 / PI);
    //Serial.println(degree);
    
    double degree = acos(x) * (180.0 / PI);
    draw(degree);

    peak[0] = 0, signalAvg[0] = 0, signalMax[0] = 0, signalMin[0] = 679;
    peak[1] = 0, signalAvg[1] = 0, signalMax[1] = 0, signalMin[1] = 679;

    count1 = count2 = 0;
    t1 = t2 = 0;
    t = micros();
  }
}

void draw(int degree)
{
  myGLCD.clrScr();
  myGLCD.print(text, LEFT , 0);
  myGLCD.printNumI(degree, 45, 0);
  myGLCD.drawBitmap(0, 16, icons, 84, 48);
  int temp = map(degree, 0, 180, 0, 75);
  myGLCD.print("+", temp , 32);
  myGLCD.invert(false);
  delay(100);
}

