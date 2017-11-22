#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define undeff -999
#define false 0
#define true 1

typedef struct{
	char s[110];
}string;

//Deklarasi variabel global
int nstate, nsymbol, nfinal, ntransisi, StateAwal, StateAkhir, Start_State;
int ii, i, j, IdxSimbol;
FILE *myfile;
string symbol[110], State[110], simbol, StartState;
int dfa[110][110], FinalState[110], jawaban[110];

//deklarasi fungsi
void Test();
void UndefDFA();
void Pembukaan();
void BacaFileDFA();
int CariIdx( string ss);
int IsFinalState( int x);
int Sama(string a,string b);


int main(){
	UndefDFA();		//deklarasi matriks dfa dengan nilai yang tidak terdefinisi
	Pembukaan();
	BacaFileDFA();	//membaca definisi dfa dari file .txt sesuai dengan format
	
	//Testing Automata
	Test();
	
	fclose(myfile);
}

void Pembukaan(){
	printf("#------------------------------------------------------------------#\n");
	printf("#======================  TUGAS BESAR 1 TBFO  ======================#\n");
	printf("#==================================================================#\n");
	printf("#==========================  CREATED BY  ==========================#\n");
	printf("#==================================================================#\n");
	printf("#=======  Senapati Sang Diwangkara & Restu Wahyu Kartiko   ========#\n");
	printf("#=====================   13516107 & 13516155  =====================#\n");
	printf("#------------------------------------------------------------------#\n");
}

void BacaFileDFA(){
	
	myfile = fopen("DFA.txt","r");
	
	//Membaca jumlah state
	fscanf(myfile,"%d",&nstate);
	for(i = 1; i <= nstate; i++)
		fscanf(myfile,"%s",&State[i]);

	//membaca symbol/alphabet
	fscanf(myfile,"%d",&nsymbol);
	for(i = 1; i <= nsymbol; i++)
		fscanf(myfile,"%s",&symbol[i]);
	
	//membaca start state
	fscanf(myfile,"%s",&StartState);
	for(i = 1; i<= nstate; i ++)
		if(Sama(StartState,State[i]))
			Start_State = i;
	
	//membaca final state
	fscanf(myfile,"%d",&nfinal);
	for(i = 1; i <= nfinal; i++)
		fscanf(myfile,"%d",&FinalState[i]);
	
	//membaca fungsi transisi
	fscanf(myfile,"%d",&ntransisi);
	for(i = 1; i <= ntransisi; i++){
		fscanf(myfile,"%d %s %d",&StateAwal, &simbol, &StateAkhir);
		IdxSimbol = CariIdx(simbol);
		dfa[StateAwal][IdxSimbol] = StateAkhir;
	}
}

void Test(){
	//menguji string masukan terhadap automata yang ada
	char cc = 'y';
	while(cc == 'y'){
		int StateNow = Start_State, accepted = 1, Automata, ind = 0;
		string  input[110];
		
		printf("\nMasukkan berapa banyak transisi yang anda inginkan : ");
		scanf("%d",&Automata);
		
		for(i = 1; i <= Automata; i++)
			scanf("%s",&input[i]);
			
		for(i = 1; i <= Automata; i++){
			IdxSimbol = CariIdx(input[i]);
			if(dfa[StateNow][IdxSimbol] == undeff){
				accepted = 0;
				if(ind == 0) ind = i;
			}
			else{
				jawaban[i] = dfa[StateNow][IdxSimbol];
				StateNow = jawaban[i];
			}
		}
		
		if(!IsFinalState(StateNow)) //Cek apakah state terakhir dari string masukan adalah final state
			accepted = 0;	
		if(accepted){
			
			printf("--------------------\n");
			printf("----String valid----\n");
			printf("--------------------\n");
			
			printf("%s ",State[Start_State],Start_State);
			for(i = 1 ;i<=Automata; i++)
				printf("--> %s ",State[jawaban[i]]);
			printf("\n");
		}
		else{	// state terakhir dari string masukan bukan final state
			printf("----------------------\n");
			printf("--String tidak valid--\n");
			printf("----------------------\n");
		
			printf("%s ",State[Start_State],Start_State);
			for(i = 1 ;i<ind; i++)
				printf("--> %s ",State[jawaban[i]]);
			printf("--> error\n");	
		}
		printf("\nIngin memeasukan string baru?(y/n)");
		cc = getch();
		printf("%c\n",cc);
	}
}

void UndefDFA(){
	//Menset nilai matriks dfa menjadi undef( tak terdefinisi)
	for( i = 0; i <= 100 ; i++)
		for( j = 1 ; j <= 100 ; j++)
			dfa[i][j] = undeff;
}

int CariIdx( string ss){
	// mencari indeks string ss pada array string symbol
	for(ii = 1; ii <= nsymbol; ii++)
		if(Sama(ss,symbol[ii])) return ii;
}

int IsFinalState( int x){
	//Menentukan apakah state x adalah final state
	for(i = 1; i <= nfinal ; i++)
		if(FinalState[i] == x) return 1;
	return 0;
}

int Sama(string a,string b)
{
	//menentukan apakah string a = string b
    int ii,ans=1;
    for(ii=0;a.s[ii]!='\0' && b.s[ii]!='\0';ii++){
        if(a.s[ii]!=b.s[ii]){
            ans=0;
            break;
        }
    }
    return ans;
}

