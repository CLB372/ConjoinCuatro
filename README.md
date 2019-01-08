# ConjoinCuatro
Game where players race to CONNECT 4 pieces to win. 1 or 2 players with adjustable difficulty.

The file ConjoinCuatro.exe contains the executable file for this program.

The file ConjoinCuatro.cpp contains the relevant C++ code, written using MS Visual Studio 2017.

2-player mode occurs on the same machine and instance of the program. The 2 players take turns using the keyboard to play.

In 1-player mode, the program has at its disposal a series of decision-making functions that it runs through to play intelligently (though not perfectly). For example, in one such function, if it sees that an opponent has a vertical stack of 3 pieces, it will try to block thhat stack. In EASY mode, when it's the computer's turn, it will only run this series of 'intelligent' functions 25% of the time and pick a randomly-generated move the remainder of the time. In MEDIUM mode, it will run these functions 2/3 of the time and pick a random move 1/3 of the time. In HARD mode, it runs these functions every time. 
