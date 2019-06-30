---
header-includes: |
	\usepackage[top=2.5cm, left=2cm, right=2cm, bottom=1.8cm]{geometry}
	\usepackage{tikz}
	\usetikzlibrary{arrows.meta}
	\usetikzlibrary{shapes}
	\usetikzlibrary{positioning}
	\usepackage{relsize}
	\tikzset{
	            base/.style = {rectangle, rounded corners, draw=black,
	                           minimum width=2cm, minimum height=0.5cm,
	                           text width = 2cm,
	                           text centered},
	            base2/.style = {diamond, minimum width=1.5cm, minimum height=0.5cm, text centered, draw=black},
	            base3/.style = {ellipse, fill = white!30, draw=black, text width = 0.75cm, text centered, minimum height = 0.5cm},
	  			Start/.style = {base3, fill=white!30},
	  			Stop/.style = {base3, fill=white!30},
	  			Stm/.style = {base, fill=white!30},
	  			Decision/.style = {base2, fill=white!30},
	}
---

# Relatório - Projeto Final

Laboratório de Sistemas Microprocessados - Turma E

Alunos:

- Eduardo Lemos Rocha	- 17/0009157
- Luísa Sinzker Fantin	- 14/0151893

## Proposta Inicial

O problema que o projeto solucionará é servir de ferramenta para um entendimento mais aprofundado e famialirização com comunicação serial. Dessa forma, uma espécie de \textit{triciclo} em miniatura será construído e programado para ser controlado por meio das teclas \textit{setas} de um teclado ligado á uma máquina que possua conexão \textit{Bluetooth}. Além disso, o móvel deve ser capaz de limitar as ações do usuário com base na distância entre este e o obstáculo seguinte, prevenindo assim possíveis acidentes que possam danificar o projeto.

## Problema/Objetivos

O problema que o projeto solucionará é servir de ferramenta para um entendimento mais aprofundado e famialirização com comunicação serial. Dessa forma, uma espécie de \textit{triciclo} em miniatura será construído e programado para ser controlado por meio de um analógico \textit{joystick}. A comunicação entre o móvel e o controle será feito por meio de comunicação assícrona, utilizando o módulo \textit{Bluetooth}. Além disso, o móvel deve ser capaz de limitar as ações do usuário com base na distância entre este e o obstáculo seguinte, prevenindo assim possíveis acidentes que possam danificar o projeto.

## Sensores/Materiais Utilizados

- 02 Módulos Bluetooth Serial HC-05 (Mestre/Escravo).
- Módulo LCD.
- Módulo Joystick.
- Módulo Driver Motor com dupla Ponte H - L298N.
- Módulo Sensor de Proximidade HC-SR04.
- 02 Motores de Micro-velocidade (3-6V DC) com Encoders.
- Roda direcional.
- 02 Rodas de 65mm de diâmetro.
- Suporte para 4 pilhas AA.
- Fonte Externa para o microprocessador.

## Funcionamento do Programa do Controle

O controle foi impementado usando outra versão da placa, a MSP430F5529. As tensões dos pinos conectados ao Joystick, representando os eixos x e y foram medidas com referência positiva 3V3 e negativa GND (terra). As tensões menores que 1.2V indicam movimento para frente no eixo x e esquerda para o eixo y, tensões maiores que 1.8V indicam movimento para trás no eixo x e direita para o eixo y. Esses limiares de descrição foram usados pois em repouso o Joystick demarca pequenas variações de 1.6V. Duas variáveis de controle foram criadas para discretizar os limiares, uma para o eixo x, outra para o y:

| direção x | direção y | medição | variavel |
|-----------|-----------|---------|----------|
|  	 Up	    |   Left    |	 <1.2V	|		 1		 |
|   Down		|	  Right		|  >1.8V	|		 2		 |
|	  Idle		|	  Idle		|1.2<M<1.8|		 0		 |

Após a tradução desses valores a variável equivalente a x era multiplicada por 10 e então somada a variável equivalente a y, obtendo a seguinte tradução:

| Byte |Var |
|------|----|
| 0x80 | 00	|
| 0x13 | 11 |
| 0x03 | 10	|
| 0x0B | 12	|
| 0x15 | 21	|
| 0x05 | 20	|
| 0x0D | 22	|

O sinal (_Byte_)era enviado por bluetooth de acordo com um _switch case_ implementado usando os valores da tabela.

Um LCD também foi conectado a placa e mostrava as direções de x e y, assim como o valor da variável de controle e as volatagens medidas para os eixos x e y.   


## Funcionamento do Programa do Triciclo

O programa executa uma estrutura de \textit{loop} infinito. Primeiramente, verifica-se se a varíavel global que controla os motores está preenchida com um \textit{byte} que representa a ação de \textit{Stop}. Caso esteja, funções de parada dos motores são chamadas, o LED vermelho é aceso e o LED verde é apagado. Caso contrário, isto é, caso o byte da variável não seja um byte de \textit{Stop}, obrigatoriamente o byte deve conter o bit \textit{Start} como '1'. Todas as ações disponíveis, tirando a de \textit{Stop}, possuem o bit de \textit{Start} como '1'. Em seguida, após ser verificado com bit de \textit{Start}, uma função de análise do sensor de ultrassom é chamada. Essa função devolve a informação se o sensor está a 30 centímetros do próximo obstáculo. Caso esteja, os motores são parados, o LED vermelho é aceso, o LED verde é apagado e a única ação permitida para o usuário é mandar um byte para andar para trás. Caso a distância do sensor para o próximo obstáculo seja maior que 30 cm, o LED vermelho é apagado, o LED verde é aceso e será analisado qual direção que o móvel vai se locomover. Essa análise altera o \textit{dutyCycle} das PWMs dos motores, de acordo com a direção escolhida. As PWMs dos motores estão configuradas para 50 Hz.


Os bytes para cada ação estão descritos na tabela abaixo:

| Byte | Função |
|------|--------|
| 0x80 | Stop |
| 0x13 | Up-Left |
| 0x03 | Up |
| 0x0B | Up-Right |
| 0x15 | Down-Left |
| 0x05 | Down |
| 0x0D | Down-Right |

A variável global responsável pelo comportamento dos motores é atualizada por meio de interrupções provocadas pelo módulo de comunicação \textit{bluetooth}. A comunicação com o módulo \textit{bluetooth} está sendo feita de maneira assíncrona sem bit de paridade, comunicando-se elos bits menos significativos primeiro, com apenas 1 Stop.


O funcionamento do programa pode ser resumido por meio do fluxograma a seguir:

\begin{center}
\begin{tikzpicture}[node distance=1cm,
    every node/.style={fill=white, font=\footnotesize}, align=center]
  \node (start)             [Start]              {Start};
  \node (configLEDS)     [Stm, above of=start, yshift=2cm]          {Configurar LEDS};
  \node (configMotors)     [Stm, left of=configLEDS, xshift=-2cm]          {Configurar Motores};
  \node (configSensor)     [Stm, left of=configMotors, xshift=-2cm]          {Configurar Sensor Ultrassom};
  \node (configBluetooth)     [Stm, left of=configSensor, xshift=-2cm]          {Configurar Módulo Bluetooth};
  \node (verifyStop)     [Decision, below of=configBluetooth, yshift=-1cm]          {Stop?};
  \node (trocaLED1)     [Stm, right of=verifyStop, xshift=1.0cm, yshift=-1cm]				{Altera LEDs};
  \node (stopMotors1)     [Stm, right of=trocaLED1, xshift=2.75cm]				{Parar Motores};
  \node (verifyStart)     [Decision, below of=verifyStop, xshift=-1.0cm, yshift=-4cm]          {Start?};
  \node (trocaLED2)     [Stm, right of=verifyStart, yshift=-1.75cm, xshift=1.5cm]				{Altera LEDs};
  \node (verifySensor)     [Decision, below of=verifyStart, xshift=6.45cm, yshift=-0.75cm]          {Distancia <= 30?};
  \node (trocaLED3)     [Stm, above of=verifySensor, yshift=1.5cm]				{Altera LEDs};
  \node (stopMotors2)     [Stm, above of=trocaLED3, yshift=1cm]				{Parar Motores};
  \node (verifyBack)     [Decision, left of=stopMotors2, xshift=-2.75cm]          {Back?};
  \node (goBack)     [Stm, below of=verifyBack, yshift=-1.75cm]				{Andar para trás};
  \node (dLeft)     [Decision, below of=verifySensor, yshift=-1cm, xshift=-1.5cm]          {Up-Left?};
  \node (godLeft)     [Stm, left of=dLeft, xshift=-2.25cm]				{Andar Diagonal Esquerda};
  \node (dRight)     [Decision, below of=dLeft, xshift=1.4cm, yshift=-0.5cm]          {Up-Right?};
  \node (godRight)     [Stm, left of=dRight, xshift=-3.65cm]				{Andar Diagonal Direita};
  \node (dLeft2)     [Decision, below of=dRight, yshift=-0.6cm, xshift=-1.45cm]          {Down-Left?};
  \node (godLeft2)     [Stm, left of=dLeft2, xshift=-2.25cm]				{Voltar Diagonal Esquerda};
  \node (dRight2)     [Decision, below of=dLeft2, xshift=1.6cm, yshift=-0.7cm]          {Down-Right?};
  \node (godRight2)     [Stm, left of=dRight2, xshift=-3.85cm]				{Voltar Diagonal Direita};
  \node (up)     [Decision, below of=dRight2, yshift=-0.6cm, xshift=-1.45cm]          {Up?};
  \node (goUp)     [Stm, left of=up, xshift=-2.4cm]				{Avançar};
  \node (down)     [Decision, below of=up, xshift=1.4cm, yshift=-0.5cm]          {Down?};
  \node (goDown)     [Stm, left of=down, xshift=-3.8cm]				{Voltar};

  % Specification of lines between nodes specified above
  % with aditional nodes for description
  \draw[->]             (start) -- (configLEDS);
  \draw[->]             (configLEDS) -- (configMotors);
  \draw[->]             (configMotors) -- (configSensor);
  \draw[->]             (configSensor) -- (configBluetooth);
  \draw[->]             (configBluetooth) -- (verifyStop);
  \draw[->]             (verifyStop) -- node[anchor=north, xshift=0.35cm, yshift=0.4cm] {yes} (trocaLED1);
  \draw[->]             (trocaLED1) -- (stopMotors1);
  \draw[->]             (stopMotors1.north)--++(0,0) |-(verifyStop);
  \draw[->]             (verifyStop.west) --+(-1.5,0) |- node[anchor=east, yshift=0.2cm, xshift=-0.2cm] {no} (verifyStart.west);
  \draw[->]             (verifyStart.north) -- node[anchor=east, yshift=0.2cm, xshift=-0.2cm] {no} (verifyStop.south);
  \draw[->]             (verifyStart.south) -- node[anchor=east] {yes} (trocaLED2.north);
  \draw[->]             (trocaLED2) -- (verifySensor.west);
  \draw[->]             (verifySensor.north) -- node[anchor=east, xshift=-0.1cm] {yes} (trocaLED3.south);
  \draw[->]             (trocaLED3) -- (stopMotors2);
  \draw[->]             (stopMotors2) -- (verifyBack);
  \draw[->]             (verifyBack) -- node[anchor=north] {no} (verifyStart);
  \draw[->]             (verifyBack) -- node[anchor=north] {yes} (goBack);
  \draw[->]             (goBack) -- (verifyStart.east);
  \draw[->]             (verifySensor.east) --++(0,0) node[anchor=north, xshift=0.3cm] {no} |- (dLeft.east);
  \draw[->]             (godLeft.west)--++(0,0) -|(verifyStart.south);
  \draw[->]				(dLeft.west) -- node[anchor=north, yshift=-0.1cm] {yes} (godLeft.east);
  \draw[->]             (dLeft) -- node[anchor=south, xshift=0.3cm, yshift=0.1cm] {no} (dRight);
  \draw[->]				(dRight.west) -- node[anchor=north, yshift=-0.1cm] {yes} (godRight.east);
  \draw[->]             (godRight.west)--++(0,0) -|(verifyStart.south);
  \draw[->]             (dRight) -- node[anchor=east, xshift=0.025cm, yshift=0.25cm] {no} (dLeft2);
  \draw[->]				(dLeft2.west) -- node[anchor=north, yshift=-0.1cm] {yes} (godLeft2.east);
  \draw[->]             (godLeft2.west)--++(0,0) -|(verifyStart.south);
  \draw[->]				(dRight2.west) -- node[anchor=north, yshift=-0.1cm] {yes} (godRight2.east);
  \draw[->]             (dLeft2) -- node[anchor=south, xshift=0.3cm, yshift=0.1cm] {no} (dRight2);
  \draw[->]             (godRight2.west)--++(0,0) -|(verifyStart.south);
  \draw[->]             (dRight2) -- node[anchor=south, xshift=0.3cm, yshift=-0.4cm] {no} (up);
  \draw[->]				(up.west) -- node[anchor=north, yshift=-0.1cm] {yes} (goUp.east);
  \draw[->]             (goUp.west)--++(0,0) -|(verifyStart.south);
  \draw[->]             (up) -- node[anchor=south, xshift=0.3cm, yshift=0.1cm] {no} (down);
  \draw[->]				(down.west) -- node[anchor=north, yshift=-0.1cm] {yes} (goDown.east);
  \draw[->]             (goDown.west)--++(0,0) -|(verifyStart.south);
  \draw[->]             (down.south)--++(0,-0.25) node[anchor=north, yshift=-0.1cm] {no} -|(verifyStart.south);

  \end{tikzpicture}
  \end{center}

## Objetivos não completados

Infelizmente, não foi possível utilizar o \textit{joystick} para controlar o triciclo. Os dois módulos estão funcionando normalmente quando conectados à um aparelho celular (\textit{smartphone}). O controle \textit{joystick} manda corretamente os bytes necessários para o aparelho celular. O triciclo recebe corretamente os bytes enviados pelo aparelho celular. O problema consistiu na comunicação dos dois módulos \textit{Bluetooth}. Não foi possível conectar um dos módulos \textit{Bluetooth} como mestre e o outro como escravo. Assim, fomos obrigados a comandar o triciclo por meio do aparelho celular.


## Energia

A alimentação do sistema utiliza um conjunto de pilhas e uma \textit{powerbank}. As pilhas em série alimentam uma Ponte-H, que por sua vez alimenta o par de motores DC. A \textit{powerbank} alimenta a MSP430FR5994, que por sua vez alimenta o sensor ultrassom e o módulo \textit{bluetooth}.
