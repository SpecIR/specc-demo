# SRS: Relógio Digital

## Escopo

Especificação de requisitos do firmware de um relógio digital, derivada de um exemplo público. O firmware mantém o horário a partir de um *tick* periódico e dispara um alarme programável.

## Dicionário de Dados

### DIC: Horário Corrente

> domain: tempo

Valor interno mantido pelo firmware a partir do *tick* periódico do temporizador, representado como hora de 24 horas no formato HH:MM:SS.

### DIC: Horário Programado

> domain: tempo

Valor interno configurado pelo usuário como alvo de disparo do alarme, representado como hora de 24 horas no formato HH:MM:SS.

### DIC: Tick

> term: tick

Interrupção periódica de 1 Hz gerada pelo temporizador do sistema.

## HLR: Disparo do Alarme @AL-001

> priority: High

O firmware deve ativar o alarme quando o [dic:horario-corrente](#) coincidir com o [dic:horario-programado](#).

## HLR: Manutenção do Horário @TM-001

O firmware deve manter horas, minutos e segundos atualizados a cada [dic:tick](#) do temporizador.

> rationale: A contagem local dispensa hardware de relógio dedicado.

> status: Approved

## HLR: Atualização do Mostrador @DP-001

> priority: Mid

O firmware deve atualizar o mostrador de sete segmentos a cada mudança de horário exibido.
