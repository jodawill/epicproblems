#include <stdio.h>

// Maximum row & column size of input matrix
#define MATMAX 32
// Maximum size of sequence is the maximum number of entries in a matrix
#define SEQMAX MATMAX * MATMAX

// Prints a sequence using space as the delimeter
void print_seq(int size,int *seq) {
 for (int i = 0; i < size; i++) {
  printf("%d ",seq[i]);
 }
 printf("\n");
}

// Convert a square matrix into a sequence
void to_seq(int size,int *seq,int matr[][MATMAX]) {
 int i,j;
 for (i = 0; i < size; i++) {
  for (j = 0; j < size; j++) {
   seq[(i * size) + j] = matr[i][j];
  }
 }
}

// This sorting algorithm is as slow as it gets, but it gets the job done,
// and these matrices are expected to be small.
void sort_seq(int size,int *seq) {
 for (int i = 1; i < size; i++) {
  if (seq[i - 1] > seq[i]) {
   int bak = seq[i];
   seq[i] = seq[i - 1];
   seq [i - 1] = bak;
   i = 0;
  }
 }
}

// Copy sequence seq to scpy
void cpy_seq(int size,int *scpy,int *seq) {
 for (int i = 0; i < size; i++) {
  scpy[i] = seq[i];
 }
}

// Delete the ith member of seq
void seq_del(int size, int *seq,int i) {
 int scpy[SEQMAX];
 cpy_seq(size,scpy,seq);
 for (int j = i; j < size; j++) {
  seq[j] = scpy[j+1];
 }
}

// Remove duplicate numbers in the sequence and return the new size
int rem_dup(int size,int *seq) {
 for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
   if (i == j) break;
   if (seq[i] == seq[j]) {
    seq_del(size,seq,i);
    size--;
    i = 0;
    j = 0;
   }
  }
 }
 return size;
}

void print_longest_snake(int matsize,int matr[][MATMAX]) {
 // Convert the matrix into a sequence seq.
 int seq[SEQMAX];
 to_seq(matsize,seq,matr);
 int size = matsize * matsize;

 // Sort the sequence
 sort_seq(size,seq);

 // Remove duplicate terms
 size = rem_dup(size,seq);

 // snakes[][] holds the longest snake sequences
 int snakes[SEQMAX][SEQMAX];
 // cur_snk is the length of the current snake sequence
 int cur_snk = 1;
 // max_snk is the length of the longest snake(s)
 int max_snk = 1;
 // max_num is the number of snakes of greatest length
 int max_num = 1;
 for (int i = 0; i < size; i++) {
  for (int j = i; j < size; j++) {
   if (seq[j] + 1 == seq[j + 1]) {
    cur_snk++;
    if (cur_snk > max_snk) {
     max_snk = cur_snk;
     max_num = 0;
    }
    if (cur_snk == max_snk) {
     max_num++;
     for (int k = 0; k < size - i; k++) {
      snakes[max_num - 1][k] = seq[i + k];
     }
    }
   } else {
    cur_snk = 1;
    break;
   }
  }
  cur_snk = 1;
 }

 printf("\nThe longest snake sequences found in this matrix are:\n");
 for (int i = 0; i < max_num; i++) {
  print_seq(max_snk,snakes[i]);
 }
}

int main(int argc,char *argv[]) {
 int size = MATMAX + 1;
 int matr[MATMAX][MATMAX];
 printf("Enter the size of the square matrix: ");
 for (scanf("%d",&size); size > MATMAX;) {
  printf("Max %d. Try again: ",MATMAX);
  scanf("%d",&size);
 }
 printf("\nEnter the values of each entry in the matrix: \n");
 for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
   printf("R%dC%d: ",i + 1,j + 1);
   scanf("%d",&matr[i][j]);
  }
 }
 print_longest_snake(size,matr);
 return 0;
}

