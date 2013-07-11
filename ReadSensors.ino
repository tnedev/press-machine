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
	in_VhMan_KraenIzklKrai = digitalRead(inPin_VhMan_KraenIzklKrai);
	in_VhMan_ReperNach = digitalRead(inPin_VhMan_ReperNach);
	in_VhMan_ReperKrai = digitalRead(inPin_VhMan_ReperKrai);
	in_VhMan_GornoPolozhenie = digitalRead(inPin_VhMan_GornoPolozhenie);
	in_VhMan_DolnoPolozhenie = digitalRead(inPin_VhMan_DolnoPolozhenie);
	
	in_Nozhica_GornoPolozh = digitalRead(inPin_Nozhica_GornoPolozh);
	in_Nozhica_DolnoPolozh = digitalRead(inPin_Nozhica_DolnoPolozh);
	in_Nozhica_Ready1_1 = digitalRead(inPin_Nozhica_Ready1_1);
	in_Nozhica_Ready1_2 = digitalRead(inPin_Nozhica_Ready1_2);
	in_Nozhica_Ready2_1 = digitalRead(inPin_Nozhica_Ready2_1);
	in_Nozhica_Ready2_2 = digitalRead(inPin_Nozhica_Ready2_2);
	in_Nozhica_Ready2_2 = digitalRead(inPin_Nozhica_Ready2_2);
	

}