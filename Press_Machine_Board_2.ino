
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

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  
boolean in_IzhMan_KraenIzklNach;
boolean in_IzhMan_KraenIzklKrai;
boolean in_IzhMan_ReperNach;
boolean in_IzhMan_ReperKrai;

  
};
SEND_DATA_STRUCTURE mydata;


byte inPin_IzhMan_KraenIzklNach = 33;
byte inPin_IzhMan_KraenIzklKrai = 35;
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
	Arduino main variables declaration

*/


boolean material_podaden = false, presa_udarila = false, material_vzet = true; // values to link the logic of operation of the press and both manipulators
int man_speed_high = 2000; // The  high setting of the speed of the input manipulator [Hz of impulse]
int man_speed_low = 200; // The low setting of the speed of the input manipulator [Hz of impulse]
int current_speed=0; // sets the current speed of the manipulator

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
	 ET.begin(details(mydata), &Serial3);

  // Arduino pinmodes set up
  

	pinMode(inPin_IzhMan_KraenIzklNach,INPUT);
	pinMode(inPin_IzhMan_KraenIzklKrai,INPUT);
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
	in_IzhMan_KraenIzklKrai = digitalRead(inPin_IzhMan_KraenIzklKrai);
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

	mydata.in_IzhMan_KraenIzklNach = in_IzhMan_KraenIzklNach;
	mydata.in_IzhMan_KraenIzklKrai = in_IzhMan_KraenIzklKrai;
	mydata.in_IzhMan_ReperNach = in_IzhMan_ReperNach;
	mydata.in_IzhMan_ReperKrai = in_IzhMan_ReperKrai;
	
	ET.sendData();


}

void IzhManipulator()
/*
	This function operates the input manipulator of the system
*/
{
	
	boolean man_dir = false; // Direction of the manipulator
	
	if( (in_IzhMan_KraenIzklNach && in_IzhMan_ReperNach && current_speed == 0) ||(in_IzhMan_KraenIzklKrai && in_IzhMan_ReperKrai && current_speed==0))
	{	// When the end switch and reper sensor are HIGH and the speed of the motor is 0, this calls for acceleration of the motor
		man_dir = ~ man_dir; // change direction
		digitalWrite(outPin_IzhManipulator_PosokaMotor, man_dir);
		Acc_Motor();
	}
	
	if((in_IzhMan_KraenIzklNach || in_IzhMan_KraenIzklKrai) && current_speed>man_speed_low )
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{
		Dec_Motor();
	}
	if(in_IzhMan_ReperNach || in_IzhMan_ReperKrai)
	{
		noTone(outPin_IzhManipulator_PulsMotor);
		current_speed=0;
		delay(3000); // This is where work will happen - to delete
	}
}

void Acc_Motor()
// Accelerate the motor
{
	int speed_steps = man_speed_high/500;
	for(int i=0; i>=man_speed_high;i=i+speed_steps)
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
		delay(1);
	}
	current_speed = man_speed_high;
}

void Dec_Motor()
// Decelerate the motor
{
	int speed_steps = man_speed_high/500;
	for(int i=man_speed_high; i<=man_speed_low;i=i-speed_steps)
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
		delay(1);
	}
	current_speed = man_speed_low;
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

  ReadSensors();

}