/*
	This is control program for production line with press machine using Arduino Mega R3
	Last Updata Jul 2013
	Developed by Tihomir Nedev - nedev@chipolabs.com
	This Code is for board 1 out of 2 bords for the control 

	With this board we will control the functions of the Press, Container and both manipulators
	All variables are main variables, there are no local variables for a function

*/

/*
	Arduino pins set up
	names formation - "inPin"/"outPin"+Function_name+ name
	The values links the pin number with the name
*/


byte inPin_Presa_KraenIzklGoren = 23;
byte inPin_Presa_KraenIzklDolen = 25;
byte inPin_Presa_AvariaGlavenMotor = 22;

byte outPin_Presa_Nagore = 26;
byte outPin_Presa_Nadolu = 28;
byte outPin_Presa_Vakum = 30;
byte outPin_Presa_Vazduh = 32;


byte inPin_Konteiner_KrainIzklDolen = 27;
byte inPin_Konteiner_Nivo = 34;
byte inPin_Konteiner_MotorAvaria = 36;

byte outPin_Konteiner_CilindarGore = 38;
byte outPin_Konteiner_CilindarDolu = 40;


byte inPin_VhMan_KraenIzklNach = 29;
byte inPin_VhMan_KraenIzkKrai = 31;
byte inPin_VhMan_ReperNach = 42;
byte inPin_VhMan_ReperKrai = 44;
byte inPin_VhMan_GornoPolozhenie = 46;
byte inPin_VhMan_DolnoPolozhenie = 48;

byte outPin_VhManipulator_Gore = 50;
byte outPin_VhManipulator_Dolu = 52;
byte outPin_VhManipulator_Vakum = 37;
byte outPin_VhManipulator_Vazduh = 39;
byte outPin_VhManipulator_PosokaMotor = 41;
byte outPin_VhManipulator_PulsMotor = 43;

byte inPin_Nozhica_GornoPolozh = 33;
byte inPin_Nozhica_DolnoPolozh = 35;
byte inPin_Nozhica_Ready1_1 = 45;
byte inPin_Nozhica_Ready1_2 = 47;
byte inPin_Nozhica_Ready2_1 = 49;
byte inPin_Nozhica_Ready2_2 = 51;
byte inPin_Nozhica_Ready2_2 = 53;

byte outPin_Nozhica_MasaGore = 53;
byte outPin_Nozhica_Nozhici1 = 9;
byte outPin_Nozhica_Nozhici2 = 10;
byte outPin_Nozhica_Butalo1 = 11;
byte outPin_Nozhica_Butalo2 = 12;
byte outPin_Nozhica_EnableNozh = 13;




/*
	Arduino main variables declaration

*/
boolean emergency = false; // Used to stop the system if there is an emegency
int pressureThreshold = 0; // Set the pressure threshold for the press. How much the press has to press. 
boolean presa_nagore = false, presa_nadolu = false; // Sets the direction of the press



/*
	Arduino variables declaration
	names formation - "in"/"out" + Function_name + name
*/

int in_Presa_Pressure;
boolean in_Presa_KraenIzklGoren = false;
boolean in_Presa_KraenIzklDolen = false;
boolean in_Presa_AvariaGlavenMotor = false;

boolean in_Konteiner_KrainIzklDolen = false;
boolean in_Konteiner_Nivo = false;
boolean in_Konteiner_MotorAvaria = false;

boolean in_VhMan_KraenIzklNach = false;
boolean in_VhMan_KraenIzklKrai = false;
boolean in_VhMan_ReperNach = false;
boolean in_VhMan_ReperKrai = false;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;

boolean in_Nozhica_GornoPolozh = false;
boolean in_Nozhica_DolnoPolozh = false;



void setup()
{

	Serial.begin(9600);
  // Arduino pinmodes set up
	pinMode(A0,INPUT); // Pressure sensor
	pinMode(inPin_Presa_KraenIzklGoren,INPUT);
	pinMode(inPin_Presa_KraenIzklDolen,INPUT);
	pinMode(inPin_Presa_AvariaGlavenMotor,INPUT);

	pinMode(outPin_Presa_Nagore,OUTPUT);
	pinMode(outPin_Presa_Nadolu,OUTPUT);
	pinMode(outPin_Presa_Vakum,OUTPUT);
	pinMode(outPin_Presa_Vazduh,OUTPUT);

	pinMode(inPin_Konteiner_KrainIzklDolen,INPUT);
	pinMode(inPin_Konteiner_Nivo,INPUT);
	pinMode(inPin_Konteiner_MotorAvaria,INPUT);

	pinMode(outPin_Konteiner_CilindarGore,INPUT);
	pinMode(outPin_Konteiner_CilindarDolu,INPUT);


	pinMode(inPin_VhMan_KraenIzklNach,INPUT);
	pinMode(inPin_VhMan_KraenIzkKrai,INPUT);
	pinMode(inPin_VhMan_ReperNach,INPUT);
	pinMode(inPin_VhMan_ReperKrai,INPUT);
	pinMode(inPin_VhMan_GornoPolozhenie,INPUT);
	pinMode(inPin_VhMan_DolnoPolozhenie,INPUT);

	pinMode(outPin_VhManipulator_Gore,OUTPUT);
	pinMode(outPin_VhManipulator_Dolu,OUTPUT);
	pinMode(outPin_VhManipulator_Vakum,OUTPUT);
	pinMode(outPin_VhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_VhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_VhManipulator_PulsMotor,OUTPUT);

	pinMode(inPin_Nozhica_GornoPolozh,INPUT);
	pinMode(inPin_Nozhica_DolnoPolozh,INPUT);
	pinMode(inPin_Nozhica_Ready1_1,INPUT);
	pinMode(inPin_Nozhica_Ready1_2,INPUT);
	pinMode(inPin_Nozhica_Ready2_1,INPUT);
	pinMode(inPin_Nozhica_Ready2_2,INPUT);
	pinMode(inPin_Nozhica_Ready2_2,INPUT);

	pinMode(outPin_Nozhica_MasaGore,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici1,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici2,OUTPUT);
	pinMode(outPin_Nozhica_Butalo1,OUTPUT);
	pinMode(outPin_Nozhica_Butalo2,OUTPUT);
	pinMode(outPin_Nozhica_EnableNozh,OUTPUT);

}

void ReadSensors()
/*
	This function reads all the sensors the funcions on this board. 
	Used as a convinient way to read and store all values instead of 
	reading the sensors only in one function
*/

{
	in_Presa_Pressure = analogRead(A0);
	in_Presa_KraenIzklGoren = digitalRead(inPin_Presa_KraenIzklGoren);
	in_Presa_KraenIzklDolen = digitalRead(inPin_Presa_KraenIzklDolen);
	in_Presa_AvariaGlavenMotor = digitalRead(inPin_Presa_AvariaGlavenMotor);

	in_Konteiner_KrainIzklDolen = digitalRead(inPin_Konteiner_KrainIzklDolen);
	in_Konteiner_Nivo = digitalRead(inPin_Konteiner_Nivo);
	in_Konteiner_MotorAvaria = digitalRead(inPin_Konteiner_MotorAvaria);
	
	in_VhMan_KraenIzklNach = digitalRead(inPin_VhMan_KraenIzklNach);
	in_VhMan_KraenIzkKrai = digitalRead(inPin_VhMan_KraenIzkKrai);
	in_VhMan_ReperNach = digitalRead(inPin_VhMan_ReperNach);
	in_VhMan_ReperKrai = digitalRead(inPin_VhMan_ReperKrai);
	in_VhMan_GornoPolozhenie = digitalRead(inPin_VhMan_GornoPolozhenie);
	in_VhMan_DolnoPolozhenie = digitalRead(inPin_VhMan_DolnoPolozhenie);
	
	in_Nozhica_GornoPolozh = digitalRead(inPin_Nozhica_GornoPolozh);
	inP_Nozhica_DolnoPolozh = digitalRead(inPin_Nozhica_DolnoPolozh);
	in_Nozhica_Ready1_1 = digitalRead(inPin_Nozhica_Ready1_1);
	in_Nozhica_Ready1_2 = digitalRead(inPin_Nozhica_Ready1_2);
	in_Nozhica_Ready2_1 = digitalRead(inPin_Nozhica_Ready2_1);
	in_Nozhica_Ready2_2 = digitalRead(inPin_Nozhica_Ready2_2);
	in_Nozhica_Ready2_2 = digitalRead(inPin_Nozhica_Ready2_2);

}

void Press()
/*
	This function operates the press module on the production line
*/
{

	if(in_Presa_AvariaGlavenMotor==LOW) // Is there an emergency in the press
	{ // Main function of the press
		if(in_Presa_KraenIzklGoren == false && in_Presa_KraenIzklDolen == true) // If the press is at up position start going down
		{
			presa_nadolu = 1;
			presa_nagore = 0;
		}
		else if(in_Presa_KraenIzklGoren == true && in_Presa_KraenIzklDolen == false && in_Presa_Pressure >= pressureThreshold) // If the press is down start going up
		{
                        presa_nagore = 1;
			presa_nadolu = 0;
			
		}

		else if (presa_nagore==false && presa_nadolu==false )
		{
			presa_nagore = true;
                        
		}

		if(presa_nadolu==true && presa_nagore==false)// Start moving the press down
		{
			digitalWrite(outPin_Presa_Nagore, LOW);
			digitalWrite(outPin_Presa_Nadolu, HIGH);
		}
		 else if(presa_nadolu==false && presa_nagore==true) // Start moving the press up
		{
			digitalWrite(outPin_Presa_Nadolu, LOW);
			digitalWrite(outPin_Presa_Nagore, HIGH);
		}
		else 
		{
			Serial.println("Presa_Nagore and Presa_Nadolu are not correct");
		}


	}
	else
	{
		Serial.println("Emergency stop at the the press");
		emergency = HIGH;
	}

}

void Konteiner()
/*
	This function operates the press module on the production line
*/
{



}

void ReadEmergency()
/*
	This function will block the operation of the production line while
	an emergency sensors is activated. The program reads all emergency sensors.
*/
{	
	ReadSensors();
	if(in_Presa_AvariaGlavenMotor == LOW &&
		in_Konteiner_MotorAvaria == LOW
		
	
	)
	{
		emergency = LOW;
	}
}

void loop()
{
	if(emergency==LOW) // Operate the production line if there is no emergency
	{ // Main loop function for normal operation
	
		ReadSensors();
		Press();
		
	}
	
	else // There was an emegency, this should be fixed before the program continues
	{
		Serial.write("Please fix the emergency before proceeding");
		while(emergency)
		{
			ReadEmergency();
		}
	}

}
