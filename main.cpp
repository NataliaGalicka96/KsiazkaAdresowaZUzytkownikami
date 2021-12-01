#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <conio.h>
#include <iterator>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};

struct Adresat
{
    int idAdresata;
    int idUzytkownika;
    string imie="";
    string nazwisko="";
    string numerTelefonu="";
    string email="";
    string adres="";
};

int wczytajWszystkichAdresatowZalogowanegoUzytkownika(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    fstream plik;

    plik.open("ksiazkaAdresowa.txt",ios::in);

    if(plik.good()==false)
    {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        return 0;
    }

    string linia, idAdresataPobraneZPlikuTxt, idUzytkownikaPobraneZPlikuTxt;
    int iloscAdresatow=0;

    while (!plik.eof())
    {
        getline(plik,idAdresataPobraneZPlikuTxt,'|');
        if (idAdresataPobraneZPlikuTxt != "")
        {
            getline(plik, idUzytkownikaPobraneZPlikuTxt, '|');
            if (atoi(idUzytkownikaPobraneZPlikuTxt.c_str()) == idZalogowanegoUzytkownika)
            {

                adresaci.push_back(Adresat());
                adresaci[iloscAdresatow].idAdresata = atoi(idAdresataPobraneZPlikuTxt.c_str());
                adresaci[iloscAdresatow].idUzytkownika = atoi(idUzytkownikaPobraneZPlikuTxt.c_str());
                getline(plik,linia,'|');
                adresaci[iloscAdresatow].imie = linia;
                getline(plik,linia,'|');
                adresaci[iloscAdresatow].nazwisko = linia;
                getline(plik,linia,'|');
                adresaci[iloscAdresatow].numerTelefonu = linia;
                getline(plik,linia,'|');
                adresaci[iloscAdresatow].email = linia;
                getline(plik,linia);
                adresaci[iloscAdresatow].adres = linia;
                iloscAdresatow++;
            }
            else
            {
                getline(plik,linia,'|');
                getline(plik,linia,'|');
                getline(plik,linia,'|');
                getline(plik,linia,'|');
                getline(plik,linia);
            }
        }
    }
    plik.close();

    return iloscAdresatow;
}
int wczytajWszystkichUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;

    plik.open("Uzytkownicy.txt",ios::in);

    if(plik.good()==false)
    {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        return 0;
    }

    string linia, idUzytkownikaPobraneZPlikuTxt;
    int iloscUzytkownikow=0;

    while (!plik.eof())
    {
        getline(plik,idUzytkownikaPobraneZPlikuTxt,'|');
        if (idUzytkownikaPobraneZPlikuTxt != "")
        {
            uzytkownicy.push_back(Uzytkownik());
            uzytkownicy[iloscUzytkownikow].idUzytkownika = atoi(idUzytkownikaPobraneZPlikuTxt.c_str());
            getline(plik,linia,'|');
            uzytkownicy[iloscUzytkownikow].login = linia;
            getline(plik,linia);
            uzytkownicy[iloscUzytkownikow].haslo = linia;
            iloscUzytkownikow++;
        }
    }
    plik.close();

    return iloscUzytkownikow;
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << uzytkownik.idUzytkownika << "|";
        plik << uzytkownik.login << "|";
        plik << uzytkownik.haslo << endl;

        plik.close();

    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku"<< endl;
        system("pause");
    }
}

int pobierzIdOstatniegoUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    if (uzytkownicy.empty() == true)
        return 1;
    else
        return uzytkownicy.back().idUzytkownika + 1;
}

int rejestracja(vector <Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    system("cls");
    string loginDoNowegoKonta, hasloDoNowegoKonta;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>loginDoNowegoKonta;

    vector <Uzytkownik>::iterator itr=uzytkownicy.begin();

    while(itr!=uzytkownicy.end())
    {
        if(itr -> login == loginDoNowegoKonta)
        {
            system("cls");
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>loginDoNowegoKonta;
            itr = uzytkownicy.begin();
        }
        else
        {
            itr++;
        }
    }

    cout<<"Podaj haslo: ";
    cin>>hasloDoNowegoKonta;

    Uzytkownik uzytkownik;

    uzytkownik.idUzytkownika=pobierzIdOstatniegoUzytkownika(uzytkownicy);
    uzytkownik.login=loginDoNowegoKonta;
    uzytkownik.haslo=hasloDoNowegoKonta;

    uzytkownicy.push_back(uzytkownik);

    dopiszUzytkownikaDoPliku(uzytkownik);
    iloscUzytkownikow++;

    cout<<"Konto zalozone"<<endl;
    Sleep(1000);

    return iloscUzytkownikow;

}

int logowanie(vector <Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    system("cls");
    string nazwaLogujacegoSieUzytkownika, hasloLogujacegoSieUzytkownika;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwaLogujacegoSieUzytkownika;

    vector <Uzytkownik>::iterator itr=uzytkownicy.begin();

    while(itr!=uzytkownicy.end())
    {
        if(itr -> login == nazwaLogujacegoSieUzytkownika)
        {

            for(int proby=0; proby<3; proby++)
            {

                cout<<"Podaj haslo. Pozostalo prob: "<<3-proby<<": ";
                cin>>hasloLogujacegoSieUzytkownika;


                if (itr -> haslo == hasloLogujacegoSieUzytkownika)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return itr -> idUzytkownika;
                }

            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(1000);
            return 0;
        }
        itr++;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;
}

void nadpisaniePlikuDoZmianyHasla(vector<Uzytkownik> &uzytkownicy, vector<Uzytkownik>::iterator itr)
{
    fstream plik, plikTymczasowy;

    plik.open("Uzytkownicy.txt", ios::in);
    plikTymczasowy.open("Uzytkownicy_tymczasowy.txt", ios::out|ios::app);

    string linia,idUzytkownikaPobraneZPlikuTxt;

    while(!plik.eof())
    {
        getline(plik,idUzytkownikaPobraneZPlikuTxt,'|');
        getline(plik,linia);

        if (itr -> idUzytkownika == atoi(idUzytkownikaPobraneZPlikuTxt.c_str()))
        {
            plikTymczasowy << itr -> idUzytkownika << "|";
            plikTymczasowy << itr -> login << "|";
            plikTymczasowy << itr -> haslo << endl;
        }
        else if (atoi(idUzytkownikaPobraneZPlikuTxt.c_str()))
        {
            plikTymczasowy << idUzytkownikaPobraneZPlikuTxt + "|" + linia << endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("Uzytkownicy.txt");
    rename("Uzytkownicy_tymczasowy.txt","Uzytkownicy.txt");
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int &idZalogowanegoUzytkownika)
{
    string noweHaslo;
    cout<<"Podaj nowe haslo: ";
    cin>>noweHaslo;

    for(vector <Uzytkownik>::iterator itr=uzytkownicy.begin(); itr!=uzytkownicy.end(); itr++)
    {
        if( itr -> idUzytkownika == idZalogowanegoUzytkownika)
        {
            itr -> haslo = noweHaslo;
            nadpisaniePlikuDoZmianyHasla(uzytkownicy,itr);
            cout<<"Haslo zostalo zmienione"<<endl;
            Sleep(1500);
            system("pause");
        }

    }
}

int sprawdzIloscWszystkichAdresatow ()
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        return 0;
    }

    string linia;
    int iloscLinii=0;
    while(!plik.eof())
    {
        getline(plik,linia);
        if (linia != "")
        {
            iloscLinii++;
        }
    }
    plik.close();
    return iloscLinii;
}

int sprawdzIdOstatniegoAdresata()
{
    int iloscWszystkichAdresatow = sprawdzIloscWszystkichAdresatow();
    if (iloscWszystkichAdresatow == 0)
    {
        return 0;
    }
    else
    {
        fstream plik;
        string linia;
        plik.open("ksiazkaAdresowa.txt", ios::in);
        for (int i=0; i < iloscWszystkichAdresatow; i++ )
        {
            if (i == iloscWszystkichAdresatow-1)
            {
                getline(plik,linia,'|');
                plik.close();
                return atoi(linia.c_str());
            }
            else
            {
                getline(plik,linia);
            }
        }
    }
}
int ustawIdOstatniegoAdresata (vector <Adresat> &adresaci)
{
    int iloscWszystkichAdresatow = sprawdzIloscWszystkichAdresatow();
    if (iloscWszystkichAdresatow == 0)
    {
        return 1;
    }
    else
    {
        return sprawdzIdOstatniegoAdresata()+1;
    }
}

Adresat podajDaneNowegoAdresata(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");

    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie adresata: ";
    cin >> imie;
    cout << "Podaj nazwisko adresata: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu adresata: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email adresata: ";
    cin >> email;
    cout << "Podaj adres adresata: ";
    cin.sync();
    getline(cin, adres);

    Adresat adresat;

    adresat.idAdresata=ustawIdOstatniegoAdresata(adresaci);
    adresat.idUzytkownika=idZalogowanegoUzytkownika;
    adresat.imie=imie;
    adresat.nazwisko=nazwisko;
    adresat.numerTelefonu=numerTelefonu;
    adresat.email=email;
    adresat.adres=adres;

    return adresat;
}
void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << adresat.idAdresata << "|";
        plik << adresat.idUzytkownika << "|";
        plik << adresat.imie << "|";
        plik << adresat.nazwisko << "|";
        plik << adresat.numerTelefonu << "|";
        plik << adresat.email << "|";
        plik << adresat.adres <<endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku"<< endl;
        system("pause");
    }
}
void dodajOsobe(vector <Adresat> &adresaci,int &iloscAdresatow, int &idZalogowanegoUzytkownika)
{
    Adresat adresat=podajDaneNowegoAdresata(adresaci, idZalogowanegoUzytkownika);

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat);
    iloscAdresatow++;

    cout<<endl<<"Dodano adresata."<<endl;
    system("pause");
}

void wyswietlAdresata(vector <Adresat> &adresaci, vector<Adresat>::iterator itr)
{
    cout << "Id: " << itr -> idAdresata << endl;
    cout << "Imie: " << itr -> imie << endl;
    cout << "Nazwisko: " << itr -> nazwisko << endl;
    cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
    cout << "Adres: " << itr -> adres << endl;
    cout << "Email: " << itr -> email << endl << endl;

}
void wyswietlWszystkichAdresatow(vector<Adresat> &adresaci)
{
    if(!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            wyswietlAdresata(adresaci,itr);
        }
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

void wyszukajPoImieniu(vector <Adresat> &adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        string imieSzukanejOsoby = "";
        cout<<"Podaj imie osoby, ktorej szukasz: ";
        cin>>imieSzukanejOsoby;
        system("cls");

        bool czyIstniejeKontakt = false;
        for(vector<Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {

            if(itr -> imie == imieSzukanejOsoby)
            {
                czyIstniejeKontakt = true;
                wyswietlAdresata(adresaci,itr);
            }

        }
        if (czyIstniejeKontakt == false)
            cout << endl << "Nie ma osoby o takim imieniu w ksiazce adresowej!" << endl << endl;
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        string nazwiskoSzukanejOsoby;
        cout<<"Podaj nazwisko osoby, ktorej szukasz: ";
        cin>>nazwiskoSzukanejOsoby;
        system("cls");

        bool czyIstniejeKontakt = false;
        for(vector<Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {

            if(itr -> nazwisko == nazwiskoSzukanejOsoby)
            {
                czyIstniejeKontakt = true;
                wyswietlAdresata(adresaci,itr);
            }

        }
        if (czyIstniejeKontakt == false)
            cout << endl << "Nie ma osoby o takim nazwisku w ksiazce adresowej!" << endl << endl;
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

void nadpisaniePlikuDoEdycjiAdresata (vector<Adresat> &adresaci, vector<Adresat>::iterator itr)
{
    fstream plik, plikTymczasowy;

    plik.open("ksiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out|ios::app);

    string linia,idAdresataPobraneZPlikuTxt;

    while(!plik.eof())
    {
        getline(plik,idAdresataPobraneZPlikuTxt,'|');
        getline(plik,linia);

        if (itr -> idAdresata == atoi(idAdresataPobraneZPlikuTxt.c_str()))
        {
            plikTymczasowy << itr -> idAdresata << "|";
            plikTymczasowy << itr -> idUzytkownika << "|";
            plikTymczasowy << itr -> imie << "|";
            plikTymczasowy << itr -> nazwisko << "|";
            plikTymczasowy << itr -> numerTelefonu << "|";
            plikTymczasowy << itr -> email << "|";
            plikTymczasowy << itr -> adres << endl;
        }
        else if (atoi(idAdresataPobraneZPlikuTxt.c_str()))
        {
            plikTymczasowy << idAdresataPobraneZPlikuTxt + "|" + linia << endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("ksiazkaAdresowa.txt");
    rename("Adresaci_tymczasowy.txt","ksiazkaAdresowa.txt");
}


void nadpisaniePlikuDoUsuwaniaAdresata (vector<Adresat> &adresaci, vector<Adresat>::iterator itr)
{
    fstream plik, plikTymczasowy;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out|ios::app);

    string linia,idAdresataPobraneZPlikuTxt;

    while(!plik.eof())
    {
        getline(plik,idAdresataPobraneZPlikuTxt,'|');
        getline(plik,linia);

        if (itr -> idAdresata == atoi(idAdresataPobraneZPlikuTxt.c_str()) )
        {
            continue;
        }
        else if (atoi(idAdresataPobraneZPlikuTxt.c_str()))
        {
            plikTymczasowy << idAdresataPobraneZPlikuTxt + "|" + linia << endl;
        }
    }

    plik.close();
    plikTymczasowy.close();

    remove("ksiazkaAdresowa.txt");
    rename("Adresaci_tymczasowy.txt","ksiazkaAdresowa.txt");
}

int usunAdresata(vector <Adresat> &adresaci, int &iloscAdresatow)
{

    if(adresaci.size()>0)
    {
        int idAdresataDoUsuniecia;
        cout<<"Podaj ID adresata do usuniecia: "<<endl;
        cin>> idAdresataDoUsuniecia;
        system("cls");

        bool czyIstniejeKontaktOTakimId = false;
        for(vector <Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {
            if(itr -> idAdresata == idAdresataDoUsuniecia)
            {
                czyIstniejeKontaktOTakimId = true;
                system("cls");
                cout<<"Adresat, ktory zostanie usuniety: " <<endl;
                wyswietlAdresata(adresaci,itr);
                cout<<"Czy na pewno chcesz usunac adresata? (t)"<<endl;

                if(getch()=='t'||getch()=='T')
                {
                    nadpisaniePlikuDoUsuwaniaAdresata(adresaci,itr);
                    adresaci.erase(itr);
                    iloscAdresatow--;
                    cout << endl << "Kontakt zostal usuniety" << endl;
                    Sleep(1000);
                    return idAdresataDoUsuniecia;
                }
                else
                {
                    return 0;
                }
            }

        }
        if (czyIstniejeKontaktOTakimId == false)
            cout << endl << "Nie ma osoby o takim numerze id w ksiazce adresowej!" << endl << endl;
    }
    else
        cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}


void edytujAdresata(vector <Adresat> &adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        bool czyIstniejeKontaktOTakimId = false;
        int idAdresataDoEdycji=0;
        cout<<"Podaj ID adresata, ktorego chcesz edytowac: ";
        cin>>idAdresataDoEdycji;

        for(vector <Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {

            if( itr -> idAdresata == idAdresataDoEdycji)
            {
                czyIstniejeKontaktOTakimId=true;



                char wybor;
                while(true)
                {
                    system("cls");
                    cout<<"Adresat ktorego dane beda edytowane: " <<endl;
                    wyswietlAdresata(adresaci,itr);
                    cout<<"Ktora informacje chcesz edytowac?"<<endl;
                    cout << "1. Imie" << endl;
                    cout << "2. Nazwisko" << endl;
                    cout << "3. Numer telefonu" << endl;
                    cout << "4. Email" << endl;
                    cout << "5. Adres" << endl;
                    cout << "6. Powrot do menu" << endl;
                    cout<<"Twoj wybor: ";
                    cin>>wybor;

                    if(wybor=='1')
                    {
                        system("cls");
                        cout<<"Wpisz nowe imie."<<endl;
                        string noweImie;
                        cin>>noweImie;

                        itr -> imie = noweImie;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");
                        continue;
                    }
                    else if(wybor=='2')
                    {
                        system("cls");
                        cout<<"Wpisz nowe nazwisko."<<endl;
                        string noweNazwisko;
                        cin>>noweNazwisko;

                        itr -> nazwisko = noweNazwisko;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;

                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='3')
                    {
                        system("cls");
                        cout<<"Wpisz nowy numer telefonu."<<endl;
                        string nowyNumerTelefonu;
                        cin.sync();
                        getline(cin,nowyNumerTelefonu);

                        itr -> numerTelefonu = nowyNumerTelefonu;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='4')
                    {
                        system("cls");
                        cout<<"Wpisz nowy email."<<endl;
                        string nowyEmail;
                        cin>>nowyEmail;

                        itr -> email = nowyEmail;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='5')
                    {
                        system("cls");
                        cout<<"Wpisz nowy adres."<<endl;
                        string nowyAdres;
                        cin.sync();
                        getline(cin,nowyAdres);

                        itr -> adres = nowyAdres;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;

                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='6')
                    {
                        break;
                    }
                }
                break;
            }

        }
        if (czyIstniejeKontaktOTakimId == false)
            cout << endl << "Nie ma osoby o takim numerze id w ksiazce adresowej!" << endl << endl;
    }
    else
        cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}
void przejdzDoKsiazkiAdresowej(vector <Uzytkownik> &uzytkownicy, int &iloscUzytkownikow, int &idZalogowanegoUzytkownika)
{
    vector <Adresat> adresaci;

    char wybor;

    int iloscAdresatowZalogowanegoUzytkownika = wczytajWszystkichAdresatowZalogowanegoUzytkownika(adresaci,idZalogowanegoUzytkownika);

    while (1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "Twoj wybor: ";

        cin>>wybor;

        if (wybor == '1')
        {
            system ("cls");
            dodajOsobe(adresaci, iloscAdresatowZalogowanegoUzytkownika, idZalogowanegoUzytkownika);
        }
        else if (wybor == '2')
        {
            system ("cls");
            wyszukajPoImieniu(adresaci);
        }
        else if (wybor == '3')
        {
            system ("cls");
            wyszukajPoNazwisku(adresaci);
        }
        else if (wybor == '4')
        {
            system ("cls");
            wyswietlWszystkichAdresatow(adresaci);
        }
        else if (wybor == '5')
        {
            system ("cls");
            usunAdresata(adresaci, iloscAdresatowZalogowanegoUzytkownika);

        }
        else if (wybor == '6')
        {
            system ("cls");
            edytujAdresata(adresaci);
        }
        else if(wybor == '7')
        {
            system("cls");
            zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
        }
        else if (wybor == '8')
        {
            idZalogowanegoUzytkownika=0;
            break;
        }
    }

}


int main()
{
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika=0;
    int iloscUzytkownikow=0;
    char wybor;

    iloscUzytkownikow=wczytajWszystkichUzytkownikowZPliku(uzytkownicy);

    while(1)
    {
        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout<<"1.Rejestracja"<<endl;
            cout<<"2.Logowanie"<<endl;
            cout<<"3.Zakoncz program"<<endl;
            cout << "Twoj wybor: ";
            cin>>wybor;


            if(wybor=='1')
            {
                iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy,iloscUzytkownikow);
                if(idZalogowanegoUzytkownika!=0)
                {
                    przejdzDoKsiazkiAdresowej(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                }
            }
            else if (wybor=='3')
            {
                exit(0);
            }
        }
    }

    return 0;
}
