#pragma region Includes
#pragma endregion Includes

#pragma region Variables
#pragma endregion Variables

void setup() {
#pragma region Setup
pinMode(LED_BUILTIN, OUTPUT);
#pragma endregion Setup
}

// the loop function runs over and over again forever
void loop() {
#pragma region Loop                                    
digitalWrite(LED_BUILTIN, HIGH);  
  delay(2000);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(2000);                      
#pragma endregion Loop
}
