# Projeto Final

Laboratório de Sistemas Microprocessados - Turma E

Alunos: 

- Eduardo Lemos Rocha
- Luísa Sinzker Fantin

## Problema

O problema que o projeto solucionará é servir de ferramenta para um entendimento mais aprofundado e famialirização com comunicação serial. Dessa forma, uma espécie de \textit{triciclo} em miniatura será construído e programado para ser controlado por meio das teclas \textit{setas} de um teclado ligado á uma máquina que possua conexão \textit{Bluetooth}. Além disso, o móvel deve ser capaz de limitar as ações do usuário com base na distância entre este e o obstáculo seguinte, prevenindo assim possíveis acidentes que possam danificar o projeto.

## Sensores/Materiais Utilizados

- Módulo Bluetooth Sereial HC-05 (Mestre/Escravo).
- Módulo Driver Motor com dupla PonteH - L298N.
- Módulo Sensor de Proximidade HC-SR04.
- 02 Motores de Micro-velocidade (3-6V DC) com Encoders.
- Roda direcional.
- 02 Rodas de 65mm de diâmetro.
- Suporte para 4 pilhas AA.

## Especificações

Para mandar um comando para o triciclo é necessário tomar conhecimento de como os bytes recebidos pelo módulo HC-05 são interpretados. Assim, os bits desse byte foram divididos da seguinte forma:

### Organização e Interpretação do Byte recebido
| Bits | B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
|------|----|----|----|----|----|----|----|----|
| Função | Stop | Turn\
Left | Turn\
Right | Go\
DLeft | Go\
DRight | Go\
Back | Go\
Forward | Start |

Para qualquer ação, com exceção de ficar parado, o bit \textit{Start} precisa estar selecionado. Algumas combinações são auto-excludentes (como por exemplo, tentar andar para a diagonal direita e esquerda simultaneamente) e quando encontradas provocarão a parada total do móvel.