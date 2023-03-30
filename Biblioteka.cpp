#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <windows.h>	
#include <stdio.h>
#include <conio.h>

using namespace std;
bool prawda3;

void DodajKsiazke() {
	bool prawda2;
	char wybor;
	do{
		prawda2=true;
		system("CLS");
		string sygnatura, autor, tytul, isbn, wydawnictwo, rok_wydania1;
		char sygnatura1[5]="", autor1[51]="", tytul1[51]="", isbn1[14]="", wydawnictwo1[51]="";
		short rok_wydania=0, id;
		bool prawda=false, prawda1=false;
		
		ofstream plik;
		string nazwa = "biblioteka.bin";
		
		plik.open(nazwa, ios::in | ios::binary);
		
		if(plik.is_open()) {
			plik.seekp(0, ios::end);
			id=(plik.tellp()/176);
			if(wybor!='\0') {
				cin.ignore();
			}
			printf("\n");
			do {
				printf("\n%40s%s","Podaj sygnaturê: ","  ");
				getline(cin, sygnatura);
				if(sygnatura.length()!=4) {
					prawda=true;
					printf("%51s","Sygnatura musi mieæ 4 znaki!");
				} else {
					for(int i=0; i<sygnatura.length(); i++) {
						sygnatura1[i]=sygnatura.at(i);
					}
					prawda=false;
				}
			}while(prawda);
			do{
				printf("\n%37s%s","Podaj autora: ","     ");
				getline(cin, autor);
				if(autor.length()<5 | autor.length()>50) {
					prawda=true;
					printf("%61s","Autor musi zawieraæ od 5 do 50 znaków!");
				} else {
					for(int i=0; i<autor.length(); i++) {
						autor1[i]=autor.at(i);
					}
					prawda=false;
				}
			}while(prawda);
			do{
				printf("\n%36s%s","Podaj tytu³: ","      ");
				getline(cin, tytul);
				if(tytul.length()<1 | tytul.length()>50) {
					prawda=true;
					printf("%61s","Tytul musi zawieraæ od 1 do 50 znaków!");
				} else {
					for(int i=0; i<tytul.length(); i++) {
						tytul1[i]=tytul.at(i);
					}
					prawda=false;
				}
			}while(prawda);
			do{
				printf("\n%35s%s","Podaj ISBN: ","       ");
				getline(cin, isbn);
				if(isbn.length()!=13) {
					prawda=true;
					printf("%48s","ISBN musi mieæ 13 znaków!");
				} else {
					for(int i=0; i<isbn.length(); i++) {
						isbn1[i]=isbn.at(i);
					}
					prawda=false;
				}
			}while(prawda);
			do{
				printf("\n%42s","Podaj wydawnictwo: ");
				getline(cin, wydawnictwo);
				if(wydawnictwo.length()<3 | wydawnictwo.length()>50) {
					prawda=true;
					printf("%67s","Wydawnictwo musi zawieraæ od 3 do 50 znaków!");
				} else {
					for(int i=0; i<wydawnictwo.length(); i++) {
						wydawnictwo1[i]=wydawnictwo.at(i);
					}
					prawda=false;
				}
			}while(prawda);
			do{
				printf("\n%42s","Podaj rok wydania: ");
				cin >> rok_wydania1;
				const char* c_inp = rok_wydania1.c_str();
				rok_wydania = atoi(c_inp);
				if(rok_wydania<1850 | rok_wydania>2021) {
					printf("%70s","Rok wydania musi byæ z przedzia³u 1850 do 2021!");
					prawda=true;
				} else {
					prawda=false;
				};
			}while(prawda);
			short g=id+1;
			
			plik.write((const char*) &g, sizeof(short));
			plik.write((const char*) &sygnatura1, sizeof(sygnatura1));
			plik.write((const char*) &autor1, sizeof(autor1));
			plik.write((const char*) &tytul1, sizeof(tytul1));
			plik.write((const char*) &isbn1, sizeof(isbn1));
			plik.write((const char*) &wydawnictwo1, sizeof(wydawnictwo1));
			plik.write((const char*) &rok_wydania, sizeof(short));
		};
		if (plik.is_open()) plik.close();
		
		printf("\n\n%33s%d%s\n","Gratulacje, uda³o Ci siê dodaæ ksi¹¿kê do bazy o id równym: ",id+1,"\n\n");
		printf("%s","Co chcesz zrobiæ dalej?\n\n");
		printf("%s","1: Dodaj now¹ ksi¹¿kê\n");
		printf("%s","2: Wróæ do menu g³ównego\n\n");
		printf("%s","WprowadŸ numer: ");
		do{
			wybor=getche();
			switch(wybor) {
				case '1':
					prawda2=true;
					prawda1=false;
				break;
				case '2':
					prawda2=false;
					prawda3=true;
					prawda1=false;
				break;
				default: 
					printf("\n%s","Niepoprawny numer!");
					printf("\n%s","Spróbuj ponownie: ");
					prawda1=true;
				break;
			}
		}while(prawda1);
	}while(prawda2);
};

void ListujKsiazki() {
	bool prawda, prawda2, prawda1=false;
	int i=0;
	char wybor;
	
	do{
	system("CLS");
	
	ifstream plik;
	string nazwa = "biblioteka.bin";
	
	plik.open(nazwa, ios::out | ios::binary);
	
	if(plik.is_open()) {
		printf("\n\n%15s%12s%30s%30s%25s%25s%25s","Numer kolejny","Sygnatura","Autor","Tytul","ISBN","Wydawnictwo","Rok wydania\n\n");
			plik.seekg(0, ios::end);
			int size = (int)plik.tellg();
			plik.seekg(0, ios::beg);
			while(plik.tellg()<size) {
				char sygnatura[5], autor[51], tytul[51], isbn[14], wydawnictwo[51];
				short id, rok_wydania;
				plik.read((char*) &id, sizeof(short));
				plik.read((char*) &sygnatura, sizeof(sygnatura));
				plik.read((char*) &autor, sizeof(autor));
				plik.read((char*) &tytul, sizeof(tytul));
				plik.read((char*) &isbn, sizeof(isbn));
				plik.read((char*) &wydawnictwo, sizeof(wydawnictwo));
				plik.read((char*) &rok_wydania, sizeof(short));
				
				printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id,sygnatura,autor,tytul,isbn,wydawnictwo,rok_wydania);
			}		
	}
	if (plik.is_open()) plik.close();
	prawda=false;
	
	printf("\n\n\n%64s","Co chcesz zrobiæ dalej?\n\n");
		printf("%50s","1: Odœwie¿\n");
		printf("%65s","2: Wróæ do menu g³ównego\n\n");
		printf("%55s","WprowadŸ numer: ");
		do{
			wybor=getche();
			switch(wybor) {
				case '1':
					prawda2=true;
					prawda1=false;
				break;
				case '2':
					prawda2=false;
					prawda3=true;
					prawda1=false;
				break;
				default: 
					printf("\n%57s","Niepoprawny numer!");
					printf("\n%57s","Spróbuj ponownie: ");
					prawda1=true;
				break;
			}
		}while(prawda1);
	}while(prawda2);
};

void WyszukajKsiazke() {
	bool prawda2=true;
	string id1, rok_wydania1, sygnatura1, autor1, tytul1, isbn1, wydawnictwo1;
	char wybor, sygnatura[5]="", autor[51]="", tytul[51]="", isbn[14]="", wydawnictwo[51]="";
	short id=0, rok_wydania=0, f=0;
	const char* c_inp;
	do{
		system("CLS");
		printf("\n\n%70s","Po jakim parametrze chcesz szukaæ?");
		printf("\n\n%44s\n%52s\n%49s\n%48s\n%46s\n%54s\n%54s\n\n%60s\n\n","1: Po ID","2: Po sygnaturze","3: Po autorze","4: Po tytule","5: Po ISBN","6: Po wydawnictwie","7: Po roku wydania","8: Wróæ do menu g³ównego");
		bool prawda1=true;
		do{
			printf("%52s","WprowadŸ numer: ");
			wybor=getche();
			
			switch(wybor) {
				case '1':
					printf("\n%49s","WprowadŸ id: ");
					getline(cin, id1);
					c_inp=id1.c_str();
					id=atoi(c_inp);
					if(id==0) {
						printf("%57s\n","Podano niepoprawne ID");
					} else {
						f=1;
						prawda1=false;
					}
				break;
				case '2':
					printf("\n%56s","WprowadŸ syganturê: ");
					getline(cin, sygnatura1);
					if(sygnatura1.length()!=4) {
							printf("%67s\n","Sygnatura powinna mieæ 4 znaki!");
					} else {
						strcpy(sygnatura, sygnatura1.c_str());
						f=2;
						prawda1=false;
					}
				break;
				case '3':
					printf("\n%53s","WprowadŸ autora: ");
					getline(cin, autor1);
					if(autor1.length()>50 || autor1.length()<5) {
						printf("%80s\n","Nazwa autora powinna mieæ od 5 do 50 znaków!");
					} else {
						strcpy(autor, autor1.c_str());
						f=3;
						prawda1=false;
					}
				break;
				case '4':
					printf("\n%52s","WprowadŸ tytul: ");
					getline(cin, tytul1);
					if(tytul1.length()<1 || tytul1.length()>50) {
						printf("%74s\n","Tytu³ powinien mieæ od 1 do 50 znaków!");
					} else {
						strcpy(tytul, tytul1.c_str());
						f=4;
						prawda1=false;
					}
				break;
				case '5':
					printf("\n%51s","WprowadŸ ISBN: ");
					getline(cin, isbn1);
					if(isbn1.length()!=13) {
						printf("%75s\n","ISBN powinien mieæ dok³adnie 13 znaków!");
					} else {
						strcpy(isbn, isbn1.c_str());
						f=5;
						prawda1=false;
					}
				break;
				case '6':
					printf("\n%58s","WprowadŸ wydawnictwo: ");
					getline(cin, wydawnictwo1);
					if(wydawnictwo1.length()<3 || wydawnictwo1.length()>50) {
						printf("%83s\n","Wydawnictwo powinno zawieraæ od 3 do 50 znaków!");
					} else {
						strcpy(wydawnictwo, wydawnictwo1.c_str());
						f=6;
						prawda1=false;
					}
				break;
				case '7':
					printf("\n%58s","WprowadŸ rok wydania: ");
					getline(cin, rok_wydania1);
					c_inp=rok_wydania1.c_str();
					rok_wydania=atoi(c_inp);
					if(rok_wydania<1850 || rok_wydania>2021) {
						printf("%95s\n","Rok wydania powinien zawieraæ siê w latach od 1850 do 2021!");
					} else {
						f=7;
						prawda1=false;
					}
				break;
				case '8':
					f=0;
					prawda1=false;
					prawda2=false;
					prawda3=true;
				break;
				default:
					printf("\n%54s\n","Niepoprawny numer!");
				break;
			}
		}while(prawda1);
		
		if(f>=1 && f<=7) {
			system("CLS");
			short i=0;
			ifstream plik;
			
			plik.open("biblioteka.bin", ios::out | ios::binary);
			
			plik.seekg(0, ios::end);
			int size = (int)plik.tellg();
			plik.seekg(0, ios::beg);
			
			printf("\n\n%15s%12s%30s%30s%25s%25s%25s","Numer kolejny","Sygnatura","Autor","Tytul","ISBN","Wydawnictwo","Rok wydania\n\n");
			
			while(plik.tellg()<size) {
				char sygnatura3[5]="", autor3[51]="", tytul3[51]="", isbn3[14]="", wydawnictwo3[51]=""; 
				short id3, rok_wydania3;
				
				if(f==1) {
					plik.seekg(i, ios::beg);
					i=(i+176);
					plik.read((char*) &id3, sizeof(short));
					if(id3==id) {
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);		
					} else {
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
					}
				} else if(f==2) {
					plik.seekg((i+=2), ios::beg);
					plik.read((char*) &sygnatura3, sizeof(sygnatura3));					
					if(strcmp(sygnatura3,sygnatura)==0) {
						plik.seekg((i-2), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-2), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				} else if(f==3) {
					plik.seekg((i+=7), ios::beg);
					plik.read((char*) &autor3, sizeof(autor3));					
					if(strcmp(autor3,autor)==0) {
						plik.seekg((i-7), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-7), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				} else if(f==4) {
					plik.seekg((i+=58), ios::beg);
					plik.read((char*) &tytul3, sizeof(tytul3));					
					if(strcmp(tytul3,tytul)==0) {
						plik.seekg((i-58), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-58), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				} else if(f==5) {
					plik.seekg((i+=109), ios::beg);
					plik.read((char*) &isbn3, sizeof(isbn3));					
					if(strcmp(isbn3,isbn)==0) {
						plik.seekg((i-109), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-109), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				} else if(f==6) {
					plik.seekg((i+=123), ios::beg);
					plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));					
					if(strcmp(wydawnictwo3,wydawnictwo)==0) {
						plik.seekg((i-123), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-123), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				} else if(f==7) {
					plik.seekg((i+=174), ios::beg);
					plik.read((char*) &rok_wydania3, sizeof(short));					
					if(rok_wydania3==rok_wydania) {
						plik.seekg((i-174), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						
						printf("%15d%12s%30s%30s%25s%25s%23d\n\n",id3,sygnatura3,autor3,tytul3,isbn3,wydawnictwo3,rok_wydania3);
						
						i=(plik.tellg());
					} else {
						plik.seekg((i-174), ios::beg);
						plik.read((char*) &id3, sizeof(short));
						plik.read((char*) &sygnatura3, sizeof(sygnatura3));
						plik.read((char*) &autor3, sizeof(autor3));
						plik.read((char*) &tytul3, sizeof(tytul3));
						plik.read((char*) &isbn3, sizeof(isbn3));
						plik.read((char*) &wydawnictwo3, sizeof(wydawnictwo3));
						plik.read((char*) &rok_wydania3, sizeof(short));
						i=(plik.tellg());
					}
				}
			}
		}
		if(prawda2) {
			printf("\n\n\n%50s","Co chcesz zrobiæ dalej?\n\n");
			printf("%53s","1: Wyszukaj kolejn¹ ksi¹¿kê\n");
			printf("%51s","2: Wróæ do menu g³ównego\n\n");
			printf("%41s","WprowadŸ numer: ");
			do{
				wybor=getche();
				switch(wybor) {
					case '1':
						prawda2=true;
						prawda1=false;
					break;
					case '2':
						prawda2=false;
						prawda3=true;
						prawda1=false;
					break;
					default: 
						printf("\n%43s","Niepoprawny numer!");
						printf("\n%43s","Spróbuj ponownie: ");
						prawda1=true;
					break;
				}
			}while(prawda1);
		}		
	}while(prawda2);
};

void UsunKsiazke() {
	bool prawda2;
	do{
		system("CLS");
		string id1;
		short id=0, id2=0, flag=0, id3, rok_wydania;
		bool prawda1;
		char sygnatura[5], autor[51], tytul[51], isbn[14], wydawnictwo[51], wybor;
		
		printf("\n\n%70s","Podaj ID ksi¹¿ki któr¹ chcesz usun¹æ: ");
		getline(cin, id1);
		const char* c_inp = id1.c_str();
		id = atoi(c_inp);
		
		bool prawda;
		ifstream plik;
		ofstream plik1;
		string nazwa = "biblioteka.bin";
	
		plik.open(nazwa, ios::in | ios::binary);
			
		plik1.open("temp.bin", ios::out | ios::binary);
				
		while(!plik.eof()) {
			
			plik.read((char*) &id2, sizeof(short));
			plik.read((char*) &sygnatura, sizeof(sygnatura));
			plik.read((char*) &autor, sizeof(autor));
			plik.read((char*) &tytul, sizeof(tytul));
			plik.read((char*) &isbn, sizeof(isbn));
			plik.read((char*) &wydawnictwo, sizeof(wydawnictwo));
			plik.read((char*) &rok_wydania, sizeof(short));				
					
			if(plik) {
				if(id2==id) {
					flag=1;
				} else {
					id3=(id2-flag);
					plik1.write((char*) &id3, sizeof(short));
					plik1.write((char*) &sygnatura, sizeof(sygnatura));
					plik1.write((char*) &autor, sizeof(autor));
					plik1.write((char*) &tytul, sizeof(tytul));
					plik1.write((char*) &isbn, sizeof(isbn));
					plik1.write((char*) &wydawnictwo, sizeof(wydawnictwo));
					plik1.write((char*) &rok_wydania, sizeof(short));						
				}
			}
		}
		
		if(flag==1) {
			printf("\n%68s%d","Usuniêto z bazy ksi¹¿kê o ID równym ",id);
		} else {
			printf("\n%67s","W bazie nie ma ksi¹¿ki o podanym ID");
		}
				
		plik.close();
		plik1.close();
		remove("biblioteka.bin");
		rename("temp.bin", "biblioteka.bin");
		
		printf("\n\n\n%57s","Co chcesz zrobiæ dalej?\n\n");
		printf("%52s","1: Spróbuj ponownie\n");
		printf("%58s","2: Wróæ do menu g³ównego\n\n");
		printf("%48s","WprowadŸ numer: ");
		do{
			wybor=getche();
			switch(wybor) {
				case '1':
					prawda2=true;
					prawda1=false;
				break;
				case '2':
					prawda2=false;
					prawda3=true;
					prawda1=false;
				break;
				default: 
					printf("\n%50s","Niepoprawny numer!");
					printf("\n%50s","Spróbuj ponownie: ");
					prawda1=true;
				break;
			}
		}while(prawda1);
	}while(prawda2);
};

int main() {
	HWND console = GetConsoleWindow();
  	RECT ConsoleRect;
  	GetWindowRect(console, &ConsoleRect); 

   	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1200, 600, TRUE);
   	
	SetConsoleCP(852);
	setlocale(LC_ALL, "");
	int i=0;
		
	do{
		system("CLS");
		char wybor;
		bool prawda;
		
		printf("\n\n%40s\n\n","Co chcesz zrobiæ?");
		printf("%39s\n","1: Dodaj ksi¹¿kê");
		printf("%40s\n","2: Listuj ksi¹¿ki");
		printf("%42s\n","3: Wyszukaj ksi¹¿kê");
		printf("%38s\n\n","4: Usuñ ksi¹¿kê");
		printf("%33s\n\n","5: Zakoñcz");
		printf("%39s","WprowadŸ numer: ");
		
		do {
			wybor=getche();
			if (wybor=='1' || wybor=='2' || wybor=='3' || wybor=='4' || wybor=='5') {
				prawda = false;
			} else {
				printf("%44s","Nieprawid³owy numer!\n");
				printf("%41s","Spróbuj ponownie: ");
				prawda = true;
			}
		} while (prawda);
		
		switch (wybor) {
			case '1':
				if(i!=0){
					cin.ignore();
				}
				i=1;
			DodajKsiazke();
				break;
			case '2':
			ListujKsiazki();	
				break;
			case '3':
			WyszukajKsiazke();	
				break;
			case '4':
			UsunKsiazke();	
				break;
			case '5':
			prawda3=false;	
				break;
		}
	}while(prawda3);
	return EXIT_SUCCESS;
}
