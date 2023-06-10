#ifndef ROULETTE_H_
#define ROULETTE_H_

#include <stdbool.h>
#include <unistd.h>

#define MIN 0
#define MAX 36

#define URANDOM_DEVICE "/dev/urandom"

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

static FILE *urandom;

struct Bet {
    char type[10];
    int value;
    int amount;
};

// Even and dozen can be deduced easily, not need to hardcode them.
struct Number {
	int value;
	char color;
	int column; // which column number belong
};

extern int zero_game[7]; 
extern int zero_neighbors[10];
extern int orphans[8];
extern int third_of_wheel[12];
extern int red[18];
extern int black[18];

// init the random generator
void rand_init(void);
// close the random generator
void rand_close(void);
// draw a random number
int draw(void);
// play until amount is 0
void play(float amount, struct Bet bets[], size_t num_bets);
// calculate the payout for each bets
float calculate_payout(int number_drawn, struct Bet bets[], size_t num_bets);

// Check a number is odd or even
bool is_even(struct Number *n);

// Check in which dozen the number is
int dozen_value(struct Number *n);

// check if the number is black or red
bool is_black(struct Number *n);

// check if the number is black or red
bool is_red(struct Number *n);

// Return the column the number belongs too
int column_value(struct Number *n);

#endif /* ROULETTE_H_ */
