#ifndef _LORA_FUNCTIONS_H_
#define _LORA_FUNCTIONS_H_

#include <Arduino.h>
#include <configuration.h>
#include <debugconf.h>
#include <aprs_functions.h>

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnRxTimeout(void);
void OnRxError(void);
bool is_new_packet(uint8_t compBuffer[4]);
bool checkLoraRxBuffer(uint8_t compBuffer[4]);

#endif