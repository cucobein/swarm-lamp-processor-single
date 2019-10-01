const unsigned char column_height = 12;
const unsigned char bit_duration = 30;
const unsigned char pin = 22;

typedef struct {
  unsigned char x;
  unsigned char y;
  unsigned char z;
} tCard;
tCard cards[column_height];

unsigned char val = 200;

void setup() {
  //Serial.begin(38400);
  initOutputs();
}

void loop() {
  initStruct();
  refreshData();
  delay(30);
}

// MARK: Init
void initStruct() {
//  val = (val + 10);
//  if(val >= 200) {
//    val = 100;
//  }
  for(int i = 0; i < column_height; i++) {
    cards[i].x = val;
    cards[i].y = val;
    cards[i].z = val;
  }
}

void initOutputs() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

// MARK: Software UART - TX
void refreshData() {
  for(int i = 0; i < column_height; i++) {
    sendStartByte();
    sendAddress(i + 1);
    sendX(cards[i].x);
    sendY(cards[i].y);
    sendZ(cards[i].z);
  }
}

void sendStartByte() { // Anything between [251, 255]
  sendByte(251);
}

void sendAddress(unsigned char address) { // Numbers between [1, 12]
  sendByte(address);
}

void sendX(unsigned char value) { // Numbers between [100, 200]
  sendByte(value);
}

void sendY(unsigned char value) { // Numbers between [100, 200]
  sendByte(value);
}

void sendZ(unsigned char value) { // Numbers between [100, 200]
  sendByte(value);
}

void sendByte(unsigned char value) {
  // Start bit
  setAllLow();
  delayMicroseconds(bit_duration);
  // 8-bit
  for (int bt = 0; bt < 8; bt++)
  {
    unsigned char bit_val = ((value >> bt) & 0x01);
    if(bit_val == 1) {
      digitalWrite(pin, HIGH);
    } else {
      digitalWrite(pin, LOW);
    }
    delayMicroseconds(bit_duration);
  }
  // Stop bit
  setAllHigh();
  delayMicroseconds(bit_duration);
}

void setAllLow() {
  digitalWrite(pin, LOW);
}

void setAllHigh() {
  digitalWrite(pin, HIGH);
}

//unsigned int rand_interval(unsigned int min, unsigned int max)
//{
//    int r;
//    const unsigned int range = 1 + max - min;
//    const unsigned int buckets = RAND_MAX / range;
//    const unsigned int limit = buckets * range;
//
//    /* Create equal size buckets all in a row, then fire randomly towards
//     * the buckets until you land in one of them. All buckets are equally
//     * likely. If you land off the end of the line of buckets, try again. */
//    do
//    {
//        r = rand();
//    } while (r >= limit);
//
//    return min + (r / buckets);
//}
