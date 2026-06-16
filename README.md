# RIA - Relógio Inteligente de Atividades (Para pessoas com TDAH)

Um relógio digital feito com Arduino que mostra a hora e o dia em uma telinha e te avisa, com som e mensagem na tela, na hora de fazer suas tarefas.

---

## O que é o projeto

É um relógio de mesa "inteligente". Além de marcar a hora certinha, ele guarda uma lista de lembretes (como "Tomar água" ou "Estudar Arduino") e, no horário programado, **toca um alarme e mostra o aviso na tela**. Quando não há nenhum lembrete no momento, ele simplesmente funciona como um relógio normal, exibindo hora, data e qual é a próxima tarefa.

---

## O que ele faz

- Mostra a **hora** em números grandes na tela.
- Exibe a **data** completa logo abaixo.
- Indica qual é o **próximo lembrete** agendado.
- No horário certo, **toca um alarme** e mostra a mensagem da tarefa com um ícone de sino.
- O aviso fica na tela por cerca de **15 segundos** e depois volta ao relógio normal.
- Mantém a hora certa **mesmo desligado**, graças à bateria do módulo de relógio.

---

## Componentes usados

| Componente | Para que serve |
|---|---|
| **Arduino Nano** | O cérebro do projeto, que controla tudo. |
| **Display OLED 0.96"** | A telinha que mostra hora, data e lembretes. |
| **Módulo RTC DS3231** | O relógio interno, que guarda a hora com precisão. |
| **Buzzer** | Emite o som do alarme. |

---

## Como funciona (de forma simples)

1. O Arduino pergunta as horas ao módulo de relógio o tempo todo.
2. Ele compara a hora atual com a lista de lembretes que você programou.
3. Se não chegou a hora de nenhum lembrete, ele mostra o relógio normal na tela.
4. Quando bate o horário de uma tarefa, ele **toca o alarme** e **mostra o aviso** na tela.
5. Passados alguns segundos, o aviso some e o relógio volta ao normal.

---

## Como personalizar os lembretes

Os lembretes ficam em uma lista dentro do código. Cada um tem um horário e uma mensagem. Para criar, mudar ou remover um lembrete, basta editar essa lista — cada linha segue o formato de hora, minuto e o texto que aparecerá na tela.

---

## Tecnologias

- **Linguagem:** C (Arduino)
- **Plataforma:** Arduino Nano
- **Comunicação:** I2C (entre o Arduino, o display e o relógio)
