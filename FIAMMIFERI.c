#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//funzione per winrate 
float fwr(float v, float s) {
  float wr;
  if (v == 0) wr = 0; //se zero vittore
  if (s == 0 && v != 0) wr = 100;//se zero sconfitto e almeno 1 vittoria
  if (v != 0 && s != 0) wr = 100 * v / (v + s);//winrate normale
  return wr;
}
void main() {
  srand(time(NULL));
  int e, v = 0, s = 0, n, f, difficolta, player, reset;
  float wr;
  FILE * out_file = 0; //file in scrittura
  FILE * in_file = fopen("Stats.txt", "r"); //file in lettura
  fscanf(in_file, "%d %d", & v, & s);//leggo le statistiche
  fclose(in_file);
  wr = fwr(v, s);
  printf("-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%.2f%%\n", v, s, wr);//visualizzo le stats all'utente
  do {
    int a = 0, c = 0, p = 0, x = 0, opt, pred, m;
    printf("Opzioni standard[1-Si;-No]: ");
    scanf("%d", & opt);
    if (opt != 1) {
      do {
        printf("Scegliere la difficolta[1-Semplice,2-Difficile]: ");
        scanf("%d", & difficolta);
        if (d != 1 && d != 2) {
          printf("Puoi scegliere solo 1-Semplice,2-Difficile!\n");
          d = 0;
        }
      } while (d == 0);
      do {
        printf("Scegli il numero di fiammiferi[MIN 3]: ");
        scanf("%d", & n);
        if (n < 3) printf("Il numero minimo e' 3!\n");
      } while (n < 3);
      m = n / 2 + 1;
      do {
        printf("Scegli il massimo di quanti spegnerne per turno [2-%d]: ", m);
        scanf("%d", & f);
        if (f < 2 || f > m) printf("I limiti sono [2-%d]\n", m);
      } while (f < 2 || f > m);
      do {
        printf("Primo turno[1-PC;2-PLAYER;3-RAND]: ");
        scanf("%d", & player);
        if (player < 1 || player > 3) {
          player == 0;
          printf("Puoi scegliere tra [1-PC;2-PLAYER;3-RAND]!\n");
        }
      } while (player == 0);
      printf("Salvare come opzioni predefinite[1-Si;-No]: ");
      scanf("%d", & pred);
      if (pred == 1) {
        out_file = fopen("Base.txt", "w");
        fprintf(out_file, "%d %d %d %d\n-OPZIONI STANDARD-\n-FIAMMIFERI:\t%d\n-MAX TURNO:\t%d\n-PRIMO TURNO:\t%d\n[1-PC;2-PLAYER;3-RAND]\n-DIFFICOLTA:\t%d\n[1-Semplice;2-Difficile]", n, f, player, difficolta);
        fclose(out_file);
      }
    } else {
      FILE * in_file = fopen("Base.txt", "r");
      fscanf(in_file, "%d %d %d %d", & n, & f, & player, & d);
      fclose(in_file);
    }
    if (player == 3) player = rand() % 2 + 1;
    printf("\nTROPPI FIAMMIFERI!!\nRiuscirai a non spegnere l'ultimo??\n");
    c = n;
    while (c > 0) {
      printf(" |");
      c--;
    }
    if (player == 1) goto pc;
    while (n > 0) {
      do {
        printf("\nScegli quanti spegnerne [1-%d]: ", f);
        scanf("%d", & a);
        if (a < 1 || a > f) {
          printf("Ne puoi spegnere [1-%d]", f);
          a = 0;
        }
      } while (a == 0);
      n = n - a;
      c = n;
      while (c > 0) {
        printf(" |");
        c--;
      }
      pc:
        if (n <= 0) x = 1;
      if (d == 1) p = rand() % f + 1;
      else {
        p = ((n % (f + 1)) + f) % (f + 1);
        if (p == 0) p = 1;
      }
      if (n > 0) {
        printf("\nIl pc ne ha spente %d\n", p);
        n = n - p;
        c = n;
        if (n <= 0) x = 2;
        while (c > 0) {
          printf(" |");
          c--;
        }
      }
    };
    if (x == 2) {
      printf("Hai vinto!\n");
      v++;
    } else {
      printf("Hai perso!\n");
      s++;
    }
    printf("Ritenta![1-Si;-Mi arrendo]: ");
    scanf("%d", & e);
  } while (e == 1);
  wr = fwr(v, s);
  out_file = fopen("Stats.txt", "w");
  fprintf(out_file, "%d %d\n-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%d%",v,s,v,s,wr);
  fclose(out_file);
  printf("-STATS-\n-VITTORIE:\t%d\n-SCONFITTE:\t%d\n-WINRATE:\t%.2f%%\n", v, s, wr);
  printf("RESET?[1-STATS;2-OPT;3-STATS&OPT;-ESCI]");
  scanf("%d", & reset);
  switch (reset) { //Per resettare i file con le imostazioni predefinite
  case 1:
    {

      out_file = fopen("Stats.txt", "w");
      fprintf(out_file, "0 0\n-STATS-\n-VITTORIE:\t0\n-SCONFITTE:\t0\n-WINRATE:\t0%");
      fclose(out_file);
    }
    break;
  case 2:
    {
      out_file = fopen("Base.txt", "w");
      fprintf(out_file, "13 3 2 1\n-OPZIONI STANDARD-\n-FIAMMIFERI:\t13\n-MAX TURNO:\t3\n-PRIMO TURNO:\t2\n[1-PC;2-PLAYER;3-RAND]\n-DIFFICOLTA:\t1\n[1-Semplice;2-Difficile]");
      fclose(out_file);
      break;
    }
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
