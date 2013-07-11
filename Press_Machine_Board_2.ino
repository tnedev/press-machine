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





byte inPin_IzhMan_KraenIzklNach = 24;
byte inPin_IzhMan_KraenIzklKrai = 22;
byte inPin_IzhMan_ReperNach = 35;
byte inPin_IzhMan_ReperKrai = 33;
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
int man_speed_high = 4000; // The  high setting of the speed of the input manipulator [Hz of impulse]
int man_speed_low = 100; // The low setting of the speed of the input manipulator [Hz of impulse]
int current_speed=0; // sets the current speed of the manipulator
boolean initial = false; // is the program initialized
boolean man_dir ; // Direction of the manipulator

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

boolean in_VhMan_KraenIzklNach;
boolean in_VhMan_KraenIzklKrai;
boolean in_VhMan_ReperNach;
boolean in_VhMan_ReperKrai;



void setup()
{
	Serial.begin(9600);


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


	digitalWrite (inPin_IzhMan_KraenIzklNach, HIGH);
	digitalWrite (inPin_IzhMan_KraenIzklKrai, HIGH);
	digitalWrite (inPin_IzhMan_ReperNach, HIGH);
	digitalWrite (inPin_IzhMan_ReperKrai, HIGH);


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
	

}

void IzhManipulator()
/*
	This function operates the input manipulator of the system
*/
{
	
	
	
	if( ( in_IzhMan_ReperNach && current_speed == 0) ||(in_IzhMan_ReperKrai && current_speed == 0))
	{	// When the end switch and reper sensor are HIGH and the speed of the motor is 0, this calls for acceleration of the motor
		//man_dir = ~ man_dir; // change direction

               if(in_IzhMan_ReperNach==true)
                {
                  man_dir=false;
                }
                if(in_IzhMan_ReperKrai==true)
                 {
                  man_dir=true;
                }
      
            
                
		digitalWrite(outPin_IzhManipulator_PosokaMotor, man_dir);
		Acc_Motor();
                ReadSensors(); 
	}
	
	if((in_IzhMan_KraenIzklNach==true || in_IzhMan_KraenIzklKrai==true) && current_speed==man_speed_high )
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{        ReadSensors();
                  
	         if(in_IzhMan_KraenIzklKrai==true && man_dir==false)
                {
		    Dec_Motor();
                }
                if(in_IzhMan_KraenIzklNach==true  && man_dir==true)
                {
		    Dec_Motor();
                }
                
	}
	if((in_IzhMan_ReperNach==true || in_IzhMan_ReperKrai==true))
	{
		noTone(outPin_IzhManipulator_PulsMotor);
		current_speed=0;
                Serial.println("Speed is 0");
		delay(1000); // This is where work will happen - to delete
                ReadSensors();
	}

}

void Acc_Motor()
// Accelerate the motor
{
    int counter=0;
	int speed_steps = man_speed_high/400;
	for(int i=0; i<man_speed_high;i=i+speed_steps)
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
		delay(1);
                counter++;
	}
        Serial.println("Accelerate");
        Serial.println(counter);
	current_speed = man_speed_high;
}

void Dec_Motor()
// Decelerate the motor
{
  int counter=0;
  int i;
	int speed_steps = man_speed_high/300;
	for(i=man_speed_high; i>man_speed_low; (i=i-speed_steps))
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
                counter++;
		delay(1);
	}
	current_speed = man_speed_low;
        Serial.println(counter);
        Serial.println("Decelerate");
}
void ReadEmergency()
/*
	This function will block the operation of the production line while
	an emergency sensors is activated. The program reads all emergency sensors.
*/
{
}

void Initialize()
/*
	This function initialized the machine
*/
{
	
	digitalWrite(outPin_IzhManipulator_PosokaMotor,LOW);
	tone(outPin_IzhManipulator_PulsMotor, 500);
	while(in_IzhMan_ReperNach == false && in_IzhMan_ReperKrai == false)
	{
		ReadSensors();
	}
	noTone(outPin_IzhManipulator_PulsMotor);
	initial=true;
}
void loop()

{

  ReadSensors();
  Serial.print(in_IzhMan_ReperNach);
  Serial.print(in_IzhMan_KraenIzklNach);
  Serial.print(in_IzhMan_KraenIzklKrai);
  Serial.print(in_IzhMan_ReperKrai);
  
  Serial.print(in_VhMan_ReperNach);
  Serial.print(in_VhMan_KraenIzklNach);
  Serial.print(in_VhMan_KraenIzklKrai);
  Serial.print(in_VhMan_ReperKrai);
  Serial.println();



/*	if(initial==false)
		{
			Initialize();
                        Serial.println("Initialized");
		}
	ReadSensors();
        IzhManipulator();
*/

}