# SDD: Relógio Digital

## FD: Subsistema de Alarme @AL-004

> traceability: [AL-001](@)

A cada segundo, o subsistema compara o [dic:horario-corrente](#) com o [dic:horario-programado](#) e ativa o alarme na coincidência. Alocado em [AL-005](@).

```puml:fig-alarm-fd{caption="Fluxo funcional mínimo do subsistema de alarme."}
@startuml
start
:Ler horário corrente;
:Ler horário programado;
if (coincidem?) then (sim)
  :Ativar alarme;
else (não)
  :Manter alarme inativo;
endif
stop
@enduml
```

## FD: Subsistema de Tempo @TM-004

> traceability: [TM-001](@)

O subsistema converte o *tick* periódico em contagem de horas, minutos e segundos. Alocado em [TM-005](@).

## CSU: alarm.c @AL-005

> file_path: firmware/alarm.c

> language: C

> implements: [alarm_check](@), [time_matches](@), [alarm_init](@)

## CSU: time_manager.c @TM-005

> file_path: firmware/time_manager.c

> language: C

> implements: [time_manager_tick](@), [time_manager_get_time](@), [time_manager_init](@)

```{.include}
symbols.md
```
