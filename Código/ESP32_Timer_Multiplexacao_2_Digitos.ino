
/* ==============================================================
   RODROBOT - MULTIPLEXACAO DE DOIS DISPLAYS
   ESP32 DevKit - Arduino IDE 3.3.11
   Displays de 7 segmentos - Catodo comum

   BOTAO:
   GPIO 15 - INPUT_PULLUP
   Botao ligado entre GPIO 15 e GND.

   CADA PRESSIONAMENTO AVANCA UMA VELOCIDADE.

   ETAPAS:
   1 - 1000 ms | Alternancia muito lenta
   2 - 500 ms  | Alternancia lenta
   3 - 100 ms  | Alternancia intermediaria
   4 - 20 ms   | Alternancia rapida
   5 - 5 ms    | Inicio da multiplexacao
   6 - 2 ms    | Multiplexacao rapida
   ============================================================== */

// ---------------- PINOS DOS SEGMENTOS -------------------------

const int segmentos[] = {23, 22, 21, 19, 18, 17, 16}; // A, B, C, D, E, F, G

// ---------------- SELECAO DOS DISPLAYS ------------------------

const int display1 = 25; // Transistor do display esquerdo
const int display2 = 26; // Transistor do display direito

// ---------------- BOTAO ----------------------------------------

const int botao = 15; // Botao com pull-up interno

// ---------------- NUMEROS EXIBIDOS -----------------------------

const byte numeros[] = {
  0b1011011, // Numero 2
  0b1101101  // Numero 5
};

// ---------------- TIMER ----------------------------------------

hw_timer_t *timer = NULL; // Ponteiro do timer

volatile uint32_t ticks = 0; // Contador de interrupcoes
uint32_t ultimoTick = 0;     // Ultimo pulso processado

// ---------------- INTERVALOS -----------------------------------

const uint32_t intervalos[] = {
  1000000, // 1000 ms
  500000,  // 500 ms
  100000,  // 100 ms
  20000,   // 20 ms
  5000,    // 5 ms
  2000     // 2 ms
};

const char *etapas[] = {
  "Alternancia muito lenta",
  "Alternancia lenta",
  "Alternancia intermediaria",
  "Alternancia rapida",
  "Inicio da multiplexacao",
  "Multiplexacao rapida"
};

const int totalEtapas = 6; // Total de velocidades
int etapaAtual = 0;        // Inicia na primeira etapa

// ---------------- DEBOUNCE DO BOTAO ----------------------------

bool ultimaLeitura = HIGH; // Ultima leitura instantanea
bool estadoBotao = HIGH;   // Estado estavel do botao

unsigned long tempoDebounce = 0; // Controle de tempo
const unsigned long debounce = 50; // Filtro de 50 ms

// ---------------- INTERRUPCAO DO TIMER -------------------------

void ARDUINO_ISR_ATTR onTimer() {

  ticks++; // Incrementa a cada interrupcao
}

// ---------------- DESLIGA DISPLAYS -----------------------------

void desligarDisplays() {

  digitalWrite(display1, LOW); // Desliga display 1
  digitalWrite(display2, LOW); // Desliga display 2
}

// ---------------- MOSTRA NUMERO -------------------------------

void mostrarDisplay(int numero, int selecionado) {

  desligarDisplays(); // Desliga antes de trocar

  for (int i = 0; i < 7; i++) {

    digitalWrite(segmentos[i],
                 bitRead(numeros[numero], i)); // Atualiza segmentos
  }

  if (selecionado == 0) {

    digitalWrite(display1, HIGH); // Liga display esquerdo

  } else {

    digitalWrite(display2, HIGH); // Liga display direito
  }
}

// ---------------- ALTERA VELOCIDADE ----------------------------

void selecionarEtapa() {

  etapaAtual++; // Avanca uma etapa

  if (etapaAtual >= totalEtapas) {

    etapaAtual = 0; // Reinicia o ciclo
  }

  // ZERA CONTADOR DE FORMA SEGURA
  noInterrupts();
  ticks = 0;
  interrupts();

  ultimoTick = 0; // Reinicia controle dos pulsos

  desligarDisplays(); // Desliga os dois displays

  timerAlarm(timer, intervalos[etapaAtual], true, 0); // Atualiza Timer

  mostrarDisplay(0, 0); // Inicia pelo numero 2

  Serial.println();
  Serial.println("==============================");

  Serial.print("ETAPA: ");
  Serial.println(etapaAtual + 1);

  Serial.println(etapas[etapaAtual]);

  Serial.print("Intervalo: ");
  Serial.print(intervalos[etapaAtual]);
  Serial.println(" microssegundos");

  Serial.println("==============================");
}

// ---------------- LEITURA DO BOTAO -----------------------------

void verificarBotao() {

  bool leitura = digitalRead(botao); // Leitura instantanea

  // DETECTA MUDANCA NA LEITURA
  if (leitura != ultimaLeitura) {

    tempoDebounce = millis(); // Reinicia contagem do debounce
  }

  // CONFIRMA ESTADO APOS 50 MS ESTAVEIS
  if ((millis() - tempoDebounce) >= debounce) {

    if (leitura != estadoBotao) {

      estadoBotao = leitura; // Atualiza estado confirmado

      // BOTAO PRESSIONADO
      if (estadoBotao == LOW) {

        selecionarEtapa(); // Avanca velocidade
      }
    }
  }

  ultimaLeitura = leitura; // Guarda ultima leitura
}

// ---------------- SETUP ----------------------------------------

void setup() {

  Serial.begin(115200); // Inicializa Serial

  for (int i = 0; i < 7; i++) {

    pinMode(segmentos[i], OUTPUT); // Configura segmentos
    digitalWrite(segmentos[i], LOW); // Inicia apagado
  }

  pinMode(display1, OUTPUT); // Configura display 1
  pinMode(display2, OUTPUT); // Configura display 2

  pinMode(botao, INPUT_PULLUP); // Ativa pull-up interno

  desligarDisplays(); // Desliga displays

  mostrarDisplay(0, 0); // Mostra numero 2 inicialmente

  timer = timerBegin(1000000); // Resolucao de 1 MHz

  timerAttachInterrupt(timer, &onTimer); // Associa interrupcao

  timerAlarm(timer, intervalos[etapaAtual], true, 0); // Configura alarme

  Serial.println();
  Serial.println("RODROBOT - MULTIPLEXACAO");
  Serial.println("Pressione o botao para avancar.");
  Serial.println(etapas[etapaAtual]);
}

// ---------------- LOOP -----------------------------------------

void loop() {

  verificarBotao(); // Verifica o botao

  uint32_t leituraTicks; // Copia do contador

  noInterrupts();
  leituraTicks = ticks; // Leitura protegida
  interrupts();

  // VERIFICA SE OCORREU NOVA INTERRUPCAO
  if (leituraTicks != ultimoTick) {

    ultimoTick = leituraTicks; // Atualiza contador

    int displayAtivo = leituraTicks % 2; // Alterna displays

    mostrarDisplay(displayAtivo, displayAtivo); // Atualiza display
  }
}
