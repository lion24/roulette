#include "roulette.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    rand_init();

    float initial_balance = 1000.0;

    //	struct Bet bets[] = {
    //		{"number", 14, 2.0},  // Bet on number 14 with $2
    //		{"number", 0, 2.0},  // Bet on number 0 with $2
    //		{"number", 2, 2.0},  // Bet on number 2 with $2
    //		{"number", 35, 2.0},  // Bet on number 35 with $2
    //		{"even", 0, 8.0},    // Bet on odd numbers with $8
    //	};

	// This one seems a rather conservative one.
    struct Bet bets[] = {
    	{"number", 0, 1.0},  // Bet on number 0 with $1
    	{"color", 1, 4.0},    // Bet 4$ on red
    };

    // struct Bet bets[] = {
    // 	{"number", 0, 1.0},  // Bet on number 14 with $1
    // 	{"even", 0, 2.0},    // Bet on even numbers with $2
    // };
    //
    // struct Bet bets[] = {
    //     {"number", 0, 1.0},  {"number", 2, 1.0},  {"number", 8, 1.0},
    //     {"number", 11, 1.0}, {"number", 17, 1.0}, {"number", 20, 1.0},
    //     {"number", 26, 1.0}, {"number", 26, 1.0}, {"number", 29, 1.0},
    //     {"even", 0, 8.0},  // Bet 7$ on odds number
    //     {"color", 1, 8.0}, // Bet 7$ on red
    // };

    size_t num_bets = COUNT_OF(bets);

    play(initial_balance, bets, num_bets);

    rand_close();

    return 0;
}
