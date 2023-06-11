#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "roulette.h"


// Some unsed declaration for strategies
int zero_game[7]; 
int zero_neighbors[10] = {22, 18, 29, 7, 28, 19, 4, 21, 2, 25};
int orphans[8] = {17, 34, 6, 9, 31, 14, 20, 1};
int third_of_wheel[12] = {27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33};
int red[18] = {32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3};
int black[18] = {15, 4, 2, 17, 6, 13, 11, 8, 10, 24, 33, 20, 31, 22, 29, 28, 35, 26};


struct Number numbers[] = {
	// Value / color / dozen / column
	{0, 'G', 0},  
	{1, 'R', 1},  
	{2, 'B', 2},  
	{3, 'R', 3},  
	{4, 'B', 1},  
	{5, 'R', 2},  
	{6, 'B', 3},  
	{7, 'R', 1},  
	{8, 'B', 2},  
	{9, 'R', 3},  
	{10, 'B', 1},  
	{11, 'B', 2},  
	{12, 'R', 3},  
	{13, 'B', 1},  
	{14, 'R', 2},  
	{15, 'B', 3},  
	{16, 'R', 1},  
	{17, 'B', 2},  
	{18, 'R', 3},  
	{19, 'B', 1},  
	{20, 'B', 2},  
	{21, 'R', 3},  
	{22, 'B', 1},  
	{23, 'R', 2},  
	{24, 'B', 3},  
	{25, 'R', 1},  
	{26, 'B', 2},  
	{27, 'R', 3},  
	{28, 'R', 1},  
	{29, 'B', 2},  
	{30, 'R', 3},  
	{31, 'B', 1},  
	{32, 'R', 2},  
	{33, 'B', 3},  
	{35, 'R', 1},  
	{35, 'B', 2},  
	{36, 'R', 3},  
};

void rand_init(void) {
    urandom = fopen(URANDOM_DEVICE, "rb");
	if (urandom == NULL) {
		fprintf(stderr, "Failed to open %s\n", URANDOM_DEVICE);
		exit(EXIT_FAILURE);
	}
}

void rand_close(void) {
    fclose(urandom);
}

int draw(void){
    int c = 0;

    do {
        c = fgetc(urandom);
        if(c == EOF) {
            fprintf(stderr, "Failed to read from %s\n", URANDOM_DEVICE);
            exit(EXIT_FAILURE);
        }
    }
	while(c > MAX-MIN);

	return c + MIN;
}

float calculate_payout(int number_drawn, struct Bet bets[], size_t num_bets) {
    float payout = 0.0;
    size_t i;

    struct Number number = numbers[number_drawn]; 

    for (i = 0; i < num_bets; i++) {
        struct Bet bet = bets[i];

		// Handle the zero, where you only win when betting directly on it
		// hence exit the loop in that case.
        if (strcmp(bet.type, "number") == 0) {
            if (bet.value == number_drawn) {
                return 36.0 * bet.amount; // You only win on zero when you explicitly bet on it
										// since zero is considered neither ood or even nor black or red
            }
		}

        if (strcmp(bet.type, "color") == 0) {
            if ((is_black(&number) && bet.value == 0) || (is_red(&number) && bet.value == 1)) {
                payout += 2.0 * bet.amount;
            }
        } else if (strcmp(bet.type, "even") == 0) {
            if ((is_even(&number) && bet.value == 1) || (!is_even(&number) && bet.value == 0)) {
                payout += 2.0 * bet.amount;
            }
        } else if (strcmp(bet.type, "range") == 0) {
            if (bet.value == 0 && number_drawn >= 1 && number_drawn <= 18) {
                payout += 2.0 * bet.amount;
            } else if (bet.value == 1 && number_drawn >= 19 && number_drawn <= 36) {
                payout += 2.0 * bet.amount;
            }
        }
    }

    return payout;
}


// game-loop, play until amount < 0
void play(float initial_balance, struct Bet bets[], size_t num_bets) {
	int number_drawn = 0;
	float payout = 0.0, bet_size = 0;
	float amount = initial_balance;

	while (amount > 0.0) {

		payout = 0;
		// Deduce bet size from the amount
		bet_size = 0.0;

		for (size_t i = 0; i < num_bets; i++) {
        		struct Bet bet = bets[i];
			bet_size += bet.amount;
		}

		// draw
		number_drawn = draw();
		printf("result: %d\n", number_drawn);

		// Calcute the payout in case of win
		payout = calculate_payout(number_drawn, bets, num_bets);
		amount += payout - bet_size;
    		printf("Bet size: %.2f\n", bet_size);
    		printf("Payout: %.2f\n", payout);
		if ( payout > 0.0 ) {
			printf("net win: %.2f\n", payout - bet_size);
		}
		printf("amount: %.2f\n", amount);

		// Sleep a bit
		usleep(200 * 1000);
	}
}


// Check a number is odd or even
bool is_even(struct Number *n) {
	if (n == NULL) {
		printf("fatal pointer is nil");
		return false;
	}

	return n->value % 2 == 0; 
}

// Check in which dozen the number is
int dozen_value(struct Number *n) {
	if (n == NULL) {
		printf("fatal pointer is nil");
		return false;
	}

	int number = n->value;

	if (number > 0 && number <= 12) {
		return 1;
	} else if (number > 12 && number <= 24) {
		return 2;
	} else if (number > 24 && number <= 36) {
		return 3;
	} else {
		printf("you appear to have enterred an invalid number");
		return -1;
	}
}

// check if the number is black
bool is_black(struct Number *n) {
	if (n == NULL) {
		printf("fatal pointer is nil");
		return false;
	}

	return n->color == 'B';
}

// check if the number is red
bool is_red(struct Number *n) {
	if (n == NULL) {
		printf("fatal pointer is nil");
		return false;
	}

	return n->color == 'R';
}

// Return the column the number belongs too
int column_value(struct Number *n) {
	if (n == NULL) {
		printf("fatal pointer is nil");
		return false;
	}

	return n->column;
}
