#include <ESP8266HTTPClient.h>  // Include the HTTP client library for making HTTP requests
#include <ArduinoJson.h>        // Include the ArduinoJson library for parsing JSON data

String currentTime = "";       // Variable to store the current time
String timeZone = "";          // Variable to store the time zone

// Function to get the public IP address
String getPublicIP() {
    WiFiClient client;         // Create a WiFiClient for the HTTP request
    String ip = "";      

    // Connect to the IP fetching service
    if (client.connect("api.ipify.org", 80)) {
        // Send HTTP GET request
        client.println("GET / HTTP/1.1");
        client.println("Host: api.ipify.org");
        client.println("Connection: close");
        client.println();

        // Read the response
        while (client.connected() || client.available()) {
            if (client.available()) {
                ip = client.readStringUntil('\n');
                Serial.println(ip);                 
            }
        }
    } else {
        Serial.println("Connection failed"); // Print error if connection fails
    }
    return ip; // Return the fetched IP address
}

// Function to fetch the current time based on the public IP address
void fetchCurrentTime(String ip) {
    WiFiClientSecure client; // Create a secure WiFiClient for HTTPS requests
    HTTPClient http;         // Create an HTTPClient for making requests

    client.setInsecure();    // Disable SSL certificate verification (not recommended for production)

    // Construct the URL for fetching the current time
    String url = "https://timeapi.io/api/Time/current/ip?ipAddress=" + ip;

    // Start the HTTP request
    http.begin(client, url);
    int httpCode = http.GET(); // Send the GET request

    if (httpCode > 0) { // Check if the request was successful
        String payload = http.getString(); // Get the response payload
        Serial.println("TimeAPI Response: ");
        Serial.println(payload); // Print the response payload

        // Parse the JSON response
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.f_str()); // Print error if JSON parsing fails
            return;
        }

        // Extract current time and timezone from the JSON document
        currentTime = doc["dateTime"].as<String>();
        timeZone = doc["timeZone"].as<String>();
        Serial.println("Current Time: " + currentTime); // Print the current time
        Serial.println("Time Zone: " + timeZone);       // Print the time zone
    } else {
        Serial.println("Failed to fetch time from timeapi.io. HTTP Code: " + String(httpCode)); // Print error if fetching fails
    }
    http.end(); // End the HTTP connection
}
