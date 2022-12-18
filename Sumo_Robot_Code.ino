// ----------- Sumo Robot Diamond Team Project ----------- //
// Arduino Project //

// Main UltraSonic Objects
#define echoPin 3
#define trigPin 4
long duration;
int distance;
int dis;

// IR Sensors Objects
#define IR1 7
#define IR2 9
#define IL1 12
#define IL2 13
byte R1;
byte R2;
byte L1;
byte L2;
// ------------------ The Place of Competition
// Black =1
// White =0

byte b=1;
byte w=0;

// ---------- Mots Objects ------------- //

// Mot1
#define mot1_1 6
#define mot1_2 5

// Mot2
#define mot2_1 10
#define mot2_2 11

// Important Variables
byte condition; // This Condition for Taking The Action Attacking or Safe you self
int diameter=80; // The Distance if you see it you will Go Forward it and Attacking
int count=0; // This Counter for Options about Orbiting about Markz Elseqal

void setup() {

// Main UltraSonic Pins
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
// IR Pins
pinMode(IR1,INPUT);
pinMode(IR2,INPUT);
pinMode(IL1,INPUT);
pinMode(IL2,INPUT);

// Mots Pins

// Right Motor
pinMode(mot1_1,OUTPUT);
pinMode(mot1_2,OUTPUT);

// Left Motor
pinMode(mot2_1,OUTPUT);
pinMode(mot2_2,OUTPUT);

// Stop Motors
stopMot();

// Time of the Competetion ( Mansoura Robotics )
delay(5000);
}

// IR Reading
byte IR()
{
R1 = digitalRead(IR1);
R2 = digitalRead(IR2);
L1 = digitalRead(IL1);
L2 = digitalRead(IL2);
// Check about IRs in Safe Place or not
if( (R1==w) || (R2==w) || (L1==w) || (L2==w) )
{
// Return with 0 For Putting Me in The Safe Place
return 0;
}
else
{
// Return with 1 For Attacking
return 1;
}
}

// ---------------------------- Make Your Robot in Safe Way ----------------------- //

void Safe()
{
// R1 Check
if(R1==w)
{
dis = ultra();
if(R2==w)
{
Mot2Stop();
Mot1Rev();
delay(250);
}
else if( (L1==w) && (dis<20) )
{
Mot1Forward();
Mot2Forward();
delay(250);
}
else if(L1==w)
{
Mot1Rev();
Mot2Rev();
delay(250);
}
else
{
Mot2Stop();
Mot1Rev();
delay(250);
}

}
// R2 Check
else if(R2==w) {
if(L2==w)
{
Mot1Forward();
Mot2Forward();
delay(250);
}
else
{
Mot1Forward();
Mot2Stop();
delay(250);
}

}
// L1 Check
else if(L1==w)
{
if(L2==w)
{
Mot2Forward();
Mot1Stop();
delay(250);
}
else
{
Mot2Rev();
Mot1Stop();
delay(250);
}
}
// L2 Check
else if(L2==w)
{
Mot1Stop();
Mot2Forward();
delay(250);
}

}

// ----------------------------- The End of Make Your Robot in Safe Way ------------------ ////////////

// ------------------------------------------- Mots Status ------------------------------------------------ //

//--------------------------- Mot 1 Status
void Mot1Forward()
{
digitalWrite(mot1_1,1);
digitalWrite(mot1_2,0);

}

void Mot1Rev()
{
digitalWrite(mot1_1,0);
digitalWrite(mot1_2,1);
}
void Mot1Stop()
{
digitalWrite(mot1_1,0);
digitalWrite(mot1_2,0);
}

//------------------------------------- Mot 2 Status
void Mot2Forward()
{
digitalWrite(mot2_1,1);
digitalWrite(mot2_2,0);

}

void Mot2Rev()
{
digitalWrite(mot2_1,0);
digitalWrite(mot2_2,1);
}
void Mot2Stop()
{
digitalWrite(mot2_1,0);
digitalWrite(mot2_2,0);
}

// --------------------------------------- Stop All Motors
void stopMot()
{
digitalWrite(mot1_1,0);
digitalWrite(mot1_2,0);

digitalWrite(mot2_1,0);
digitalWrite(mot2_2,0);
}

// ---------------------------------------------- End of Mot Status ---------------------------------------------- //

// ----------------------------------------------------- UltraSonics Code Reading ------------------------------------ //

//-------------------------- Main Ultrasonic Return With The Value in cm ---------------------- //
int ultra(){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration * 0.034 / 2;
// Distance in cm
return distance;
}

// ----------------------------------------- The End of The UltraSonics ------------------------------------------------ //

// -------------------------------- Start Main Repeat Code ------------------------------ //
void loop()
{
// IRs Reading
condition = IR();
// condition = 1 is For Attacking ---- condition = 0 is For Putting you in The Safe Place
if(condition==1)
{
// Check UltraSonic Before Attack
dis = ultra();
// Attack Only if The Condtion is True ^_^
if(dis<=diameter)
{
Mot1Forward();
Mot2Forward();
delay(250);
}

// Orbiting About Markz Elseql
else
{
count++;
while(1)
{
dis = ultra();
condition = IR();
// Start Options of Orbit
if(count%2==0)
{
Mot2Forward();
Mot1Rev();
}
else{
Mot1Forward();
Mot2Rev();
}
// End Options of Orbit

if( (dis<=diameter) || (condition==0) )
{
stopMot();
delay(500);
break;
}

}

}
}

else if (condition==0)
{
// Put Me in Safe Place
Safe();
}

}
// ------------------------------- End Main Repeat Code ----------------------------------- //
