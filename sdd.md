# SDD: Thermal Management Design @SDD-001

> version: 1.0

> date: 2026-05-24

> status: Draft

> subtitle: Software Design Description

> author: SpecCompiler Demo

## COVER: Cover @SDD-COVER

## Table of Contents

`toc:`

A small example design for the thermal management subsystem. The
Controller polls the Temperature Sensor; on overheat it records the
event and asks the Safety Manager to enter safe mode.

```puml:fig-thermal-overview{caption="Overheat detection and safe-mode transition sequence."}
@startuml
skinparam backgroundColor #FFFFFF
skinparam defaultFontSize 11
skinparam sequence {
  ArrowColor #333333
  LifeLineBorderColor #888888
  ParticipantBorderColor #555555
  ParticipantBackgroundColor #F4F4F4
}

participant "TempSensor"   as TS
participant "Controller"   as CTL
participant "SafetyManager" as SM
participant "EventLog"     as EL

loop every 10 ms
  TS -> CTL : read()
  activate CTL
  alt temperature > limit
    CTL -> EL : record(OVERHEAT)
    CTL -> SM : enterSafeMode()
  end
  deactivate CTL
end
@enduml
```

## DD: Use polling rather than interrupts @DD-001

The temperature sensor is polled at a fixed cadence from the
Controller rather than driven by interrupts on threshold crossings.

> rationale: Polling avoids interrupt-storm risk when the reading hovers near the threshold and keeps timing analysis simple — a single periodic tick covers both the sensor read and the dispatch to the Safety Manager.

> status: Approved

## LLR: Poll temperature at 10 ms @LLR-001

The Controller shall read the temperature sensor every 10 ms ± 1 ms.

> rationale: 10 ms is the longest sample interval that still meets the safe-mode entry deadline from threshold crossing, with margin for jitter.

> verification_method: Test

> traceability: [HLR-042](@)

> status: Draft

## LLR: Record overheat event before mode transition @LLR-002

When an overheat is detected, the Controller shall write the overheat
event to the EventLog before invoking `enterSafeMode()` on the
Safety Manager.

> rationale: Ordering guarantees the event survives any subsequent safe-mode behaviour that may halt non-essential logging subsystems.

> verification_method: Inspection

> traceability: [HLR-043](@)

> status: Draft
