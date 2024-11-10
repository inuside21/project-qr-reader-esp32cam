// QR READER
#include <ESP32QRCodeReader.h>
ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

// FLASH
int outPinFlash = 4;

// RELAY
int outPinDoor1 = 12;
int outPinDoor2 = 13;
int outPinDoor3 = 15;
int outPinDoor4 = 14;

// VAR
String sPass1 = "TestDoor1";
String sPass2 = "TestDoor2";
String sPass3 = "TestDoor3";
String sPass4 = "TestDoor4";



// START
// ====================================
void setup()
{
  //
  Serial.begin(9600);
  Serial.println();

  //
  reader.setup();
  reader.beginOnCore(1);
  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);

  //
  pinMode(outPinFlash, OUTPUT); digitalWrite(outPinFlash, HIGH);

  //
  pinMode(outPinDoor1, OUTPUT); digitalWrite(outPinDoor1, LOW);
  pinMode(outPinDoor2, OUTPUT); digitalWrite(outPinDoor2, LOW);
  pinMode(outPinDoor3, OUTPUT); digitalWrite(outPinDoor3, LOW);
  pinMode(outPinDoor4, OUTPUT); digitalWrite(outPinDoor4, LOW);
}


// LOOP
// ====================================
void loop()
{
  
}


// FUNCTION
// ====================================
void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;

  while (true)
  {
    Serial.println("nope");
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
      
        if ((const char *)qrCodeData.payload == sPass1)
        {
          Serial.print("DOOR 1 UNLOCK");
          digitalWrite(outPinDoor1, HIGH);
          digitalWrite(outPinFlash, LOW);
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          digitalWrite(outPinDoor1, LOW);
          digitalWrite(outPinFlash, HIGH);
          Serial.print("DOOR 1 LOCK");
        }

        if ((const char *)qrCodeData.payload == sPass2)
        {
          Serial.print("DOOR 2 UNLOCK");
          digitalWrite(outPinDoor2, HIGH);
          digitalWrite(outPinFlash, LOW);
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          digitalWrite(outPinDoor2, LOW);
          digitalWrite(outPinFlash, HIGH);
          Serial.print("DOOR 2 LOCK");
        }

        if ((const char *)qrCodeData.payload == sPass3)
        {
          Serial.print("DOOR 3 UNLOCK");
          digitalWrite(outPinDoor3, HIGH);
          digitalWrite(outPinFlash, LOW);
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          digitalWrite(outPinDoor3, LOW);
          digitalWrite(outPinFlash, HIGH);
          Serial.print("DOOR 3 LOCK");
        }

        if ((const char *)qrCodeData.payload == sPass4)
        {
          Serial.print("DOOR 4 UNLOCK");
          digitalWrite(outPinDoor4, HIGH);
          digitalWrite(outPinFlash, LOW);
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          digitalWrite(outPinDoor4, LOW);
          digitalWrite(outPinFlash, HIGH);
          Serial.print("DOOR 4 LOCK");
        }
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
