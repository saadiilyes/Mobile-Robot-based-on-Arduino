#include <Servo.h>
Servo Baleyage;
#define echoPin 13 //attach pin 
#define trigPin 12

int tourna = 1100;  // Delay de tourne                                                                                                                                                                                                                                                                    //delay de tourneur
long duration;
int distance, distanceG, distanceD;

int speedPin = 11; // speedpin droite
int speedPinG = 3; // speedpin gauche


int MdroiteB = 4;//Moteur Droite arrière
int MdroiteA = 7; //Moteyr Droite avant
int MgaucheB = 2;//Moteur Gauche arrière
int MgaucheA = A0;//Moteur Gauche avant
int vtt = 0;//vitesse



void CalculDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void MarcheAv(int spd) { //=Marche Avant
  //speedPin.write(spd);
  analogWrite(speedPin, spd);
  analogWrite(speedPinG, spd -10);
  digitalWrite(MdroiteA, HIGH);
  digitalWrite(MdroiteB, LOW);
  digitalWrite(MgaucheA, HIGH);
  digitalWrite(MgaucheB, LOW);
}

void MarcheAr(int spd) { //Marche Arrière
  //speedPin.write(spd);
  analogWrite(speedPin, spd);
  analogWrite(speedPinG, spd - 10);
  digitalWrite(MdroiteA, LOW);
  digitalWrite(MdroiteB, HIGH);
  digitalWrite(MgaucheA, LOW);
  digitalWrite(MgaucheB, HIGH );
}

void TourneG(int spd) { //Tourne Gauche
  //speedPin.write(spd);
  analogWrite(speedPin, spd);
  analogWrite(speedPinG, spd - 10);
  digitalWrite(MdroiteA, HIGH);
  digitalWrite(MdroiteB, LOW);
  digitalWrite(MgaucheA, LOW);
  digitalWrite(MgaucheB, HIGH );
}

void TourneD(int spd) {// Tourne Droite
  //speedPin.write(spd);
  analogWrite(speedPin, spd);
  analogWrite(speedPinG, spd - 10);
  digitalWrite(MdroiteA, LOW);
  digitalWrite(MdroiteB, HIGH);
  digitalWrite(MgaucheA, HIGH);
  digitalWrite(MgaucheB, LOW);
}

void Stop() { // Stop
  //speedPin.write(spd);
  analogWrite(speedPin, 0);
  analogWrite(speedPinG, 0);
  digitalWrite(MdroiteA, LOW);
  digitalWrite(MdroiteB, LOW);
  digitalWrite(MgaucheA, LOW);
  digitalWrite(MgaucheB, LOW);
}

void setup() {  

  pinMode(MdroiteA, OUTPUT);
  pinMode(MdroiteB, OUTPUT);
  pinMode(MgaucheA, OUTPUT);
  pinMode(MgaucheB, OUTPUT);


  pinMode(speedPin, OUTPUT);
  pinMode(speedPinG, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Baleyage.attach(9);
  Baleyage.write(90);//90°
  Serial.begin(115200);
  vtt = 60;// Vitesse

}

void loop() {
  
  vtt=60;//vitesse = 60
  CalculDistance();
  MarcheAv(vtt + 40);// Marche avant vitesse = 60+40
  if (distance <= 25) {
    vtt = 80;// vitesse =80
    MarcheAr(vtt); // Marche arrière vitesse = 80
    delay(200); 
    Stop();
    Baleyage.write(0);
    delay(1000);
    CalculDistance();
    distanceD = distance; // distance Droite
    Baleyage.write(180);
    delay(1000);
    CalculDistance();
    distanceG = distance; // distance Gauche
    Serial.print("distance G =");
    Serial.print(distanceG);
    Serial.print("distance D =");
    Serial.println(distanceD);
    Baleyage.write(90);
    delay(1000);

    if (distanceG > distanceD) {
      if (distanceG >= 50) {
        TourneG(vtt + 30);// tourne gauche vitesse = 60 + 30
        delay(tourna);//tourna = 1100
        TourneD(vtt);// tourne droite vitesse = 60
        delay(250);
        Stop();
      }
      else {
        MarcheAr(vtt);
        delay(1500);
        Stop();
        TourneG(vtt+40);//tourne gauche vitesse=60+40
        delay(1.5*tourna);//1100*1.5
        Stop();
      }
    } else   if (distanceD > distanceG) {
      if (distanceD >= 50) {
        TourneD(vtt + 30);//tourne droite vitesse=60+30
        delay(tourna);//tourna = 1100
        TourneG(vtt);//tourne gauche vitesse=60
        delay(250);
        Stop();
      }
      else {
        MarcheAr(vtt);//marche arrière vitesse=60
        delay(1500);
        Stop();
        TourneG(vtt+40);//tourne gauche vitesse=100
        delay(1.5*tourna);//1100*1.5
        Stop();
      }
    }
  }
}
