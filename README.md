# Bussrutesystem-Terminal

C++

# Bussrutesystem – C++ prosjekt

Et terminalbasert C++-prosjekt for administrasjon av bussruter og busstopp.

## Om prosjektet

Bussrutesystemet er et terminalprogram utviklet i C++. Programmet lar brukeren opprette, vise og slette bussruter med flere stopp.

Gjennom prosjektet arbeidet jeg med funksjoner, `struct`, `vector`, pekere, dynamisk minnehåndtering og validering av brukerinput.

## Teknologier

* C++
* `struct`
* `vector`
* Pekere
* Dynamisk minnehåndtering
* Funksjoner
* Header-filer (`.h`)
* Implementasjonsfiler (`.cpp`)
* Terminal / kommandolinje

## Funksjonalitet

Programmet støtter blant annet:

* visning av alle busstopp
* visning av registrerte bussruter
* opprettelse av nye bussruter
* valg av startstopp
* valg av neste stopp på en rute
* beregning av samlet kjøretid
* sletting av én bestemt rute
* sletting av alle ruter
* validering av brukerinput

## Hva jeg lærte

Prosjektet ga meg mer erfaring med:

* organisering av data med `struct`
* bruk av `vector` i C++
* arbeid med pekere
* dynamisk opprettelse og sletting av objekter
* oppdeling av programmet i mindre funksjoner
* håndtering og validering av brukerinput
* debugging og testing
* kompilering og kjøring fra terminalen

## Kompilering

På macOS/Linux kan prosjektet kompileres fra terminalen:

```bash
g++ oblig1.cpp -std=c++11 -o bussrutesystem
```

Start programmet med:

```bash
./bussrutesystem
```

Hvis prosjektet består av flere `.cpp`-filer, kan det også kompileres med:

```bash
g++ *.cpp -std=c++11 -o bussrutesystem
```

## Prosjektstruktur

```text
Bussrutesystem-Terminal/
├── oblig1.cpp
├── LesData2.h
└── README.md
```

## Resultat

Resultatet er et fungerende terminalbasert bussrutesystem hvor brukeren kan bygge opp bussruter steg for steg ved å velge stoppesteder.

Programmet holder oversikt over registrerte ruter, viser stoppene på hver rute og beregner samlet reisetid.

Prosjektet ga meg praktisk erfaring med grunnleggende datastrukturer, pekere og minnehåndtering i C++.

## Utvikler

**Phong Nguyen**

Studentprosjekt utviklet ved NTNU og Høgskolen i Molde.

