/**
 *   Programeksempel nr 6 - Obligatorisk oppgave nr 1.
 *
 *   Program for administrasjon av bussruter i Gjøvik.
 *   Programmet kan opprette nye ruter, slette ruter,
 *   og vise oversikt over alle ruter og busstopp.
 *
 *   @file     OBLIG1.CPP
 *   @author   Ditt Navn
 */

#include <iostream>
#include <string>
#include <vector>
#include "LesData2.h" // Ligger i samme katalog som denne filen.

using namespace std;

const int ANTSTOPP = 11; ///< Totalt antall ulike busstopp.

/**
 *  Rute (med rutenummer, stoppesteder og total kjøretid).
 */
struct Rute
{
    vector<string> stopp; // Rutens ulike stoppesteder.
    int ruteNr,           // Reelt rutenr, f.eks. 42, 165, 718
        totMin;           // Totalt antall minutter å kjøre på ruten
}; // (fra første til siste stoppested).

void nyRute();
bool ruteLesData(Rute &rute);
void ruteSkrivData(const Rute *rute);
void slett();
void slett(const int nr);
void skrivMeny();
void skrivNesteStoppesteder(const int stopp);
void skrivRuter();
void skrivStopp();
void slettRute();

vector<Rute *> gRuter; ///< Pekere til rutene.

const vector<string> gBusstopp ///< Navn på alle busstopp.
    {"Skysstasjonen", "Fahlstroms plass", "Sykehuset",
     "Gjovik stadion", "Bergslia", "Overby", "Nybrua",
     "NTNU", "Kallerud", "Hunndalen", "Mustad fabrikker"};

const int gMinutter[ANTSTOPP][ANTSTOPP] = ///< Min. mellom stoppesteder.
    {{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Skysstasjonen = 0
     {3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4},   // Fahlstrøms plass = 1
     {0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0},   // Sykehuset = 2
     {0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},   // Gjøvik stadion = 3
     {0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0},   // Bergslia = 4
     {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},   // Øverby = 5
     {0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 2},   // Nybrua = 6
     {0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0},   // NTNU = 7
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Kallerud = 8
     {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2},   // Hunndalen = 9
     {0, 4, 0, 0, 0, 0, 2, 0, 0, 2, 0}};  // Mustad fabrikker = 10

/**
 *  Hovedprogrammet.
 */
int main()
{
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q')
    {
        switch (kommando)
        {
        case 'N':
            nyRute();
            break;
        case 'S':
            slettRute();
            break;
        case 'A':
            skrivRuter();
            break;
        case 'B':
            skrivStopp();
            break;
        default:
            skrivMeny();
            break;
        }
        kommando = lesChar("\nKommando");
    }

    slett(); // Sletter alle rutene ved programmets slutt.

    cout << "\n\n";
    return 0;
}

/**
 *  Oppretter en ny rute, leser inn data og legger den til i gRuter.
 */
void nyRute()
{
    Rute *nyRute = new Rute; // Oppretter ny rute.

    cout << "\nOppretter ny rute:\n";

    if (ruteLesData(*nyRute))
    {                             // Leser inn rutedata. Gikk det bra?
        gRuter.push_back(nyRute); // Legger til bakerst i vectoren.
        cout << "\nNy rute lagt til som nr." << gRuter.size() << ":\n";
        ruteSkrivData(nyRute); // Skriver ut den nye ruten.
    }
    else
    {
        cout << "\nRuten må ha minst to stoppesteder. Ruten ble ikke opprettet.\n";
        delete nyRute; // Sletter ruten hvis den ikke er gyldig.
    }
}

/**
 *  Leser inn data for en rute.
 *
 *  @param   rute  -  Ruten det skal leses data for
 *  @return  true hvis ruten har minst 2 stoppesteder, false ellers
 */
bool ruteLesData(Rute &rute)
{
    int forrigeStoppIndeks, nesteStoppIndeks;

    rute.totMin = 0; // Initialiserer total kjøretid.

    // Leser rutenummer:
    rute.ruteNr = lesInt("Rutenummer", 1, 999);

    // Skriver ut alle stoppesteder:
    cout << "\nVelg stoppesteder for ruten:\n";
    skrivStopp();

    // Leser første stoppested:
    forrigeStoppIndeks = lesInt("\nStartstoppested (1-11)", 1, ANTSTOPP) - 1;
    rute.stopp.push_back(gBusstopp[forrigeStoppIndeks]);

    // Leser neste stoppesteder:
    do
    {
        cout << "\nMulige neste stoppesteder fra "
             << gBusstopp[forrigeStoppIndeks] << ":\n";
        skrivNesteStoppesteder(forrigeStoppIndeks);

        nesteStoppIndeks = lesInt("\nNeste stoppested (0=ferdig)",
                                  0, ANTSTOPP);

        if (nesteStoppIndeks != 0)
        {                       // Ikke ferdig?
            nesteStoppIndeks--; // Konverterer til indeks (0-10).

            // Sjekker om det er gyldig forbindelse:
            if (gMinutter[forrigeStoppIndeks][nesteStoppIndeks] != 0)
            {
                rute.stopp.push_back(gBusstopp[nesteStoppIndeks]);
                rute.totMin += gMinutter[forrigeStoppIndeks][nesteStoppIndeks];
                forrigeStoppIndeks = nesteStoppIndeks; // Oppdaterer posisjon.
            }
            else
            {
                cout << "Ugyldig valg! Ingen direkte forbindelse.\n";
            }
        }
    } while (nesteStoppIndeks != 0);

    return (rute.stopp.size() >= 2); // Returnerer true hvis minst 2 stopp.
}

/**
 *  Skriver ut data for en rute.
 *
 *  @param   rute  -  Ruten som skal skrives ut
 */
void ruteSkrivData(const Rute *rute)
{
    cout << "Rute " << rute->ruteNr << " (" << rute->totMin << " min): ";

    for (int i = 0; i < rute->stopp.size(); i++)
    {
        cout << rute->stopp[i];
        if (i < rute->stopp.size() - 1) // Ikke etter siste stoppested.
            cout << " --> ";
    }
    cout << '\n';
}

/**
 *  Sletter ALLE rutene.
 */
void slett()
{
    for (int i = 0; i < gRuter.size(); i++)
        delete gRuter[i]; // Sletter alle Rute-objektene.
    gRuter.clear();       // Tømmer vectoren.
    cout << "\nAlle ruter er slettet.\n";
}

/**
 *  Sletter EN spesifikk rute.
 *
 *  @param   nr  -  Indeksen (0-basert) til ruten som skal slettes
 */
void slett(const int nr)
{
    delete gRuter[nr]; // Sletter Rute-objektet.

    // Flytter den siste ruten til den slettedes plass:
    if (nr < gRuter.size() - 1)
        gRuter[nr] = gRuter[gRuter.size() - 1];

    gRuter.pop_back(); // Fjerner siste element.
    cout << "\nRute slettet.\n";
}

/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()
{
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "   N - Ny rute\n"
         << "   S - Slett rute\n"
         << "   A - skriv Alle ruter\n"
         << "   B - skriv alle Busstopp\n"
         << "   Q - Quit/avslutt\n";
}

/**
 *  Skriver ut alle mulige neste stoppesteder fra et gitt stoppested.
 *
 *  @param   stopp  -  Indeksen (0-basert) til stoppestedet
 */
void skrivNesteStoppesteder(const int stopp)
{
    for (int i = 0; i < ANTSTOPP; i++)
    {
        if (gMinutter[stopp][i] != 0)
        { // Er det en forbindelse?
            cout << "   " << (i + 1) << ": " << gBusstopp[i]
                 << " (" << gMinutter[stopp][i] << " min)\n";
        }
    }
}

/**
 *  Skriver ut alle eksisterende ruter.
 */
void skrivRuter()
{
    if (gRuter.empty())
    {
        cout << "\nIngen ruter er registrert ennå.\n";
    }
    else
    {
        cout << "\nAlle ruter:\n";
        for (int i = 0; i < gRuter.size(); i++)
        {
            cout << "   " << (i + 1) << ". ";
            ruteSkrivData(gRuter[i]);
        }
    }
}

/**
 *  Skriver ut alle busstopp med nummerering.
 */
void skrivStopp()
{
    for (int i = 0; i < ANTSTOPP; i++)
    {
        cout << "   " << (i + 1) << ": " << gBusstopp[i] << '\n';
    }
}

/**
 *  Sletter en eller flere ruter basert på brukerens valg.
 */
void slettRute()
{
    if (gRuter.empty())
    {
        cout << "\nIngen ruter å slette.\n";
    }
    else
    {
        skrivRuter(); // Viser alle ruter.

        int valg = lesInt("\nSlett rute nr (-1=alle, 0=ingen)",
                          -1, gRuter.size());

        if (valg == -1)
        {
            slett(); // Sletter alle.
        }
        else if (valg == 0)
        {
            cout << "\nIngen rute slettet.\n";
        }
        else
        {
            slett(valg - 1); // Sletter valgt rute (konverterer til 0-basert).
        }
    }
}