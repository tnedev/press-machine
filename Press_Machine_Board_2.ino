
/*
	This is control program for production line with press machine using Arduino Mega R3
	Last Updata Jul 2013
	Developed by Tihomir Nedev - nedev@chipolabs.com
	This code is for board 2 out of 2 bords for the control

	This board will be used to control the functions for the roller and the scissors 


*/

/*
	Arduino pins set up
	names formation - "inPin"/"outPin"+Function_name+ name
	The values links the pin number with the name
*/


byte inPin_IzhMan_KraenIzklNach = 33;
byte inPin_IzhMan_KraenIzkKrai = 35;
byte inPin_IzhMan_ReperNach = 22;
byte inPin_IzhMan_ReperKrai = 24;
byte inPin_IzhMan_GornoPolozhenie = 26;
byte inPin_IzhMan_DolnoPolozhenie = 29;

byte outPin_IzhManipulator_Gore = 30;
byte outPin_IzhManipulator_Dolu = 32;
byte outPin_IzhManipulator_Vakum = 34;
byte outPin_IzhManipulator_Vazduh = 36;
byte outPin_IzhManipulator_PosokaMotor = 38;
byte outPin_IzhManipulator_PulsMotor = 40;

byte inPin_Razmotalka_SenzorFolio1 = 42;
byte inPin_Razmotalka_SenzorFolio2 = 44;
byte inPin_Razmotalka_DatAkumFolio = 37;
byte inPin_Razmotalka_DatIzkonsumiranAkum = 39;
byte inPin_Razmotalka_DatKraiFolio = 46;
byte inPin_Razmotalka_NozhStart = 41;
byte inPin_Razmotalka_NozhStop = 43;
byte inPin_Razmotalka_ReadyServo = 52;
byte inPin_Razmotalka_ReadyNozh = 48;
byte inPin_Razmotalka_ReadyDisk = 50;

byte outPin_Razmotalka_GlavenMotor = 45;
byte outPin_Razmotalka_MotorVisSkorost = 47;
byte outPin_Razmotalka_MotorNisSkorost = 49;
byte outPin_Razmotalka_NozhicaOtiva = 51;
byte outPin_Razmotalka_NozhicaVrashta = 53;
byte outPin_Razmotalka_StartNozhicaDiskOtiva = 8;
byte outPin_Razmotalka_StartNozhicaDiskVrashta = 9;
byte outPin_Razmotalka_EnableSevo = 10;
byte outPin_Razmotalka_EnableNozh_Disc = 11;
byte outPin_Razmotalka_Vakum = 12;



/*
	Arduino variables declaration
	names formation - "input"/"output" + Function_name + name
*/
boolean in_IzhMan_KraenIzklNach = false;
boolean in_IzhMan_KraenIzklKrai = false;
boolean in_IzhMan_ReperNach = false;
boolean in_IzhMan_ReperKrai = false;
boolean in_IzhMan_GornoPolozhenie = false;
boolean in_IzhMan_DolnoPolozhenie = false;

boolean in_Razmotalka_SenzorFolio1 = false;
boolean in_Razmotalka_SenzorFolio2 = false;
boolean in_Razmotalka_DatAkumFolio = false;
boolean in_Razmotalka_DatIzkonsumiranAkum = false;
boolean in_Razmotalka_DatKraiFolio = false;
boolean in_Razmotalka_NozhStart = false;
boolean in_Razmotalka_NozhStop = false;
boolean in_Razmotalka_ReadyServo = false;
boolean in_Razmotalka_ReadyNozh = false;
boolean in_Razmotalka_ReadyDisk = false;



void setup()
{
	Serial.begin(9600);

  // Arduino pinmodes set up
  

	pinMode(inPin_IzhMan_KraenIzklNach,INPUT);
	pinMode(inPin_IzhMan_KraenIzkKrai,INPUT);
	pinMode(inPin_IzhMan_ReperNach,INPUT);
	pinMode(inPin_IzhMan_ReperKrai,INPUT);
	pinMode(inPin_IzhMan_GornoPolozhenie,INPUT);
	pinMode(inPin_IzhMan_DolnoPolozhenie,INPUT);

	pinMode(outPin_IzhManipulator_Gore,OUTPUT);
	pinMode(outPin_IzhManipulator_Dolu,OUTPUT);
	pinMode(outPin_IzhManipulator_Vakum,OUTPUT);
	pinMode(outPin_IzhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_IzhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_IzhManipulator_PulsMotor,OUTPUT);
  
	pinMode(inPin_Razmotalka_SenzorFolio1,INPUT);
	pinMode(inPin_Razmotalka_SenzorFolio2,INPUT);
	pinMode(inPin_Razmotalka_DatAkumFolio,INPUT);
	pinMode(inPin_Razmotalka_DatIzkonsumiranAkum,INPUT);
	pinMode(inPin_Razmotalka_DatKraiFolio,INPUT);
	pinMode(inPin_Razmotalka_NozhStart,INPUT);
	pinMode(inPin_Razmotalka_NozhStop,INPUT);
	pinMode(inPin_Razmotalka_ReadyServo,INPUT);
	pinMode(inPin_Razmotalka_ReadyNozh,INPUT);
	pinMode(inPin_Razmotalka_ReadyDisk,INPUT);

	pinMode(outPin_Razmotalka_GlavenMotor,OUTPUT);
	pinMode(outPin_Razmotalka_MotorVisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_MotorNisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDiskOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDiskVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_EnableSevo,OUTPUT);
	pinMode(outPin_Razmotalka_EnableNozh_Disc,OUTPUT);
	pinMode(outPin_Razmotalka_Vakum,OUTPUT);



}
void ReadSensors()
/*
	This function reads all the sensors the funcions on this board. 
	Used as a convinient way to read and store all values instead of 
	reading the sensors only in one function
*/
{
	in_IzhMan_KraenIzklNach = digitalRead(inPin_IzhMan_KraenIzklNach);
	in_IzhMan_KraenIzkKrai = digitalRead(inPin_IzhMan_KraenIzkKrai);
	in_IzhMan_ReperNach = digitalRead(inPin_IzhMan_ReperNach);
	in_IzhMan_ReperKrai = digitalRead(inPin_IzhMan_ReperKrai);
	in_IzhMan_GornoPolozhenie = digitalRead(inPin_IzhMan_GornoPolozhenie);
	in_IzhMan_DolnoPolozhenie = digitalRead(inPin_IzhMan_DolnoPolozhenie);

	in_Razmotalka_SenzorFolio1 = digitalRead(inPin_Razmotalka_SenzorFolio1);
	in_Razmotalka_SenzorFolio2 = digitalRead(inPin_Razmotalka_SenzorFolio2);
	in_Razmotalka_DatAkumFolio = digitalRead(inPin_Razmotalka_DatAkumFolio);
	in_Razmotalka_DatIzkonsumiranAkum = digitalRead(inPin_Razmotalka_DatIzkonsumiranAkum);
	in_Razmotalka_DatKraiFolio = digitalRead(inPin_Razmotalka_DatKraiFolio);
	in_Razmotalka_NozhStart = digitalRead(inPin_Razmotalka_NozhStart);
	in_Razmotalka_NozhStop = digitalRead(inPin_Razmotalka_NozhStop);
	in_Razmotalka_ReadyServo = digitalRead(inPin_Razmotalka_ReadyServo);
	in_Razmotalka_ReadyNozh = digitalRead(inPin_Razmotalka_ReadyNozh);
	in_Razmotalka_ReadyDisk = digitalRead(inPin_Razmotalka_ReadyDisk);



}
void ReadEmergency()
/*
	This function will block the operation of the production line while
	an emergency sensors is activated. The program reads all emergency sensors.
*/
{
}
void loop()
{

  /* add main program code here */

}