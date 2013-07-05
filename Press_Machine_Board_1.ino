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


byte inPin_Presa_KraenIzklGoren = 2;
byte inPin_Presa_KraenIzklDolen = 3;
byte inPin_Presa_AvariaGlavenMotor = 4;

byte outPin_Presa_Nagore = 5;
byte outPin_Presa_Nadolu = 6;
byte outPin_Presa_Vakum = 7;
byte outPin_Presa_Vazduh = 8;


byte inPin_Konteiner_KrainIzklDolen = 26;
byte inPin_Konteiner_Nivo = 27;
byte inPin_Konteiner_MotorAvaria = 28;

byte outPin_Konteiner_CilindarGore = 29;
byte outPin_Konteiner_CilindarDolu = 30;


byte inPin_VhMan_KraenIzklNach = 14;
byte inPin_VhMan_KraenIzkKrai = 15;
byte inPin_VhMan_Reper = 16;
byte inPin_VhMan_GornoPolozhenie = 17;
byte inPin_VhMan_DolnoPolozhenie = 20;

byte outPin_VhManipulator_Gore = 21;
byte outPin_VhManipulator_Dolu = 22;
byte outPin_VhManipulator_Vakum = 23;
byte outPin_VhManipulator_Vazduh = 24;
byte outPin_VhManipulator_PosokaMotor = 25;
byte outPin_VhManipulator_PulsMotor = 45;




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
boolean in_VhMan_Reper = false;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;



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
	pinMode(inPin_VhMan_Reper,INPUT);
	pinMode(inPin_VhMan_GornoPolozhenie,INPUT);
	pinMode(inPin_VhMan_DolnoPolozhenie,INPUT);

	pinMode(outPin_VhManipulator_Gore,OUTPUT);
	pinMode(outPin_VhManipulator_Dolu,OUTPUT);
	pinMode(outPin_VhManipulator_Vakum,OUTPUT);
	pinMode(outPin_VhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_VhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_VhManipulator_PulsMotor,OUTPUT);


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
	in_VhMan_KraenIzklKrai = (inPin_VhMan_KraenIzkKrai);
	in_VhMan_Reper = digitalRead(inPin_VhMan_Reper);
	in_VhMan_GornoPolozhenie = digitalRead(inPin_VhMan_GornoPolozhenie);
	in_VhMan_DolnoPolozhenie = digitalRead(inPin_VhMan_DolnoPolozhenie);


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

	if(in_Konteiner_MotorAvaria==LOW) // Is there an emergency in the container
	{ 
		
	}
	else
	{
		Serial.write("Emergency stop at the the container");
		emergency = HIGH;
	}

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
