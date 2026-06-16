#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUZZER_PIN 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

// ================= TAREFAS =================

struct Tarefa {
  byte hora;
  byte minuto;
  const char* mensagem;
  bool disparada;
};

Tarefa tarefas[] = {

  {15, 25, "Tomar Agua", false},
  {15, 27, "Ler Emails", false},
  {15, 29, "Revisar Projeto", false},
  {15, 31, "Estudar Arduino", false},
  {15, 33, "Pausa Rapida", false},
  {15, 35, "Voltar ao Trabalho", false}

};

const int NUM_TAREFAS = sizeof(tarefas) / sizeof(tarefas[0]);

// ================= ALARME =================

bool alarmeAtivo = false;
const char* mensagemAtiva = "";

unsigned long inicioAlarme = 0;
const unsigned long DURACAO_ALARME = 15000;

// =====================================================

void setup() {

  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(100000);

  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED nao encontrado");
    while (1);
  }

  if (!rtc.begin()) {
    Serial.println("RTC nao encontrado");
    while (1);
  }

  // AJUSTAR APENAS UMA VEZ
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("RELOGIO");

  display.display();

  delay(2000);
}

// =====================================================

void loop() {

  DateTime agora = rtc.now();

  verificarAlarmes(agora);

  desenharTela(agora);

  delay(200);
}

// =====================================================

void verificarAlarmes(DateTime agora) {

  for (int i = 0; i < NUM_TAREFAS; i++) {

    if (agora.hour() == tarefas[i].hora &&
        agora.minute() == tarefas[i].minuto &&
        !tarefas[i].disparada) {

      tarefas[i].disparada = true;

      alarmeAtivo = true;
      mensagemAtiva = tarefas[i].mensagem;

      inicioAlarme = millis();

      tocarBuzzer();
    }
  }

  for (int i = 0; i < NUM_TAREFAS; i++) {

    if (agora.minute() != tarefas[i].minuto) {
      tarefas[i].disparada = false;
    }
  }

  if (alarmeAtivo &&
      millis() - inicioAlarme > DURACAO_ALARME) {

    alarmeAtivo = false;
  }
}

// =====================================================

void tocarBuzzer() {

  for (int i = 0; i < 8; i++) {

    tone(BUZZER_PIN, 3000);
    delay(200);

    noTone(BUZZER_PIN);
    delay(100);
  }
}

// =====================================================

void desenharTela(DateTime agora) {

  display.clearDisplay();

  if (alarmeAtivo) {

    display.setTextSize(1);
    display.setCursor(30, 0);
    display.println("LEMBRETE");

    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // Sino
    display.drawCircle(18, 25, 8, SSD1306_WHITE);
    display.drawLine(10, 25, 26, 25, SSD1306_WHITE);
    display.drawLine(18, 33, 18, 38, SSD1306_WHITE);
    display.drawLine(13, 38, 23, 38, SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(35, 22);
    display.println("TAREFA:");

    display.setCursor(35, 40);
    display.println(mensagemAtiva);
  }

  else {

    int h = agora.hour();
    int m = agora.minute();

    // Hora
    display.setTextSize(3);
    display.setCursor(12, 2);

    if (h < 10) display.print("0");
    display.print(h);

    display.print(":");

    if (m < 10) display.print("0");
    display.print(m);

    // Linha
    display.drawLine(0, 30, 127, 30, SSD1306_WHITE);

    // Data
    display.setTextSize(1);
    display.setCursor(22, 36);

    if (agora.day() < 10) display.print("0");
    display.print(agora.day());

    display.print("/");

    if (agora.month() < 10) display.print("0");
    display.print(agora.month());

    display.print("/");

    display.print(agora.year());

    // Próxima tarefa
    display.setCursor(0, 54);
    display.print("Prox: ");

    const char* prox = proximaTarefa(agora);

    if (prox)
      display.println(prox);
    else
      display.println("Nenhuma");
  }

  display.display();
}

// =====================================================

const char* proximaTarefa(DateTime agora) {

  int atual =
    agora.hour() * 60 +
    agora.minute();

  int melhor = 9999;

  const char* resultado = nullptr;

  for (int i = 0; i < NUM_TAREFAS; i++) {

    int horario =
      tarefas[i].hora * 60 +
      tarefas[i].minuto;

    int diff = horario - atual;

    if (diff > 0 && diff < melhor) {

      melhor = diff;
      resultado = tarefas[i].mensagem;
    }
  }

  return resultado;
}