#pragma region Includes
#pragma endregion Includes

#pragma region Variables
#pragma endregion Variables

void setup() {
#pragma region Setup
Serial.begin(9600);
#pragma endregion Setup
}

// the loop function runs over and over again forever
void loop() {
String Message = "#";
#pragma region Loop            
#pragma endregion Loop

//loop ends here
	Message += "*";
	if (Message != "#*"){
		Serial.print(Message);
	}
}
