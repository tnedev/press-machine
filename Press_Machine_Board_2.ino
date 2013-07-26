/*
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
	names formation - "inPin"/"outPin"+Function_name+ name
	The values links the pin number with the name
*/


byte inPin_IzhMan_KraenIzklNach = 22;
byte inPin_IzhMan_KraenIzklKrai = 24;
byte inPin_IzhMan_ReperNach = 33;
byte inPin_IzhMan_ReperKrai = 35;
byte inPin_IzhMan_GornoPolozhenie = 26;
byte inPin_IzhMan_DolnoPolozhenie = 28;

byte outPin_IzhManipulator_Gore = 30;
byte outPin_IzhManipulator_Vakum = 34;
byte outPin_IzhManipulator_Vazduh = 36;
byte outPin_IzhManipulator_PosokaMotor = 38;
byte outPin_IzhManipulator_PulsMotor = 40;

byte inPin_Razmotalka_SenzorFolio1 = 42;
byte inPin_Razmotalka_SenzorFolio2 = 44;
byte inPin_Razmotalka_DatAkumFolio = 37;
byte inPin_Razmotalka_DatIzkonsumiranAkum = 39;
byte inPin_Razmotalka_NozhStart = 43;
byte inPin_Razmotalka_NozhStop = 41;
byte inPin_Razmotalka_ReadyServo = 52;
byte inPin_Razmotalka_ReadyNozh = 48;
byte inPin_Razmotalka_ReadyDisk = 50;

byte outPin_Razmotalka_GlavenMotor = 3;
byte outPin_Razmotalka_GlavenMotor_Visoka = 4;
byte outPin_Razmotalka_MotorVisSkorost = 49;
byte outPin_Razmotalka_MotorNisSkorost = 47;
byte outPin_Razmotalka_NozhicaOtiva = 51;
byte outPin_Razmotalka_NozhicaVrashta = 53;
byte outPin_Razmotalka_StartNozhicaDiskOtiva = 23;
byte outPin_Razmotalka_StartNozhicaDiskVrashta = 25;
byte outPin_Razmotalka_EnableSevo = 27;
byte outPin_Razmotalka_EnableNozh_Disc = 29;
byte outPin_Razmotalka_Vakum = 31;

byte pin_material_podaden = 21; // Input
byte pin_presa_udarila = 20; // input
byte pin_material_vzet = 19; // output
byte pin_razmotalka_nozh_razreshenie = 18;
byte pin_razmotalka_stoper = 17;

/*
	Arduino main variables declaration

*/


boolean material_podaden = false, presa_udarila = false, material_vzet = false; // values to link the logic of operation of the press and both manipulators
int man_speed_high = 3000; // The  high setting of the speed of the input manipulator [Hz of impulse]
int man_speed_low = 200; // The low setting of the speed of the input manipulator [Hz of impulse]
int current_speed=0; // sets the current speed of the manipulator
boolean initial = false; // is the program initialized
boolean man_dir ; // Direction of the manipulator
boolean man_cycle; // shows that a cycle of operation has been done
boolean razmotalka_cycle = true; // Show if the roller has already cut a piece of material
boolean razmotalka_posoka;
// Show the direction of the disk
boolean razmotalka_posoka1, razmotalka_posoka2;
boolean posoka1, posoka2;

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
boolean in_Razmotalka_NozhStart = false;
boolean in_Razmotalka_NozhStop = false;
boolean in_Razmotalka_ReadyServo = false;
boolean in_Razmotalka_ReadyNozh = false;
boolean in_Razmotalka_ReadyDisk = false;

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
  

	pinMode(inPin_IzhMan_KraenIzklNach,INPUT_PULLUP);
	pinMode(inPin_IzhMan_KraenIzklKrai,INPUT_PULLUP);
	pinMode(inPin_IzhMan_ReperNach,INPUT_PULLUP);
	pinMode(inPin_IzhMan_ReperKrai,INPUT_PULLUP);
	pinMode(inPin_IzhMan_GornoPolozhenie,INPUT_PULLUP);
	pinMode(inPin_IzhMan_DolnoPolozhenie,INPUT_PULLUP);

	pinMode(outPin_IzhManipulator_Gore,OUTPUT);
	pinMode(outPin_IzhManipulator_Vakum,OUTPUT);
	pinMode(outPin_IzhManipulator_Vazduh,OUTPUT);
	pinMode(outPin_IzhManipulator_PosokaMotor,OUTPUT);
	pinMode(outPin_IzhManipulator_PulsMotor,OUTPUT);
  
	pinMode(inPin_Razmotalka_SenzorFolio1,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_SenzorFolio2,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_DatAkumFolio,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_DatIzkonsumiranAkum,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_NozhStart,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_NozhStop,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_ReadyServo,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_ReadyNozh,INPUT_PULLUP);
	pinMode(inPin_Razmotalka_ReadyDisk,INPUT_PULLUP);

	pinMode(outPin_Razmotalka_GlavenMotor,OUTPUT);
        pinMode(outPin_Razmotalka_GlavenMotor_Visoka,OUTPUT);
	pinMode(outPin_Razmotalka_MotorVisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_MotorNisSkorost,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_NozhicaVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDiskOtiva,OUTPUT);
	pinMode(outPin_Razmotalka_StartNozhicaDiskVrashta,OUTPUT);
	pinMode(outPin_Razmotalka_EnableSevo,OUTPUT);
	pinMode(outPin_Razmotalka_EnableNozh_Disc,OUTPUT);
	pinMode(outPin_Razmotalka_Vakum,OUTPUT);
	
	pinMode(pin_material_podaden,INPUT);
	pinMode(pin_presa_udarila,INPUT);
	pinMode(pin_material_vzet,OUTPUT);
        pinMode(pin_razmotalka_nozh_razreshenie, INPUT);
        pinMode(pin_razmotalka_stoper, OUTPUT);
        pinMode(13,INPUT_PULLUP);



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


	for (int k=0; k<5;k++) // Take 5 readings for all inputs
	{
		digital_1[k] = digitalRead(inPin_IzhMan_KraenIzklNach);
		digital_2[k] = digitalRead(inPin_IzhMan_KraenIzklKrai);
		digital_3[k] = digitalRead(inPin_IzhMan_ReperNach);
		digital_4[k] = digitalRead(inPin_IzhMan_ReperKrai);
		digital_5[k] = digitalRead(inPin_IzhMan_GornoPolozhenie);
		digital_6[k] = digitalRead(inPin_IzhMan_DolnoPolozhenie);
		
		digital_7[k] = digitalRead(inPin_Razmotalka_SenzorFolio1);
		digital_8[k] = digitalRead(inPin_Razmotalka_SenzorFolio2);
		digital_9[k] = digitalRead(inPin_Razmotalka_DatAkumFolio);
		digital_10[k] = digitalRead(inPin_Razmotalka_DatIzkonsumiranAkum);
		digital_11[k] = digitalRead(pin_razmotalka_nozh_razreshenie);
		digital_12[k] = digitalRead(inPin_Razmotalka_NozhStart);
		digital_13[k] = digitalRead(inPin_Razmotalka_NozhStop);
		digital_14[k] = digitalRead(inPin_Razmotalka_ReadyServo);
		digital_15[k] = digitalRead(inPin_Razmotalka_ReadyNozh);
		digital_16[k] = digitalRead(inPin_Razmotalka_ReadyDisk);
		digital_17[k] = digitalRead(pin_material_podaden);
		digital_18[k] = digitalRead(pin_presa_udarila);

				
		delayMicroseconds(4);
	}

	// Check if all 5 readings are the same. If they are the same, store the value. If not, go to the next value. 
	
	if(digital_1[0]==digital_1[1] && digital_1[0]==digital_1[2]&& digital_1[0]==digital_1[3]&& digital_1[0]==digital_1[4])
	{
		in_IzhMan_KraenIzklNach = digital_1[0];
	}
	if(digital_2[0]==digital_2[1] && digital_2[0]==digital_2[2]&& digital_2[0]==digital_2[3]&& digital_2[0]==digital_2[4])
	{
		in_IzhMan_KraenIzklKrai = digital_2[0];
	}
	if(digital_3[0]==digital_3[1] && digital_3[0]==digital_3[2]&& digital_3[0]==digital_3[3]&& digital_3[0]==digital_3[4])
	{
		in_IzhMan_ReperNach = digital_3[0];
	}
	if(digital_4[0]==digital_4[1] && digital_4[0]==digital_4[2]&& digital_4[0]==digital_4[3]&& digital_4[0]==digital_4[4])
	{
		in_IzhMan_ReperKrai = digital_4[0];
	}
	if(digital_5[0]==digital_5[1] && digital_5[0]==digital_5[2]&& digital_5[0]==digital_5[3]&& digital_5[0]==digital_5[4])
	{
		in_IzhMan_GornoPolozhenie = digital_5[0];
	}
	if(digital_6[0]==digital_6[1] && digital_6[0]==digital_6[2]&& digital_6[0]==digital_6[3]&& digital_6[0]==digital_6[4])
	{
		in_IzhMan_DolnoPolozhenie = digital_6[0];
	}
	if(digital_7[0]==digital_7[1] && digital_7[0]==digital_7[2]&& digital_7[0]==digital_7[3]&& digital_7[0]==digital_7[4])
	{
		in_Razmotalka_SenzorFolio1 = digital_7[0];
	}
	if(digital_8[0]==digital_8[1] && digital_8[0]==digital_8[2]&& digital_8[0]==digital_8[3]&& digital_8[0]==digital_8[4])
	{
		in_Razmotalka_SenzorFolio2 = digital_8[0];
	}
	if(digital_9[0]==digital_9[1] && digital_9[0]==digital_9[2]&& digital_9[0]==digital_9[3]&& digital_9[0]==digital_9[4])
	{
		in_Razmotalka_DatAkumFolio = digital_9[0];
	}
	if(digital_10[0]==digital_10[1] && digital_10[0]==digital_10[2]&& digital_10[0]==digital_10[3]&& digital_10[0]==digital_10[4])
	{
		in_Razmotalka_DatIzkonsumiranAkum = digital_10[0];
	}
	if(digital_11[0]==digital_11[1] && digital_11[0]==digital_11[2]&& digital_11[0]==digital_11[3]&& digital_11[0]==digital_11[4])
	{
		razmotalka_nozh_razreshenie = digital_11[0];
	}
	if(digital_12[0]==digital_12[1] && digital_12[0]==digital_12[2]&& digital_12[0]==digital_12[3]&& digital_12[0]==digital_12[4])
	{
		in_Razmotalka_NozhStart = digital_12[0];
	}
	if(digital_13[0]==digital_13[1] && digital_13[0]==digital_13[2]&& digital_13[0]==digital_13[3]&& digital_13[0]==digital_13[4])
	{
		in_Razmotalka_NozhStop = digital_13[0];
	}
	if(digital_14[0]==digital_14[1] && digital_14[0]==digital_14[2]&& digital_14[0]==digital_14[3]&& digital_14[0]==digital_14[4])
	{
		in_Razmotalka_ReadyServo  = digital_14[0];
	}
	if(digital_15[0]==digital_15[1] && digital_15[0]==digital_15[2]&& digital_15[0]==digital_15[3]&& digital_15[0]==digital_15[4])
	{
		in_Razmotalka_ReadyNozh = digital_15[0];
	}
	if(digital_16[0]==digital_16[1] && digital_16[0]==digital_16[2]&& digital_16[0]==digital_16[3]&& digital_16[0]==digital_16[4])
	{
		in_Razmotalka_ReadyDisk = digital_16[0];
	}
		if(digital_17[0]==digital_17[1] && digital_17[0]==digital_17[2]&& digital_17[0]==digital_17[3]&& digital_17[0]==digital_17[4])
	{
		material_podaden = digital_17[0];
	}
	if(digital_18[0]==digital_18[1] && digital_18[0]==digital_18[2]&& digital_18[0]==digital_18[3]&& digital_18[0]==digital_18[4])
	{
		presa_udarila = digital_18[0];
	}
	
	
	if (material_podaden == false && presa_udarila == false )
	// if the input manipulator and the press have finished, restart the output manipulator
	{
		material_vzet = false;
		man_cycle = false;
	}
        digitalWrite(pin_material_vzet, man_cycle); // man_cycle to show that the cycle has finished. The other manipulator will wait until then
        digitalWrite(pin_razmotalka_stoper, razmotalka_stoper); // it show if the cutter of the roller is at end position, this will allow the input manipulator to work

	


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
                  man_dir=true;
                }
                if(in_IzhMan_ReperKrai==true)
                 {
                  man_dir=false;
                }

		digitalWrite(outPin_IzhManipulator_PosokaMotor, man_dir);
		Acc_Motor();  
                ReadSensors();

		if (man_dir == false) // if the manipulator is moving out, this could start the input manipulator.
		{
			material_vzet = true;
                        digitalWrite(pin_material_vzet, man_cycle);
                        Serial.println("Material vzet!");
		}


 
	}
	
	if((in_IzhMan_KraenIzklNach==true || in_IzhMan_KraenIzklKrai==true) && current_speed==man_speed_high )
	// When an end switch is HIGH and the speed is HIGH, decelerate the motor
	{        ReadSensors();
                  
	         if(in_IzhMan_KraenIzklNach==true && man_dir==false)
                {
					Dec_Motor();
                                        ReadSensors();
                }
                if(in_IzhMan_KraenIzklKrai==true  && man_dir==true)
                {
					Dec_Motor();
                                        ReadSensors();
                }
                
	}
	if((in_IzhMan_ReperNach==true || in_IzhMan_ReperKrai==true))
	{
		noTone(outPin_IzhManipulator_PulsMotor);
		if(material_vzet == true && presa_udarila==true) // if the element was taken and the manipulatorstoped, this is a cycle
		{
			man_cycle = true; // when the work is added, another logic should be added too
                        Serial.println("Man Cycle is true");
		}
		current_speed=0;
                Serial.println("Speed is 0");
                Manipulator_Take();
                Manipulator_Drop();
		//delay(1000); // This is where work will happen - to delete
                ReadSensors();
	}

}
void Manipulator_Take()
// Takes the element and gives permission to the roller to cut
{      Serial.println("Manipulator Take");
	if(in_IzhMan_ReperKrai==true)
	{
	  while(in_IzhMan_DolnoPolozhenie==true&& digitalRead(13))
	  {
		ReadSensors();
		digitalWrite(outPin_IzhManipulator_Gore, HIGH);
                Serial.println("First while");
	  }
	  digitalWrite(outPin_IzhManipulator_Vakum, HIGH);
	  while(in_IzhMan_GornoPolozhenie==true&& digitalRead(13))
	  {
		ReadSensors();
		digitalWrite(outPin_IzhManipulator_Gore, LOW);
                Serial.println("third while");
	  }
	}
}

void Manipulator_Drop()
{      
        Serial.println("Manipulator Drop");
	if(in_IzhMan_ReperNach==true)
		{
		  while(in_IzhMan_DolnoPolozhenie==true && digitalRead(13))
		  {
			ReadSensors();
			digitalWrite(outPin_IzhManipulator_Gore, HIGH);
                        Serial.println("First while");
		  }
		  digitalWrite(outPin_IzhManipulator_Vakum, LOW);
		  while(in_IzhMan_GornoPolozhenie==true && digitalRead(13))
		  {
                        Serial.println("Second while");
			ReadSensors();
			digitalWrite(outPin_IzhManipulator_Gore, LOW);
		  }
		}
}
void Acc_Motor()
// Accelerate the motor
{
	int speed_steps = man_speed_high/400;
	for(int i=0; i<man_speed_high;i=i+speed_steps)
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
		delay(1);
	}
	current_speed = man_speed_high;
}

void Dec_Motor()
// Decelerate the motor
{
  int i;
	int speed_steps = man_speed_high/300;
	for(i=man_speed_high; i>man_speed_low; (i=i-speed_steps))
	{
		tone(outPin_IzhManipulator_PulsMotor, i);
		delay(1);
	}
	current_speed = man_speed_low;
}

void Razmotalka()
/*
	This function controls the roller of the machine. 
	
*/
{  
	if(in_Razmotalka_ReadyNozh==false && in_Razmotalka_ReadyServo==false && in_Razmotalka_ReadyDisk==false )
	{	// If the motors are Ready and there is material on the spool, enable the motors and start the program
		digitalWrite(outPin_Razmotalka_EnableSevo, HIGH);
		digitalWrite(outPin_Razmotalka_EnableNozh_Disc, HIGH);

		// Rolling the material control
		if(in_Razmotalka_SenzorFolio1==true && in_Razmotalka_SenzorFolio2==true)
		{ // If no of the sensor is HIGH push the material with high speed
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, HIGH);
                         Serial.println("Motor high speed");
			razmotalka_cycle = false; // when there is no material, we could restart the cycle
		}
		else if(in_Razmotalka_SenzorFolio1==false && in_Razmotalka_SenzorFolio2==true)
		{	// If the sensor 1 is HIGH, start pushing the material with low speed
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, HIGH);  
                        Serial.println("Motor low speed");
                        razmotalka_cycle = false;
		}
		else if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false)
		{	// If the sensor 2 is HIGH, stop the motor
			digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
			digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
		}
		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStop && razmotalka_posoka2==true && razmotalka_block==true )
		{	// If there is a material and it is cur, stop the blades

			digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);	
                        Serial.println("Nozhica vrashta spira");
                          razmotalka_stoper = true;	
                          razmotalka_cycle = true;	
                          razmotalka_block=false;	
		}
	      if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && in_Razmotalka_NozhStart && razmotalka_cycle==false && razmotalka_posoka1==true && razmotalka_block==true)
		{	// If there is a material and it is cut, stop the blades
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
                        razmotalka_stoper = true;
                        razmotalka_block=false;
                          Serial.println("Nozhica otiva spira");		
			razmotalka_cycle = true;		
		}
		// Cutting the material control
		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStop)// && razmotalka_posoka2==true )
		{	// If there is a material and it is still not cut
                          razmotalka_posoka1=true;
                          razmotalka_posoka2=false;
                          razmotalka_block=true;
                         Serial.println("Nozhica otiva");
			
		}
	

		if(in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_cycle==false && in_Razmotalka_NozhStart)// && razmotalka_posoka1==true)
		{	// If there is a material and it is still not cut, start the blades
                           razmotalka_posoka1=false;
                          razmotalka_posoka2=true;
                          razmotalka_block=true;
                         Serial.println("Nozhica vrashta");	
		}
		
                if(razmotalka_posoka1 == false && razmotalka_posoka2==true && razmotalka_cycle==false && in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_nozh_razreshenie)
                {
                       // digitalWrite(outPin_Razmotalka_Vakum, HIGH);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, HIGH);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, HIGH);
                         razmotalka_stoper = false;
                }
                if(razmotalka_posoka2 == false && razmotalka_posoka1==true && razmotalka_cycle==false && in_Razmotalka_SenzorFolio2==false && in_Razmotalka_SenzorFolio1==false && razmotalka_nozh_razreshenie)
                {
                        // digitalWrite(outPin_Razmotalka_Vakum, HIGH);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
			digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, HIGH);
			digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
			digitalWrite(outPin_Razmotalka_NozhicaOtiva, HIGH);
                        razmotalka_stoper = false;
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
		  
		if(in_Razmotalka_DatAkumFolio)
		{	// If there is enough buffer material, stop the spool motor
		  digitalWrite(outPin_Razmotalka_GlavenMotor, HIGH);
		}
                else
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor, LOW);
                }
                if (in_Razmotalka_DatIzkonsumiranAkum==false)
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor_Visoka, HIGH);
                }
                else
                {
                  digitalWrite(outPin_Razmotalka_GlavenMotor_Visoka, LOW);
                }
		

	}
	else
	{
		// Avaria 
                Serial.println("Motors not Ready");
                delay(500);
		digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
		digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
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
	
	digitalWrite(outPin_IzhManipulator_PosokaMotor,LOW);
        Serial.println("Initialize");
	tone(outPin_IzhManipulator_PulsMotor, 500);
	while(in_IzhMan_ReperNach == false && in_IzhMan_ReperKrai == false && digitalRead(13)==true)
	{
		ReadSensors();
	}
	noTone(outPin_IzhManipulator_PulsMotor);

	initial=true;
        current_speed = 0;
}

void Operation()
/*
This function controls the normal operation of the program. It sequences the operations of the machine.
*/
{
	ReadSensors();
 
	//if(material_podaden == true && presa_udarila == true && man_cycle == false ) // ! Add material_vzet to null the previous 2 values
	{
                 if(initial==false)
                {
                  Initialize(); 
                }
		IzhManipulator();
               
	}
         //Razmotalka();


}

void Razmotalka_Test()
{
  ReadSensors();

if( in_Razmotalka_ReadyNozh==false && in_Razmotalka_ReadyDisk==false )
{
   
   
   if(digitalRead(26)==true)
   {
     if(in_Razmotalka_NozhStart)
     {
       posoka2 =false;
       posoka1=true;
     }
     
     if(in_Razmotalka_NozhStop)
     {
       posoka1=false;
       posoka2=true;
     }
     if(posoka1==false && posoka2==false)
     {
       posoka2=true;
     }
     
     
     if(posoka1)
     {
       digitalWrite(outPin_Razmotalka_EnableNozh_Disc, HIGH);
       
       digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW); 
     digitalWrite(outPin_Razmotalka_NozhicaOtiva, HIGH);
     digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
     digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, HIGH);
     }
     if(posoka2)
     {
        digitalWrite(outPin_Razmotalka_EnableNozh_Disc, HIGH);
        
            digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
      digitalWrite(outPin_Razmotalka_NozhicaVrashta, HIGH); 

          digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
     digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, HIGH);

     
     }
   }
   else
   {
      digitalWrite(outPin_Razmotalka_EnableNozh_Disc, LOW);
     digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
     digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
    digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
    digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
   }
   
}
else 
{
     digitalWrite(outPin_Razmotalka_EnableNozh_Disc, LOW);
     digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
     digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
    digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
    digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
  Serial.println("NOT READY");

}
}
void loop()

{

  ReadSensors();
  if (digitalRead(13)==true)
{
  Operation();
 
}
else
{
		digitalWrite(outPin_Razmotalka_StartNozhicaDiskVrashta, LOW);
		digitalWrite(outPin_Razmotalka_StartNozhicaDiskOtiva, LOW);
		digitalWrite(outPin_Razmotalka_NozhicaVrashta, LOW);
		digitalWrite(outPin_Razmotalka_NozhicaOtiva, LOW);
		digitalWrite(outPin_Razmotalka_MotorVisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_MotorNisSkorost, LOW);
		digitalWrite(outPin_Razmotalka_GlavenMotor, LOW);
		digitalWrite(outPin_Razmotalka_EnableSevo, LOW);
		digitalWrite(outPin_Razmotalka_EnableNozh_Disc, LOW);
                 noTone(outPin_IzhManipulator_PulsMotor);
                 Serial.println("Press the button");
    delay(1000);
}

/*
if(digitalRead(13)==false)
{
  Operation();
}
else
{
  noTone(outPin_IzhManipulator_PulsMotor);
  Serial.print(material_podaden);
  Serial.print(presa_udarila);
  Serial.println(material_vzet);
  delay(500);
  
}

*/
/*	if(initial==false)
		{
			Initialize();
                        Serial.println("Initialized");
		}
	ReadSensors();
        IzhManipulator();
*/

}