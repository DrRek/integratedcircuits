#include <gprs.h>

#define PIN_TX    7  // Has already exchanged TX and RX pins
#define PIN_RX    8
#define SWITCH_ON_GPRS 2

void init_gprs();

void send_http_message(char* data);
