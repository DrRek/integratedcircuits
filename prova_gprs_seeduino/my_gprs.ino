#define DEFAULT_TIMEOUT     5
#define SIM800_TX_PIN           7
#define SIM800_RX_PIN           8

SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);

void sendCmd(const char* cmd) {
    serialSIM800.write(cmd);
}

int waitForResp(const char* resp, unsigned int timeout) {
    int len = strlen(resp);
    int sum = 0;
    unsigned long timerStart;
    timerStart = millis();

    while (1) {
        if (serialSIM800.available()) {
            char c = serialSIM800.read();
            sum = (c == resp[sum]) ? sum + 1 : 0;
            if (sum == len) {
                break;
            }
        }
        if (millis() - timerStart > 1000 * timeout) {
            return -1;
        }
    }

    while (serialSIM800.available()) {
        serialSIM800.read();
    }

    return 0;
}

int sendCmdAndWaitForResp(const char* cmd, const char* resp, unsigned timeout) {
    sendCmd(cmd);
    return waitForResp(resp, timeout);
}

int checkSIMStatus(void) {
    char gprsBuffer[32];
    int count = 0;
    cleanBuffer(gprsBuffer, 32);
    while (count < 3) {
        sendCmd("AT+CPIN?\r\n");
        readBuffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
        if ((NULL != strstr(gprsBuffer, "+CPIN: READY"))) {
            break;
        }
        count++;
        delay(300);
    }
    if (count == 3) {
        return -1;
    }
    return 0;
}

int readBuffer(char* buffer, int count, unsigned int timeOut) {
    int i = 0;
    unsigned long timerStart;
    timerStart = millis();
    while (1) {
        while (serialSIM800.available()) {
            char c = serialSIM800.read();
            if (c == '\r' || c == '\n') {
                c = '$';
            }
            buffer[i++] = c;
            if (i > count - 1) {
                break;
            }
        }
        if (i > count - 1) {
            break;
        }
        if (millis() - timerStart > 1000 * timeOut) {
            break;
        }
    }
    delay(500);
    while (serialSIM800.available()) {  // display the other thing..
        serialSIM800.read();
    }
    return 0;
}

void cleanBuffer(char* buffer, int count) {
    for (int i = 0; i < count; i++) {
        buffer[i] = '\0';
    }
}

void main(void){
  while(sendCmdAndWaitForResp("AT\r\n", "OK\r\n", DEFAULT_TIMEOUT * 3) != 0){
    Serial.println("1. Errore comando AT");
    delay(1000);
  }
  Serial.println("Problema risolto");
  
  while(sendCmdAndWaitForResp("AT+CFUN=1\r\n", "OK\r\n", DEFAULT_TIMEOUT * 3) != 0){
    Serial.println("2. Errore comando AT+CFUN=1");
    delay(1000);
  }
  Serial.println("Problema risolto");

  while(checkSIMStatus() != 0){
    Serial.println("3. Errore comando AT+CPIN?");
    delay(1000);
  }
  Serial.println("Problema risolto");

  while(sendCmdAndWaitForResp("AT+CSTT=\"TM\"\r\n", "OK\r\n", DEFAULT_TIMEOUT * 3) != 0){
    Serial.println("4. Errore comando AT+CSTT=\"TM\"");
    delay(1000);
  }
  Serial.println("Problema risolto");

  sendCmd("AT+CIICR\r\n");

  //Get local IP address
  char ipAddr[32];
  do {
    Serial.print("Provo a prendere l'ip: ");
    cleanBuffer(ipAddr, 32);
    sendCmd("AT+CIFSR\r\n");
    readBuffer(ipAddr, 32, 2);
  } while(NULL == strstr(ipAddr, "ERROR"))
  Serial.println(ipAddr);


}
