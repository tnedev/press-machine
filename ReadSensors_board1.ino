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
	unsigned long analog_sum=0;

	for (int k=0; k<5;k++)
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
		
		
		delayMicroseconds(4);
	}
	
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
	if(digital_10[0]==digital_11[1] && digital_11[0]==digital_11[2]&& digital_11[0]==digital_11[3]&& digital_11[0]==digital_11[4])
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

	for (int k=0; k<50;k++)
	{
		analog_sum = analog_sum+analogRead(A0);
	}
	in_Presa_Pressure = analog_sum/50;

	

}