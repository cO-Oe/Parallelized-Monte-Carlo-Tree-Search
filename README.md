# SurakartaAI
This Repository build a [Surakarta Game](https://en.wikipedia.org/wiki/Surakarta_(game)) framework and implement [MCTS (Monte Carlo Tree Search)](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search) technique to train AI.
## How to Run?
1. git clone this Repository
2. ``` make```
3. ```./surakarta (--total=1000 --block=100 (default argument))``` 
## How to Modify Strategy?
- By deault, The two agent **player** and **envir** move according to two different strategy, **MCTS** and **Eat First Greedy**.
- Modify ```agent.h``` and choose the strategy you want in ```policy.h```
