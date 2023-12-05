#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Stack.h"
#include "randgen.h"


/* 

	Author: Anil Sen
	Student ID: 29556

*/






/*GENERAL IDEA OF THE DESIGN OF THE PROGRAM*/

//Basically, for example a cell having (1,9) coordinates
//located in a maze vector at index [9][1]

//This idea could be found in possibleMove strings
//where xCord's taking place in 2nd indexes of the maze vector
//and yCord's taking place in 1st indexes of the maze vector

using namespace std;







class Cell {
	//x and y values are considered as index numbers while pushing into maze vector


public:
	int xCord;
	int yCord;


	//visited boolean value to be used while creating maze
	bool visited = false;
	//isVisitedInPath boolean value to be used while finding path for maze
	bool isVisitedInPath = false;

	int upperWall;
	int lowerWall;
	int rightWall;
	int leftWall;
	//while instantiating, cells start as having all the walls standing
	Cell(int x, int y) :
		upperWall(1), lowerWall(1), rightWall(1), leftWall(1) {
		this->xCord = x;
		this->yCord = y;
	}



};

//returns a string for possible move cases for a specific cell
//i.e if a cell can go UP,DOWN and LEFT, resulting string will be UDL

/*
R- INCREMENT X
L- DECREMENT X
U- INCREMENT Y
D- DECREMENT Y
*/


//Possible Moves for finding a path in a maze
//i.e deciding on which cells to move on


string possibleMovePath(int xCord, int yCord, int xUpperBound, int yUpperBound, vector<vector<Cell>>& mazeVec) {
	string result = "";

	if (xCord + 1 <= xUpperBound) {

		if (mazeVec[yCord][xCord + 1].leftWall == 0
			&& mazeVec[yCord][xCord + 1].isVisitedInPath==false) {
			result += 'R';
		}


	}
	if (yCord + 1 <= yUpperBound) {
		if (mazeVec[yCord + 1][xCord].lowerWall == 0
			&& mazeVec[yCord+1][xCord].isVisitedInPath == false) {
			result += 'U';
		}
	}
	if (xCord - 1 >= 0) {
		if (mazeVec[yCord][xCord - 1].rightWall == 0
			&& mazeVec[yCord][xCord - 1].isVisitedInPath == false) {
			result += 'L';
		}
	}
	if (yCord - 1 >= 0) {
		if (mazeVec[yCord - 1][xCord].upperWall == 0
			&& mazeVec[yCord-1][xCord].isVisitedInPath == false) {
			result += 'D';
		}
	}

	return result;
}



//Possible Moves for creating a maze, i.e deciding on which walls to break
string possibleMoveString(int xCord, int yCord, int xUpperBound, int yUpperBound,vector<vector<Cell>> & mazeVec) {
	string result = "";

	if (xCord + 1 <= xUpperBound) {

		if (mazeVec[yCord][xCord+1].visited == false) {
			result += 'R';
		}

		
	}
	if (yCord + 1 <= yUpperBound) {
		if (mazeVec[yCord+1][xCord].visited == false) {
			result += 'U';
		}
	}
	if (xCord - 1 >= 0 ) {
		if (mazeVec[yCord][xCord-1].visited == false) {
			result += 'L';
		}
	}
	if (yCord - 1 >= 0) {
		if (mazeVec[yCord-1][xCord].visited == false) {
			result += 'D';
		}
	}

	return result;
}







void generateMaze(int rowNum, int colNum,vector<vector<Cell>> & mazeToBeFilled) {
	for (int row = 0;row < rowNum;row++) {
		
		vector<Cell> tempVec;
		for (int col = 0; col < colNum;col++) {
			//to have coordinates (x,y) in [y][x]th index in a vector
			tempVec.push_back(Cell(col,row));
		}
		mazeToBeFilled.push_back(tempVec);



	}
}


//Writes out the coordinates in the required format for MazeDrawer.exe to .txt file
void writeMaze(ofstream& out, vector<vector<Cell>>& mazeVec) {

	for (int i = 0;i < mazeVec[0].size();i++) {
		for (int j = 0;j < mazeVec.size();j++) {
			out << "x=" << i << " y=" << j << " l="<<mazeVec[j][i].leftWall
				<<" r="<< mazeVec[j][i].rightWall <<" u="<< 
				mazeVec[j][i].upperWall <<" d="<< mazeVec[j][i].lowerWall <<endl;
		}
	}
}

//Writes out the path to .txt file
//To start from the 1st element of the stack, using recursion
void writePath(ofstream& out, Node<Cell>* ptr) {
	if (ptr == nullptr) {
		
	}
	else {
		writePath(out, ptr->next);
		out << ptr->data.xCord << " " << ptr->data.yCord << endl;
	}

}



int main() {
	int K, M, N;
	cout << "Enter the number of mazes: ";
	cin >> K;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M >> N;

	//to store all mazes that are going to be created
	vector <vector <vector<Cell>>> allMazesCreated;

	for (int mazeNum = 0;mazeNum < K;mazeNum++) {

		Stack<Cell> mazeStack;

		
		vector<vector<Cell>> mazeVec;
		generateMaze(M, N, mazeVec);

		//Boundaries are used in possibleMove functions
		//in order not to take moves outside the borders into account

		const int X_UPPER_BOUND = mazeVec[0].size() - 1;
		const int Y_UPPER_BOUND = mazeVec.size() - 1;
		
		
		mazeVec[0][0].visited = true;
		mazeStack.push(mazeVec[0][0]);
		
		for (int cellNumber = 0;cellNumber < (M * N)-1;cellNumber++) {
			
			//getting the possible moves string
			string moveHint = 
				possibleMoveString(mazeStack.top()->data.xCord,
				mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND,mazeVec);
		
			
			int moveHintLength = moveHint.length();

			bool stackBeUsed = false;

			if (moveHintLength == 0) {
				// If no wall exists to knock down for the currentCell,
				// backtrack using the stack until you find a cell 
				//which has an unvisited neighbor cell.
														
				while (possibleMoveString(mazeStack.top()->data.xCord,
					mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND,
					mazeVec).length() == 0) {
					//while there is no possible move statement for top
					//popping the top of the stack to look for the next cell

					mazeStack.pop();
				}
				stackBeUsed = true;
			}
			
			if (stackBeUsed) {
				moveHint =possibleMoveString(mazeStack.top()->data.xCord,
						mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND, mazeVec);
				moveHintLength = moveHint.length();
			
			}

			//Now, possible moves string is ready
			//we can choose random character from the string
			//by choosing a random number between [0,LengthString]

			RandGen random;
			int randomIndex = random.RandInt(0,moveHintLength-1);

			char randomMoveKey = moveHint[randomIndex];


			int destinationX=0;
			int destinationY=0;

			
			if (randomMoveKey == 'R') {
				//Going Right

				//Breaking current cell's wall from the cell's side
				mazeStack.top()->data.rightWall = 0;
					
				destinationX = mazeStack.top()->data.xCord + 1;
				destinationY = mazeStack.top()->data.yCord;

				//Breaking the other cell's wall from the other cell's side
				mazeVec[destinationY][destinationX].leftWall = 0;

			}
			else if (randomMoveKey == 'L') {
				//Going Left

				mazeStack.top()->data.leftWall = 0;

				destinationX = mazeStack.top()->data.xCord - 1;
				destinationY = mazeStack.top()->data.yCord;


				mazeVec[destinationY][destinationX].rightWall = 0;
			}
			else if (randomMoveKey == 'U') {
				//Going Up
				mazeStack.top()->data.upperWall = 0;

				destinationX = mazeStack.top()->data.xCord;
				destinationY = mazeStack.top()->data.yCord + 1;


				mazeVec[destinationY][destinationX].lowerWall = 0;
			}
			else if (randomMoveKey == 'D') {
				//Going Down
				mazeStack.top()->data.lowerWall = 0;

				destinationX = mazeStack.top()->data.xCord;
				destinationY = mazeStack.top()->data.yCord - 1;


				mazeVec[destinationY][destinationX].upperWall = 0;
			}

			//setting the cell whose wall is broken as visited
			mazeVec[destinationY][destinationX].visited = true;
			mazeStack.push(mazeVec[destinationY][destinationX]);


		

			

		}
		string filename = "maze_" + to_string(mazeNum+1) + ".txt";


		ofstream out;

		out.open(filename);
		
		out << M << " " << N << endl;

		writeMaze(out, mazeVec);

		allMazesCreated.push_back(mazeVec);

		//emptying stack, freeing memory
		while (mazeStack.top() != nullptr) {

			mazeStack.pop();
		}

	}
	
	//To find a path, starting with a fresh stack
	Stack<Cell> mazeStack;



	cout << "All mazes are generated.\n" << endl;
	
	int mazeID = 0;
	cout << "Enter a maze ID between 1 to " << K << " inclusive to find a path: ";
	cin >> mazeID;

	int entryX = 0, entryY = 0;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;

	int exitX = 0, exitY = 0;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;
	
	
	//pushing entry cell to stack
	mazeStack.push(allMazesCreated[mazeID - 1][entryY][entryX]);
	allMazesCreated[mazeID - 1][entryY][entryX].isVisitedInPath = true;

	//the same approach used in the boundaries used to create mazes
	const int X_UPPER_BOUND = allMazesCreated[mazeID - 1][0].size() - 1;
	const int Y_UPPER_BOUND = allMazesCreated[mazeID - 1].size() - 1;

	//until there is an exit cell at the top of the stack, we continue
	while (&mazeStack.top()->data != &allMazesCreated[mazeID - 1][exitY][exitX]) {
		
		string moveHint =
			possibleMovePath(mazeStack.top()->data.xCord,
				mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND, 
				allMazesCreated[mazeID - 1]);


		int moveHintLength = moveHint.length();

		bool stackBeUsed = false;

		if (moveHintLength == 0) {
			

			while (possibleMovePath(mazeStack.top()->data.xCord,
				mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND,
				allMazesCreated[mazeID - 1]).length() == 0) {
				//while there is no possible move statement for top
				//keep doing pop

				mazeStack.pop();
			}
			stackBeUsed = true;
		}

		if (stackBeUsed) {
			moveHint = possibleMovePath(mazeStack.top()->data.xCord,
				mazeStack.top()->data.yCord, X_UPPER_BOUND, Y_UPPER_BOUND, 
				allMazesCreated[mazeID - 1]);

			moveHintLength = moveHint.length();

		}

		//Possible move string is ready
		
		RandGen random;
		int randomIndex = random.RandInt(0, moveHintLength - 1);

		char randomMoveKey = moveHint[randomIndex];


		int destinationX = 0;
		int destinationY = 0;

		//Depending on the direction, the needed coordinate gets updated to pinpoint the cell

		if (randomMoveKey == 'R') {

			//Going right

			destinationX = mazeStack.top()->data.xCord + 1;
			destinationY = mazeStack.top()->data.yCord;

			

		}
		else if (randomMoveKey == 'L') {

			//Going left

			destinationX = mazeStack.top()->data.xCord - 1;
			destinationY = mazeStack.top()->data.yCord;


			
		}
		else if (randomMoveKey == 'U') {

			//Going up

			destinationX = mazeStack.top()->data.xCord;
			destinationY = mazeStack.top()->data.yCord + 1;


			
		}
		else if (randomMoveKey == 'D') {

			//Going down

			destinationX = mazeStack.top()->data.xCord;
			destinationY = mazeStack.top()->data.yCord - 1;


			
		}
		//setting the cell which has been reached as visited
		allMazesCreated[mazeID - 1][destinationY][destinationX].isVisitedInPath = true;
		//pushing the cell onto the stack
		mazeStack.push(allMazesCreated[mazeID - 1][destinationY][destinationX]);


		

	}

	ofstream outPath;
	string filenamePath = "maze_" + to_string(mazeID) + "_path_" + to_string(entryX)
		+ "_" + to_string(entryY) + "_" + to_string(exitX) 
		+ "_" + to_string(exitY) + ".txt";
	
	outPath.open(filenamePath);


	//our initial point is at the end of the stack
	//so we need to write onto txt backwards

	Node<Cell>* temp = mazeStack.top();

	writePath(outPath, temp);
	
	//emptying stack, freeing memory
	while (mazeStack.top() != nullptr) {
		
		mazeStack.pop();
	}

	
	return 0;
}