# SVC: Relógio Digital

## VC: Verificação do Disparo do Alarme @AL-002

Confirmar que o alarme é ativado quando o horário corrente coincide com o horário programado.

> objective: Verificar o disparo do alarme na coincidência entre horário corrente e horário programado.

> verification_method: Test

> input: [dic:horario-programado](#) 06:30:00 e [dic:horario-corrente](#) avançando a partir de 06:29:58

> procedure: Configurar o alarme, avançar o *tick* até 06:30:00 e observar a saída do alarme

> expected: Alarme ativo no *tick* em que os horários coincidem

> traceability: [AL-001](@)

## VC: Verificação da Manutenção do Horário @TM-002

Confirmar a contagem de horas, minutos e segundos a partir do *tick* periódico.

> objective: Verificar que o firmware mantém a contagem de tempo correta após uma sequência de ticks.

> verification_method: Test

> input: Sequência de 3.600 ocorrências do [dic:tick](#) a partir de 06:00:00

> procedure: Avançar os *ticks* e ler o [dic:horario-corrente](#) ao final da sequência

> expected: [dic:horario-corrente](#) igual a 07:00:00

> traceability: [TM-001](@)

## VC: Verificação do Mostrador @DP-002

Confirmar a atualização do mostrador na mudança do horário exibido.

> objective: Verificar que o mostrador reflete a mudança do horário corrente.

> verification_method: Test

> input: Virada de minuto no [dic:horario-corrente](#)

> procedure: Avançar o *tick* através da virada e capturar o conteúdo do mostrador

> expected: Dígitos de minuto apresentando o novo valor

> traceability: [DP-001](@)

## Matriz de Rastreabilidade

`traceability_matrix:`
