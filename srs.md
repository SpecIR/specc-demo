# SRS: Thermal Management Requirements @SRS-001

> version: 1.0

> date: 2026-05-24

> status: Draft

> subtitle: Software Requirements Specification

> author: SpecCompiler Demo

## COVER: Cover @SRS-COVER


## Functional Requirements

A small example illustrating two requirements for the thermal
management subsystem of an embedded controller.

## HLR: Detect overheat @HLR-042

The controller shall enter safe mode when temperature
exceeds the limit.

> status: Draft

> priority: High

> rationale: Prevent thermal damage.

## HLR: Log overheat event @HLR-043

The controller shall record an overheat event before
entering safe mode.

> status: Draft

> priority: High

> rationale: Provide reviewable fault evidence.

## HLR: Classify thermal state by reading @HLR-044

The controller shall map each temperature reading to a thermal-state
classification according to the decision table below.

```list-table:tbl-thermal-mode{caption="Thermal-state classification by temperature reading."}
> header-rows: 1
> aligns: l,l,l

* - Condition
  - Previous state
  - Resulting state
* - reading <= 60 C
  - any
  - Normal
* - 60 C < reading <= 80 C
  - Normal
  - Caution
* - 60 C < reading <= 80 C
  - Caution or Safe Mode
  - unchanged
* - reading > 80 C
  - any
  - Safe Mode
```

> status: Draft

> priority: Mid

> rationale: A pure-function classification keeps the state machine deterministic and easy to test in isolation.
