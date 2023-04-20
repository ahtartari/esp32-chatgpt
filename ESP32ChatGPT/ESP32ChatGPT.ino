/*
   Based on the ChatGPT library by Eric Nam
*/

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ChatGPT.hpp>

static const char *ssid = "user";
static const char *password = "password";

WiFiClientSecure client;
ChatGPT<WiFiClientSecure> chat_gpt(&client, "v1", "yourkey");

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network: ");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected!");

  // Ignore SSL certificate validation
  client.setInsecure();

}

void loop() {

  String result;

  if (Serial.available()) {
    String msg = Serial.readString();
    msg.trim();
    Serial.print("You: ");
    Serial.println(msg);
    if (chat_gpt.simple_message("gpt-3.5-turbo-0301", "user", msg, result)) {
      Serial.print("ChatGPT: ");
      String resposta = result;
      resposta.trim();
      Serial.println(resposta);
    } else {
      Serial.println("===ERROR===");
      Serial.println(result);
    }
    Serial.println();
  }
}
