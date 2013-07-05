
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
byte inPin_IzhMan_KraenIzklNach = 38;
byte inPin_IzhMan_KraenIzklKrai = 39;
byte inPin_IzhMan_Reper = 40;
byte inPin_IzhMan_GornoPolozhenie = 41;
byte inPin_IzhMan_DolnoPolozhenie = 42;

byte outPin_IzhManipulator_Gore = 43;
byte outPin_IzhManipulator_Dolu = 48;
byte outPin_IzhManipulator_Vakum = 45;
byte outPin_IzhManipulator_Vazduh = 46;
byte outPin_IzhManipulator_PosokaMotor = 47;
byte outPin_IzhManipulator_PulsMotor = 45;

byte inPin_Razmotalka_SenzorFolio1 = 14;
byte inPin_Razmotalka_SenzorFolio2 = 15;
byte inPin_Razmotalka_DatAkumFolio = 16;
byte inPin_Razmotalka_DatIzkonsumiranAkum = 17;
byte inPin_Razmotalka_DatKraiFolio = 18;
byte inPin_Razmotalka_NozhStart = 19;
byte inPin_Razmotalka_NozhStop = 20;
byte inPin_Razmotalka_MotorAvaria = 21;

byte outPin_Razmotalka_GlavenMotor = 22;
byte outPin_Razmotalka_MotorVisSkorost = 23;
byte outPin_Razmotalka_MotorNisSkorost = 24;
byte outPin_Razmotalka_NozhicaOtiva = 25;
byte outPin_Razmotalka_NozhicaVrashta = 26;
byte outPin_Razmotalka_StartNozhicaDisk = 27;
byte outPin_Razmotalka_Vakum = 28;

byte inPin_Nozhica_GornoPolozh = 29;
byte inPin_Nozhica_DolnoPolozh = 30;

byte outPin_Nozhica_MasaGore = 31;
byte outPin_Nozhica_Nozhici1Napred = 32;
byte outPin_Nozhica_Nozhici2Napred = 34;
byte outPin_Nozhica_Nozhici1Nazad = 33;
byte outPin_Nozhica_Nozhici2Nazad = 35;
byte outPin_Nozhica_Motori1Disk =  36;
byte outPin_Nozhica_Motori2Disk = 37;

/*
	Arduino variables declaration
	names formation - "input"/"output" + Function_name + name
*/
boolean in_IzhMan_KraenIzklNach = false;
boolean in_IzhMan_KraenIzklKrai = false;
boolean in_IzhMan_Reper = false;
boolean in_IzhMan_GornoPolozhenie = false;
boolean in_IzhMan_DolnoPolozhenie = false;
boolean in_IzhMan_Material = false;

boolean in_Razmotalka_SenzorFolio1 = false;
boolean in_Razmotalka_SenzorFolio2 = false;
boolean in_Razmotalka_DatAkumFolio = false;
boolean in_Razmotalka_DatIzkonsumiranAkum = false;
boolean in_Razmotalka_DatKraiFolio = false;
boolean in_Razmotalka_NozhStart = false;
boolean in_Razmotalka_NozhStop = false;
boolean in_Razmotalka_MotorAvaria = false;

boolean in_Nozhica_GornoPolozh = false;
boolean in_Nozhica_DolnoPolozh = false;

void setup()
{
	Serial.begin(9600);

  // Arduino pinmodes set up
  

	pinMode(inPin_IzhMan_KraenIzklNach,INPUT);
	pinMode(inPin_IzhMan_KraenIzklKrai,INPUT);
	pinMode(inPin_IzhMan_Reper,INPUT);
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
	pinMode(inPin_Razmotalka_MotorAvaria,INPUT);

	pinMode(outPin_Razmotalka_GlavenMotor,OUTPUT);
	pinMode(outPin_Razmotalka_MotorVisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_MotorNisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDisk,OUTPUT);
	pinMode(outPin_Razmotalka_Vakum,OUTPUT);

	pinMode(inPin_Nozhica_GornoPolozh,INPUT);
	pinMode(inPin_Nozhica_DolnoPolozh,INPUT);

	pinMode(outPin_Nozhica_MasaGore,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici1Napred,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici2Napred,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici1Nazad,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici2Nazad,OUTPUT);
	pinMode(outPin_Nozhica_Motori1Disk,OUTPUT);
	pinMode(outPin_Nozhica_Motori2Disk,OUTPUT);

}
void ReadSensors()
/*
	This function reads all the sensors the funcions on this board. 
	Used as a convinient way to read and store all values instead of 
	reading the sensors only in one function
*/
{
	in_IzhMan_KraenIzklNach = digitalRead(inPin_IzhMan_KraenIzklNach);
	in_IzhMan_KraenIzklKrai = digitalRead(inPin_IzhMan_KraenIzklKrai);
	in_IzhMan_Reper = digitalRead(inPin_IzhMan_Reper);
	in_IzhMan_GornoPolozhenie = digitalRead(inPin_IzhMan_GornoPolozhenie);
	in_IzhMan_DolnoPolozhenie = digitalRead(inPin_IzhMan_DolnoPolozhenie);

	in_Razmotalka_SenzirFolio1 = digitalRead(inPin_Razmotalka_SenzorFolio1);
	in_Razmotalka_SenzorFolio2  = digitalRead(inPin_Razmotalka_SenzorFolio2);
	in_Razmotalka_DatAkumFolio  = digitalRead(inPin_Razmotalka_DatAkumFolio);
	in_Razmotalka_DatIzkonsumiranAkum  = digitalRead(inPin_Razmotalka_DatIzkonsumiranAkum);
	in_Razmotalka_DatKraiFolio  = digitalRead(inPin_Razmotalka_DatKraiFolio);
	in_Razmotalka_NozhStart  = digitalRead(inPin_Razmotalka_NozhStart);
	in_Razmotalka_NozhStop  = digitalRead(inPin_Razmotalka_NozhStop);
	in_Razmotalka_MotorAvaria  = digitalRead(inPin_Razmotalka_MotorAvaria);

	in_Nozhica_GornoPolozh  = digitalRead(inPin_Nozhica_GornoPolozh);
	in_Nozhica_DolnoPolozh  = digitalRead(inPin_Nozhica_DolnoPolozh);

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