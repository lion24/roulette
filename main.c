#include <stdio.h>
#include <stdlib.h>
#include "roulette.h"

int main(void) {
	rand_init();

	float initial_balance = 1000.0;

//	struct Bet bets[] = {
//		{"number", 14, 2.0},  // Bet on number 14 with $1
//		{"number", 0, 2.0},  // Bet on number 14 with $1
//		{"number", 2, 2.0},  // Bet on number 14 with $1
//		{"number", 35, 2.0},  // Bet on number 14 with $1
//		{"even", 0, 8.0},    // Bet on even numbers with $2
//	};
//	
//	struct Bet bets[] = {
//		{"number", 0, 1.0},  // Bet on number 14 with $1
//		{"even", 0, 2.0},    // Bet on even numbers with $2
//	};

//	struct Bet bets[] = {
//		{"number", 0, 1.0},  // Bet on number 14 with $1
//		{"even", 0, 8.0},    // Bet on even numbers with $2
//	};
//
	struct Bet bets[] = {
		{"number", 0, 1.0},
		{"number", 2, 1.0},
		{"number", 8, 1.0},
		{"number", 11, 1.0},
		{"number", 20, 1.0},
		{"number", 24, 1.0},
		{"number", 26, 1.0},
		{"even", 0, 7.0},     // Bet 7$ on odds number
		{"color", 1, 7.0},    // Bet 7$ on red
	};

	size_t num_bets = COUNT_OF(bets);

	play(initial_balance, bets, num_bets);

	rand_close();

	return 0;
}
