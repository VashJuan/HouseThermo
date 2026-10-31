/**
 * @file secrets_template.h
 * @brief Template for WiFi and other sensitive configuration constants
 * @note Copy this file to secrets.h and update with your actual credentials
 * 
 * This is a template file that can be safely committed to version control.
 * It shows the structure of the secrets.h file without exposing actual credentials.
 */

#pragma once

// WiFi Configuration - Replace with your actual credentials in secrets.h
#define DEFAULT_WIFI_SSID "your_wifi_network_name"
#define DEFAULT_WIFI_PASSWORD "your_wifi_password"

// LoRaWAN Configuration - Replace with your actual LoRaWAN credentials in secrets.h
// Obtain these from your LoRaWAN network provider (e.g., The Things Network)
#define LORAWAN_APP_EUI "0000000000000000"        // 16 hex chars - Application EUI from network provider
#define LORAWAN_APP_KEY "00000000000000000000000000000000"  // 32 hex chars - Application Key from network provider

// Note: Both transmitter and receiver should use the same AppEUI and AppKey
// when they belong to the same LoRaWAN application

// You can add other sensitive configuration here as needed
// For example:
// #define API_KEY "your_api_key_here"
// #define MQTT_USERNAME "your_mqtt_username"
// #define MQTT_PASSWORD "your_mqtt_password"