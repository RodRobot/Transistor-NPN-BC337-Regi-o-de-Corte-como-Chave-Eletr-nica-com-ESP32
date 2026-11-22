# Transistor NPN BC337 – Região de Corte como Chave Eletrônica com ESP32

**Projeto educacional RodRobot – Fundamentos de Eletrônica**

## 📌 Sobre o projeto

Neste projeto, vamos entender como funciona a **região de corte de um transistor bipolar de junção (BJT) NPN**, utilizando o BC337 como exemplo de chave eletrônica controlada por um ESP32.

O ESP32 controla a corrente aplicada à base do transistor por meio de uma saída GPIO. Quando o transistor está na região de corte, permanece desligado, funcionando de maneira semelhante a uma chave aberta.

O objetivo é demonstrar como um microcontrolador pode controlar um transistor e como esse componente pode ser utilizado para acionar cargas em circuitos eletrônicos.

## ⚡ O que é a região de corte?

A região de corte ocorre quando a junção base-emissor não recebe polarização direta suficiente para permitir a condução do transistor.

Nessa condição:

- **Corrente de base (IB):** praticamente zero.
- **Corrente de coletor (IC):** praticamente zero.
- **Transistor:** desligado.
- **LED:** apagado.
- **Equivalência:** chave aberta.

## 🔧 Componentes utilizados

- 1 × ESP32 DevKit
- 1 × Transistor NPN BC337
- 1 × LED
- 1 × Resistor limitador de corrente para o LED
- 1 × Resistor para a base do transistor
- 1 × Fonte de alimentação de 5 V
- Protoboard
- Fios de conexão

## 🔌 Funcionamento do circuito

O circuito utiliza o transistor BC337 na configuração de chave eletrônica de baixa tensão (*low-side switch*).

O ESP32 controla a base do transistor através de um pino GPIO, utilizando um resistor para limitar a corrente de base.

O LED e seu resistor limitador ficam conectados entre a alimentação positiva de 5 V e o coletor do transistor. O emissor é conectado ao GND.

Quando o ESP32 mantém a saída GPIO em nível LOW, o transistor permanece na região de corte, sem condução significativa entre coletor e emissor.

Consequentemente, o LED permanece apagado.

**Atenção:** o GND do ESP32 e o GND da alimentação do circuito devem estar conectados em comum. Não aplique 5 V diretamente a um GPIO do ESP32.

## 🧠 O papel do ESP32

O ESP32 é responsável por enviar o sinal de controle para a base do transistor.

Com isso, podemos utilizar a programação para controlar o estado do transistor:

- **GPIO em LOW:** transistor em corte, LED apagado.
- **GPIO em HIGH:** transistor conduzindo, podendo atingir a saturação, LED aceso.

Assim, conseguimos demonstrar a relação entre programação, eletrônica digital e funcionamento dos semicondutores.

## 🔄 Comparação com uma chave mecânica

Podemos compreender melhor o funcionamento do transistor comparando-o com uma chave convencional:

| Transistor NPN | Chave mecânica |
|---|---|
| Região de corte | Chave aberta |
| Desligado | Desligada |
| Sem condução significativa | Circuito interrompido |
| LED apagado | LED apagado |
| Saturação | Chave fechada |

## 📚 As três regiões de operação do transistor

Um transistor BJT pode trabalhar em diferentes regiões de operação:

- **Corte:** transistor desligado, funcionando como chave aberta.
- **Saturação:** transistor ligado, funcionando como chave fechada.
- **Região ativa:** utilizada principalmente para amplificação de sinais.

Neste exemplo, o foco é a região de corte. As outras regiões permitem compreender como o mesmo componente pode desempenhar funções diferentes em um circuito.

## 🎯 Objetivo didático

Este projeto faz parte dos conteúdos de fundamentos de eletrônica do RodRobot e tem como objetivo apresentar, de maneira prática e visual, o funcionamento do transistor NPN como chave eletrônica controlada por um microcontrolador.

Compreender essas regiões de operação é fundamental para avançar em projetos com LEDs, motores, relés, sensores, ESP32, automação e robótica.

## 🌐 Acompanhe o RodRobot

Confira outros tutoriais e projetos:

- **Página de projetos:** https://rodrobot.blogspot.com/p/projetos.html
- **Blog:** https://rodrobot.blogspot.com/
- **GitHub:** https://github.com/RodRobot

---

**RodRobot – Projetos maker, eletrônica e programação na prática.**
