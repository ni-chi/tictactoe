#include<bits/stdc++.h>
#include<limits>
using namespace std;

struct Move
{
	int row, col, bestVal;
};

char player = 'x', opponent = 'o';

void print(char board[3][3])
{
	for(int i = 0;i<3; i++)
	{
		for(int j = 0; j<3; j++)
			cout<<board[i][j];
		cout<<endl;
	}
	cout<<endl;
}

bool isMovesLeft(char board[3][3])
{
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<3; j++)
		{
			if(board[i][j] == '_')
				return true;
		}
	}
	return false;
}

int evaluate(char board[3][3])
{
	int i, j;
	for(i = 0; i<3; i++)
	{
		char temp = board[i][0];
		if(temp == board[i][1] && temp == board[i][2])
		{
			if(temp == player)
				return 10;
			else if(temp == opponent)
				return -10;
		}
	}

	for(i = 0; i<3; i++)
	{
		char temp = board[0][i];
		if(temp == board[1][i] && temp == board[2][i])
		{
			if(temp == player)
				return 10;
			else if(temp == opponent)
				return -10;
		}
	}

	char temp = board[0][0];
	if(temp == board[1][1] && temp == board[2][2])
	{
		if(temp == player)
			return 10;
		else if(temp == opponent)
			return -10;
	}

	temp = board[0][2];
	if(temp == board[1][1] && temp == board[2][0])
	{
		if(temp == player)
			return 10;
		else if(temp == opponent)
			return -10;
	}

	return 0;
}

int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	if(score == 10 || score == -10)
		return score;
	
	if(!isMovesLeft(board))
		return 0;

	if(isMax)
	{
		int bestVal = -1000;

		for(int i = 0; i<3; i++)
		{
			for(int j = 0; j<3; j++)
			{
				if(board[i][j] == '_')
				{
					board[i][j] = player;
					int moveVal = minimax(board, depth+1, false);
					bestVal = max(bestVal, moveVal);
					board[i][j] = '_';
				}
			}
		}
		return bestVal;
	}

	else
	{
		int bestVal = 1000;
		for(int i = 0; i<3; i++)
		{
			for(int j = 0; j<3; j++)
			{
				if(board[i][j] == '_')
				{
					board[i][j] = opponent;
					int moveVal = minimax(board, depth+1, true);
					bestVal = min(bestVal, moveVal);
					board[i][j] = '_';
				}
			}
		}
		return bestVal;
	}
}

Move findBestMove(char board[3][3])
{
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	bestMove.bestVal = -1000;
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<3;j++)
		{
			if (board[i][j] == '_')
			{
				board[i][j] = player;
				int moveVal = minimax(board, 0, false);
				board[i][j] = '_';

				if (moveVal > bestMove.bestVal)
				{
					bestMove.bestVal = moveVal;
					bestMove.row = i;
					bestMove.col = j;
				}
			}
		}
	}
	return bestMove;
}

int main()
{
	char board[3][3] = 
	{
		{'_', '_', '_'},
		{'_', '_', '_'},
		{'_', '_', '_'}
	};
	print(board);
	Move bestMove;
	while(isMovesLeft(board) && evaluate(board) == 0)
	{
		int x, y;
		cout<<"Enter coordinates : "<<endl;
		cin>>x>>y;
		if(board[x][y] == '_')
		{	board[x][y] = opponent;
			print(board);
		}
		else
		{
			cout<<"Wrong coordinates! Enter again...";
			continue;
		}
		bestMove = findBestMove(board);
		board[bestMove.row][bestMove.col] = player;
		print(board);
	}
	if(bestMove.bestVal == -10)
		cout<<"AI has beaten you!!!"<<endl;
	else
		cout<<"It's a Tie"<<endl;
	return 0;
}