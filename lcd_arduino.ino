#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Updated LCD pin configuration
byte DINO_PARADO_PARTE_1[8] = { B00000, B00000, B00010, B00010, B00011,
                                B00011, B00001, B00001 };
byte DINO_PARADO_PARTE_2[8] = { B00111, B00111, B00111, B00100, B11100,
                                B11100, B11000, B01000 };
byte DINO_PIE_DERE_PART_1[8] = { B00000, B00000, B00010, B00010, B00011,
                                 B00011, B00001, B00001 };
byte DINO_PIE_DERE_PART_2[8] = { B00111, B00111, B00111, B00100, B11100,
                                 B11100, B11000, B00000 };
byte DINO_PIE_IZQU_PART_1[8] = { B00000, B00000, B00010, B00010, B00011,
                                 B00011, B00001, B00000 };
byte DINO_PIE_IZQU_PART_2[8] = { B00111, B00111, B00111, B00100, B11100,
                                 B11100, B11000, B01000 };
byte DOS_RAMAS_PART_1[8] = { B00000, B00100, B00100, B10100, B10100,
                             B11100, B00100, B00100 };
byte DOS_RAMAS_PART_2[8] = { B00100, B00101, B00101, B10101, B11111,
                             B00100, B00100, B00100 };
byte AVE_ALAS_PART1[8] = { B00001, B00001, B00001, B00001, B01001, B11111,
                           B00000, B00000 };
byte AVE_ALAS_PART2[8] = { B00000, B10000, B11000, B11100, B11110, B11111,
                           B00000, B00000 };
// Define variables
int columna_dino1 = 1;
int columna_dino2 = 2;
int fila_dino = 1;
unsigned long reloj = 0;
int periodo = 100;
int flag = 1;
int fila_rama = 0;
int columna_rama = 13;
int periodo2 = 100;
unsigned long reloj2 = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long reloj3 = 0;
int periodo3 = 100;

int puntos = 0;
int punto2 = 0;
int numerorandom = 0;
int columnaave = 13;
int e = 0;
int fila_ave = 1;
int senalactual = 0;
int senalantigua = 0;
int f = 13;
int aceleracion = 1;
unsigned long reloj4 = 0;
int periodo4 = 800;
const int buttonPin = 8;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.createChar(0, DINO_PARADO_PARTE_1);
  lcd.createChar(1, DINO_PARADO_PARTE_2);
  lcd.createChar(2, DINO_PIE_DERE_PART_1);
  lcd.createChar(3, DINO_PIE_DERE_PART_2);
  lcd.createChar(4, DINO_PIE_IZQU_PART_1);
  lcd.createChar(5, DINO_PIE_IZQU_PART_2);
  lcd.createChar(6, DOS_RAMAS_PART_1);
  lcd.createChar(7, DOS_RAMAS_PART_2);
}
void loop() {
  int buttonState = digitalRead(buttonPin);
  if (millis() > reloj + periodo) {
    reloj = millis();
    flag = (flag == 1) ? 2 : 1;
  }
  updateObstacles();
  updateScore();
  if (d == 0) {
    updateDinoPosition();
  }
  if (buttonState == LOW) {
    jump();
  }
  if ((columna_rama == b || columna_rama == c) && fila_rama == 1) {

    gameOver();
  }
  senalactual = digitalRead(buttonPin);
  if (senalactual != senalantigua) {
    lcd.setCursor(1, 0);
    lcd.print(" ");
  }
  senalantigua = senalactual;
}
void jump() {
  unsigned long jumpStartTime = millis();
  unsigned long jumpDuration = 500;  // Adjust this value to change jump
  duration while (millis() - jumpStartTime < jumpDuration) {
    // Clear previous Dino position
    lcd.setCursor(columna_dino1, fila_dino);
    lcd.write(' ');
    lcd.setCursor(columna_dino2, fila_dino);
    lcd.write(' ');
    // Update Dino position to simulate jump
    lcd.setCursor(columna_dino1, 0);  // Move Dino to the top row
    lcd.write(byte(0));               // Use the correct byte for the top part of the Dino
    lcd.setCursor(columna_dino2, 0);
    lcd.write(byte(1));  // Use the correct byte for the top part of the Dino
    // Check for collision with branch or bird during jump
    if ((columna_rama == b || columna_rama == c) && fila_rama == 0) {
      gameOver();
      return;
    }
    // Update obstacles and score during jump
    updateObstacles();
    updateScore();
    delay(10);  // Small delay to control the loop speed
  }
  // Clear Dino's jump position
  lcd.setCursor(columna_dino1, 0);
  lcd.write(' ');
  lcd.setCursor(columna_dino2, 0);
  lcd.write(' ');

  // Return Dino to the bottom row
  fila_dino = 1;
  updateDinoPosition();
}
void updateObstacles() {
  if (millis() > reloj2 + periodo2) {
    reloj2 = millis();
    columna_rama = columna_rama - 1;
    if (columna_rama < 0) {
      columna_rama = 13;
      periodo2 = periodo2 - aceleracion;  // Acceleration
      numerorandom = random(0, 3);        // Randomize branch or bird
    }
    lcd.setCursor(columna_rama + 1, 1);
    lcd.print(" ");
    lcd.setCursor(columna_rama + 1, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(0, 0);
    lcd.print(" ");
    a = 1;
  }
  if (a == 1) {
    if (numerorandom == 1 || numerorandom == 2) {
      fila_rama = 1;
      lcd.createChar(numerorandom == 1 ? 6 : 7, numerorandom == 1 ? DOS_RAMAS_PART_1 : DOS_RAMAS_PART_2);
      lcd.setCursor(columna_rama, fila_rama);
      lcd.write(byte(numerorandom == 1 ? 6 : 7));
    } else {
      columnaave = columna_rama - 1;
      fila_rama = 0;
      lcd.createChar(6, AVE_ALAS_PART1);
      lcd.setCursor(columnaave, fila_rama);
      lcd.write(byte(6));
      lcd.createChar(7, AVE_ALAS_PART2);
      lcd.setCursor(columna_rama, fila_rama);
      lcd.write(byte(7));
    }
    a = 0;
  }
}

void updateScore() {
  if (millis() > reloj3 + periodo3) {
    reloj3 = millis();
    puntos++;
    if (puntos == 100) {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("LEVEL UP!");
      delay(1000);
      lcd.clear();
      puntos = 0;
      punto2++;
      if (punto2 == 100) {
        punto2 = 0;
      }
    }
    lcd.setCursor(14, 1);
    lcd.print(puntos);
    lcd.setCursor(14, 0);
    lcd.print(punto2);
  }
}
void updateDinoPosition() {
  if (flag == 1) {
    lcd.setCursor(columna_dino1, fila_dino);
    lcd.write(byte(2));
    lcd.setCursor(columna_dino2, fila_dino);
    lcd.write(byte(3));
  } else if (flag == 2) {
    lcd.setCursor(columna_dino1, fila_dino);
    lcd.write(byte(4));
    lcd.setCursor(columna_dino2, fila_dino);
    lcd.write(byte(5));
  }
}
void gameOver() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME OVER");
  delay(2000);
  lcd.clear();
  columna_rama = 15;
  periodo2 = 100;
  puntos = 0;
  punto2 = 0;
}
