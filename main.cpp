/* 
El¿bieta M¹czka
Program obliczaj¹cy liczbê dni miêdzy dwiema datami
	*/
#include <iostream>
#include <string>
#include <Windows.h>

#define reset SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);				//resetuje kolor tekstu do zielonego :D
#define czerwony SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); //wpiszesz 'czerwony' to tekst od momentu wpisania pojawia siê na czerwono
#define iczerwony SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY); //mocny czerwony
#define zolty SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN);
#define niebieski SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);

using namespace std;
//tablica liczb dni w latach od 0 - 99
const int tab[] = {0, 365, 731, 1096, 1461, 1827, 2192, 2557, 2922, 3288, 3653, 4018, 4383, 4749, 5114, 5479, 5844, 6210, 6575, 6940, 7305, 7671, 8036, 8401, 8766, 9132, 9497, 9862, 10227, 10593, 10958, 11323, 11688, 12054, 12419, 12784, 13149, 13515, 13880, 14245, 14610, 14976, 15341, 15706, 16071, 16437, 16802, 17167, 17532, 17898, 18263, 18628, 18993, 19359, 19724, 20089, 20454, 20820, 21185, 21550, 21915, 22281, 22646, 23011, 23376, 23742, 24107, 24472, 24837, 25203, 25568, 25933, 26298, 26664, 27029, 27394, 27759, 28125, 28490, 28855, 29220, 29586, 29951, 30316, 30681, 31047, 31412, 31777, 32142, 32508, 32873, 33238, 33603, 33969, 34334, 34699, 35064, 35430, 35795, 36160, 36525};

const unsigned short dni_w_miesiacu[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned short dni_w_miesiacuP[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


//dni do koñca roku. Liczy od dnia i miesi¹ca podanych jako argumenty. 
//zale¿nie od tego, czy rok jest przestêpny, czy nie.
unsigned short dni_do_konca(unsigned short miesiac, unsigned short dni, bool przestepny)
{ 
	int temp=0;
	
	if(przestepny==false)
	{
		for(int i=11; i>miesiac-2; i--)
		{
			temp+=dni_w_miesiacu[i];
		}
		return temp-dni;
	}
	else
	{
		for(int i=11; i>miesiac-2; i--)
		{
			temp+=dni_w_miesiacuP[i];
		}
		return temp-dni;
	}
}

//dni od pocz¹tku roku do dnia [i miesi¹ca] podanych jako argumenty.
unsigned short dni_od_poczatku(unsigned short miesiac, unsigned short dni, bool przestepny)
{
		int temp=0;
	
	if(przestepny==false)
	{
		for(int i=0; i<miesiac-1; i++)
		{
			temp+=dni_w_miesiacu[i];
		}
		return temp+dni;
	}
	else
	{
		for(int i=0; i<miesiac-1; i++)
		{
			temp+=dni_w_miesiacuP[i];
		}
		return temp+dni;
	}
}

//liczy sumê dni miêdzy miesi¹cami 
unsigned short dni_w_miesiacach(unsigned short nMiesiac1, unsigned short nMiesiac2, bool przestepny)
{
	if(przestepny==false)
	{
		int temp=0;
		for(int i=nMiesiac1; i<nMiesiac2; i++)
		{
			temp+=dni_w_miesiacu[i-1];
		}
		return temp;
	}
	else
	{
		int temp=0;
		for(int i=nMiesiac1; i<nMiesiac2; i++)
		{
			temp+=dni_w_miesiacuP[i-1];
		}
		return temp;
	}
}

//weryfikacja poprawnoœci daty
bool weryfikacja(unsigned short nDni1, unsigned short nMiesiac1, unsigned short nLata1, bool przestepny)
{
	if(przestepny==false)
	{
		if(nDni1<=dni_w_miesiacu[nMiesiac1-1] && nDni1>=1 && nMiesiac1<=12 && nMiesiac1>=1)
			return true;
	}
	else if(przestepny==true)
	{
		if(nDni1<=dni_w_miesiacuP[nMiesiac1-1] && nDni1>=1 && nMiesiac1<=12 && nMiesiac1>=1)
			return true;
	}
	else 
		return false;
}

//'serce' programu - funkcja obliczaj¹ca ró¿nicê dni miêdzy datami podanymi jako argumenty
unsigned short oblicz(char cData1[], char cData2[])
{
	unsigned short temp = 0;
//dni
	unsigned short nDni1		= ((int)cData1[0]-48)*10+(int)cData1[1]-48;
	unsigned short nMiesiac1	= ((int)cData1[3]-48)*10+(int)cData1[4]-48;
	unsigned short nLata1	= ((int)cData1[6]-48)*1000+((int)cData1[7]-48)*100+((int)cData1[8]-48)*10+(int)cData1[9]-48;
	
//dni 2
	unsigned short nDni2		= ((int)cData2[0]-48)*10+(int)cData2[1]-48;
	unsigned short nMiesiac2	= ((int)cData2[3]-48)*10+(int)cData2[4]-48;
	unsigned short nLata2		= ((int)cData2[6]-48)*1000+((int)cData2[7]-48)*100+((int)cData2[8]-48)*10+(int)cData2[9]-48;
	
	unsigned short nRoznicaLat	= nLata2 - nLata1;
	unsigned short jedn_dzie	= nRoznicaLat - (nRoznicaLat/1000)*1000 - (nRoznicaLat/100)*100; //zmienna pomocnicza - przechowuje liczbê bêd¹c¹ jednoœciami i dziesiatkami

	bool bRok1P=false;
	bool bRok2P=false;

	if(nLata1%4==0 && (nLata1%100!=0||nLata1%1000==0))
	{
		bRok1P=true;
	}
	if(nLata2%4==0 && (nLata2%100!=0||nLata2%1000==0))
	{
		bRok2P=true;
	}


	if(weryfikacja(nDni1, nMiesiac1, nLata1, bRok1P)==false)
	{
		std::cout<<"Nieprawidlowa data! Kod bledu: "; return 1;
	}
	if(weryfikacja(nDni2, nMiesiac2, nLata2, bRok2P)==false)
	{
		std::cout<<"Nieprawidlowa data! Kod bledu: "; return 2;
	}

	if(nLata2<nLata1)
	{
		cout<<"Nieprawidlowa data! Kod bledu: "; return 3; 
	}
	
	if(nLata1==nLata2 && nMiesiac2<=nMiesiac1 && nDni2<nDni1)
	{
		cout<<"Nieprawidlowa data! Kod bledu: "; return 4;
	}; 
	
	//cout<<endl;
	if(nLata1!=nLata2){
		temp += (nRoznicaLat/1000)*365241 + (nRoznicaLat/100)*36524 + tab[jedn_dzie-1] + dni_do_konca(nMiesiac1, nDni1, bRok1P) + dni_od_poczatku(nMiesiac2, nDni2, bRok2P);}
		else{
			temp += dni_w_miesiacach(nMiesiac1, nMiesiac2, bRok1P) - nDni1 + nDni2;}

	return temp;
}

void wyswietl()
{
	char cData1[] = "DD.MM.RRRR\0"; // data wczeœniejsza
	char cData2[] = "DD.MM.RRRR\0"; // data póŸniejsza

	Sleep(1000);
				cout<<endl;
				cout<<"\npodaj date wczesniejsza w formacie: DD.MM.RRRR: ";
				cin>>cData1;
				cout<<"\n\npodaj date pozniejsza w formacie: DD.MM.RRRR: ";
				cin>>cData2;
				cout<<endl;
				
				cout<<"\t\tRoznica dni: ";
				zolty;
				cout<< oblicz(cData1, cData2) <<endl;;
				reset;
				Sleep(2000);
}

int main()
{
	reset;
	cout<<"\t\t\t\tKalkulator Dat\n\t\t\t\t   Od Eli";
	iczerwony;
	cout<<"\n\t\t\t\t   v. 3.14 :)\n\n"<<endl;
	reset;
	int nOpcja, nPowtorzenia;
menu:
	cout<<"\n\nWybierz opcje: "
		<<"\n1. przelicz liczbe dni miedzy jedna para dat"
		<<"\n2. przelicz liczbe dni miedzy wieksza iloscia par dat"
		<<"\n3. pomoc"
		<<"\n0. exit"<<endl;
	cout<<"Opcja: ";
	cin>>nOpcja;
	nOpcja=(int)nOpcja;
	
	switch(nOpcja)
	{
		case 1:	wyswietl();
				break;

		case 2: cout<<"podaj ilosc par, ktore chcesz porownywac: ";
				cin>>nPowtorzenia;
				cout<<endl;
				for(int i=0; i<nPowtorzenia; i++)
				{
					wyswietl();	
				}
				break;
		case 3: czerwony;
				cout<<"\n\t\tPOMOC KALKULATORA DNI"<<endl;
				reset;
				cout<<"\nProgram oblicza liczbe dni miedzy podanymi datami. Format daty to: DD.MM.RR."
					<<"\nBrakujace miejsca nalezy uzupelniac zerami, np.: \n02.09.0996 oznacza drugi wrzesnia 996 roku"
					<<"\n\nKody bledow: "
					<<"\n\t1 - bledny miesiac, lub dzien w dacie wczesniejszej"
					<<"\n\t2 - bledny miesiac, lub dzien w dacie pozniejszej"
					<<"\n\t3 - bledny rok"
					<<"\n\t4 - dzien/miesiac daty pozniejszej < daty wczesniejszej";
				cout<<"\n\n\t\tKoniec tematow pomocy\n"; 
				system("pause"); break;


		case 0: cout<<endl; exit(0); break;

		default: cout<<"Bledna opcja! Wybierz poprawna: "<<endl;
			goto menu;

	}
	goto menu;
}