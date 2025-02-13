/* Ali Safarli made with AI */

#include <ESP8266WiFi.h>          
#include <ESP8266WebServer.h>     
#include "index.h"                // Include the HTML template for the web page
#include "Api.h"                  // Include the API functions
#include "counter.h"              // Include the counter functions

// WiFi credentials
const char* ssid = "";
const char* password = "";      

ESP8266WebServer server(80);     

String publicIP = "";            // Variable to store the public IP address

void setup() {
    Serial.begin(115200);        
    WiFi.begin(ssid, password);  

    // Connect to WiFi
    while (WiFi.status() != WL_CONNECTED) { 
        delay(1000);                
        Serial.println("Connecting to WiFi..."); 
    }
    Serial.println("WiFi connected!"); 
    Serial.print("Local IP: ");         
    Serial.println(WiFi.localIP());     // Note: Local IP is private, not public

    //Get the public IP address
    publicIP = getPublicIP();           // Call function to get the public IP address
    Serial.print(publicIP);             
    Serial.println(" ->Public IP Address");
    
    if (publicIP != "") {                
        //Fetch current time using timeapi.io
        fetchCurrentTime(publicIP);      // Call function to fetch the current time
    }
    
    counterBegin(currentTime);           // Initialize the counter with the current time

    // Set up the web server
    server.on("/", []() {
        String page = pageTemplate;      // Load the HTML template
        String place = "Timezone: " + timeZone; // Create a string for the timezone
        page.replace("%TIMEZONE%", place); // Replace placeholder with actual timezone
        page.replace("%TIME%", "Loading..."); // Replace time placeholder with loading message
        server.send(200, "text/html", page); 
    });

    // Define the remaining time URL handler
    server.on("/remaining-time", []() {
        // Create a string representing the remaining time
        String remainingTimeString = String(hours) + "h " + String(minutes) + "m " + String(seconds) + "s";
        // Create a JSON response with the remaining time
        String jsonResponse = "{\"remainingTime\":\"" + remainingTimeString + "\"}";
        server.send(200, "application/json", jsonResponse); // Send JSON response to the client
    });

    server.begin();                      
    Serial.println("HTTP server started");
}

void loop() {
    count();                            // Call the count function to update the timer
    server.handleClient();              
    delay(100);                         
}
