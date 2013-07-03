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
byte inPin_Presa_VhStrana = 4;
byte inPin_Presa_IzhStrana = 5;
byte inPin_Presa_VklGlavenMoror = 6;
byte inPin_Presa_AvariaGlavenMotor = 7;

byte outPin_Presa_Nagore = 8;
byte outPin_Presa_Nadolu = 9;
byte outPin_Presa_Vakum = 10;
byte outPin_Presa_Vazduh = 11;


byte inPin_Konteiner_KrainIzklGoren = 12;
byte inPin_Konteiner_KrainIzklDolen = 13;
byte inPin_Konteiner_Nivo = 14;
byte inPin_Konteiner_MotorRaboti = 15;
byte inPin_Konteiner_MotorAvaria = 16;
byte inPin_Konteiner_BroyachPresa = 17;
byte inPin_Konteiner_Material = 18;

byte outPin_Konteiner_CilindarGore = 19;
byte outPin_Konteiner_CilindarDolu = 20;


byte inPin_VhMan_KraenIzklGoren = 21;
byte inPin_VhMan_KraenIzklDolen = 22;
byte inPin_VhMan_Reper = 23;
byte inPin_VhMan_GornoPolozhenie = 24;
byte inPin_VhMan_DolnoPolozhenie = 25;
byte inPin_VhMan_Material = 26;

byte outPin_VhManipulator_Gore = 27;
byte outPin_VhManipulator_Dolu = 28;
byte outPin_VhManipulator_Vakum = 29;
byte outPin_VhManipulator_Vazduh = 30;
byte outPin_VhManipulator_PosokaMotor = 31;
byte outPin_VhManipulator_PulsMotor = 32;


byte inPin_IzhMan_KraenIzklGoren = 33;
byte inPin_IzhMan_KraenIzklDolen = 34;
byte inPin_IzhMan_Reper = 35;
byte inPin_IzhMan_GornoPolozhenie = 36;
byte inPin_IzhMan_DolnoPolozhenie = 37;
byte inPin_IzhMan_Material = 38;

byte outPin_IzhManipulator_Gore = 39;
byte outPin_IzhManipulator_Dolu = 40;
byte outPin_IzhManipulator_Vakum = 41;
byte outPin_IzhManipulator_Vazduh = 42;
byte outPin_IzhManipulator_PosokaMotor = 43;
byte outPin_IzhManipulator_PulsMotor = 44;

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
boolean in_Presa_VhStrana = false;
boolean in_Presa_IzhStrana = false;
boolean in_Presa_VklGlavenMoror = false;
boolean in_Presa_AvariaGlavenMotor = false;

boolean in_Konteiner_KrainIzklGoren = false;
boolean in_Konteiner_KrainIzklDolen = false;
boolean in_Konteiner_Nivo = false;
boolean in_Konteiner_MotorRaboti = false;
boolean in_Konteiner_MotorAvaria = false;
boolean in_Konteiner_BroyachPresa = false;
boolean in_Konteiner_Material = false;

boolean in_VhMan_KraenIzklGoren = false;
boolean in_VhMan_KraenIzklDolen = false;
boolean in_VhMan_Reper = false;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;
boolean in_VhMan_Material = false;

boolean in_IzhMan_KraenIzklGoren = false;
boolean in_IzhMan_KraenIzklDolen = false;
boolean in_IzhMan_Reper = false;
boolean in_IzhMan_GornoPolozhenie = false;
boolean in_IzhMan_DolnoPolozhenie = false;
boolean in_IzhMan_Material = false;


void setup()
{

	Serial.begin(9600);
  // Arduino pinmodes set up
	pinMode(A0,INPUT); // Pressure sensor
	pinMode(inPin_Presa_KraenIzklGoren,INPUT);
	pinMode(inPin_Presa_KraenIzklDolen,INPUT);
	pinMode(inPin_Presa_VhStrana,INPUT);
	pinMode(inPin_Presa_IzhStrana,INPUT);
	pinMode(inPin_Presa_VklGlavenMoror,INPUT);
	pinMode(inPin_Presa_AvariaGlavenMotor,INPUT);

	pinMode(outPin_Presa_Nagore,OUTPUT);
	pinMode(outPin_Presa_Nadolu,OUTPUT);
	pinMode(outPin_Presa_Vakum,OUTPUT);
	pinMode(outPin_Presa_Vazduh,OUTPUT);

	pinMode(inPin_Konteiner_KrainIzklGoren,INPUT);
	pinMode(inPin_Konteiner_KrainIzklDolen,INPUT);
	pinMode(inPin_Konteiner_Nivo,INPUT);
	pinMode(inPin_Konteiner_MotorRaboti,INPUT);
	pinMode(inPin_Konteiner_MotorAvaria,INPUT);
	pinMode(inPin_Konteiner_BroyachPresa,INPUT);
	pinMode(inPin_Konteiner_Material,INPUT);

	pinMode(outPin_Konteiner_CilindarGore,INPUT);
	pinMode(outPin_Konteiner_CilindarDolu,INPUT);


	pinMode(inPin_VhMan_KraenIzklGoren,INPUT);
	pinMode(inPin_VhMan_KraenIzklDolen,INPUT);
	pinMode(inPin_VhMan_Reper,INPUT);
	pinMode(inPin_VhMan_GornoPolozhenie,INPUT);
	pinMode(inPin_VhMan_DolnoPolozhenie,INPUT);
	pinMode(inPin_VhMan_Material,INPUT);

	pinMode(outPin_VhManipulator_Gore,OUTPUT);
	pinMode(outPin_VhManipulator_Dolu,OUTPUT);
	pinMode(outPin_VhManipulator_Vakum,OUTPUT);
	pinMode(outPin_VhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_VhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_VhManipulator_PulsMotor,OUTPUT);


	pinMode(inPin_IzhMan_KraenIzklGoren,INPUT);
	pinMode(inPin_IzhMan_KraenIzklDolen,INPUT);
	pinMode(inPin_IzhMan_Reper,INPUT);
	pinMode(inPin_IzhMan_GornoPolozhenie,INPUT);
	pinMode(inPin_IzhMan_DolnoPolozhenie,INPUT);
	pinMode(inPin_IzhMan_Material,INPUT);

	pinMode(outPin_IzhManipulator_Gore,OUTPUT);
	pinMode(outPin_IzhManipulator_Dolu,OUTPUT);
	pinMode(outPin_IzhManipulator_Vakum,OUTPUT);
	pinMode(outPin_IzhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_IzhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_IzhManipulator_PulsMotor,OUTPUT);


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
	in_Presa_VhStrana = digitalRead(inPin_Presa_VhStrana);
	in_Presa_IzhStrana = digitalRead(inPin_Presa_IzhStrana);
	in_Presa_VklGlavenMoror = digitalRead(inPin_Presa_VklGlavenMoror);
	in_Presa_AvariaGlavenMotor = digitalRead(inPin_Presa_AvariaGlavenMotor);

	in_Konteiner_KrainIzklGoren = digitalRead(inPin_Konteiner_KrainIzklGoren);
	in_Konteiner_KrainIzklDolen = digitalRead(inPin_Konteiner_KrainIzklDolen);
	in_Konteiner_Nivo = digitalRead(inPin_Konteiner_Nivo);
	in_Konteiner_MotorRaboti = digitalRead(inPin_Konteiner_MotorRaboti);
	in_Konteiner_MotorAvaria = digitalRead(inPin_Konteiner_MotorAvaria);
	in_Konteiner_BroyachPresa = digitalRead(inPin_Konteiner_BroyachPresa);
	in_Konteiner_Material = digitalRead(inPin_Konteiner_Material);
	
	in_VhMan_KraenIzklGoren = digitalRead(inPin_VhMan_KraenIzklGoren);
	in_VhMan_KraenIzklDolen = (inPin_VhMan_KraenIzklDolen);
	in_VhMan_Reper = digitalRead(inPin_VhMan_Reper);
	in_VhMan_GornoPolozhenie = digitalRead(inPin_VhMan_GornoPolozhenie);
	in_VhMan_DolnoPolozhenie = digitalRead(inPin_VhMan_DolnoPolozhenie);
	in_VhMan_Material = digitalRead(inPin_VhMan_Material);

	in_IzhMan_KraenIzklGoren = digitalRead(inPin_IzhMan_KraenIzklGoren);
	in_IzhMan_KraenIzklDolen = digitalRead(inPin_IzhMan_KraenIzklDolen);
	in_IzhMan_Reper = digitalRead(inPin_IzhMan_Reper);
	in_IzhMan_GornoPolozhenie = digitalRead(inPin_IzhMan_GornoPolozhenie);
	in_IzhMan_DolnoPolozhenie = digitalRead(inPin_IzhMan_DolnoPolozhenie);
	in_IzhMan_Material = digitalRead(inPin_IzhMan_Material);


}

void Press()
/*
	This function operates the press module on the production line
*/
{

	if(in_Presa_AvariaGlavenMotor==LOW) // Is there an emergency in the press
	{
		if (in_Presa_VklGlavenMoror) // Is the main motor of the press functioning
		// There is no emergency and the motor is working, start the normal operation of the press
		{
			if(	in_Presa_VhStrana == LOW && in_Presa_IzhStrana == LOW) // Check if manipulators are on the way of the press
			{
				if(in_Presa_KraenIzklGoren==true && in_Presa_KraenIzklDolen==false)
				{
					presa_nadolu = true; // the press should move down
					presa_nagore = false;
				}
				else if(in_Presa_KraenIzklGoren==false && in_Presa_KraenIzklDolen==true && in_Presa_Pressure>=pressureThreshold)
				{
					presa_nagore = true; // the press should move up
					presa_nadolu = false; 
				}
				else if (presa_nagore == false && presa_nadolu == false) // if the program has started but the press is somewhere in between, start the press down
				{
					presa_nadolu = true;
				}
				
				if(presa_nadolu) // When the press should go down
				{
					digitalWrite(outPin_Presa_Nagore, LOW); // Stop the press going up
					digitalWrite(outPin_Presa_Vazduh, LOW); // Turn off the air
					
					digitalWrite(outPin_Presa_Nadolu, HIGH); // Start the press going down
					digitalWrite(outPin_Presa_Vakum, HIGH); // Start the vacum
				}
				else if(presa_nagore) // When the press should go up
				{
					digitalWrite(outPin_Presa_Nadolu, LOW); // Stop the press going down
					digitalWrite(outPin_Presa_Vakum, LOW); // Stop the vacum
					
					digitalWrite(outPin_Presa_Nagore, HIGH); // Start the press going up
					digitalWrite(outPin_Presa_Vazduh, HIGH); // Start the air
				}
			}
			
			else // Manupulators are on the way of the press, stop the press, stop the vacum and the air
			{
				digitalWrite(outPin_Presa_Nagore, LOW);
				digitalWrite(outPin_Presa_Nadolu, LOW);
				digitalWrite(outPin_Presa_Vazduh, LOW);
				digitalWrite(outPin_Presa_Vakum, LOW);
			}
		}
		else
		{
			Serial.write("The main motor of the press is not working");
		}
	}
	else
	{
		Serial.write("Emergency stop at the the press");
		emergency = HIGH;
	}

}

void ReadEmergency()
/*
	This function will block the operation of the production line while
	an emergency sensors is activated. The program reads all emergency sensors.
*/
{
	if(in_Presa_AvariaGlavenMotor==LOW)
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
