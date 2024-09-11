# 15 puzzle solver
An 15 puzzle solver using A* algorithm with Manhattan distance as heuristic to find optimal solution.  
This implementation is unable to solve puzzles that need more than ~60 moves, as it requires too much memory.  

# Test inputs:
a\~f stands for 10\~15, 0 stands for the blank tile   
- 2348170c56ab9def (15 moves)
- 51309af4d7b826ec (25 moves)
- 1f3452d8a70b96ec (30 moves)
- 12345dc8796eba0f (33 moves)
- 1f345dc8796eab20 (44 moves)
- 0bd45c329671af8e (50 moves)
- 58d9ebc1324a70f6 (56 moves)
- 0291ca8d6574feb3 (60 moves, unsolvable with 8GiB memory)