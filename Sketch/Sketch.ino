#pragma region Includes
#pragma endregion Includes

#pragma region Variables
#pragma endregion Variables

void setup() {
Serial.begin(9600);
Serial.println("Ready!!!");
#pragma region Setup
#pragma endregion Setup
}

// the loop function runs over and over again forever
void loop() {
String Message = "#";
#pragma region Loop      #pragma endregion Loop

//loop ends here
	Message += "*";
	if (Message != "#*"){
		Serial.print(Message);
	}
}
