//*
	This is control program for production line with press machine using Arduino Mega R3
	Last Update Jul 2013
	Developed by Tihomir Nedev - nedev@chipolabs.com
	This code is for board 2 out of 2 bords for the control

	This board will be used to control the functions for the roller and output manipulator


*/

/*
	Progam, how to add new inputs?
	If a new input has to be added to the program the following actions should be done. 
	1. Under pins set up - add name and number for the pin.
	2. Declare a boolean/int value assigned to the new input.
	3. Add the pinMode for the input under Setup().
	4. Add the variable for this input and its declared pin under ReadSensors() function.
*/

/*
	Arduino pins set up
	names formation - "inPin"/"outPin"+Fusname
*/

// pins to be changed
byte inPin_Nozhica_GornoPolozh = 22;
byte inPin_Nozhica_DolnoPolozh = 24;
byte inPin_Nozhica_Kraen1 = 28;
byte inPin_Nozhica_Nach1 = 26;
byte inPin_Nozhica_Kraen2 = 32;
byte inPin_Nozhica_Nach2 = 30;

byte outPin_Nozhica_MasaGore = 34;
byte outPin_Nozhica_Butalo1 = 36;
byte outPin_Nozhica_Butalo2 = 38;
byte outPin_Nozhica_Vakum = 40;

byte inPin_Razmotalka_SenzorFolio1 = 42;
byte inPin_Razmotalka_SenzorFolio2 = 44;
byte inPin_Razmotalka_DatAkumFolio = 37;
byte inPin_Razmotalka_DatIzkonsumiranAkum = 39;
byte inPin_Razmotalka_NozhStart = 43;
byte inPin_Razmotalka_NozhStop = 41;
byte inPin_Razmotalka_ReadyServo = 52;
byte inPin_Razmotalka_ReadyNozh = 48;

byte outPin_Razmotalka_GlavenMotor = 3;
byte outPin_Razmotalka_GlavenMotor_Visoka = 4;
byte outPin_Razmotalka_MotorVisSkorost = 49;
byte outPin_Razmotalka_MotorNisSkorost = 47;
byte outPin_Razmotalka_NozhicaOtiva = 51;
byte outPin_Razmotalka_NozhicaVrashta = 53;
byte outPin_Razmotalka_EnableServo = 27;
byte outPin_Razmotalka_EnableNozh_Disc = 29;
byte outPin_Razmotalka_Vakum = 31;

byte pin_material_podaden = 21; // Input
byte pin_presa_udarila = 20; // input
byte pin_material_vzet = 19; // input
byte pin_razmotalka_nozh_razreshenie = 14;
byte pin_razmotalka_stoper = 17;
byte pin_starter = 13; 
byte pin_nozhica_razr = 15; 

/*
	Arduino main variables declaration

*/


boolean material_podaden = false, presa_udarila = false, material_vzet = false; // values to link the logic of operation of the press and both manipulators
boolean initial = false; // is the program initialized
boolean razmotalka_cycle = false ; // Show if the roller has already cut a piece of material
boolean razmotalka_posoka;
boolean razmotalka_posoka1, razmotalka_posoka2;
boolean posoka1, posoka2;
boolean manipulator_cycle = false; 


boolean nozhica1_napred, nozhica1_nazad,nozhica2_napred, nozhica2_nazad, nozhica_cycle;
boolean nozhici_posoka1 = true;
boolean nozhici_posoka2 = false; 
boolean nozhici_mark = false;
boolean nozhici_cycle = false; // indicates a cycle for the cutters. 
boolean nozhici_finish = false; 
boolean starter = false; 
boolean roller_razreshenie=true; 
boolean nozhica_razr; 
boolean razmotalka_finish = false; 
boolean emergency_b1=false, emergency_b2=false; // emergency lines signals 
/*
	Arduino variables declaration
	names formation - "input"/"output" + Function_name + name
*/


boolean in_Razmotalka_SenzorFolio1 = false;
boolean in_Razmotalka_SenzorFolio2 = false;
boolean in_Razmotalka_DatAkumFolio = false;
boolean in_Razmotalka_DatIzkonsumiranAkum = false;
boolean in_Razmotalka_NozhStart = false;
boolean in_Razmotalka_NozhStop = false;
boolean in_Razmotalka_ReadyServo = false;
boolean in_Razmotalka_ReadyNozh = false;
boolean in_Razmotalka_ReadyDisk = false;

boolean in_Nozhica_GornoPolozh = false;
boolean in_Nozhica_DolnoPolozh = false;
boolean in_Nozhica_Kraen1 = false;
boolean in_Nozhica_Nach1 = false;
boolean in_Nozhica_Kraen2 = false;
boolean in_Nozhica_Nach2 = false;

boolean in_VhMan_KraenIzklNach;
boolean in_VhMan_KraenIzklKrai;
boolean in_VhMan_ReperNach;
boolean in_VhMan_ReperKrai;
boolean razmotalka_nozh_razreshenie = false;
boolean razmotalka_block=false;
boolean razmotalka_stoper=false; 


void setup()
{
	Serial.begin(9600);


  // Arduino pinmodes set up
  

  
	pinMode(inPin_Razmotalka_SenzorFolio1,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_SenzorFolio2,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_DatAkumFolio,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_DatIzkonsumiranAkum,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_NozhStart,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_NozhStop,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_ReadyServo,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_ReadyNozh,INPUT_PULLUP);

	pinMode(outPin_Razmotalka_GlavenMotor,OUTPUT);
        pinMode(outPin_Razmotalka_GlavenMotor_Visoka,OUTPUT);
	pinMode(outPin_Razmotalka_MotorVisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_MotorNisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_EnableServo,OUTPUT);
	pinMode(outPin_Razmotalka_EnableNozh_Disc,OUTPUT);
	pinMode(outPin_Razmotalka_Vakum,OUTPUT);
	
	pinMode(inPin_Nozhica_GornoPolozh,INPUT_PULLUP);
	pinMode(inPin_Nozhica_DolnoPolozh,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Kraen1,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Nach1,INPUT_PULLUP);
        pinMode(inPin_Nozhica_Kraen2,INPUT_PULLUP);
	pinMode(inPin_Nozhica_Nach2,INPUT_PULLUP);

	pinMode(outPin_Nozhica_MasaGore,OUTPUT);
	pinMode(outPin_Nozhica_Butalo1,OUTPUT);
	pinMode(outPin_Nozhica_Butalo2,OUTPUT);
	pinMode(outPin_Nozhica_Vakum, OUTPUT);

	pinMode(pin_material_podaden,INPUT);
	pinMode(pin_presa_udarila,INPUT);
	pinMode(pin_material_vzet,INPUT);
        pinMode(pin_razmotalka_nozh_razreshenie, INPUT);
        pinMode(pin_razmotalka_stoper, OUTPUT);
        pinMode(pin_starter,INPUT_PULLUP);
        pinMode(pin_nozhica_razr, INPUT);
        



}

void Read_Emergency()
{
  if(in_Razmotalka_NozhStart && in_Razmotalka_NozhStop)
  {
    Serial.println("24 volts line is not on");
    emergency_b2=true; 
  }
  
  if(emergency_b1 || emergency_b2)
  {
    while(1)
  {
    Stop();
  }
  }

}
void Stop()
{
      digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
      digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
		digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_GlavenMotor, LOW);
		digitalWrite(outPin_Razmotalka_EnableServo, LOW);
      digitalWrite(outPin_Razmotalka_EnableNozh_Disc, LOW);
      digitalWrite(outPin_Nozhica_Butalo1, LOW);
      digitalWrite(outPin_Nozhica_Butalo2, LOW);
      digitalWrite(outPin_Nozhica_MasaGore, LOW);
      digitalWrite(outPin_Nozhica_Vakum, LOW); 
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
	// Bolean values to be used to store 5 readings
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


	for (int k=0; k<5;k++) // Take 5 readings for all inputs
	{
		
		digital_1[k] = digitalRead(inPin_Nozhica_Kraen1);
		digital_2[k] = digitalRead(inPin_Nozhica_Nach1);
		digital_3[k] = digitalRead(inPin_Nozhica_Kraen2);
		digital_4[k] = digitalRead(inPin_Nozhica_Nach2);
		digital_5[k] = digitalRead(inPin_Razmotalka_SenzorFolio1);
		digital_6[k] = digitalRead(inPin_Razmotalka_SenzorFolio2);
		digital_7[k] = digitalRead(inPin_Razmotalka_DatAkumFolio);
		digital_8[k] = digitalRead(inPin_Razmotalka_DatIzkonsumiranAkum);
		digital_9[k] = digitalRead(pin_razmotalka_nozh_razreshenie);
		digital_10[k] = digitalRead(inPin_Razmotalka_NozhStart);
		digital_11[k] = digitalRead(inPin_Razmotalka_NozhStop);
		digital_12[k] = digitalRead(inPin_Razmotalka_ReadyServo);
		digital_13[k] = digitalRead(inPin_Razmotalka_ReadyNozh);
		digital_14[k] = digitalRead(pin_material_podaden);
		digital_15[k] = digitalRead(pin_presa_udarila);	
                digital_16[k] = digitalRead(pin_material_vzet);	
                digital_18[k] = digitalRead(inPin_Nozhica_GornoPolozh);
                digital_19[k] = digitalRead(inPin_Nozhica_DolnoPolozh);
                digital_17[k] = digitalRead(pin_starter);
                digital_20[k] = digitalRead(pin_nozhica_razr);	
				
		delayMicroseconds(4);
	}

	// Check if all 5 readings are the same. If they are the same, store the value. If not, go to the next value. 
	
	if(digital_1[0]==digital_1[1] && digital_1[0]==digital_1[2]&& digital_1[0]==digital_1[3]&& digital_1[0]==digital_1[4])
	{
		in_Nozhica_Kraen1 = digital_1[0];
	}
	if(digital_2[0]==digital_2[1] && digital_2[0]==digital_2[2]&& digital_2[0]==digital_2[3]&& digital_2[0]==digital_2[4])
	{
		in_Nozhica_Nach1 = digital_2[0];
	}
	if(digital_3[0]==digital_3[1] && digital_3[0]==digital_3[2]&& digital_3[0]==digital_3[3]&& digital_3[0]==digital_3[4])
	{
		in_Nozhica_Kraen2 = digital_3[0];
	}
	if(digital_4[0]==digital_4[1] && digital_4[0]==digital_4[2]&& digital_4[0]==digital_4[3]&& digital_4[0]==digital_4[4])
	{
		in_Nozhica_Nach2 = digital_4[0];
	}
	if(digital_5[0]==digital_5[1] && digital_5[0]==digital_5[2]&& digital_5[0]==digital_5[3]&& digital_5[0]==digital_5[4])
	{
		in_Razmotalka_SenzorFolio1 = digital_5[0];
	}
	if(digital_6[0]==digital_6[1] && digital_6[0]==digital_6[2]&& digital_6[0]==digital_6[3]&& digital_6[0]==digital_6[4])
	{
		in_Razmotalka_SenzorFolio2 = digital_6[0];
	}
	if(digital_7[0]==digital_7[1] && digital_7[0]==digital_7[2]&& digital_7[0]==digital_7[3]&& digital_7[0]==digital_7[4])
	{
		in_Razmotalka_DatAkumFolio = digital_7[0];
	}
	if(digital_8[0]==digital_8[1] && digital_8[0]==digital_8[2]&& digital_8[0]==digital_8[3]&& digital_8[0]==digital_8[4])
	{
		in_Razmotalka_DatIzkonsumiranAkum = digital_8[0];
	}
	if(digital_9[0]==digital_9[1] && digital_9[0]==digital_9[2]&& digital_9[0]==digital_9[3]&& digital_9[0]==digital_9[4])
	{
		razmotalka_nozh_razreshenie = digital_9[0];
	}
	if(digital_10[0]==digital_10[1] && digital_10[0]==digital_10[2]&& digital_10[0]==digital_10[3]&& digital_10[0]==digital_10[4])
	{
		in_Razmotalka_NozhStart = digital_10[0];
	}
	if(digital_11[0]==digital_11[1] && digital_11[0]==digital_11[2]&& digital_11[0]==digital_11[3]&& digital_11[0]==digital_11[4])
	{
		in_Razmotalka_NozhStop  = digital_11[0];
	}

if(digital_12[0]==digital_12[1] && digital_12[0]==digital_12[2]&& digital_12[0]==digital_12[3]&& digital_12[0]==digital_12[4])
	{
		in_Razmotalka_ReadyServo = digital_12[0];
	}
	if(digital_13[0]==digital_13[1] && digital_13[0]==digital_13[2]&& digital_13[0]==digital_13[3]&& digital_13[0]==digital_13[4])
	{
		in_Razmotalka_ReadyNozh = digital_13[0];
	}
	if(digital_14[0]==digital_14[1] && digital_14[0]==digital_14[2]&& digital_14[0]==digital_14[3]&& digital_14[0]==digital_14[4])
	{
		material_podaden  = digital_14[0];
	}
	if(digital_15[0]==digital_15[1] && digital_15[0]==digital_15[2]&& digital_15[0]==digital_15[3]&& digital_15[0]==digital_15[4])
	{
		presa_udarila = digital_15[0];
	}
	if(digital_16[0]==digital_16[1] && digital_16[0]==digital_16[2]&& digital_16[0]==digital_16[3]&& digital_16[0]==digital_16[4])
	{
		material_vzet = digital_16[0];
	}
if(digital_17[0]==digital_17[1] && digital_17[0]==digital_17[2]&& digital_17[0]==digital_17[3]&& digital_17[0]==digital_17[4])
	{
		starter = digital_17[0];
	}
if(digital_18[0]==digital_18[1] && digital_18[0]==digital_18[2]&& digital_18[0]==digital_18[3]&& digital_18[0]==digital_18[4])
	{
		in_Nozhica_GornoPolozh = digital_18[0];
	}
	if(digital_19[0]==digital_19[1] && digital_19[0]==digital_19[2]&& digital_19[0]==digital_19[3]&& digital_19[0]==digital_19[4])
	{
		in_Nozhica_DolnoPolozh = digital_19[0];
	}
if(digital_20[0]==digital_20[1] && digital_20[0]==digital_20[2]&& digital_20[0]==digital_20[3]&& digital_20[0]==digital_20[4])
	{
		nozhica_razr = digital_20[0];
	}
	
	
	if (material_vzet==true)
	// if the input manipulator and the press have finished, restart the output manipulator
	{

                 nozhici_cycle=false; 
                 nozhici_finish = false; 
                 roller_razreshenie = true; 
            
	}
if (material_vzet==true )
{
                 razmotalka_cycle=false;
}
  

  digitalWrite(pin_razmotalka_stoper, razmotalka_stoper); 
     if(razmotalka_finish == true && nozhici_cycle==true && (in_Razmotalka_NozhStart || in_Razmotalka_NozhStop)&& in_Nozhica_GornoPolozh==false && in_Nozhica_DolnoPolozh)
     {
       razmotalka_stoper = true; 
       digitalWrite(outPin_Nozhica_Vakum, LOW);
     }
     if(material_podaden==false)
     {
       razmotalka_stoper = false;
     }
    


}



void Nozhica()
/*
	This function operates the form cutters of the machine
*/
{
  

if(nozhici_cycle==false)
{
   digitalWrite(outPin_Nozhica_MasaGore, LOW);
  digitalWrite(outPin_Nozhica_Vakum, HIGH);
}

if(nozhici_cycle==true)
{
   digitalWrite(outPin_Nozhica_MasaGore, HIGH);
  if(in_Nozhica_GornoPolozh==false)
  {
    digitalWrite(outPin_Nozhica_Vakum, LOW);
    nozhici_finish = true; 
  }
}
if(nozhici_cycle==false && in_Nozhica_DolnoPolozh == false) // check if a cycle has been done and if the platform is down
{ 
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
      digitalWrite(outPin_Nozhica_MasaGore, HIGH);
      }
    }
  }
  
}

  }

void Razmotalka()
/*
	This function controls the roller of the machine. 
	
*/
{  
         
	if(in_Razmotalka_ReadyNozh==false && in_Razmotalka_ReadyServo==false)
	{	// If the motors are Ready and there is material on the spool, enable the motors and start the program
		digitalWrite(outPin_Razmotalka_EnableServo, HIGH);
		digitalWrite(outPin_Razmotalka_EnableNozh_Disc, HIGH);

		// Rolling the material control
		if(in_Razmotalka_SenzorFolio1==true && in_Razmotalka_SenzorFolio2==true && (in_Razmotalka_NozhStop || in_Razmotalka_NozhStart) )
		{ // If no of the sensor is HIGH push the material with high speed
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, HIGH);
			razmotalka_cycle = false; // when there is no material, we could restart the cycle
		}
		else if(in_Razmotalka_SenzorFolio1==false && in_Razmotalka_SenzorFolio2==true && (in_Razmotalka_NozhStop || in_Razmotalka_NozhStart))
		{	// If the sensor 1 is HIGH, start pushing the material with low speed
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, HIGH);  
                        razmotalka_cycle = false;
		}
		else if(in_Razmotalka_SenzorFolio2==false )//&& in_Razmotalka_SenzorFolio1==false)
		{	// If the sensor 2 is HIGH, stop the motor
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
		}
		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStop && razmotalka_posoka2==true && razmotalka_block==true )
		{	// If there is a material and it is cur, stop the blades

			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);	
                          razmotalka_stoper = true;	
                          razmotalka_cycle = true;	
                          razmotalka_block=false;	
		}
	      if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && in_Razmotalka_NozhStart && razmotalka_cycle==false && razmotalka_posoka1==true && razmotalka_block==true)
		{	// If there is a material and it is cut, stop the blades
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
                        razmotalka_stoper = true;
                        razmotalka_block=false;		
			razmotalka_cycle = true;
       	
		}
		// Cutting the material control
		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStop)// && razmotalka_posoka2==true )
		{	// If there is a material and it is still not cut
                          razmotalka_posoka1=true;
                          razmotalka_posoka2=false;
                          razmotalka_block=true;
                          razmotalka_finish = true;
                           Serial.println("POSOKA SMQNA 1");
			
		}
	
		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStart)// && razmotalka_posoka1==true)
		{	// If there is a material and it is still not cut, start the blades
                           razmotalka_posoka1=false;
                          razmotalka_posoka2=true;
                          razmotalka_block=true;
                          razmotalka_finish=true; 
                          Serial.println("POSOKA SMQNA 2");	
		}

                if(razmotalka_posoka1 == false && razmotalka_posoka2==true && razmotalka_cycle==false && in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_nozh_razreshenie)
                {
                       // digitalWrite(outPin_Razmotalka_Vakum, HIGH);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, HIGH);
                         razmotalka_stoper = false;
                         razmotalka_finish = false; 
                         Serial.println("POSOKA1");
                }
                if(razmotalka_posoka2 == false && razmotalka_posoka1==true && razmotalka_cycle==false && in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_nozh_razreshenie)
                {
                        // digitalWrite(outPin_Razmotalka_Vakum, HIGH);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, HIGH);
                        razmotalka_stoper = false;
                        razmotalka_finish = false; 
                         Serial.println("POSOKA2");
                }
                else
                {
                  if(in_Razmotalka_NozhStart)
                  {
                  razmotalka_posoka2=true;
                  razmotalka_posoka1=false;
                  }
                  else if(in_Razmotalka_NozhStop)
                  {
                  razmotalka_posoka2=false;
                  razmotalka_posoka1=true;
                  }
                  else
                  {
                    razmotalka_posoka2=true;
                    razmotalka_posoka1=false;
                  }
                  
                }
                if(in_Razmotalka_SenzorFolio2==true)
                {
                  razmotalka_cycle = false;
                }
		  
              if(roller_razreshenie)
              {
		if(in_Razmotalka_DatAkumFolio && presa_udarila==false )
		{	// If there is enough buffer material, stop the spool motor
		  digitalWrite(outPin_Razmotalka_GlavenMotor, HIGH);
		}
                else
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor, LOW);
                  roller_razreshenie=false; 
                }
                if (in_Razmotalka_DatIzkonsumiranAkum==false && presa_udarila==false )
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor_Visoka, HIGH);
                }
                else
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor_Visoka, LOW);
                }
		
              }
	}
	else
	{
		// Avaria 
                Serial.println("Motors not Ready");
                delay(500);
		digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
		digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
		digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_GlavenMotor, LOW);

		
		if(in_Razmotalka_ReadyNozh==false && in_Razmotalka_ReadyServo==false && in_Razmotalka_ReadyDisk==false )
		{
			Serial.println("A motor stopped working on the roller");
		}
		// emergency = true;
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
	if(inPin_Nozhica_Nach1==true || inPin_Nozhica_Nach2==true)
{
  while(1)
  {
    Serial.println("Nozhica not in position");
  }
}
if(inPin_Nozhica_Nach1==true || inPin_Nozhica_Nach2==true)
{
  while(1)
  {
    Serial.println("Nozhica not in position");
    delay(2000);
  }
}
if(in_Razmotalka_NozhStart==false && in_Razmotalka_NozhStop==false)
{
  while(1)
  {
    Serial.println("Razmotalka Nozh not in position");
    delay(2000);
  }
}
	initial=true;
}

void Operation()
/*
This function controls the normal operation of the program. It sequences the operations of the machine.
*/
{ 
	ReadSensors();
        Razmotalka();
        if(nozhica_razr)
        {
          Nozhica();
        }
        else
        {
           digitalWrite(outPin_Nozhica_MasaGore, HIGH);
           digitalWrite(outPin_Nozhica_Vakum, HIGH);
        }
         


}


void loop()

{

  ReadSensors();


  /*
  Serial.print("Nozhica GP/DP: ");
  Serial.print(digitalRead(inPin_Nozhica_GornoPolozh));
  Serial.print(digitalRead(inPin_Nozhica_DolnoPolozh));
  Serial.print("N/K 1-2: ");
  Serial.print(digitalRead(inPin_Nozhica_Nach1));
  Serial.print(digitalRead(inPin_Nozhica_Kraen1));
  Serial.print(digitalRead(inPin_Nozhica_Nach2));
  Serial.print(digitalRead(inPin_Nozhica_Kraen2));
  Serial.println();
  Serial.print("Folio 1/2 Ak/Izk: ");
    Serial.print(digitalRead(inPin_Razmotalka_SenzorFolio1));
  Serial.print(digitalRead(inPin_Razmotalka_SenzorFolio2));
  Serial.print(digitalRead(inPin_Razmotalka_DatAkumFolio));
  Serial.print(digitalRead(inPin_Razmotalka_DatIzkonsumiranAkum));
  Serial.print("Nozh Start/Stop");
   Serial.print(digitalRead(inPin_Razmotalka_NozhStart));
  Serial.println(digitalRead(inPin_Razmotalka_NozhStop));
  delay(2000);
  */

  if (starter==true)
{
  Operation();

}
else
{
  
    Stop();
    delay(1000);
}
}


