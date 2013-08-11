//*
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

byte inPin_VhMan_KraenIzklNach = 29;
byte inPin_VhMan_KraenIzklKrai = 31;
byte inPin_VhMan_ReperNach = 42;
byte inPin_VhMan_ReperKrai = 44;
byte inPin_VhMan_GornoPolozhenie = 46;
byte inPin_VhMan_DolnoPolozhenie = 48;
byte inPin_VhMan_Ready = 34; // Pin to be added

byte outPin_VhManipulator_Gore = 50;
byte outPin_VhManipulator_Vakum = 37;
byte outPin_VhManipulator_VisokaSk = 38; 
byte outPin_VhManipulator_NiskaSk = 40; 
byte outPin_VhManipulator_Dir = 36; 

byte inPin_IzhMan_KraenIzklNach = 45;
byte inPin_IzhMan_KraenIzklKrai = 52;
byte inPin_IzhMan_ReperNach = 22;
byte inPin_IzhMan_ReperKrai = 27;
byte inPin_IzhMan_GornoPolozhenie = 53;
byte inPin_IzhMan_DolnoPolozhenie = 43;
byte inPin_IzhMan_Ready = 33; 

byte outPin_IzhManipulator_Gore = 47;
byte outPin_IzhManipulator_Vakum = 6;
byte outPin_IzhManipulator_VisokaSk = 39; 
byte outPin_IzhManipulator_NiskaSk = 41; 
byte outPin_IzhManipulator_Dir = 35; 

byte pin_material_podaden = 21; 
byte pin_presa_udarila = 20; 
byte pin_material_vzet = 19; 
byte pin_razmotalka_stoper = 17;
byte pin_nozhica_cycle = 16; 
byte pin_razmotalka_nozh_razreshenie=14;

byte pin_starter = 13; 

/*
	Arduino main variables declaration

*/
boolean emergency = false; // Used to stop the system if there is an emegency
int pressureThreshold = 500; // Set the pressure threshold for the press. How much the press has to press. 
boolean presa_nagore = false, presa_nadolu = false; // Sets the direction of the press

boolean material_podaden = false, presa_udarila = false, material_vzet = false; // values to link the logic of operation of the press and both manipulators
int man_speed_high = 4000; // The  high setting of the speed of the input manipulator [Hz of impulse]
int man_speed_low = 100; // The low setting of the speed of the input manipulator [Hz of impulse]
int current_speed=0; // sets the current speed of the manipulator
boolean initial = false; // is the program initialized
boolean man_dir ; // Direction of the manipulator
boolean man_cycle=false;
boolean presa_natisna = false; // to know when the press made an element
int presa_count=0;
boolean razmotalka_nozh_razreshenie=false;
boolean razmotalka_stoper;
boolean presa_razreshenie = false; 

int IzhCurrent_speed=0; // sets the current speed of the manipulator
boolean Izhhan_dir ; // Direction of the manipulator
boolean IzhMan_cycle; // shows that a cycle of operation has been done
boolean manipulator_cycle = false; 
boolean nozhica_cycle=false; 
boolean IzhMan_dir=false; 
boolean starter; 
/*
	Arduino variables declaration
	names formation - "in"/"out" + Function_name + name
*/

int in_Presa_Pressure;
boolean in_Presa_KraenIzklGoren = false;
boolean in_Presa_KraenIzklDolen = false;
boolean in_Presa_AvariaGlavenMotor = false;
boolean in_Presa_AvariaOhladitel = false;

boolean in_VhMan_KraenIzklNach = false;
boolean in_VhMan_KraenIzklKrai = false;
boolean in_VhMan_ReperNach = true;
boolean in_VhMan_ReperKrai = true;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;
boolean in_VhMan_Ready = true; 

boolean in_IzhMan_KraenIzklNach = false;
boolean in_IzhMan_KraenIzklKrai = false;
boolean in_IzhMan_ReperNach = false;
boolean in_IzhMan_ReperKrai = false;
boolean in_IzhMan_GornoPolozhenie = false;
boolean in_IzhMan_DolnoPolozhenie = false;
boolean in_IzhMan_Ready = true; 

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
        
        pinMode(inPin_IzhMan_KraenIzklNach,INPUT_PULLUP);
	pinMode(inPin_IzhMan_KraenIzklKrai,INPUT_PULLUP);
	pinMode(inPin_IzhMan_ReperNach,INPUT_PULLUP);
	pinMode(inPin_IzhMan_ReperKrai,INPUT_PULLUP);
	pinMode(inPin_IzhMan_GornoPolozhenie,INPUT_PULLUP);
	pinMode(inPin_IzhMan_DolnoPolozhenie,INPUT_PULLUP);
        pinMode(inPin_IzhMan_Ready,INPUT_PULLUP);

	pinMode(outPin_IzhManipulator_Gore,OUTPUT);
	pinMode(outPin_IzhManipulator_Vakum,OUTPUT);
	pinMode(outPin_IzhManipulator_VisokaSk,OUTPUT);
	pinMode(outPin_IzhManipulator_NiskaSk,OUTPUT);
pinMode(outPin_IzhManipulator_Dir, OUTPUT);
	pinMode(inPin_VhMan_KraenIzklNach,INPUT_PULLUP);
	pinMode(inPin_VhMan_KraenIzklKrai,INPUT_PULLUP);
	pinMode(inPin_VhMan_ReperNach,INPUT_PULLUP);
	pinMode(inPin_VhMan_ReperKrai,INPUT_PULLUP);
	pinMode(inPin_VhMan_GornoPolozhenie,INPUT_PULLUP);
	pinMode(inPin_VhMan_DolnoPolozhenie,INPUT_PULLUP);
        pinMode(inPin_VhMan_Ready,INPUT_PULLUP);

	pinMode(outPin_VhManipulator_Gore,OUTPUT);
	pinMode(outPin_VhManipulator_Vakum,OUTPUT);
	pinMode(outPin_VhManipulator_VisokaSk,OUTPUT);
	pinMode(outPin_VhManipulator_NiskaSk,OUTPUT);
	pinMode(outPin_VhManipulator_Dir, OUTPUT);

	pinMode(pin_material_podaden,OUTPUT);
	pinMode(pin_presa_udarila,OUTPUT);
	pinMode(pin_material_vzet,OUTPUT);
	pinMode(pin_razmotalka_nozh_razreshenie, OUTPUT);
	pinMode(pin_razmotalka_stoper, INPUT);
        pinMode(pin_nozhica_cycle, INPUT);
        pinMode(pin_starter, INPUT_PULLUP);
	
	
	//pinMode(13,INPUT_PULLUP); // Used only in testing



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
	int analog_1[50];
	unsigned long analog_sum=0;

	for (int k=0; k<5;k++) // Take 5 readings for all inputs
	{
		digital_1[k] = digitalRead(inPin_Presa_KraenIzklGoren);
		digital_2[k] = digitalRead(inPin_Presa_KraenIzklDolen);
		digital_3[k] = digitalRead(inPin_Presa_AvariaGlavenMotor);
		digital_4[k] = digitalRead(inPin_IzhMan_Ready);
		digital_5[k] = digitalRead(inPin_VhMan_Ready);
		digital_6[k] = digitalRead(inPin_Presa_AvariaOhladitel);
		digital_7[k] = digitalRead(inPin_VhMan_KraenIzklNach);
		digital_8[k] = digitalRead(inPin_VhMan_KraenIzklKrai);
		digital_9[k] = digitalRead(inPin_VhMan_ReperNach);
		digital_10[k] = digitalRead(inPin_VhMan_ReperKrai);
		digital_11[k] = digitalRead(inPin_VhMan_GornoPolozhenie);
		digital_12[k] = digitalRead(inPin_VhMan_DolnoPolozhenie);
		digital_13[k] = digitalRead(pin_nozhica_cycle);
		digital_14[k] = digitalRead(pin_razmotalka_stoper);
                digital_15[k] = digitalRead(inPin_IzhMan_KraenIzklNach);
		digital_16[k] = digitalRead(inPin_IzhMan_KraenIzklKrai);
		digital_17[k] = digitalRead(inPin_IzhMan_ReperNach);
		digital_18[k] = digitalRead(inPin_IzhMan_ReperKrai);
		digital_19[k] = digitalRead(pin_material_vzet);
                digital_20[k] = digitalRead(inPin_IzhMan_GornoPolozhenie);
		digital_21[k] = digitalRead(inPin_IzhMan_DolnoPolozhenie);
                digital_22[k] = digitalRead(pin_starter);
                               
		
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
		in_IzhMan_Ready = digital_4[0];
	}
	if(digital_5[0]==digital_5[1] && digital_5[0]==digital_5[2]&& digital_5[0]==digital_5[3]&& digital_5[0]==digital_5[4])
	{
		in_VhMan_Ready = digital_5[0];
	}
        if(digital_6[0]==digital_6[1] && digital_6[0]==digital_6[2]&& digital_6[0]==digital_6[3]&& digital_6[0]==digital_6[4])
	{
		in_Presa_AvariaOhladitel = digital_6[0];
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
		nozhica_cycle = digital_13[0];
	}
	if(digital_14[0]==digital_14[1] && digital_14[0]==digital_14[2]&& digital_14[0]==digital_14[3]&& digital_14[0]==digital_14[4])
	{
		razmotalka_stoper = digital_14[0];
	}
	if(digital_15[0]==digital_15[1] && digital_15[0]==digital_15[2]&& digital_15[0]==digital_15[3]&& digital_15[0]==digital_15[4])
	{
		in_IzhMan_KraenIzklNach = digital_15[0];
	}
	if(digital_16[0]==digital_16[1] && digital_16[0]==digital_16[2]&& digital_16[0]==digital_16[3]&& digital_16[0]==digital_16[4])
	{
		in_IzhMan_KraenIzklKrai = digital_16[0];
	}
	if(digital_17[0]==digital_17[1] && digital_17[0]==digital_17[2]&& digital_17[0]==digital_17[3]&& digital_17[0]==digital_17[4])
	{
		in_IzhMan_ReperNach = digital_17[0];
	}
	if(digital_18[0]==digital_18[1] && digital_18[0]==digital_18[2]&& digital_18[0]==digital_18[3]&& digital_18[0]==digital_18[4])
	{
		in_IzhMan_ReperKrai = digital_18[0];
	}
	if(digital_19[0]==digital_19[1] && digital_19[0]==digital_19[2]&& digital_19[0]==digital_19[3]&& digital_19[0]==digital_19[4])
	{
		material_vzet = digital_19[0];
	}
	if(digital_20[0]==digital_20[1] && digital_20[0]==digital_20[2]&& digital_20[0]==digital_20[3]&& digital_20[0]==digital_20[4])
	{
		in_IzhMan_GornoPolozhenie = digital_20[0];
	}
	if(digital_21[0]==digital_21[1] && digital_21[0]==digital_21[2]&& digital_21[0]==digital_21[3]&& digital_21[0]==digital_21[4])
	{
		in_IzhMan_DolnoPolozhenie = digital_21[0];
	}
        if(digital_22[0]==digital_22[1] && digital_22[0]==digital_22[2]&& digital_22[0]==digital_22[3]&& digital_22[0]==digital_22[4])
	{
		starter = digital_22[0];
	}

	for (int k=0; k<50;k++)
	{
		analog_sum = analog_sum+analogRead(A0); // collect 50 readings from the analog sensor
	}
	in_Presa_Pressure = analog_sum/50; // take the mean value from it
	
	digitalWrite(pin_material_podaden, material_podaden); // write the logical values use as "communication" between the boards
	digitalWrite(pin_presa_udarila, presa_udarila); // This indicates that the press has pressed and sends the information to the other board
      digitalWrite(pin_razmotalka_nozh_razreshenie,razmotalka_nozh_razreshenie);
      digitalWrite(pin_material_vzet, IzhMan_cycle); // man_cycle to show that the cycle has finished. The other manipulator will wait until then
      
	if(material_vzet == true && material_podaden==true && presa_udarila==true) // when the material was taken out of the press, restart the first two operations
	{
		material_podaden = false;
		presa_udarila = false;
                presa_razreshenie = false; 
	}
      if (material_podaden == true && presa_udarila == false )
	// if the input manipulator and the press have finished, restart the output manipulator
	{
		material_vzet = false;
		IzhMan_cycle = false;
	}
      if(presa_udarila==true )
      {
        manipulator_cycle=true; 
      }
              
  if(in_VhMan_KraenIzklNach && in_VhMan_KraenIzklKrai)
  {
    Serial.write("24 Volts are out or sensors not working");
    while(1)
    {
	digitalWrite(outPin_Presa_Nadolu, LOW);
	digitalWrite(outPin_Presa_Nagore, LOW);
        digitalWrite(outPin_VhManipulator_Gore, LOW);
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
	if( ( in_VhMan_ReperNach==false && current_speed == 0) ||(in_VhMan_ReperKrai==false && current_speed == 0))
	{
	   if(in_VhMan_ReperNach==false)
		{
			man_dir=true;
		}
		if(in_VhMan_ReperKrai==false)
		{
			man_dir=false;
		} 
		digitalWrite(outPin_VhManipulator_Dir, man_dir);
                digitalWrite(outPin_VhManipulator_VisokaSk, HIGH);
                current_speed = man_speed_high;
		ReadSensors(); 
	}

	if((in_VhMan_KraenIzklNach==true || in_VhMan_KraenIzklKrai==true) && current_speed==man_speed_high)
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{        
		ReadSensors(); 
		if(in_VhMan_KraenIzklNach==true && man_dir==false)
		{
		digitalWrite(outPin_VhManipulator_VisokaSk, LOW);
                digitalWrite(outPin_VhManipulator_NiskaSk, HIGH);
                man_cycle=true; // A manipulator cycle indicator, if man_cycle is true, it gives permission for material_podaden to take a true value and therefore start the next operation
		}
		if(in_VhMan_KraenIzklKrai==true && man_dir==true)
		{
		digitalWrite(outPin_VhManipulator_VisokaSk, LOW);
                digitalWrite(outPin_VhManipulator_NiskaSk, HIGH);

		}

	}
	if((in_VhMan_ReperNach==false || in_VhMan_ReperKrai==false))
	{        
                  if( (in_VhMan_ReperNach==false && man_dir==false ))
                  {
		digitalWrite(outPin_VhManipulator_VisokaSk, LOW);
                digitalWrite(outPin_VhManipulator_NiskaSk, LOW);
                Serial.println("stop 1");
		current_speed=0; // Indicator of the current speed of the motor
                Manipulator_Take();
                  }
                  
                  if (in_VhMan_ReperKrai==false && man_dir==true)
                  {
                    digitalWrite(outPin_VhManipulator_VisokaSk, LOW);
                digitalWrite(outPin_VhManipulator_NiskaSk, LOW);
		current_speed=0; // Indicator of the current speed of the motor
                Manipulator_Drop();
                Serial.println("stop 2");
                  }
               // 
                ReadSensors();
	}

}
void Manipulator_Nozhica()
// Takes the element and gives permission to the roller to cut
{    
  /*
  
    

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
      
*/
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
	  while(in_VhMan_DolnoPolozhenie==true )//|| digitalRead(27))
	  {
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, HIGH);
	  }
	    digitalWrite(outPin_VhManipulator_Vakum, HIGH);
	    razmotalka_nozh_razreshenie=true;
	  while(razmotalka_stoper==false )//|| digitalRead(27));
	  {
		ReadSensors();
                razmotalka_nozh_razreshenie=true;
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
	  
	  while(in_VhMan_GornoPolozhenie==true )//&& digitalRead(27))
	  {
		ReadSensors();
		digitalWrite(outPin_VhManipulator_Gore, LOW);
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
          razmotalka_nozh_razreshenie=false;
	}
      

}

void Manipulator_Drop()
{          

	if(in_VhMan_ReperKrai==false)
		{
		  while(in_VhMan_DolnoPolozhenie==true && starter)
		  {
			ReadSensors();
			digitalWrite(outPin_VhManipulator_Gore, HIGH);
		  }
		  digitalWrite(outPin_VhManipulator_Vakum, LOW);
		  while(in_VhMan_GornoPolozhenie==true && starter)
		  {
			ReadSensors();
			digitalWrite(outPin_VhManipulator_Gore, LOW);
		  }
		}

   
}

void IzhManipulator()
/*
	This function operates the input manipulator of the system
*/
{
	
	if( ( in_IzhMan_ReperNach && IzhCurrent_speed == 0) ||(in_IzhMan_ReperKrai && IzhCurrent_speed == 0))
	{

               if(in_IzhMan_ReperNach==true)
                {
                  IzhMan_dir=true;
                }
                if(in_IzhMan_ReperKrai==true)
                 {
                  IzhMan_dir=false;
                }

		digitalWrite(outPin_IzhManipulator_Dir, IzhMan_dir);
         if(presa_udarila)
          {
		digitalWrite(outPin_IzhManipulator_VisokaSk, HIGH); 
                IzhCurrent_speed = man_speed_high;
          }
                ReadSensors();

		if (IzhMan_dir == false) // if the manipulator is moving out, this could start the input manipulator.
		{
			material_vzet = true;
                        digitalWrite(pin_material_vzet, IzhMan_cycle);
		}


 
	}
	
	if((in_IzhMan_KraenIzklNach==true || in_IzhMan_KraenIzklKrai==true) &&   IzhCurrent_speed==man_speed_high )
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{        ReadSensors();
                  
	         if(in_IzhMan_KraenIzklNach==true && IzhMan_dir==false)
                {
		  digitalWrite(outPin_IzhManipulator_VisokaSk, LOW);
                  digitalWrite(outPin_IzhManipulator_NiskaSk, HIGH);
                  IzhCurrent_speed = man_speed_low;
                }
                if(in_IzhMan_KraenIzklKrai==true  && IzhMan_dir==true)
                {
		  digitalWrite(outPin_IzhManipulator_VisokaSk, LOW);
                  digitalWrite(outPin_IzhManipulator_NiskaSk, HIGH);
                  IzhCurrent_speed = man_speed_low;
                                        
                }  
               if(in_IzhMan_KraenIzklKrai==true && IzhMan_dir==false)
               
              {
              digitalWrite(pin_material_vzet, HIGH);
              ReadSensors();
          
              }  
	}
	if((in_IzhMan_ReperNach==true || in_IzhMan_ReperKrai==true))
	{
            if(in_IzhMan_ReperNach==true && IzhMan_dir==false)
            {
              digitalWrite(outPin_IzhManipulator_VisokaSk, LOW);
                  digitalWrite(outPin_IzhManipulator_NiskaSk, LOW);
                  IzhCurrent_speed=0;
                  IzhManipulator_Drop();
            }
            if(in_IzhMan_ReperKrai==true && IzhMan_dir==true)
            {
              digitalWrite(outPin_IzhManipulator_VisokaSk, LOW);
                  digitalWrite(outPin_IzhManipulator_NiskaSk, LOW);
                  IzhCurrent_speed=0;
                  IzhManipulator_Take();
            }
		
		if(material_vzet == true && presa_udarila==true) // if the element was taken and the manipulatorstoped, this is a cycle
		{
			IzhMan_cycle = true; // when the work is added, another logic should be added too
		} 
		//delay(1000); // This is where work will happen - to delete
                ReadSensors();
                if (in_IzhMan_ReperNach==true)
                {
                manipulator_cycle=false;
                }
	}

}
void IzhManipulator_Take()
// Takes the element and gives permission to the roller to cut
{ 
	if(in_IzhMan_ReperKrai==true)
	{
	  while(in_IzhMan_DolnoPolozhenie==true&& starter)
	  {
                ReadSensors();
		digitalWrite(outPin_IzhManipulator_Gore, HIGH);
                digitalWrite(outPin_IzhManipulator_Vakum, HIGH);
	  }
	  
	  while(in_IzhMan_GornoPolozhenie==true && starter)
	  {
                ReadSensors();
		digitalWrite(outPin_IzhManipulator_Gore, LOW);
	  }
	}
}

void IzhManipulator_Drop()
{      
	if(in_IzhMan_ReperNach==true)
		{
		  while(in_IzhMan_DolnoPolozhenie==true && starter)
		  {
			ReadSensors();
			digitalWrite(outPin_IzhManipulator_Gore, HIGH);
                        VhManipulator();
		  }
		  digitalWrite(outPin_IzhManipulator_Vakum, LOW);
		  while(in_IzhMan_GornoPolozhenie==true && starter)
		  {
			ReadSensors();
                        VhManipulator();
			digitalWrite(outPin_IzhManipulator_Gore, LOW);
		  }
		}
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
  
	Serial.println("Initialize");
	digitalWrite(outPin_VhManipulator_Dir,LOW);
	digitalWrite(outPin_VhManipulator_NiskaSk, HIGH);
	while(in_VhMan_ReperNach == true && starter)
	{
		ReadSensors();
               Serial.println(in_VhMan_ReperNach);
	}
        Serial.println(in_VhMan_ReperNach);
	digitalWrite(outPin_VhManipulator_NiskaSk, LOW);
        current_speed=0;
        
	digitalWrite(outPin_IzhManipulator_Dir,LOW);
	digitalWrite(outPin_IzhManipulator_NiskaSk, HIGH);
	while(in_IzhMan_ReperNach == false && starter)
	{
		ReadSensors();
	}
	digitalWrite(outPin_IzhManipulator_NiskaSk, LOW);
        IzhCurrent_speed=0;
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

	initial=true;
Serial.println("Initialize FINISH");
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
	if(material_podaden == false && presa_udarila == false && in_Presa_KraenIzklGoren) // ! Add material_vzet to null the previous 2 values
	{
		VhManipulator();

	}
        if(manipulator_cycle=true && in_Presa_KraenIzklGoren )
        {
          IzhManipulator();
        }
	 if(presa_udarila == false && presa_razreshenie == true && in_VhMan_ReperNach==false && in_IzhMan_ReperNach)
	{
		Press(); 
                Serial.println("Press");
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
 //digitalWrite(outPin_IzhManipulator_Dir,HIGH);

// Test the sensors
/*
Serial.print("Vh manipulator: ");
Serial.print(digitalRead(inPin_VhMan_ReperNach));
Serial.print(digitalRead(inPin_VhMan_KraenIzklNach));
Serial.print(digitalRead(inPin_VhMan_KraenIzklKrai));
Serial.print(digitalRead(inPin_VhMan_ReperKrai));
Serial.print(" Gore/Dolu: ");
Serial.print(digitalRead(inPin_VhMan_GornoPolozhenie));
Serial.println(digitalRead(inPin_VhMan_DolnoPolozhenie));
Serial.print("Izh manipulator: ");
Serial.print(digitalRead(inPin_IzhMan_ReperNach));
Serial.print(digitalRead(inPin_IzhMan_KraenIzklNach));
Serial.print(digitalRead(inPin_IzhMan_KraenIzklKrai));
Serial.print(digitalRead(inPin_IzhMan_ReperKrai));
Serial.print(" Gore/Dolu: ");
Serial.print(digitalRead(inPin_IzhMan_GornoPolozhenie));
Serial.println(digitalRead(inPin_IzhMan_DolnoPolozhenie));
Serial.print("Presa G/D");
Serial.print(digitalRead(inPin_Presa_KraenIzklGoren));
Serial.println(digitalRead(inPin_Presa_KraenIzklDolen));
Serial.println(analogRead(A0));


delay(2000);
 digitalWrite(outPin_IzhManipulator_Dir,HIGH);
	digitalWrite(outPin_IzhManipulator_VisokaSk, HIGH);
*/

// Test vh manipulator


if(starter)
{
 Operation();
   //   digitalWrite(outPin_IzhManipulator_Dir,LOW);
	//digitalWrite(outPin_IzhManipulator_NiskaSk, HIGH);
       //digitalWrite(outPin_IzhManipulator_NiskaSk, HIGH);
       // digitalWrite(outPin_IzhManipulator_Dir,LOW);
        //Serial.println("Motors run");
}
else
{
        
	digitalWrite(outPin_VhManipulator_VisokaSk, LOW);
        digitalWrite(outPin_VhManipulator_NiskaSk, LOW);
        digitalWrite(outPin_IzhManipulator_VisokaSk, LOW);
        digitalWrite(outPin_IzhManipulator_NiskaSk, LOW);
	digitalWrite(outPin_Presa_Nadolu, LOW);
	digitalWrite(outPin_Presa_Nagore, LOW);
        digitalWrite(outPin_Presa_StopGC, LOW);
        digitalWrite(outPin_VhManipulator_Gore, LOW);
        digitalWrite(outPin_VhManipulator_Vakum, LOW);
        digitalWrite(outPin_IzhManipulator_Gore, LOW);
        digitalWrite(outPin_IzhManipulator_Vakum, LOW);
	Serial.println("STOPED");
        ReadSensors();
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