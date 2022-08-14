#include <iostream>
#include <fstream>
#include<unordered_map>
#include<sstream>
#include <string>

using namespace std;

double black = 0;
double white = 0;

class Piece {
public:
	bool isEmpty;
	string type;
	int point;
	bool isWhite;
	bool inThreat;
	pair<int, int> coord;

	Piece(string t, int x, int y) {
		type = t;
		if (t == "--") {
			isEmpty = true;
			return;
		}

		type = t;
		isEmpty = false;
		inThreat = false;
		coord.first = x;
		coord.second = y;

		switch (type[0]) {          //assign points
		case 'p':
			point = 1;
			break;
		case 'a':
			point = 3;
			break;
		case 'f':
			point = 3;
			break;
		case 'k':
			point = 5;
			break;
		case 'v':
			point = 9;
			break;
		case 's':
			point = 100;
			break;
		default:
			point = 0;
			cout << "invalid piece on board";
			return;
		}
		if (type[1] == 'b')
			isWhite = true;
		else if (type[1] == 's')
			isWhite = false;
		else {
			cout << "invalid piece on board";
			return;
		}

	}
	void addPoints() {          //add points for each piece to total
		if (this->isWhite)
			white += point;
		else
			black += point;

	}

	virtual void checkThreat(vector<vector<Piece*>>& board) {   //virtual function fot at vezir and piyon
		return;
	}



};

class Piyon : public Piece {
public:
	Piyon(string t, int x, int y) :Piece(t, x, y) {};

	void checkThreat(vector<vector<Piece*>>& board) {               // checks if pawn threatens a piece and substracts from total
		Piece* temp;
		if (this->isWhite) {

			if (this->coord.first - 1 >= 0 && this->coord.second - 1 >= 0) { //left upper box
				temp = board[this->coord.first - 1][this->coord.second - 1];


				if (!temp->isEmpty && !temp->isWhite && !temp->inThreat) {

					black -= temp->point / 2.0;
					temp->inThreat = true;

				}
			}
			if (this->coord.first - 1 >= 0 && this->coord.second + 1 < 8) {   //right upper box
				temp = board[this->coord.first - 1][this->coord.second + 1];


				if (!temp->isEmpty && !temp->isWhite && !temp->inThreat) {

					black -= temp->point / 2.0;
					temp->inThreat = true;
				}
			}




		}
		else {

			if (this->coord.first + 1 < 8 && this->coord.second - 1 >= 0) { //lower left  box
				temp = board[this->coord.first + 1][this->coord.second - 1];
				if (!temp->isEmpty && temp->isWhite && !temp->inThreat) {

					white -= temp->point / 2.0;
					temp->inThreat = true;
				}
			}
			if (this->coord.first + 1 < 8 && this->coord.second + 1 < 8) {   //lower right  box
				temp = board[this->coord.first + 1][this->coord.second + 1];


				if (!temp->isEmpty && temp->isWhite && !temp->inThreat) {


					white -= temp->point / 2.0;
					temp->inThreat = true;
				}
			}

		}

	}
};

class At : public Piece {
public:

	At(string t, int x, int y) :Piece(t, x, y) {};


	void checkThreat(vector<vector<Piece*>>& board) {
		Piece* temp;
		double* changep;					//picks which points to subtract from

		if (this->isWhite) {
			changep = &black;
		}
		else {
			changep = &white;
		}




		if (this->coord.first - 2 >= 0 && this->coord.second - 1 >= 0) { //2 up 1 left box
			temp = board[this->coord.first - 2][this->coord.second - 1];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first - 2 >= 0 && this->coord.second + 1 < 8) {   //2 up 1 right box
			temp = board[this->coord.first - 2][this->coord.second + 1];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first - 1 >= 0 && this->coord.second - 2 >= 0) {   //1 up 2 left box
			temp = board[this->coord.first - 1][this->coord.second - 2];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first - 1 >= 0 && this->coord.second + 2 < 8) {   //1 up 2 right box
			temp = board[this->coord.first - 1][this->coord.second + 2];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first + 1 < 8 && this->coord.second - 2 >= 0) {   //1 down 2 left box
			temp = board[this->coord.first + 1][this->coord.second - 2];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first + 1 < 8 && this->coord.second + 2 < 8) {   //1 down 2 right box
			temp = board[this->coord.first + 1][this->coord.second + 2];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first + 2 < 8 && this->coord.second - 1 >= 0) {   //2 down 1 left box
			temp = board[this->coord.first + 2][this->coord.second - 1];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}
		if (this->coord.first + 2 < 8 && this->coord.second + 1 < 8) {   //2 down 1 right box
			temp = board[this->coord.first + 2][this->coord.second + 1];


			if (!temp->isEmpty && temp->isWhite != this->isWhite && !temp->inThreat) {

				*changep -= temp->point / 2.0;
				temp->inThreat = true;
			}
		}

	}

};

class Vezir : public Piece {

public:
	Vezir(string t, int x, int y) :Piece(t, x, y) {};


	void checkThreat(vector<vector<Piece*>>& board) {
		Piece* temp;
		int x = this->coord.second;
		int y = this->coord.first;
		double* changep;

		if (this->isWhite) {
			changep = &black;

		}
		else {
			changep = &white;
		}


		y = this->coord.first + 1;
		while (y < 8) {             // straight down
			temp = board[y][x];
			if (temp->isEmpty) {
				y++;
				continue;
			}

			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;



			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}



		y = this->coord.first - 1;
		while (y >= 0) {            // straight up
			temp = board[y][x];
			if (temp->isEmpty) {
				y--;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;

			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}



		y = this->coord.first;
		x = this->coord.second + 1;
		while (x < 8) {             // straight right
			temp = board[y][x];
			if (temp->isEmpty) {
				x++;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;

			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}





		x = this->coord.second - 1;
		while (x >= 0) {             // straight left
			temp = board[y][x];
			if (temp->isEmpty) {
				x--;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;

			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}


		x = this->coord.second + 1;
		y = this->coord.first + 1;
		while (y < 8 && x < 8) {         // diagonal down right
			temp = board[y][x];
			if (temp->isEmpty) {
				y++;
				x++;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;


			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}

		x = this->coord.second - 1;
		y = this->coord.first + 1;
		while (y < 8 && x >= 0) {     //diagonal down left
			temp = board[y][x];
			if (temp->isEmpty) {
				x--;
				y++;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;

			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}


		x = this->coord.second + 1;
		y = this->coord.first - 1;
		while (y >= 0 && x < 8) {     //diagonal up right
			temp = board[y][x];
			if (temp->isEmpty) {
				x++;
				y--;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;


			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}



		x = this->coord.second - 1;
		y = this->coord.first - 1;

		while (y >= 0 && x >= 0) {     //diagonal up left
			temp = board[y][x];
			if (temp->isEmpty) {
				x--;
				y--;
				continue;
			}
			if (temp->isWhite == this->isWhite)
				break;
			if (temp->inThreat)
				break;

			*changep -= temp->point / 2.0;
			temp->inThreat = true;
			break;
		}



	}


};

void boardClear(vector<vector<Piece*>>& board) {		//clear board after calculation
	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int index = 0; index < board[i].size(); index++)
		{
			delete board[i][index];

		}
		board[i].clear();
	}

}


int main()
{
	ifstream myFile;
	vector<vector<Piece*>> board(8);
	string line;
	string foldername = "board1.txt";
	for (int foldernum = 1; foldernum <= 3; foldernum++) {		//calculates all 3 board txt
		white = 0;
		black = 0;

		foldername[5] = to_string(foldernum)[0];
		cout << foldername << endl;
		myFile.open(foldername, ios::in);
		if (!myFile.is_open())
			return 0;


		for (int i = 0; i < 8; i++) {				//initialize board
			for (int j = 0; j < 8; j++) {
				if (!(myFile >> line)) {

					return 0;
				}
				if (line[0] == 'p') {

					board[i].push_back(new Piyon(line, i, j));

				}
				else if (line[0] == 'a') {
					board[i].push_back(new At(line, i, j));

				}
				else if (line[0] == 'v') {

					board[i].push_back(new Vezir(line, i, j));


				}
				else
				{
					board[i].push_back(new Piece(line, i, j));

				}


				cout << board[i][j]->type << " ";

			}
			cout << endl;
		}


		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (board[i][j]->isEmpty)
					continue;

				board[i][j]->addPoints();
				board[i][j]->checkThreat(board);


			}
		}


		cout << endl << "black: " << black << " white: " << white;
		cout << endl << "-------------------------- " << endl;
		myFile.close();
		cout << endl;



		boardClear(board);
	}




}
