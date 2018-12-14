#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//FUNZIONE WINRATE
float funwinrate(float vitt, float sconf) {
  float winrate;
  if (vitt == 0) winrate = 0; //se zero vittore
  if (sconf == 0 && vitt != 0) winrate = 100;//se zero sconfitte e almeno 1 vittoria
  if (vitt != 0 && sconf != 0) winrate = 100 * vitt / (vitt + sconf);//winrate normale
  return winrate;
}
/*						ALESSANDRO MANFUCCI
.							14/12/2018  
.						GIOCO DEI FIAMMIFERI!
*/						
void main() {
  srand(time(NULL));//inizializzo random
  int ciclo, vitt = 0, sconf = 0, fiamm, maxft, difficolta, turno1, reset;
  //ciclo->Ripetere il gioco | fiamm->fiammiferi totali | maxft->Massimi fiammiferi spegnibili | reset->Resettare stats o opzioni pred
  float winrate;
  FILE * out_file = 0; //file in scrittura
  FILE * in_file = fopen("Stats.txt", "r"); //file in lettura
  fscanf(in_file, "%d %d", & vitt, & sconf);//leggo le statistiche
  fclose(in_file);
  winrate = funwinrate(vitt, sconf);//Ogni volta che stampo il winrate lo aggiorno
  printf("-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%.2f%%\n", vitt, sconf, winrate);//stampo le stats all'utente
  do {
    int player = 0, printer = 0, pc = 0, win = 0, opt, saveopt, maxftposs;
    /*player->fiamm spenti dall'utente | printer->Stampare i fiammiferi | pc->fiamm spenti dal pc | win->Determina il vincitore | opt->Opzioni
    saveopt->salvare come opzoni pred | maxftposs->Massimi fiammiferi spegnibili impostabili nelle opt*/
    printf("Opzioni standard[1-Si;-No]: ");
    scanf("%d", & opt);
    //Chiede di scegliere le opzioni alternative
    if (opt != 1) {
      do {
        printf("Scegliere la difficolta[1-Semplice,2-Difficile]: ");
        scanf("%d", & difficolta);
        if (difficolta != 1 && difficolta != 2) {
          printf("Puoi scegliere solo [1-Semplice,2-Difficile]!\n");
          difficolta = 0;
        }
      } while (difficolta == 0);
      do {
        printf("Scegli il numero di fiammiferi[MIN 3]: ");
        scanf("%d", & fiamm);
        if (fiamm < 3) printf("Il numero minimo e' 3!\n");
      } while (fiamm < 3);
      maxftposs = fiamm / 2 + 1;
      do {
        printf("Scegli il massimo di quanti spegnerne per turno [2-%d]: ", maxftposs);
        scanf("%d", & maxft);
        if (maxft < 2 || maxft > maxftposs) printf("I limiti sono [2-%d]\n", maxftposs);
      } while (maxft < 2 || maxft > maxftposs);
      do {
        printf("Primo turno[1-PC;2-PLAYER;3-RAND]: ");
        scanf("%d", & turno1);
        if (turno1 < 1 || turno1 > 3) {
          turno1 == 0;
          printf("Puoi scegliere tra [1-PC;2-PLAYER;3-RAND]!\n");
        }
      } while (turno1 == 0);
      printf("Salvare come opzioni predefinite[1-Si;X-No]: ");
      scanf("%d", & saveopt);
      //Salva le opzioni appena scelte nel file
      if (saveopt == 1) {
        out_file = fopen("Base.txt", "w");
        fprintf(out_file, "%d %d %d %d\n-OPZIONI STANDARD-\n-FIAMMIFERI:\t%d\n-MAX TURNO:\t%d\n-PRIMO TURNO:\t%d\n[1-PC;2-PLAYER;3-RAND]\n-DIFFICOLTA:\t%d\n[1-Semplice;2-Difficile]", fiamm, maxft, turno1, difficolta);
        fclose(out_file);
      }
    }
    //Legge le opzioni predefinite
	else {
      FILE * in_file = fopen("Base.txt", "r");
      fscanf(in_file, "%d %d %d %d", & fiamm, & maxft, & turno1, & difficolta);
      fclose(in_file);
    }
    
    //INIZIO GIOCO
    if (turno1 == 3) turno1 = rand() % 2 + 1;//Assegna un valore random per stabilire chi inizia(se scelto nelle opzioni)
    printf("\nTROPPI FIAMMIFERI!!\nRiuscirai a non spegnere l'ultimo??\n");
    printer = fiamm;//Il printer e' una variabile contatore utilizzata per stampare i fiammiferi
    while (printer > 0) {
      printf(" |");
      printer--;
    }
    if (turno1 == 1) goto pc;//Se inizia il pc salta il pezzo iniziale e va direttamente al turno del pc(GOTOOOOOOOO!!!!!!)
    //TURNO PLAYER
    while (fiamm > 0) {
      do {
        printf("\nScegli quanti spegnerne [1-%d]: ", maxft);
        scanf("%d", & player);
        if (player < 1 || player > maxft) {
          printf("Ne puoi spegnere [1-%d]", maxft);
          player = 0;
        }
      } while (player == 0);
      fiamm = fiamm - player;
      printer = fiamm;
      while (printer > 0) {
        printf(" |");
        printer--;
      }
      pc:
    //TURNO PC
        if (fiamm <= 0) win = 1;
      if (difficolta == 1) pc = rand() % maxft + 1;
      else {
        pc = ((fiamm % (maxft + 1)) + maxft) % (maxft + 1);
        if (pc == 0) pc = 1;
      }
      if (fiamm > 0) {
        printf("\nIl pc ne ha spente %d\n", pc);
        fiamm = fiamm - pc;
        printer = fiamm;
        if (fiamm <= 0) win = 2;
        while (printer > 0) {
          printf(" |");
          printer--;
        }
      }
    };
    //DETERMINA VINCITORE
    if (win == 2) {
      printf("Hai vinto!\n");
      vitt++;
    } else {
      printf("Hai perso!\n");
      sconf++;
    }
    //RESTART
    printf("Ritenta![1-Si;X-Mi arrendo]: ");
    scanf("%d", & ciclo);
  } while (ciclo == 1);
  //FINE GIOCO
  //AGGIORNO STATISTICHE
  winrate = funwinrate(vitt, sconf);//Ogni volta che stampo il winrate lo aggiorno
  out_file = fopen("Stats.txt", "w");
  fprintf(out_file, "%d %d\n-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%d%",vitt,sconf,vitt,sconf,winrate);
  fclose(out_file);
  printf("-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%.2f%%\n", vitt, sconf, winrate);
  //CHIEDO RESET FILE OPZIONI E/O STATS
  printf("RESET?[1-STATS;2-OPT;3-STATS&OPT;-ESCI]");
  scanf("%d", & reset);
  
  switch (reset) {
  	//RESET STATISTICHE
  case 1:
    {

      out_file = fopen("Stats.txt", "w");
      fprintf(out_file, "0 0\n-STATS-\n-VITTORIE:\t0\n-SCONFITTE:\t0\n-WINRATE:\t0%");
      fclose(out_file);
    }
    break;
    //RESET OPZIONI
  case 2:
    {
      out_file = fopen("Base.txt", "w");
      fprintf(out_file, "13 3 2 1\n-OPZIONI STANDARD-\n-FIAMMIFERI:\t13\n-MAX TURNO:\t3\n-PRIMO TURNO:\t2\n[1-PC;2-PLAYER;3-RAND]\n-DIFFICOLTA:\t1\n[1-Semplice;2-Difficile]");
      fclose(out_file);
      break;
    }
    //RESET OPZIONI E STATISTICHE
  case 3:
    {
      out_file = fopen("Stats.txt", "w");
      fprintf(out_file, "0 0\n-STATS-\n-VITTORIE:\t0\n-SCONFITTE:\t0\n-WINRATE:\t0%");
      fclose(out_file);
      out_file = fopen("Base.txt", "w");
      fprintf(out_file, "13 3 2 1\n-OPZIONI STANDARD-\n-FIAMMIFERI:\t13\n-MAX TURNO:\t3\n-PRIMO TURNO:\t2\n[1-PC;2-PLAYER;3-RAND]\n-DIFFICOLTA:\t1\n[1-Semplice;2-Difficile]");
      fclose(out_file);
      break;
    }
  default:
    break;
  }
  
  printf("\n\n");
  system("PAUSE");
  return;
}
/*						ALESSANDRO MANFUCCI
.							14/12/2018  
.						GIOCO DEI FIAMMIFERI!
*/
