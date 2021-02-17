/*
Program 		: Tubes Games Tictactoe.c
Nama /Author 	: Caturiani Pratidina dan Kevandra Rivaldy
*/

//header
#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>

//modul
void game();
	int setLevel();
	void setGrid();
	void setNama(int player);
	void setRonde();
	
	void grid1();
	void grid2();
	void grid3();
	
	bool fillGrid(int giliran,int grid,int pilihan);
	void resetGrid(int grid);
	int randomGrid(int sampai);
	bool cekStatusGrid(int grid);
	bool cekLine(int giliran,int grid);
	
	void viewScore();
	void resetScore();
	void viewGiliran(int giliran);
	bool switchGiliran(int giliran);
	void showJuara();
	
	int StartTime();
	int EndTime();	
void help();
void about();


//struct 
typedef struct {
	int index;
	char nama[100];
	int score;
	bool status;
} Player;

typedef struct {
	int pola;
	char ordo[9][9];
	int ordoDone[9][9];
	int ordoStatus[9][9];
	bool status;
	int waktu;
	int ronde;
} Grid;

typedef struct {
	bool active;
} Komputer;


//Variabel Global
Player pemain[2];
Grid papan;
Komputer bot;
int pilihan;
int i,j;


//Program utama
int main(){
	int pilihan,error=0;
	
	do{
		system("cls");
		printf("---------   Selamat Datang di Permainan Tic Tac Toe ---------\n");
		printf("Silahkan Pilih Menu \n\n");
		printf("[1] Start Game  \n");
		printf("[2] Help   \n");
		printf("[3] About   \n");
		printf("[4] Exit  \n\n");
		if(error == 1)printf("Inputan Error\n");
		error=0;
		printf("Pilihan anda : ");
		scanf("%d",&pilihan);
	
		switch(pilihan){
			case 1:
				game();
				break;
				
			case 2:
				help();
				break;
				
			case 3:
				about();
				break;
				
			case 4:
				break;
				
			default:
				error=1;
				break;
		}
	}while(pilihan != 4);
	
	return 0;
}

//Modul game()
//Modul utama untuk bermain
void game(){
	int s,vsBot = 1;
	bool gameEnd = false;
	setGrid();
	if(setLevel() == 4){
		vsBot = 2;
	}
	setNama(vsBot);
	setRonde();
	
	system("cls");
	do{
		switch(papan.pola){
			case 1:
				grid1();
				break;

			case 2:
				grid2();
				break;

			case 3:
				grid3();
				break;

			default:
				break;
		}
	}while(gameEnd);
	
}

//Modul setLevel()
//Modul untuk menentukan level / mode yang akan dimainkan player
int setLevel(){

	bot.active = false;
	
	do{
		system("cls");
		printf("------------   Pilih Level Permainan   --------------\n");
		printf("[1] Easy    \n");
		printf("[2] Medium  \n");
		printf("[3] Hard    \n");
		printf("[4] Vs.Player  \n");
		printf("\n\n");
		printf("Pilihan Anda : ");
		scanf("%d",&pilihan);
		if(pilihan != 4){
			bot.active = true;
		}
	}while(pilihan > 4 || pilihan < 0);
	
	return pilihan;
}

// Modul setGrid()
// Modul untuk menentukan jenis papan yang akan digunakan saat bermain
void setGrid(){
	do{
		system("cls");
		printf("---------------- Pilihan Ukuran Board --------------\n\n");
		printf("[1] 3 X 3                         \n");
		printf("[2] 5 X 5                         \n");
		printf("[3] 7 X 7                         \n\n");
		printf("Pilihan Anda : ");
		scanf("%d",&papan.pola);
	}while(papan.pola > 3 || papan.pola < 0);
}

// Modul setNama(int player)
// Modul untuk memasukan nama para player yang akan bermain
void setNama(int player){
	int i;
	for(i=0;i<player;i++){
		system("cls");
		printf("----------------- Nama Player --------------\n");
		if(player>1) printf("Masukan Nama Player %d:\n",i+1);
			else printf("Masukan Nama Anda :\n");
		scanf("%s",&pemain[i].nama);
		pemain[i].index=i;
	}
	pemain[1].index=1;
}

// Modul setRonde()
// Modul untuk menentukan berapa kali pertandingan akan dilakukan
void setRonde(){
	bool salah=false;
	
	do{
		system("cls");
		printf("--------------- Ronde Permainan ------------------ \n");
		if(salah==true) printf("Ronde harus ganjil\n");
		printf("Berapa ronde anda ingin bermain ? ");
		scanf("%d",&papan.ronde);
		if(papan.ronde % 2 == 0) salah=true;
	}while(papan.ronde % 2 == 0);
	
}

// Modul ukuran board()
// Modul untuk bermain game dengan papan 3x3
void grid1(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(1);
	resetScore();
	do{
		do{
			system("cls");
			printf("-------------   PAPAN PERMAINAN  ---------------\n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			printf("||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n");
			printf("||4          ||5          ||6          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n");
			printf("||7          ||8          ||9          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,1,pilihan);

		}while(errorPilih == true);
		if(cekStatusGrid(1) == false)resetGrid(1); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,1) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara(giliran);
}

// Modul grid2()
// Modul untuk bermain game dengan papan 5x5
void grid2(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(2);
	resetScore();
	do{
		do{
			system("cls");
			printf("----------------------- PAPAN PERMAINAN  ----------------------\n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			
			printf("---------------------- PAPAN PERMAINAN  ---------------------- \n\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||4          ||5          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2],papan.ordo[0][3],papan.ordo[0][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||6          ||7          ||8          ||9          ||10         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2],papan.ordo[1][3],papan.ordo[1][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||11         ||12         ||13         ||14         ||15         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2],papan.ordo[2][3],papan.ordo[2][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||16         ||17         ||18         ||19         ||20         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[3][0],papan.ordo[3][1],papan.ordo[3][2],papan.ordo[3][3],papan.ordo[3][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||21         ||22         ||23         ||24         ||25         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[4][0],papan.ordo[4][1],papan.ordo[4][2],papan.ordo[4][3],papan.ordo[4][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,2,pilihan);
			
		}while(errorPilih == true);
		if(cekStatusGrid(2) == false)resetGrid(2); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,2) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara();
}

// Modul grid3()
// Modul untuk bermain game dengan papan 7x7
void grid3(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(3);
	resetScore();
	do{
		do{
			system("cls");
			printf("---------------------- PAPAN PERMAINAN  ---------------------- \n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			printf("---------------------- PAPAN PERMAINAN  ---------------------- \n\n");			
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||4          ||5          ||6          ||7          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2],papan.ordo[0][3],papan.ordo[0][4],papan.ordo[0][5],papan.ordo[0][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||8          ||9          ||10         ||11         ||12         ||13         ||14         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2],papan.ordo[1][3],papan.ordo[1][4],papan.ordo[1][5],papan.ordo[1][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||15         ||16         ||17         ||18         ||19         ||20         ||21         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2],papan.ordo[2][3],papan.ordo[2][4],papan.ordo[2][5],papan.ordo[2][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||22         ||23         ||24         ||25         ||26         ||27         ||28         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[3][0],papan.ordo[3][1],papan.ordo[3][2],papan.ordo[3][3],papan.ordo[3][4],papan.ordo[3][5],papan.ordo[3][6]);			
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||29         ||30         ||31         ||32         ||33         ||34         ||35         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[4][0],papan.ordo[4][1],papan.ordo[4][2],papan.ordo[4][3],papan.ordo[4][4],papan.ordo[4][5],papan.ordo[4][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||36         ||37         ||38         ||39         ||40         ||41         ||42         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[5][0],papan.ordo[5][1],papan.ordo[5][2],papan.ordo[5][3],papan.ordo[5][4],papan.ordo[5][5],papan.ordo[5][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||43         ||44         ||45         ||46         ||47         ||48         ||49         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[6][0],papan.ordo[6][1],papan.ordo[6][2],papan.ordo[6][3],papan.ordo[6][4],papan.ordo[6][5],papan.ordo[6][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,3,pilihan);
			
		}while(errorPilih == true);
		if(cekStatusGrid(3) == false)resetGrid(3); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,3) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara();
}

// Modul fillGrid(int giliran,int grid,int pilihan)
// Modul untuk memasukan ordo dari papan permainan yang akan diisi oleh player
bool fillGrid(int giliran,int grid,int pilihan){
	int batasWaktuInput;
	int pilih,noGrid=1,t;
	bool errorPilih=false;
	double waktuInput = 0;
	
	if(pilihan == 1){
		batasWaktuInput = 10;
	} else if(pilihan == 2){
		batasWaktuInput = 5;
	} else if(pilihan == 3){
		batasWaktuInput = 3;
	} else {
		batasWaktuInput = 10;
	}
	
	
	if(bot.active == true && pemain[giliran].index == 1){
		pilih = randomGrid(grid);
	}else{
		
		t = StartTime();
		
		printf("Masukan nomor grid yang akan diisi : ");
		scanf("%d",&pilih);
		
		t = EndTime() - t;
		
		waktuInput = ((double) t)/CLOCKS_PER_SEC;
		
		if(waktuInput>batasWaktuInput){
			printf("Anda Melebihi Batas Waktu Lebih Dari %d Detik, Giliran di Ganti",batasWaktuInput);
			printf("\nWaktu Anda Adalah %2.f Detik", waktuInput);			
			Sleep(3000);
			return errorPilih;
		}
	}

	switch(grid){
		case 1:
			if(pilih > 9 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 2:
			if(pilih > 25 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 3:
			if(pilih > 49 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
	}
	
	

	return errorPilih;
}

// Modul resetGrid(int grid)
// Modul untuk mereset semua data yang ada di papan permainan
void resetGrid(int grid){
	int i,j,noGrid=1;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
	}
	

}

// Modul randomGrid(int sampai)
// Referensi Googling
// Modul untuk menghasilkan angka acak dari 1 sampai sekian
int randomGrid(int sampai){
	switch(sampai){
		case 1:
			return rand() % 9 + 1;
			break;
		
		case 2:
			return rand() % 25 + 1;			
			break;
			
		case 3:
			return rand() % 49 + 1;
			break;
			
	}
}

// Modul cekStatusGrid(int grid)
// Modul untuk mengecek apakah grid masih bisa diisi atau sudah terisi semua
bool cekStatusGrid(int grid){
	int noGrid=1, hasil=0;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 9) return false;
				else return true;
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 25) return false;
				else return true;
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 49) return false;
				else return true;
			break;
	}
}

// Modul cekLine(int giliran,int grid)
// Modul untuk mengecek apakah ada line yang berhasil terbentuk atau tidak
bool cekLine(int giliran,int grid){
	bool ronde=false;
	int putaran,miringkanan;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){					
					if((papan.ordoDone[i][0] == papan.ordoDone[i][1] && papan.ordoDone[i][1] == papan.ordoDone[i][2]) ||
					(papan.ordoDone[0][j] == papan.ordoDone[1][j] && papan.ordoDone[1][j] == papan.ordoDone[2][j]) || 
					(papan.ordoDone[0][0] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][2]) ||
					(papan.ordoDone[0][2] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][0]) ){	
						ronde = true;
						if(pemain[giliran].index == 0) pemain[1].score++;
							else pemain[0].score++;
						resetGrid(1);
					}
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){					

					for(putaran=0;putaran<2;putaran++){
						if(
						//horizontal
						(papan.ordoDone[i][0+putaran] == papan.ordoDone[i][1+putaran] && papan.ordoDone[i][1+putaran] == papan.ordoDone[i][2+putaran] &&
				 		papan.ordoDone[i][2+putaran] == papan.ordoDone[i][3+putaran])||
				 		
				 		//vertikal
						(papan.ordoDone[0+putaran][j] == papan.ordoDone[1+putaran][j] && papan.ordoDone[1+putaran][j] == papan.ordoDone[2+putaran][j] &&
						papan.ordoDone[2+putaran][j] == papan.ordoDone[3+putaran][j])|| 
						
						//miring
						(papan.ordoDone[0+putaran][0+putaran] == papan.ordoDone[1+putaran][1+putaran] && papan.ordoDone[1+putaran][1+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][3+putaran]) ||
						
						(papan.ordoDone[0+putaran][4-putaran] == papan.ordoDone[1+putaran][3-putaran] && papan.ordoDone[1+putaran][3-putaran] == papan.ordoDone[2+putaran][2-putaran] &&
						papan.ordoDone[2+putaran][2-putaran] == papan.ordoDone[3+putaran][1-putaran])
						){	ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(2);
						}			
					}
					
					
					for(putaran=0;putaran<=2;putaran++){
						if(
						//miring 1 kali
						(papan.ordoDone[0+putaran][1-putaran] == papan.ordoDone[1+putaran][2-putaran] && papan.ordoDone[1+putaran][2-putaran] == papan.ordoDone[2+putaran][3-putaran] &&
						papan.ordoDone[2+putaran][3-putaran] == papan.ordoDone[3+putaran][4-putaran]) ||
						
						(papan.ordoDone[0+putaran][3+putaran] == papan.ordoDone[1+putaran][2+putaran] && papan.ordoDone[1+putaran][2+putaran] == papan.ordoDone[2+putaran][1+putaran] &&
						papan.ordoDone[2+putaran][1+putaran] == papan.ordoDone[3+putaran][0+putaran])
						){
						ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(2);
						}
					}

				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){		
				
					for(putaran=0;putaran<3;putaran++){
						if(
						//horizontal
						(papan.ordoDone[i][0+putaran] == papan.ordoDone[i][1+putaran] && papan.ordoDone[i][1+putaran] == papan.ordoDone[i][2+putaran] &&
				 		papan.ordoDone[i][2+putaran] == papan.ordoDone[i][3+putaran] && papan.ordoDone[i][3+putaran] == papan.ordoDone[i][4+putaran])||
				 		
				 		//vertikal
						(papan.ordoDone[0+putaran][j] == papan.ordoDone[1+putaran][j] && papan.ordoDone[1+putaran][j] == papan.ordoDone[2+putaran][j] &&
						papan.ordoDone[2+putaran][j] == papan.ordoDone[3+putaran][j] && papan.ordoDone[3+putaran][j] == papan.ordoDone[4+putaran][j])|| 
						
						//miring
						(papan.ordoDone[0+putaran][0+putaran] == papan.ordoDone[1+putaran][1+putaran] && papan.ordoDone[1+putaran][1+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][3+putaran] && papan.ordoDone[3+putaran][3+putaran] == papan.ordoDone[4+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][6-putaran] == papan.ordoDone[1+putaran][5-putaran] && papan.ordoDone[1+putaran][5-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][3-putaran] && papan.ordoDone[3+putaran][3-putaran] == papan.ordoDone[4+putaran][2-putaran])
						){	ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}			
					}
					
					for(putaran=0;putaran<2;putaran++){
						if(
						//miring 2 kali
						(papan.ordoDone[0+putaran][1+putaran] == papan.ordoDone[1+putaran][2+putaran] && papan.ordoDone[1+putaran][2+putaran] == papan.ordoDone[2+putaran][3+putaran] &&
						papan.ordoDone[2+putaran][3+putaran] == papan.ordoDone[3+putaran][4+putaran] && papan.ordoDone[3+putaran][4+putaran] == papan.ordoDone[4+putaran][5+putaran]) ||
						
						(papan.ordoDone[1+putaran][0+putaran] == papan.ordoDone[2+putaran][1+putaran] && papan.ordoDone[2+putaran][1+putaran] == papan.ordoDone[3+putaran][2+putaran] &&
						papan.ordoDone[3+putaran][2+putaran] == papan.ordoDone[4+putaran][3+putaran] && papan.ordoDone[4+putaran][3+putaran] == papan.ordoDone[5+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][5-putaran] == papan.ordoDone[1+putaran][4-putaran] && papan.ordoDone[1+putaran][4-putaran] == papan.ordoDone[2+putaran][3-putaran] &&
						papan.ordoDone[2+putaran][3-putaran] == papan.ordoDone[3+putaran][2-putaran] && papan.ordoDone[3+putaran][2-putaran] == papan.ordoDone[4+putaran][1-putaran]) ||
						
						(papan.ordoDone[1+putaran][6-putaran] == papan.ordoDone[2+putaran][5-putaran] && papan.ordoDone[2+putaran][5-putaran] == papan.ordoDone[3+putaran][4-putaran] &&
						papan.ordoDone[3+putaran][4-putaran] == papan.ordoDone[4+putaran][3-putaran] && papan.ordoDone[4+putaran][3-putaran] == papan.ordoDone[5+putaran][2-putaran])
						){
						ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}
					}
					
					for(putaran=0;putaran<=2;putaran+=2){
						if(
						//miring 1 kali
						(papan.ordoDone[0+putaran][2-putaran] == papan.ordoDone[1+putaran][3-putaran] && papan.ordoDone[1+putaran][3-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][5-putaran] && papan.ordoDone[3+putaran][5-putaran] == papan.ordoDone[4+putaran][6-putaran]) ||
						
						(papan.ordoDone[0+putaran][4+putaran] == papan.ordoDone[1+putaran][3+putaran] && papan.ordoDone[1+putaran][3+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][1+putaran] && papan.ordoDone[3+putaran][1+putaran] == papan.ordoDone[4+putaran][0+putaran])
						){
						ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}
					}
					
				}
			}
			break;		
	}
	
	return ronde;
}

// Modul viewScore()
// Modul untuk menampilkan score sementara
void viewScore(){
	if(bot.active == false){
		printf("Score %s : %d     Score %s : %d\n\n",pemain[0].nama,pemain[0].score,pemain[1].nama,pemain[1].score);
	}else{
		printf("Score %s : %d     Score Komputer : %d\n\n",pemain[0].nama,pemain[0].score,pemain[1].score);		
	}
}

// Modul resetScore()
// Modul untuk mereset score dari semua player / komputer
void resetScore(){
	pemain[0].score = 0;
	pemain[1].score = 0;
}

// Modul viewGiliran(int giliran)
// Modul untuk melihat giliran siapa yang harus mengisi papan permainan
void viewGiliran(int giliran){
	printf("Giliran : %s\n\n",pemain[giliran].nama);
}

// Modul switchGiliran(int giliran)
// Modul untuk mengganti-ganti giliran para player
bool switchGiliran(int giliran){
	if(giliran == 0){
		pemain[giliran].status = false;
		return true;
	}else{
		pemain[giliran].status = false;
		return false;
	}
}

// Modul showJuara()
// Modul untuk meihat siapa juara dari pertandingan tersebut
void showJuara(){
	system("cls");
	printf("------------- Game Over!!! -------------------\n");
	
	if(bot.active == true && (pemain[1].score > pemain[0].score)){
		printf("Juaranya adalah : Komputer\n");
		printf("Score           : %d - %d\n",pemain[1].score,pemain[0].score);
	}else if(pemain[1].score > pemain[0].score){
		printf("Juaranya adalah : %s\n",pemain[1].nama);
		printf("Score           : %d - %d\n",pemain[1].score,pemain[0].score);
	}else{
		printf("Juaranya adalah : %s\n",pemain[0].nama);
		printf("Score           : %d - %d\n",pemain[0].score,pemain[1].score);
	}
	printf("\n\n\n");
	printf("Ketik (Y) / (N) untuk kembali ke Main Menu : ");
	scanf("%c",&pilihan);
	if(tolower(pilihan) == 'y'){
		main();
	}else if(tolower(pilihan) == 'n'){
		exit(0);
	}else{
		showJuara();
	}
}

// Modul StartTime()
// Referensi dari kelompok Arsal & Naufal
// Modul untuk mencatat waktu pertama dihitung
int StartTime(){
    clock_t startInput;
    startInput = clock();

    return startInput;
}

// Modul EndTime()
// Referensi dari kelompok Arsal & Naufal
// Modul untuk mencatat waktu terakhir dihitung
int EndTime(){
    clock_t endInput;
    endInput = clock();

    return endInput;
}

// Modul help()
// Modul untuk melihat help dari program
void help(){
	char buff[255];
	char pilihan='N';

  	FILE *how;
	// membuka file
	
	if ((how = fopen("help.txt","r")) == NULL){
    	printf("Error: File tidak ada!");
	    exit(1);
	}
	
	do{
		system("cls");
		while(fgets(buff, sizeof(buff), how)){
	        printf("%s\n", buff);
	    }
	    Sleep(10000);
	    pilihan = 'y';
	}while(tolower(pilihan)!= 'y');
	
	fclose(how);
}

// Modul about()
// Modul untuk melihat about dari program
void about(){
	char buff[255];
	char pilihan='N';

  	FILE *how;
	// membuka file
	
	if ((how = fopen("about.txt","r")) == NULL){
    	printf("Error: File tidak ada!");
	    exit(1);
	}
	
	do{
		system("cls");
		
		while(fgets(buff, sizeof(buff), how)){
	        printf("%s\n", buff);
	    }
	    Sleep(10000);
	    pilihan = 'y';	    
	}while(tolower(pilihan)!= 'y');
	
	fclose(how);
}
