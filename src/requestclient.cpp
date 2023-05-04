#include "requestclient.h"

// MQTT Information
const char *mqtt_server = "cloud.tbz.ch";
const char *clientId = "m1Stack";
const char *username = "";
const char *password = "";

// WIFI Information
const char *ssid = "LERNKUBE";
const char *passphrase = "lernkube";

// Vars
WiFiClient espClient;
PubSubClient client(espClient);

// Functions
void setup_wifi()
{
    Serial.println("Connecting to: " + String(ssid));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(".");
    }

    Serial.println("\nSuccess\n");
}

void mqtt_loop()
{
    if (client.state() != MQTT_CONNECTED)
    {
        mqtt_re_connect();
    }
    client.loop();
}

void mqtt_init(MQTT_CALLBACK_SIGNATURE)
{
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    mqtt_re_connect();
}

void mqtt_publish(const char *topic, const char *payload)
{
    client.publish(topic, payload);
    Serial.println("requestclient#mqtt_publish: Published: " + String(payload) + " to " + String(topic));
}

void mqtt_re_connect()
{
    while (client.state() != MQTT_CONNECTED)
    {
        Serial.println("Attempting to connect to MQTT...");

        String randomClientId = clientId + String("-" + random(0xffff), HEX);
        if (client.connect(randomClientId.c_str()))
        {
            client.subscribe("garage/#");
            Serial.println("MQTT connected");
        }
        else
        {
            Serial.println("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
        }
    }
}
