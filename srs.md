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
