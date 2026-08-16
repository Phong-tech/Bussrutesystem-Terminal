/**
 *   LesData2.h  -  Hjelpefunksjoner for innlesing av data.
 *
 *   Dette er en forenklet versjon av LesData2.h
 *   Inneholder funksjoner for å lese inn char og int med validering.
 */

#ifndef __LESDATA2_H
#define __LESDATA2_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/**
 *  Leser og returnerer ett tegn.
 *
 *  @param   melding  -  Ledetekst til brukeren
 *  @return  Ett character/tegn (konvertert til stort)
 */
char lesChar(const string melding)
{
    char tegn;
    cout << melding << ": ";
    cin >> tegn;
    cin.ignore();
    return toupper(tegn);
}

/**
 *  Leser og returnerer et tall mellom to grenser.
 *
 *  @param   melding  -  Ledetekst til brukeren
 *  @param   min      -  Minimum tillatt verdi
 *  @param   max      -  Maksimum tillatt verdi
 *  @return  Verdien som er lest inn (garantert i intervallet [min, max])
 */
int lesInt(const string melding, const int min, const int max)
{
    int tall;
    do
    {
        cout << melding << " (" << min << "-" << max << "): ";
        cin >> tall;
        cin.ignore();
        if (tall < min || tall > max)
            cout << "Feil: Tallet må være mellom " << min
                 << " og " << max << "!\n";
    } while (tall < min || tall > max);
    return tall;
}

#endif