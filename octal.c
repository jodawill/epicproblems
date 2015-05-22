/* ------------------------------------------------------------------ */
/* This program will list all of the integers within an interval that */
/* are palindromes in both decimal and octal.                         */
/* ------------------------------------------------------------------ */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *out) {
 char rev[sizeof out];
 for (int i = strlen(out); i >= 0; i--) {
  rev[strlen(out) - 1 - i] = out[i];
 }
 strcpy(out,rev);
}

void to_oct(char *out) {
 int i, dec, base = 8;
 dec = atoi(out);

 for (i = 0; dec >= base; i++){
  out[i] = '0' + (dec % base);
  dec /= base;
 }
 out[i] = '0' + dec;
 out[++i] = '\0';

 // out[] is backwards, so we must reverse it
 reverse(out);
}

bool is_palindrome(char *num) {
 for (int i = 0; i < strlen(num); i++) {
  if (num[i] != num[strlen(num) - i - 1]) return false;
 }
 return true;
}

bool is_palboth(char *in) {
 char num[32];
 strcpy(num,in);
 if (!is_palindrome(num)) return false;
 to_oct(num);
 return (is_palindrome(num));
}

void draw_line(int len) {
 for (int i = 0; i < len; i++) {
  printf("-");
 }
 printf("\n");
}

void list_pals(int start,int end) {
 char num[32];
 char oct[32];
 int width = 27;
 draw_line(width);
 printf("| %10s | %10s |\n","Decimal","Octal");
 draw_line(width);
 for (int i = start; i <= end; i++) {
  sprintf(num,"%d",i);
  strcpy(oct,num);
  to_oct(oct);
  if (is_palboth(num)) printf("| %10s | %10s |\n",num,oct);
 }
 draw_line(width);
}

int main(int argc,char *argv[]) {
 int start, end;
 printf("Enter the starting integer: ");
 scanf("%d",&start);
 printf("Enter the ending integer: ");
 scanf("%d",&end);
 printf("\nThe following integers between %d and %d\nare palindromes in both decimal and octal:\n\n",start,end);
 list_pals(start,end);
 return 0;
}

