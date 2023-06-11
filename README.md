# roulette

A basic european roulette simulation in C.

Test different strategies base on different bets and initial balance.

Roulette is an EV- game, so you cannot beat the house, the only way to win is to stole coin when dealer is not looking (Einstein)

> Personne ne peut gagner à la roulette à moins qu’il ne vole l’argent de la table lorsque le croupier ne regarde pas.
>
> -- <cite>Albert Einstein</cite>


## Compile

```sh
make
```

## Have fun

```sh
➜  roulette git:(main) ✗ ./roulette
result: 20
Bet size: 21.00
Payout: 36.00
net win: 15.00
amount: 1015.00
result: 22
Bet size: 21.00
Payout: 0.00
amount: 994.00
result: 32
Bet size: 21.00
Payout: 14.00
net win: -7.00
amount: 987.00
result: 23
Bet size: 21.00
Payout: 28.00
net win: 7.00
amount: 994.00
result: 22
Bet size: 21.00
Payout: 0.00
amount: 973.00
result: 12
Bet size: 21.00
Payout: 14.00
net win: -7.00
amount: 966.00
```

## RNG

Thanks to [skeeto](https://www.reddit.com/r/C_Programming/comments/146cnjx/comment/jnpzwun/?utm_source=share&utm_medium=web2x&context=3),
he found an issue with the number generator with attempt at rejection sampling and proposed a fixed I implemented. Number seems now more uniformly
distributed as you can see: ![roulette-distribution-histogram](./graph.jpg)

I'm aware this is a toy RNG and the purpose is not to replicate a true RNG which can be quiet hard without dedicated hardware.
