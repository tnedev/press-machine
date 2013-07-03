
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

byte inPin_Razmotalka_DatFolio = 45;
byte inPin_Razmotalka_SenzorFolio = 46;
byte inPin_Razmotalka_DatAkumFolio = 47;
byte inPin_Razmotalka_DatIzkonsumiranAkum = 48;
byte inPin_Razmotalka_DatKraiFolio = 49;
byte inPin_Razmotalka_NozhStart = 50;
byte inPin_Razmotalka_NozhStop = 51;
byte inPin_Razmotalka_MotorVkl = 52;
byte inPin_Razmotalka_MotorAvaria = 53;

byte outPin_Razmotalka_GlavenMotor = 54;
byte outPin_Razmotalka_MotorVisSkorost = 55;
byte outPin_Razmotalka_MotorNisSkorost = 56;
byte outPin_Razmotalka_NozhicaOtiva = 57;
byte outPin_Razmotalka_NozhicaVrashta = 58;
byte outPin_Razmotalka_StartNozhicaDisk = 59;
byte outPin_Razmotalka_Vakum = 60;

byte inPin_Nozhica_List = 61;
byte inPin_Nozhica_GornoPolozh = 62;
byte inPin_Nozhica_DolnoPolozh = 63;

byte outPin_Nozhica_MasaGore = 64;
byte outPin_Nozhica_Nozhici1Napred = 65;
byte outPin_Nozhica_Nozhici2Napred = 66;
byte outPin_Nozhica_Nozhici1Nazad = 67;
byte outPin_Nozhica_Nozhici2Nazad = 68;
byte outPin_Nozhica_Motori1Disk = 69;
byte outPin_Nozhica_Motori2Disk = 70;

/*
	Arduino variables declaration
	names formation - "input"/"output" + Function_name + name
*/

boolean in_Razmotalka_DatFolio = false;
boolean in_Razmotalka_SenzorFolio = false;
boolean in_Razmotalka_DatAkumFolio = false;
boolean in_Razmotalka_DatIzkonsumiranAkum = false;
boolean in_Razmotalka_DatKraiFolio = false;
boolean in_Razmotalka_NozhStart = false;
boolean in_Razmotalka_NozhStop = false;
boolean in_Razmotalka_MotorVkl = false;
boolean in_Razmotalka_MotorAvaria = false;

boolean out_Razmotalka_GlavenMotor = false;
boolean out_Razmotalka_MotorVisSkorost = false;
boolean out_Razmotalka_MotorNisSkorost = false;
boolean out_Razmotalka_NozhicaOtiva = false;
boolean out_Razmotalka_NozhicaVrashta = false;
boolean out_Razmotalka_StartNozhicaDisk = false;
boolean out_Razmotalka_Vakum = false;

boolean in_Nozhica_List = false;
boolean in_Nozhica_GornoPolozh = false;
boolean in_Nozhica_DolnoPolozh = false;

boolean out_Nozhica_MasaGore = false;
boolean out_Nozhica_Nozhici1Napred = false;
boolean out_Nozhica_Nozhici2Napred = false;
boolean out_Nozhica_Nozhici1Nazad = false;
boolean out_Nozhica_Nozhici2Nazad = false;
boolean out_Nozhica_Motori1Disk = false;
boolean out_Nozhica_Motori2Disk = false;

void setup()
{

  // Arduino pinmodes set up
	pinMode(inPin_Razmotalka_DatFolio,INPUT);
	pinMode(inPin_Razmotalka_SenzorFolio,INPUT);
	pinMode(inPin_Razmotalka_DatAkumFolio,INPUT);
	pinMode(inPin_Razmotalka_DatIzkonsumiranAkum,INPUT);
	pinMode(inPin_Razmotalka_DatKraiFolio,INPUT);
	pinMode(inPin_Razmotalka_NozhStart,INPUT);
	pinMode(inPin_Razmotalka_NozhStop,INPUT);
	pinMode(inPin_Razmotalka_MotorVkl,INPUT);
	pinMode(inPin_Razmotalka_MotorAvaria,INPUT);

	pinMode(outPin_Razmotalka_GlavenMotor,OUTPUT);
	pinMode(outPin_Razmotalka_MotorVisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_MotorNisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDisk,OUTPUT);
	pinMode(outPin_Razmotalka_Vakum,OUTPUT);

	pinMode(inPin_Nozhica_List,INPUT);
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

void loop()
{

  /* add main program code here */

}