/*
	This is control program for production line with press machine using Arduino Mega R3
	Last Updata Jul 2013
	Developed by Tihomir Nedev - nedev@chipolabs.com
	This Code is for board 1 out of 2 bords for the control 

	With this board we will control the functions of the Press, Container and both manipulators

*/

/*
	Arduino pins set up
	names formation - "inPin"/"outPin"+Function_name+ name
	The values links the pin number with the name
*/

byte inPin_Presa_KraenIzklGoren = 1;
byte inPin_Presa_KraenIzklSreden = 2;
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
	Arduino variables declaration
	names formation - "in"/"out" + Function_name + name
*/

boolean in_Presa_KraenIzklGoren = false;
boolean in_Presa_KraenIzklSreden = false;
boolean in_Presa_KraenIzklDolen = false;
boolean in_Presa_VhStrana = false;
boolean in_Presa_IzhStrana = false;
boolean in_Presa_VklGlavenMoror = false;
boolean in_Presa_AvariaGlavenMotor = false;

boolean out_Presa_Nagore = false;
boolean out_Presa_Nadolu = false;
boolean out_Presa_Vakum = false;
boolean out_Presa_Vazduh = false;


boolean in_Konteiner_KrainIzklGoren = false;
boolean in_Konteiner_KrainIzklDolen = false;
boolean in_Konteiner_Nivo = false;
boolean in_Konteiner_MotorRaboti = false;
boolean in_Konteiner_MotorAvaria = false;
boolean in_Konteiner_BroyachPresa = false;
boolean in_Konteiner_Material = false;

boolean out_Konteiner_CilindarGore = false;
boolean out_Konteiner_CilindarDolu  = false;


boolean in_VhMan_KraenIzklGoren = false;
boolean in_VhMan_KraenIzklDolen = false;
boolean in_VhMan_Reper = false;
boolean in_VhMan_GornoPolozhenie = false;
boolean in_VhMan_DolnoPolozhenie = false;
boolean in_VhMan_Material = false;

boolean out_VhManipulator_Gore = false;
boolean out_VhManipulator_Dolu = false;
boolean out_VhManipulator_Vakum = false;
boolean out_VhManipulator_Vazduh = false;
boolean out_VhManipulator_PosokaMotor = false;
boolean out_VhManipulator_PulsMotor = false;


boolean in_IzhMan_KraenIzklGoren = false;
boolean in_IzhMan_KraenIzklDolen = false;
boolean in_IzhMan_Reper = false;
boolean in_IzhMan_GornoPolozhenie = false;
boolean in_IzhMan_DolnoPolozhenie = false;
boolean in_IzhMan_Material = false;

boolean out_IzhManipulator_Gore = false;
boolean out_IzhManipulator_Dolu = false;
boolean out_IzhManipulator_Vakum = false;
boolean out_IzhManipulator_Vazduh = false;
boolean out_IzhManipulator_PosokaMotor = false;
boolean out_IzhManipulator_PulsMotor = false;

void setup()
{

  // Arduino pinmodes set up

	pinMode(inPin_Presa_KraenIzklGoren,INPUT);
	pinMode(inPin_Presa_KraenIzklSreden,INPUT);
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

void loop()
{

  /* add main program code here */

}
