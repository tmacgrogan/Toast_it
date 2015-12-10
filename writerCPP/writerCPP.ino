#include <Servo.h>
#include <math.h>

struct Dest {
  int8_t x;
  int8_t y;
};

struct Letter {
  int8_t dests[15][3];
};

Letter arr [26] = {{{{15,90,0},{50,10,1},{85,90,1},{33,50,0},{66,50,1}}},
                  {{{20,10,0},{20,90,1},{80,66,1},{20,50,1},{80,33,1},{20,10,1}}},
                  {{{80,15,0},{30,15,1},{15,50,1},{30,85,1},{80,85,1}}},
                  {{{15,15,0},{15,85,1},{70,85,1},{85,50,1},{70,15,1},{15,15,1}}},
                  {{{80,15,0},{20,15,1},{20,85,1},{80,85,1},{20,50,0},{60,50,1}}},
                  {{{80,15,0},{20,15,1},{20,85,1},{20,50,0},{60,50,1}}},
                  {{{80,15,0},{30,15,1},{15,50,1},{30,85,1},{80,85,1},{80,50,1},{60,50,1}}},
                  {{{20,15,0},{20,85,1},{80,85,0},{80,15,1},{20,50,0},{80,50,1}}},
                  {{{20,15,0},{80,15,1},{20,85,0},{80,85,1},{50,85,0},{50,15,1}}},
                  {{{15,65,0},{25,85,1},{40,85,1},{50,65,1},{50,15,1},{20,15,0},{80,15,1}}},
                  {{{20,15,0},{20,85,1},{20,50,0},{80,15,1},{20,50,0},{80,85,1}}},
                  {{{20,15,0},{20,85,1},{80,85,1}}},
                  {{{20,85,0},{20,15,1},{50,50,1},{80,15,1},{80,85,1}}},
                  {{{20,85,0},{20,15,1},{80,85,1},{80,15,1}}},
                  {{{30,15,0},{15,30,1},{15,70,1},{30,85,1},{70,85,1},{85,70,1},{85,30,1},{70,15,1},{30,15,1}}},
                  {{{20,85,0},{20,15,1},{80,15,1},{80,50,1},{20,50,1}}},
                  {{{30,15,0},{15,30,1},{15,70,1},{30,85,1},{70,85,1},{85,70,1},{85,30,1},{70,15,1},{30,15,1},{70,70,0},{85,85,1}}},
                  {{{20,85,0},{20,15,1},{80,15,1},{80,50,1},{20,50,1},{80,85,1}}},
                  {{{80,15,0},{20,15,1},{20,50,1},{80,50,1},{80,85,1},{20,85,1}}},
                  {{{50,85,0},{50,15,1},{20,15,0},{80,15,1}}},
                  {{{20,15,0},{20,85,1},{80,85,1},{80,15,1}}},
                  {{{20,15,0},{50,85,1},{80,15,1}}},
                  {{{15,15,0},{20,85,1},{50,50,1},{80,85,1},{85,15,1}}},
                  {{{20,15,0},{80,85,1},{20,85,0},{80,15,1}}},
                  {{{20,15,0},{50,50,1},{80,15,1},{50,50,0},{50,85,1}}},
                  {{{20,15,0},{80,15,1},{20,85,1},{80,85,1}}}};

Servo ll;
Servo lr;

Servo ul;
Servo ur;

Servo b;

int currentX = 0;
int currentY = 0;

int speed = 5;
double refresh_rate = 0.005; //seconds

int letterDensity = 5;
int pixelDensity = 1000;

String TEXT = "";

void setup() {
  //fillArr();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  // put your setup code here, to run once:
  ll.attach(2);
  lr.attach(3);
  ul.attach(4);
  ur.attach(5);
  b.attach(6);
  Serial.begin(9600);
  Serial.write("Initializing...\n");
  //drive_line({0,0},0);
  reset();
  analogWrite(10, 0);
  Serial.write("Ready for input.\n");
  while(1){
    if(Serial.available()){
      char c = Serial.read();
      if(c=='\n'){
//        Serial.write("recieved string '");
//        Serial.print(TEXT);
//        Serial.write("'\n");
        break;
      }
      else{
        TEXT += c;
      }
    }
  }
}

void reset(){
  upper_cart(0);
  lower_cart(0);
  currentX = 0;
  currentY = 0;
  burn(0);
}


void loop() {
//  Serial.print("text length is ");
//  Serial.print(TEXT.length());
//  Serial.print(TEXT.charAt(0));
//  Serial.print(TEXT.charAt(1));
  for(int i = 0; i < TEXT.length()-1; i++ ){
    if(TEXT.charAt(i) == ' '){
      continue;
    }
    write_letter(TEXT.charAt(i), i);
  }
//  Serial.write("done");
//  while(1==1){
//    
//    
//  }
//  analogWrite(10, 128);
  
//  upper_cart(100);
//
//  delay(1000);
//
//  upper_cart(10);
//
//  analogWrite(10, 255);

//  drive_line({100,100}, 1);
  
  drive_line({0,0},0);

  while(1){
    
    
  }
}

void percent(Servo servo, double percent){
  servo.write((percent * 1.7) + 10);
}

void lower_cart(double y){
  percent(lr, 100-y);
  percent(ll, y);
}

void upper_cart(double x){
  percent(ur, 100-x);
  percent(ul, x);
}

void burn(bool burning){
//  Serial.write("burning\n");
  percent(b, burning?0:90);
//  Serial.write("burnt\n");
}

void drive_line(Dest d, bool burning){
  burn(burning);
  int x1 = currentX;
  int y1 = currentY;
  int x2 = d.x;
  int y2 = d.y;
  int dx = x2 - x1;
  int dy = y2 - y1;
  
//  Serial.write("getting length\n");
  double length = sqrt((dx*dx) + (dy*dy));
//  Serial.write("getting duration\n");
  double duration = length / speed;
  int refreshes = duration/refresh_rate;
  for(int i = 0; i < refreshes; i++){
    double y = ((double)i/(double)refreshes) * dy + y1;
    double x = ((double)i/(double)refreshes) * dx + x1;
    lower_cart(y);
    upper_cart(x);
    delay(refresh_rate*1000);
  }
//  Serial.write("FINISHED\n");
  currentX = x2;
  currentY = y2;
}

void write_letter(char letter, int frameNum){
  double ox = (frameNum % letterDensity) * 100 / letterDensity;
  double oy = (frameNum / letterDensity) * 100 / letterDensity + 10;
  Letter l = arr[letter - 'A'];
//  Serial.print("printing letter " + letter);
  for(int i = 0; i < 15; i++){
    if(l.dests[i][0] != 0 || l.dests[i][1] != 0 || l.dests[i][2] != 0){
      Dest target = {(l.dests[i][0]/letterDensity) + ox, (l.dests[i][1]/letterDensity) + oy};
      drive_line(target, (l.dests[i][2] != 0));
    }
  }
}























