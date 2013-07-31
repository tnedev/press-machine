/*
	This is control program for production line with press machine using Arduino Mega R3
	Last Update Jul 2013
	Developed by Tihomir Nedev - nedev@chipolabs.com
	This Code is for board 1 out of 2 bords for the control 

	With this board we will control the functions of the Press, Container and input manipulator
	All variables are global variables, there are no local inputs.

*/

/*
	Progam: how to add new inputs?
	If a new input has to be added to the program the following actions should be done. 
	1. Under pins set up - add name and number for the pin.
	2. Declare a boolean/int value assigned to the new input.
	3. Add the pinMode for the input under Setup().
	4. Add the variable for this input and its declared pin under ReadSensors() function.
*/


/*
	Arduino pins set up
	names formation - "inPin"/"outPin"+Function_name+ name
	The values links the pin number with the name
*/

byte inPin_Presa_KraenIzklGoren = 23;
byte inPin_Presa_KraenIzklDolen = 25;
byte inPin_Presa_AvariaGlavenMotor = 49;
byte inPin_Presa_AvariaOhladitel = 51;

byte outPin_Presa_StartMotor = 24;
byte outPin_Presa_Nagore = 26;
byte outPin_Presa_Nadolu = 28;
byte outPin_Presa_StopGC = 7;
byte outPin_Presa_Vakum = 30;
byte outPin_Presa_Vazduh = 32;


byte inPin_Konteiner_KrainIzklDolen = 27;
byte inPin_Konteiner_Nivo = 13;
byte inPin_Konteiner_MotorAvaria = 53;

byte outPin_Konteiner_Motor = 34;
byte outPin_Konteiner_CilindarGore = 38;
byte outPin_Konteiner_CilindarDolu = 40;


byte inPin_VhMan_KraenIzklNach = 42;
byte inPin_VhMan_KraenIzklKrai = 44;
byte inPin_VhMan_ReperNach = 29;
byte inPin_VhMan_ReperKrai = 31;
byte inPin_VhMan_GornoPolozhenie = 48;
byte inPin_VhMan_DolnoPolozhenie = 46;

byte outPin_VhManipulator_Gore = 50;
byte outPin_VhManipulator_Vakum = 37;
byte outPin_VhManipulator_Vazduh = 39;
byte outPin_VhManipulator_PosokaMotor = 41;
byte outPin_VhManipulator_PulsMotor = 43;

byte inPin_Nozhica_GornoPolozh = 33;
byte inPin_Nozhica_DolnoPolozh = 35;
byte inPin_Nozhica_Ready1_1 = 45;
byte inPin_Nozhica_Ready1_2 = 47;
byte inPin_Nozhica_Ready2_1 = 22;
byte inPin_Nozhica_Ready2_2 = 36;

byte inPin_Nozhica_Kraen1 = 3;
byte inPin_Nozhica_Nach1 = 2;
byte inPin_Nozhica_Kraen2 = 5;
byte inPin_Nozhica_Nach2 = 4;


byte outPin_Nozhica_MasaGore = 52;
byte outPin_Nozhica_Nozhici1 = 9;
byte outPin_Nozhica_Nozhici2 = 10;
byte outPin_Nozhica_Butalo1 = 11;
byte outPin_Nozhica_Butalo2 = 12;
byte outPin_Nozhica_EnableNozh = 13;
byte outPin_Nozhica_Vakum = 6;

byte pin_material_podaden = 21; // output
byte pin_presa_udarila = 20; // output
byte pin_material_vzet = 19; // input
byte pin_razmotalka_stoper = 17;

byte pin_razmotalka_nozh_razreshenie=14;




/*
	Arduino main variables declaration

*/
boolean emergency = false; // Used to stop the system if there is an emegency
int pressureThreshold = 500; // Set the pressure threshold for the press. How much the press has to press. 
boolean presa_nagore = false, presa_nadolu = false; // Sets the direction of the press

boolean material_podaden = false, presa_udarila = false, material_vzet = false; // values to link the logic of operation of the press and both manipulators
int man_speed_high = 6000; // The  high setting of the speed of the input manipulator [Hz of impulse]
int man_speed_low = 100; // The low setting of the speed of the input manipulator [Hz of impulse]
int current_speed=0; // sets the current speed of the manipulator
boolean initial = false; // is the program initialized
boolean man_dir ; // Direction of the manipulator
boolean man_cycle=false;
boolean presa_natisna = false; // to know when the press made an element
int presa_count=0;
boolean nozhica1_napred, nozhica1_nazad,nozhica2_napred, nozhica2_nazad, nozhica_cycle;
boolean razmotalka_nozh_razreshenie=false;
boolean razmotalka_stoper;
boolean nozhici_posoka1 = true;
boolean nozhici_posoka2 = false; 
boolean nozhici_mark = false;
boolean nozhici_cycle = false; // indicates a cycle for the cutters. 
boolean presa_razreshenie = false; 



/*
	Arduino variables declaration
	names formation - "in"/"out" + Function_name + name
*/

int in_Presa_Pressure;
boolean in_Presa_KraenIzklGoren = false;
boolean in_Presa_KraenIzklDolen = false;
boolean in_Presa_AvariaGlavenMotor = false;
boolean in_Presa_AvariaOhladitel = false;

boolean in_Konteiner_KrainIzklDolen = false;
boolean in_Konteiner_Nivo = false;
boolean in_Konteiner_MotorAvaria = false;

boolean in_VhMan_KraenIzklNach = false;
boolean in_VhMan_KraenIzklKrai = false;
boolean in_VhMan_ReperNach = true;
boolean in_VhMan_ReperKrai = true;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;

boolean in_Nozhica_GornoPolozh = false;
boolean in_Nozhica_DolnoPolozh = false;
boolean in_Nozhica_Ready1_1 = false;
boolean in_Nozhica_Ready1_2 = false;
boolean in_Nozhica_Ready2_1 = false;
boolean in_Nozhica_Ready2_2 = false;
boolean in_Nozhica_Kraen1 = false;
boolean in_Nozhica_Nach1 = false;
boolean in_Nozhica_Kraen2 = false;
boolean in_Nozhica_Nach2 = false;


void setup()
{

	Serial.begin(9600);

	// Arduino pinmodes set up
	pinMode(A0,INPUT); // Pressure sensor
	pinMode(inPin_Presa_KraenIzklGoren,INPUT_PULLUP);
	pinMode(inPin_Presa_KraenIzklDolen,INPUT_PULLUP);
	pinMode(inPin_Presa_AvariaGlavenMotor,INPUT);
    pinMode(inPin_Presa_AvariaOhladitel, INPUT);
        
    pinMode(outPin_Presa_StartMotor, OUTPUT);
	pinMode(outPin_Presa_Nagore,OUTPUT);
	pinMode(outPin_Presa_Nadolu,OUTPUT);
	pinMode(outPin_Presa_Vakum,OUTPUT);
	pinMode(outPin_Presa_Vazduh,OUTPUT);

	pinMode(inPin_Konteiner_KrainIzklDolen,INPUT_PULLUP);
	pinMode(inPin_Konteiner_Nivo,INPUT);
	pinMode(inPin_Konteiner_MotorAvaria,INPUT);

	pinMode(outPin_Konteiner_CilindarGore,OUTPUT);
	pinMode(outPin_Konteiner_CilindarDolu,OUTPUT);
	pinMode(outPin_Konteiner_Motor, OUTPUT);


	pinMode(inPin_VhMan_KraenIzklNach,INPUT_PULLUP);
	pinMode(inPin_VhMan_KraenIzklKrai,INPUT_PULLUP);
	pinMode(inPin_VhMan_ReperNach,INPUT_PULLUP);
	pinMode(inPin_VhMan_ReperKrai,INPUT_PULLUP);
	pinMode(inPin_VhMan_GornoPolozhenie,INPUT_PULLUP);
	pinMode(inPin_VhMan_DolnoPolozhenie,INPUT_PULLUP);

	pinMode(outPin_VhManipulator_Gore,OUTPUT);
	pinMode(outPin_VhManipulator_Vakum,OUTPUT);
	pinMode(outPin_VhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_VhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_VhManipulator_PulsMotor,OUTPUT);

	pinMode(inPin_Nozhica_GornoPolozh,INPUT_PULLUP);
	pinMode(inPin_Nozhica_DolnoPolozh,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Ready1_1,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Ready1_2,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Ready2_1,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Ready2_2,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Ready2_2,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Kraen1,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Nach1,INPUT_PULLUP);
        pinMode(inPin_Nozhica_Kraen2,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Nach2,INPUT_PULLUP);

	pinMode(outPin_Nozhica_MasaGore,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici1,OUTPUT);
	pinMode(outPin_Nozhica_Nozhici2,OUTPUT);
	pinMode(outPin_Nozhica_Butalo1,OUTPUT);
	pinMode(outPin_Nozhica_Butalo2,OUTPUT);
	pinMode(outPin_Nozhica_EnableNozh,OUTPUT);
	pinMode(outPin_Nozhica_Vakum, OUTPUT);
	
	pinMode(pin_material_podaden,OUTPUT);
	pinMode(pin_presa_udarila,OUTPUT);
	pinMode(pin_material_vzet,INPUT);
	pinMode(pin_razmotalka_nozh_razreshenie, OUTPUT);
	pinMode(pin_razmotalka_stoper, INPUT);
	
	
	pinMode(27,INPUT_PULLUP); // Used only in testing



}

void ReadSensors()
/*
	This function reads all the sensors the funcions on this board. 
	Used as a convinient way to read and store all values instead of 
	reading the sensors only in one function. Using global values is helpful as it will save time in execution and
	readings will be available all the time. 
	This function takes 5 readings in between 4 microseconds and only if they are all the same, it stores the new value. 
	The analog is taken by reading 50 values and taking an avarage. 
*/

{
	// Bolean values used to store 5 readings and debounce/filter the signal
	boolean digital_1[5];
	boolean digital_2[5];
	boolean digital_3[5];
	boolean digital_4[5];
	boolean digital_5[5];
	boolean digital_6[5];
	boolean digital_7[5];
	boolean digital_8[5];
	boolean digital_9[5];
	boolean digital_10[5];
	boolean digital_11[5];
	boolean digital_12[5];
	boolean digital_13[5];
	boolean digital_14[5];
	boolean digital_15[5];
	boolean digital_16[5];
	boolean digital_17[5];
	boolean digital_18[5];
	boolean digital_19[5];
	boolean digital_20[5];
	boolean digital_21[5];
	boolean digital_22[5];
	boolean digital_23[5];
	boolean digital_24[5];
	boolean digital_25[5];
	int analog_1[50];
	unsigned long analog_sum=0;

	for (int k=0; k<5;k++) // Take 5 readings for all inputs
	{
		digital_1[k] = digitalRead(inPin_Presa_KraenIzklGoren);
		digital_2[k] = digitalRead(inPin_Presa_KraenIzklDolen);
		digital_3[k] = digitalRead(inPin_Presa_AvariaGlavenMotor);
		digital_4[k] = digitalRead(inPin_Konteiner_KrainIzklDolen);
		digital_5[k] = digitalRead(inPin_Konteiner_Nivo);
		digital_6[k] = digitalRead(inPin_Konteiner_MotorAvaria);
		digital_7[k] = digitalRead(inPin_VhMan_KraenIzklNach);
		digital_8[k] = digitalRead(inPin_VhMan_KraenIzklKrai);
		digital_9[k] = digitalRead(inPin_VhMan_ReperNach);
		digital_10[k] = digitalRead(inPin_VhMan_ReperKrai);
		digital_11[k] = digitalRead(inPin_VhMan_GornoPolozhenie);
		digital_12[k] = digitalRead(inPin_VhMan_DolnoPolozhenie);
		digital_13[k] = digitalRead(inPin_Nozhica_GornoPolozh);
		digital_14[k] = digitalRead(inPin_Nozhica_DolnoPolozh);
		digital_15[k] = digitalRead(inPin_Nozhica_Ready1_1);
		digital_16[k] = digitalRead(inPin_Nozhica_Ready1_2);
		digital_17[k] = digitalRead(inPin_Nozhica_Ready2_1);
		digital_18[k] = digitalRead(inPin_Nozhica_Ready2_2);
		digital_19[k] = digitalRead(pin_material_vzet);
		digital_20[k] = digitalRead(inPin_Nozhica_Kraen1);
		digital_21[k] = digitalRead(inPin_Nozhica_Nach1);
		digital_22[k] = digitalRead(inPin_Presa_AvariaOhladitel);
		digital_23[k] = digitalRead(inPin_Nozhica_Kraen2);
		digital_24[k] = digitalRead(inPin_Nozhica_Nach2);
		digital_25[k] = digitalRead(pin_razmotalka_stoper);

		delayMicroseconds(10); // Delay betweeen readings
	}
	// Check if all 5 readings are the same. If they are the same, store the value. If not, go to the next value. 	
	if(digital_1[0]==digital_1[1] && digital_1[0]==digital_1[2]&& digital_1[0]==digital_1[3]&& digital_1[0]==digital_1[4])
	{
		in_Presa_KraenIzklGoren = digital_1[0];
	}
	if(digital_2[0]==digital_2[1] && digital_2[0]==digital_2[2]&& digital_2[0]==digital_2[3]&& digital_2[0]==digital_2[4])
	{
		in_Presa_KraenIzklDolen = digital_2[0];
	}
	if(digital_3[0]==digital_3[1] && digital_3[0]==digital_3[2]&& digital_3[0]==digital_3[3]&& digital_3[0]==digital_3[4])
	{
		in_Presa_AvariaGlavenMotor = digital_3[0];
	}
	if(digital_4[0]==digital_4[1] && digital_4[0]==digital_4[2]&& digital_4[0]==digital_4[3]&& digital_4[0]==digital_4[4])
	{
		in_Konteiner_KrainIzklDolen = digital_4[0];
	}
	if(digital_5[0]==digital_5[1] && digital_5[0]==digital_5[2]&& digital_5[0]==digital_5[3]&& digital_5[0]==digital_5[4])
	{
		in_Konteiner_Nivo = digital_5[0];
	}
	if(digital_6[0]==digital_6[1] && digital_6[0]==digital_6[2]&& digital_6[0]==digital_6[3]&& digital_6[0]==digital_6[4])
	{
		in_Konteiner_MotorAvaria = digital_6[0];
	}
	if(digital_7[0]==digital_7[1] && digital_7[0]==digital_7[2]&& digital_7[0]==digital_7[3]&& digital_7[0]==digital_7[4])
	{
		in_VhMan_KraenIzklNach = digital_7[0];
	}
	if(digital_8[0]==digital_8[1] && digital_8[0]==digital_8[2]&& digital_8[0]==digital_8[3]&& digital_8[0]==digital_8[4])
	{
		in_VhMan_KraenIzklKrai = digital_8[0];
	}
	if(digital_9[0]==digital_9[1] && digital_9[0]==digital_9[2]&& digital_9[0]==digital_9[3]&& digital_9[0]==digital_9[4])
	{
		in_VhMan_ReperNach = digital_9[0];
	}
	if(digital_10[0]==digital_10[1] && digital_10[0]==digital_10[2]&& digital_10[0]==digital_10[3]&& digital_10[0]==digital_10[4])
	{
		in_VhMan_ReperKrai = digital_10[0];
	}
	if(digital_11[0]==digital_11[1] && digital_11[0]==digital_11[2]&& digital_11[0]==digital_11[3]&& digital_11[0]==digital_11[4])
	{
		in_VhMan_GornoPolozhenie = digital_11[0];
	}
	if(digital_12[0]==digital_12[1] && digital_12[0]==digital_12[2]&& digital_12[0]==digital_12[3]&& digital_12[0]==digital_12[4])
	{
		in_VhMan_DolnoPolozhenie = digital_12[0];
	}
	if(digital_13[0]==digital_13[1] && digital_13[0]==digital_13[2]&& digital_13[0]==digital_13[3]&& digital_13[0]==digital_13[4])
	{
		in_Nozhica_GornoPolozh = digital_13[0];
	}
	if(digital_14[0]==digital_14[1] && digital_14[0]==digital_14[2]&& digital_14[0]==digital_14[3]&& digital_14[0]==digital_14[4])
	{
		in_Nozhica_DolnoPolozh = digital_14[0];
	}
	if(digital_15[0]==digital_15[1] && digital_15[0]==digital_15[2]&& digital_15[0]==digital_15[3]&& digital_15[0]==digital_15[4])
	{
		in_Nozhica_Ready1_1 = digital_15[0];
	}
	if(digital_16[0]==digital_16[1] && digital_16[0]==digital_16[2]&& digital_16[0]==digital_16[3]&& digital_16[0]==digital_16[4])
	{
		in_Nozhica_Ready1_2 = digital_16[0];
	}
	if(digital_17[0]==digital_17[1] && digital_17[0]==digital_17[2]&& digital_17[0]==digital_17[3]&& digital_17[0]==digital_17[4])
	{
		in_Nozhica_Ready2_1 = digital_17[0];
	}
	if(digital_18[0]==digital_18[1] && digital_18[0]==digital_18[2]&& digital_18[0]==digital_18[3]&& digital_18[0]==digital_18[4])
	{
		in_Nozhica_Ready2_2 = digital_18[0];
	}
	if(digital_19[0]==digital_19[1] && digital_19[0]==digital_19[2]&& digital_19[0]==digital_19[3]&& digital_19[0]==digital_19[4])
	{
		material_vzet = digital_19[0];
	}
	if(digital_20[0]==digital_20[1] && digital_20[0]==digital_20[2]&& digital_20[0]==digital_20[3]&& digital_20[0]==digital_20[4])
	{
		in_Nozhica_Kraen1 = digital_20[0];
	}
	if(digital_21[0]==digital_21[1] && digital_21[0]==digital_21[2]&& digital_21[0]==digital_21[3]&& digital_21[0]==digital_21[4])
	{
		in_Nozhica_Nach1 = digital_21[0];
	}
    if(digital_22[0]==digital_21[1] && digital_21[0]==digital_21[2]&& digital_21[0]==digital_21[3]&& digital_21[0]==digital_21[4])
	{
		in_Presa_AvariaOhladitel = digital_22[0];
	}
    if(digital_23[0]==digital_23[1] && digital_23[0]==digital_23[2]&& digital_23[0]==digital_23[3]&& digital_23[0]==digital_23[4])
	{
		in_Nozhica_Kraen2 = digital_23[0];
	}
	if(digital_24[0]==digital_24[1] && digital_24[0]==digital_24[2]&& digital_24[0]==digital_24[3]&& digital_24[0]==digital_24[4])
	{
		in_Nozhica_Nach2 = digital_24[0];
	}
    if(digital_25[0]==digital_25[1] && digital_25[0]==digital_25[2]&& digital_25[0]==digital_25[3]&& digital_25[0]==digital_25[4])
	{
		razmotalka_stoper = digital_25[0];
	}

	for (int k=0; k<50;k++)
	{
		analog_sum = analog_sum+analogRead(A0); // collect 50 readings from the analog sensor
		delayMicroseconds(1);
	}
	in_Presa_Pressure = analog_sum/50; // take the mean value from it
	
	digitalWrite(pin_material_podaden, material_podaden); // write the logical values use as "communication" between the boards
	digitalWrite(pin_presa_udarila, presa_udarila); // This indicates that the press has pressed and sends the information to the other board
      digitalWrite(pin_razmotalka_nozh_razreshenie,razmotalka_nozh_razreshenie);
      Serial.println(razmotalka_nozh_razreshenie);

	if(material_vzet == true && material_podaden==true && presa_udarila==true) // when the material was taken out of the press, restart the first two operations
	{
		material_podaden = false;
		presa_udarila = false;
                nozhici_cycle=false;
                presa_razreshenie = false; 
	}

  if(in_VhMan_KraenIzklNach && in_VhMan_KraenIzklKrai)
  {
    Serial.write("24 Volts are out or sensors not working");
    while(1)
    {
      noTone(outPin_VhManipulator_PulsMotor);
	digitalWrite(outPin_Presa_Nadolu, LOW);
	digitalWrite(outPin_Presa_Nagore, LOW);
        digitalWrite(outPin_VhManipulator_Gore, LOW);
        digitalWrite(outPin_Nozhica_Butalo1, LOW);
        digitalWrite(outPin_Nozhica_Butalo2, LOW);
        digitalWrite(outPin_Nozhica_MasaGore, LOW);
        digitalWrite(outPin_Nozhica_Vakum, LOW);
        digitalWrite(outPin_VhManipulator_Vakum, LOW);
    }
  }


}

void Press()
/*
	This function operates the press module on the production line
*/
{

	//if(in_Presa_AvariaGlavenMotor==LOW) // Is there an emergency in the press
	{ // Main function of the press
		if(in_Presa_KraenIzklGoren == true && in_Presa_KraenIzklDolen == false) // If the press is at up position start going down
		{
                
            Serial.println("Presa nadolu");
			if(presa_natisna==true) // if the upper end switch is pressed and there was an element pressed, presa_udarila could take true value
			{
				presa_udarila = true;
				presa_natisna = false;
                Serial.println("Presa udari i se varna");
			}
            if(presa_udarila == false)
            {
				presa_nadolu = 1;
				presa_nagore = 0;
            }
		}
		if(in_Presa_KraenIzklGoren == false && (in_Presa_Pressure >= pressureThreshold || in_Presa_KraenIzklDolen==HIGH)) // If the press is down start going up
		{           
			presa_nagore = 1;
			presa_nadolu = 0;	
			digitalWrite(outPin_Presa_Nadolu, LOW);
			presa_natisna = true;
			Serial.println("Presa natisna");
			digitalWrite(outPin_Presa_StopGC, LOW);
			delay(500);
			digitalWrite(outPin_Presa_Nadolu, LOW);
		}

		if (presa_nagore==false && presa_nadolu==false )  // If there is no inforamtion for the direction of the press go upwards
		{
			presa_nagore = true; 
			Serial.println("Presa nagore");                   
		}

		if(presa_nadolu==true && presa_nagore==false)// Start moving the press down
		{
			digitalWrite(outPin_Presa_Nagore, LOW);
			digitalWrite(outPin_Presa_StopGC, HIGH);
			digitalWrite(outPin_Presa_Nadolu, HIGH);
                        digitalWrite(outPin_Presa_Vakum, HIGH);

		}
		else if(presa_nadolu==false && presa_nagore==true) // Start moving the press up
		{
			digitalWrite(outPin_Presa_Nadolu, LOW);
			digitalWrite(outPin_Presa_Nagore, HIGH);
                        digitalWrite(outPin_Presa_Vakum, LOW);
                        digitalWrite(outPin_Presa_Vazduh, HIGH);
		}
		else 
		{
			Serial.println("Presa_Nagore and Presa_Nadolu are not correct");
		}


	}
	//else
	{
		//Serial.println("Emergency stop at the the press");
		//emergency = HIGH;
	}

}
void VhManipulator()
/*
	This function operates the input manipulator of the system
*/
{
	Serial.println("Vhodqsht");
	if( ( in_VhMan_ReperNach==false && current_speed == 0) ||(in_VhMan_ReperKrai==false && current_speed == 0))
	{	// When the end switch and reper sensor are HIGH and the speed of the motor is 0, this calls for acceleration of the motor
		//man_dir = ~ man_dir; // change direction

	   if(in_VhMan_ReperNach==false)
		{
			man_dir=true;
		}
		if(in_VhMan_ReperKrai==false)
		{
			man_dir=false;
		} 
		digitalWrite(outPin_VhManipulator_PosokaMotor, man_dir);
		Acc_Motor(); // Accelerate the motor 
                if(man_dir==false)
                {
                  digitalWrite(outPin_Nozhica_MasaGore, LOW);
                }
                Serial.println("Acc");

      
		ReadSensors(); 
	}
	if((in_VhMan_KraenIzklNach==true || in_VhMan_KraenIzklKrai==true) && current_speed==man_speed_high)
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{        
		ReadSensors(); 
		if(in_VhMan_KraenIzklNach==true && man_dir==false)
		{
			Dec_Motor();
                  man_cycle=true; // A manipulator cycle indicator, if man_cycle is true, it gives permission for material_podaden to take a true value and therefore start the next operation
		}
		if(in_VhMan_KraenIzklKrai==true && man_dir==true)
		{
			Dec_Motor(); // Decelerate the motor
                digitalWrite(outPin_Nozhica_MasaGore, HIGH); // push the platform up
                digitalWrite(outPin_Nozhica_Vakum, HIGH); // stop the vacum of the cutters while going u
		}

	}
	if((in_VhMan_ReperNach==false || in_VhMan_ReperKrai==false))
	{
   //digitalWrite(outPin_Nozhica_MasaGore, HIGH); // push the platform up
		noTone(outPin_VhManipulator_PulsMotor); // Stop command for the motor
		current_speed=0; // Indicator of the current speed of the motor
        Manipulator_Take();
        Manipulator_Drop();
		//delay(1000); // This is where work will happen - to delete
        ReadSensors();
	}

}
void Manipulator_Nozhica()
// Takes the element and gives permission to the roller to cut
{    
  
    

        if(in_VhMan_ReperNach==false)
	{
        digitalWrite(outPin_Nozhica_Vakum, LOW); // stop the vacum of the cutters while going up
        digitalWrite(outPin_Nozhica_MasaGore, HIGH); // push the platform up
	  while(in_VhMan_DolnoPolozhenie==true )//|| digitalRead(27))
	  {
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, HIGH);
                digitalWrite(outPin_VhManipulator_Vakum, HIGH);
                Serial.println("1 While");
	  }
	    
	  delay(1000);
	  while(in_VhMan_GornoPolozhenie==true )//&& digitalRead(27))
	  {
              Serial.println("3 While");
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, LOW);
                //razmotalka_nozh_razreshenie=false;
                 
	  }
           digitalWrite(outPin_Nozhica_MasaGore, LOW); // push the platform down
	}
      

}
void Manipulator_Take()
// Takes the element and gives permission to the roller to cut
{    
  
    

        if(in_VhMan_ReperNach==false)
	{
        if(man_cycle )
		{
			material_podaden=true;
                        presa_razreshenie = true; 
		}
        digitalWrite(outPin_Nozhica_MasaGore, LOW); // push the platform up
	  while(in_VhMan_DolnoPolozhenie==true )//|| digitalRead(27))
	  {
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, HIGH);
                Serial.println("1 While");
                Serial.println(razmotalka_stoper);
	  }
	    digitalWrite(outPin_VhManipulator_Vakum, HIGH);
	    razmotalka_nozh_razreshenie=true;
	  while(razmotalka_stoper==false )//|| digitalRead(27));
	  {
                Serial.println("2 While");
		ReadSensors();
                razmotalka_nozh_razreshenie=true;
               // digitalWrite(outPin_Nozhica_Vakum, LOW);
                 if(presa_udarila == false && material_podaden == true)
	{
		Press();
	}
               else
              {
          digitalWrite(outPin_Presa_Vazduh, LOW);
          digitalWrite(outPin_Presa_Vakum, LOW);
                }
	  }
          digitalWrite(outPin_Nozhica_MasaGore, LOW); // push the platform down
	  
	  while(in_VhMan_GornoPolozhenie==true )//&& digitalRead(27))
	  {
              Serial.println("3 While");
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, LOW);
                //razmotalka_nozh_razreshenie=false;
                 if(presa_udarila == false && material_podaden == true)
	{
		Press();
	}
 else
        {
          digitalWrite(outPin_Presa_Vazduh, LOW);
          digitalWrite(outPin_Presa_Vakum, LOW);
        }
	  }
          razmotalka_nozh_razreshenie=false;
	}
      

}

void Manipulator_Drop()
{          

	if(in_VhMan_ReperKrai==false)
		{
		  while(in_VhMan_DolnoPolozhenie==true && digitalRead(27))
		  {
			ReadSensors();
			digitalWrite(outPin_VhManipulator_Gore, HIGH);
                        digitalWrite(outPin_Nozhica_MasaGore, HIGH);
		  }
		  digitalWrite(outPin_VhManipulator_Vakum, LOW);
		  while(in_VhMan_GornoPolozhenie==true && digitalRead(27))
		  {
			ReadSensors();
			digitalWrite(outPin_VhManipulator_Gore, LOW);
		  }
		}

   
}
void Acc_Motor()
// Accelerate the motor
{
	int speed_steps = man_speed_high/500;
	for(int i=0; i<man_speed_high;i=i+speed_steps)
	{
		tone(outPin_VhManipulator_PulsMotor, i);
		delayMicroseconds(10);
	}
	current_speed = man_speed_high;
}

void Dec_Motor()
// Decelerate the motor
{
	int counter=0;
	int i;
	int speed_steps = man_speed_high/500;
	for(i=man_speed_high; i>man_speed_low; (i=i-speed_steps))
	{
		tone(outPin_VhManipulator_PulsMotor, i);
        counter++;
		delayMicroseconds(10);
	}
	current_speed = man_speed_low;
    Serial.println(counter);
}



void Konteiner()
/*
	This function operates the press module on the production line
	Трябва да сложим горния изключвател на контейнера!
*/
{
	digitalWrite(outPin_Konteiner_Motor, HIGH); // Set the motor ready
	if(in_Konteiner_Nivo == false) // If the sensor can't see the material, move down
	{
		digitalWrite(outPin_Konteiner_CilindarGore, LOW);
		digitalWrite(outPin_Konteiner_CilindarDolu, HIGH);
	}
		if(in_Konteiner_Nivo == true) // When the material is positioned infront, stop the contrainer
	{
		digitalWrite(outPin_Konteiner_CilindarGore, LOW);
		digitalWrite(outPin_Konteiner_CilindarDolu, LOW);
	}
	if(in_Konteiner_KrainIzklDolen)
	{
		Serial.println("Container is full");
	}


}


void Nozhica()
/*
	This function operates the form cutters of the machine

*/
{
if(nozhici_cycle==false && in_Nozhica_DolnoPolozh == false) // check if a cycle has been done and if the platform is down
{
  digitalWrite(outPin_Nozhica_Vakum, HIGH);
  if(nozhici_posoka1==true)
  {
    
    if(in_Nozhica_Kraen1==true && nozhici_mark==false)
    {
       digitalWrite(outPin_Nozhica_Butalo1, HIGH);
    }
    else
    {
      digitalWrite(outPin_Nozhica_Butalo1, LOW);
      nozhici_mark=true; 
    }
    if(nozhici_mark==true)
    {
      if(in_Nozhica_Nach1==true)
      {
      }
      else
      {
        nozhici_posoka1=false;
        nozhici_posoka2=true;
        nozhici_mark=false; 
      }
    }
  }
  

    if(nozhici_posoka2==true)
  {
    
    if(in_Nozhica_Kraen2==true && nozhici_mark==false)
    {
       digitalWrite(outPin_Nozhica_Butalo2, HIGH);
    }
    else
    {
      digitalWrite(outPin_Nozhica_Butalo2, LOW);
      nozhici_mark=true; 
    }
    if(nozhici_mark==true)
    {
      if(in_Nozhica_Nach2==true)
      {
      }
      else
      {
        nozhici_posoka2=false;
        nozhici_posoka1=true;
        nozhici_mark=false; 
        nozhici_cycle=true; 
        digitalWrite(outPin_Nozhica_Vakum, LOW);
        Manipulator_Nozhica();
      }
    }
  }
  
}

  }
/*

	if(inPin_Nozhica_Ready1_1&&inPin_Nozhica_Ready1_2&&inPin_Nozhica_Ready2_1&&inPin_Nozhica_Ready2_2)
	{
		digitalWrite(outPin_Nozhica_EnableNozh, HIGH); // If all motors are ready, set enable
		
		if(material_podaden==false)
		{
			digitalWrite(outPin_Nozhica_MasaGore, HIGH); // Push the platform up
		}
		
		if(material_podaden && presa_udarila)
		{
			if(inPin_Nozhica_DolnoPolozh==false)
			{
				digitalWrite(outPin_Nozhica_MasaGore, LOW); // If the material was placed by the manipulator, push the platform down
			}
			if(in_Nozhica_Nach1==true && nozhica2_napred == false && nozhica2_nazad=false && nozhica1_napred==false)
			{
				nozhica1_nazad==false;
				nozhica2_nazad==false;
				nozhica2_napred==false;
				nozhica1_napred==true;

			}
			if(in_Nozhica_Kraino && nozhica2_napred == false && nozhica2_nazad=false && nozhica1_napred==true)
			{
				nozhica2_nazad==false;
				nozhica2_napred==false;
				nozhica1_napred==true;
				nozhica1_nazad==true;
			}
			if(in_Nozhica_Nach && nozhica1_napred == true && nozhica2_napred=false && nozhica1_nazad==true)
			{
				nozhica1_nazad==false;
				nozhica1_napred==false;
				nozhica2_nazad==false;
				nozhica2_napred==true;
			}
			if(in_Nozhica_Kraino && nozhica1_napred == false && nozhica2_napred=true && nozhica1_nazad==false)
			{
				nozhica1_nazad==false;
				nozhica1_napred==false;
				nozhica2_nazad==true;
				nozhica2_napred==true;
			}
			if(in_Nozhica_Nach && nozhica1_napred == false && nozhica2_napred=true && nozhica1_nazad==false && nozhica2_nazad=true)
			{
				nozhica_cycle = true;
				nozhica1_nazad==false;
				nozhica1_napred==false;
				nozhica2_nazad==false;
				nozhica2_napred==false;
			}
			
			if(nozhica1_napred && nozhica1_nazad==false && nozhica2_napred==false)
			{
				digitalWrite(outPin_Nozhica_Nozhici1, HIGH); // Start rotating the motor
				digitalWrite(byte outPin_Nozhica_Butalo1, HIGH); // Push them
			}
			if(nozhica1_nazad&& nozhica2_napred==false)
			{
				digitalWrite(outPin_Nozhica_Nozhici1, LOW); // Stop rotating the motor
				digitalWrite(byte outPin_Nozhica_Butalo1, LOW); // Pull them
			}
			if(nozhica2_napred && nozhica2_nazad==false && nozhica1_napred==false )
			{
				digitalWrite(outPin_Nozhica_Nozhici2, HIGH); // Start rotating the motor
				digitalWrite(byte outPin_Nozhica_Butalo2, HIGH); // Push them
			}
			if(nozhica2_nazad && nozhica1_napred==false)
			{
				digitalWrite(outPin_Nozhica_Nozhici2, LOW); // Stop rotating the motor
				digitalWrite(byte outPin_Nozhica_Butalo2, LOW); // Pull them
			}
			
			
		}
		
	}
	else
	{
		// Emergency
	}
*/

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

void Initialize()
/*
	This function initialized the machine
*/
{
	
	digitalWrite(outPin_VhManipulator_PosokaMotor,LOW);
	tone(outPin_VhManipulator_PulsMotor, 200);
	while(in_VhMan_ReperNach == true && digitalRead(27))
	{
		ReadSensors();
	}
	noTone(outPin_VhManipulator_PulsMotor);
        current_speed=0;
	
	///*
	while(in_Presa_KraenIzklGoren == false)
	{
		ReadSensors();
		digitalWrite(outPin_Presa_Nagore, HIGH);
		digitalWrite(outPin_Presa_Nadolu, LOW);
	}
		digitalWrite(outPin_Presa_Nagore, LOW);
		digitalWrite(outPin_Presa_Nadolu, LOW);
		presa_nadolu = true;
		presa_nagore = false;
//*/
	initial=true;
}

void Operation()
/*
This function controls the normal operation of the program. It sequences the operations of the machine.
boolean material_podaden = false, presa_udarila = false, material_vzet = false;
*/
{
	ReadSensors();
	if(initial==false)
	{
	  Initialize();
	}
	if(material_podaden == false && presa_udarila == false ) // ! Add material_vzet to null the previous 2 values
	{
		VhManipulator();
	}
        if(material_podaden == true)
        {
          Nozhica(); 
        }
	 if(presa_udarila == false && presa_razreshenie == true)
	{
		Press();
	}
        else
        {
          digitalWrite(outPin_Presa_Vazduh, LOW);
          digitalWrite(outPin_Presa_Vakum, LOW);
        }

}

void Press_test()
{
ReadSensors(); 
if(digitalRead(27)==HIGH)
{
  Press();
  if(analogRead(in_Presa_Pressure)>450)
  {
  Serial.println(in_Presa_Pressure);
  }
}
else
{
  	digitalWrite(outPin_Presa_Nadolu, LOW);
	digitalWrite(outPin_Presa_Nagore, LOW);
}
}


void loop()
{
 
//Press_test(); 
ReadSensors();
// Test the sensors

/*Serial.print("Vh manipulator: ");
Serial.print(in_VhMan_ReperNach);
Serial.print(in_VhMan_KraenIzklNach);
Serial.print(in_VhMan_KraenIzklKrai);
Serial.print(in_VhMan_ReperKrai);
Serial.print(" Gore/Dolu: ");
Serial.print(in_VhMan_GornoPolozhenie);
Serial.println(in_VhMan_DolnoPolozhenie);



Serial.print(digitalRead(inPin_Nozhica_Kraen1));
Serial.print(digitalRead(inPin_Nozhica_Nach1));
Serial.print(digitalRead(4));
Serial.println(digitalRead(5));

delay(100);

*/

// Test vh manipulator


if(digitalRead(27)==true)
{

	Operation();
}
else
{
	noTone(outPin_VhManipulator_PulsMotor);
	digitalWrite(outPin_Presa_Nadolu, LOW);
	digitalWrite(outPin_Presa_Nagore, LOW);
        digitalWrite(outPin_VhManipulator_Gore, LOW);
        digitalWrite(outPin_Nozhica_Butalo1, LOW);
        digitalWrite(outPin_Nozhica_Butalo2, LOW);
        digitalWrite(outPin_Nozhica_MasaGore, LOW);
        digitalWrite(outPin_Nozhica_Vakum, LOW);
        digitalWrite(outPin_VhManipulator_Vakum, LOW);
	Serial.println("Press the button");
	delay(1000);


}





  /*
	if(emergency==LOW) // Operate the production line if there is no emergency
	{ // Main loop function for normal operation
	
		if(initial=false)
		{
			Initialize();
		}
		ReadSensors();
		if(in_Presa_KraenIzklGoren) // if the press is up
		{
			VhManipulator();
		}
		else
		{
			noTone(outPin_VhManipulator_PulsMotor);
		}

		if(in_VhMan_KraenIzklNach && in_VhMan_ReperNach)
		{
		}
		
	}
	
	else // There was an emegency, this should be fixed before the program continues
	{
		Serial.write("Please fix the emergency before proceeding");
		while(emergency)
		{
			ReadEmergency();
		}
	}
*/
}