#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>				// for srand(time())
#include <fstream>				// for file handling
#include <vector>	
#include <windows.h>			// for sleep
#include <chrono>				// for timer
#include <iomanip>				// for setfill('0') & setw(2)

using namespace std;

//Global variables:
string** board;
string Username;

int n;
int Number_of_our_ships = 0, Number_of_enemy_ships;
int Number_of_Our_Shots = 0, Number_of_Our_Correct_Shots = 0, Number_of_Our_Incorrect_Shoots = 0;
int Number_of_Enemy_Shots = 0, Number_of_Enemy_Correct_Shots = 0, Number_of_Enemy_Incorrect_Shots = 0;
double Score;
int inum = 0;					// tedad kol bazi konan dar file record

bool fsign = false;				// baraye anajam nadadan bazi khali hengami ke esm eshtebah dar load ya Leaderboard vared mishavad
bool Exit = false;				//for Exit

struct rec						//structure to save score and name of players 
{
	double s_core;
	string n_ame;
};
vector<rec> arr;

//for time:
auto Start = chrono::system_clock::now();
int all;

//fasele baraye inke timer vasat board bashad
void space()
{
	for (int i = 0; i < 2.5 * n - 10.5; i++)
	{
		cout << " ";
	}
}

//tabe timer
void timer()
{
	auto End = chrono::system_clock::now();
	chrono::duration<double> time = (End - Start);
	all = (int)time.count();
	int seconds = all % 60;
	int minutes = (all % 3600) / 60;
	int hours = all / 3600;

	space();
	cout << char(219);
	for (int i = 0; i < 26; i++)
	{
		cout << char(220);
	}
	cout << char(219) << endl;
	space();
	cout << char(222);
	cout << "           TIME           ";
	cout << char(221) << endl;
	space();
	cout << char(222) << " " << setfill('0') << setw(2) << hours << " hrs : " << setfill('0') << setw(2) << minutes << " min : " << setfill('0') << setw(2) << seconds << " sec" << " " << char(221) << endl;
	space();
	cout << char(219);
	for (int i = 0; i < 26; i++)
	{
		cout << char(223);
	}
	cout << char(219) << endl;
	cout << '\n';
}

//tabe e barraye tahksis hadeaghale hafeze be vector dar (addrecord) va be dast avardane meghdar (inum)
void read()
{
	fstream F("record.txt", ios::in);
	F >> inum;
	rec ne;
	for (int i = 0; i < inum; i++)
	{
		F >> ne.n_ame >> ne.s_core;
		arr.push_back(ne);
	}
	F.close();
}

//tabe e baraye ezafae kardan bazikon va emtiyazesh ya taghieer emtiaz =>(estefade dar akhar tabe (save))
void addrecord(string name, double score)
{
	bool exist = false;
	for (int i = 0; i < inum; i++)
	{
		if (arr[i].n_ame == name)
		{
			arr[i].s_core = score;
			exist = true;
			break;
		}
	}
	if (!exist)
	{
		rec ne;
		ne.n_ame = name;
		ne.s_core = score;
		arr.push_back(ne);
		inum++;
	}
	fstream FQ("record.txt", ios::out);
	FQ << inum << endl;
	for (int i = 0; i < inum; i++)
	{
		FQ << arr[i].n_ame << " " << arr[i].s_core << endl;
	}
	FQ.close();
}

//tabe e baraye namayesh bazikonan va emtiyazeshon
void showrecord()
{
	string name;
	double score;
	fstream x("record.txt", ios::in);
	x >> inum;
	for (int i = 0; i < inum; i++)
	{
		x >> name >> score;
		cout << '\t' << name << " : " << score << endl;
	}
	x.close();
}

//tebe e barraye save
void save(string fname)
{
	string filePath;
	filePath = fname + ".txt";
	fstream f(filePath, ios::out);
	// n:
	{
		f << n << endl;
	}
	int tk; 	// avalin adad har satr dar file neshan dahande tedad etelaat oon satr hastesh =>(tk) => albate be tedad dobarar oon adad chon araye 2 bodie
	// *:
	{
		tk = 0;
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "*")
				{
					tk++;
				}
			}
		}
		f << tk << " ";
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "*")
				{
					f << i << " " << j << " ";
				}
			}
		}
		f << endl;
	}
	// @:
	{
		tk = 0;
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "@")
				{
					tk++;
				}
			}
		}
		f << tk << " ";
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "@")
				{
					f << i << " " << j << " ";
				}
			}
		}
		f << endl;
	}
	// #:
	{
		tk = 0;
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "#")
				{
					tk++;
				}
			}
		}
		f << tk << " ";
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "#")
				{
					f << i << " " << j << " ";
				}
			}
		}
		f << endl;
	}
	// 1:
	{
		tk = 0;
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "1")
				{
					tk++;
				}
			}
		}
		f << tk << " ";
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "1")
				{
					f << i << " " << j << " ";
				}
			}
		}
		f << endl;
	}
	// 0:
	{
		tk = 0;
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "0")
				{
					tk++;
				}
			}
		}
		f << tk << " ";
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (board[i][j] == "0")
				{
					f << i << " " << j << " ";
				}
			}
		}
		f << endl;
	}
	// Variables:
	{
		f << Number_of_our_ships << endl;
		f << Number_of_enemy_ships << endl;

		f << Number_of_Our_Correct_Shots << endl;
		f << Number_of_Our_Incorrect_Shoots << endl;
		f << Number_of_Our_Incorrect_Shoots << endl;

		f << Number_of_Enemy_Shots << endl;
		f << Number_of_Enemy_Correct_Shots << endl;
		f << Number_of_Enemy_Incorrect_Shots << endl;

		f << Score;
	}
	f.close();
	addrecord(fname, Score);
}

//tabe score
void score()
{
	{
		Score = (double)(Number_of_Our_Correct_Shots + ((double)n / (Number_of_Our_Incorrect_Shoots + 1)) + Number_of_our_ships);
		for (int i = 0; i < 2.5 * n - 2.5; i++)
		{
			cout << " ";
		}
		cout << char(244) << "Score:" << (double)Score << char(245) << endl;
		cout << '\n';
	}
}

//tabe e baraye update board
void print(int n)
{
	system("cls");

	timer();

	//adad (i) neshan dahande stoonha:
	{
		cout << "   ";
		for (int i = 1; i <= n; i++)
		{
			if (i < 10)
			{
				cout << "  " << i << "  ";
			}
			else
			{
				cout << " " << i << "  ";
			}
		}
		cout << '\n';
	}

	//zele bala:
	{
		cout << "  " << char(201);		//gooshe bala chap
		for (int i = 1; i <= 5 * n; i++)
		{
			if (i == 5 * n / 2 + 1)
			{
				cout << char(203);				//3rah zele bala
			}
			else
			{
				cout << char(205);				//zele bala(khotoot saf)
			}
		}
		cout << char(187) << '\n';				//gooshe bala rast
	}

	//mohtaviat vasat board
	{
		for (int i = 1; i < n + 1; i++)			//adad (i) neshan dahande radifha:
		{
			//zele chap:
			{
				if (i < 10)
				{
					cout << " " << i << char(186);	//zele chap( (baraye fix kardan adad 1raghami)
				}
				else
				{
					cout << i << char(186);			//zele chap
				}
			}
			//chap keshti ha va vazieyat shelikha:
			{
				for (int j = 1; j < n + 1; j++)
				{
					//jahat neshan nadadan keshtihaye doshman:
					if (j > (n + 1) / 2 && board[i][j] == "@")
					{
						cout << "  " << "#" << "  ";

					}
					else
					{
						cout << "  " << board[i][j] << "  ";
					}
				}
			}
			//zele rast:
			{
				cout << char(186);					//zele rast
			}
			cout << '\n';
		}
	}

	//zele paeen:
	{
		cout << "  " << char(200);				//gooshe paeen chap
		for (int i = 1; i <= 5 * n; i++)
		{
			if (i == 5 * n / 2 + 1)
			{
				cout << char(202);				//3rah (roo be bala) zele paeen
			}
			else if (i == n - 3 || i == n + 5 || i == 3.5 * n - 2.5 || i == 3.5 * n + 7.5)
			{
				cout << char(203);				//3rah (roo be paeen) zele paeen
			}
			else
			{
				cout << char(205);				//zele paeen(khotoot saf)
			}
		}
		cout << char(188) << '\n';				//gooshe paeen rast
	}

	//nahiye esm daryaha :
	{
		for (int i = 1; i < n; i++)
		{
			cout << " ";
		}
		cout << char(186) << "Our Sea" << char(186);
		for (int i = 1; i <= 2.5 * n - 8.5; i++)
		{
			cout << " ";
		}
		cout << char(186) << "Enemy Sea" << char(186) << endl;
		for (int i = 1; i < n; i++)
		{
			cout << " ";
		}
		cout << char(200);
		for (int i = 1; i <= 7; i++)
		{
			cout << char(205);
		}
		cout << char(188);
		for (int i = 1; i <= 2.5 * n - 8.5; i++)
		{
			cout << " ";
		}
		cout << char(200);
		for (int i = 1; i <= 9; i++)
		{
			cout << char(205);
		}
		cout << char(188);
		cout << '\n';
	}

	score();
	cout << char(244) << "Number of Our remaining ships: " << Number_of_our_ships << endl;
	cout << char(245) << "Number of remaining Enemy ships: " << Number_of_enemy_ships << endl;
	cout << '\n';

	save(Username);								//har bar ke bazi update mishavad,save mishavad (auto save)
}

//tabe e barraye chideshodan keshti haye ma va doshman
void Placing_ships()
{
	srand(time(NULL));		//srand(time(NULL)) : baraye inke tabe rand har bar ke farakhani mishavad meghdar motefaveti bedahad.

	//gereftan abad board:
	{
		cout << "Dimensions of the game table" << endl;
		cout << "(The dimensions must be a positive odd number that is opposite to 1 and 3.)" << endl;
		cout << "Enter the dimensions :";
		cin >> n;
		while (true)
		{
			if (n < 0)
			{
				system("cls");
				cout << "Dimensions of the game table" << endl;
				cout << "Dimensions must be positive !" << endl;
				cout << "Please enter a positive number :";
				cin >> n;
			}
			else if (n % 2 == 0)
			{
				system("cls");
				cout << "Dimensions of the game table" << endl;
				cout << "Dimensions must be odd !" << endl;
				cout << "Please enter an odd number :";
				cin >> n;
			}
			else if (n == 1 || n == 3)
			{
				system("cls");
				cout << "Dimensions of the game table" << endl;
				cout << "The dimensions must be the opposite of 1 and 3 !" << endl;
				cout << "Please enter a number opposite 1 and 3 :";
				cin >> n;
			}
			else
			{
				break;
			}
		}
	}
	//tarife board be soorat arraye daynamic va meghdar dehi avalie: 
	{
		board = new string * [n + 1];		//n+1 be dalil inke ararye ye vahed jolo beravad va beshavad as 1 ta n mokhtasat dad.
		for (int i = 1; i < n + 1; i++)
		{
			board[i] = new string[n + 1];

			for (int j = 1; j < n + 1; j++)
			{
				if (j == (n + 1) / 2)
				{
					board[i][j] = char(186);    //khat joda konande do darya ( 186 : || )
				}
				else
				{
					board[i][j] = "#";			//meghdar valie hame khane ha # ast
				}
			}
		}
	}
	//Placing enemy ships:
	{
		Number_of_enemy_ships = n;
		int enemyI, enemyJ, LowerBound_I = 1, UpperBound_I = n, LowerBound_J = ((n + 1) / 2) + 1, UpperBound_J = n;
		for (int i = 1; i <= n; i++)
		{
			while (true)
			{
				enemyI = (rand() % (UpperBound_I - LowerBound_I + 1)) + LowerBound_I;
				enemyJ = (rand() % (UpperBound_J - LowerBound_J + 1)) + LowerBound_J;
				if (board[enemyI][enemyJ] == "@")
				{
					continue;
				}
				else
				{
					board[enemyI][enemyJ] = "@";
					break;
				}
			}
		}
	}
	print(n);
	//Placing our own ships:
	{
		int inputI, inputJ;
		cout << char(254) << "Please do not exit the game before placing your ships so that the game saves properly." << endl;
		cout << "Enter the coordinates of your ships :" << endl;
		cout << "(The coordinates must be in Our Sea)" << endl;
		for (int i = 1; i <= n; i++)
		{
			while (true)
			{
				cout << "Ship " << i << ":" << endl;
				cout << "Row: ";
				cin >> inputI;
				cout << "Column: ";
				cin >> inputJ;
				if (inputI > n || inputI < 1 || inputJ >= (n + 1) / 2 || inputJ < 1)
				{
					print(n);
					cout << "Error! Re-enter the coordinates correctly." << endl;
					cout << "(The coordinates must be in Our Sea)" << endl;
					continue;
				}
				else if (board[inputI][inputJ] == "*")
				{
					print(n);
					cout << "You have already placed a ship in these coordinates." << endl;
					cout << "Please choose another coordinate." << endl;
					continue;
				}
				else
				{
					board[inputI][inputJ] = "*";
					break;
				}
			}
			Number_of_our_ships++;
			print(n);
		}
	}
}

//tabe e barraye khondan etelaat har bazikon => (estefade dar tabe (loadcustom))
void load(string fname)
{
	string filePath;
	filePath = fname + ".txt";
	fstream f(filePath, ios::in);
	// n:
	{
		f >> n;
		board = new string * [n + 1];      //tabe ro dobare meghdar dehi avalie mikonim va bad por mikonim
		for (int i = 1; i < n + 1; i++)
		{
			board[i] = new string[n + 1];

			for (int j = 1; j < n + 1; j++)
			{
				board[i][j] = char(186);    // 186 : ||
			}
		}
	}
	int coi, coj, tk; // coi : satr , coj : sotoon
	// *:
	{
		f >> tk;
		for (int q = 0; q < tk; q++)
		{
			f >> coi >> coj;
			board[coi][coj] = "*";
		}
	}
	// @:
	{
		f >> tk;
		for (int q = 0; q < tk; q++)
		{
			f >> coi >> coj;
			board[coi][coj] = "@";
		}
	}
	// #:
	{
		f >> tk;
		for (int q = 0; q < tk; q++)
		{
			f >> coi >> coj;
			board[coi][coj] = "#";
		}
	}
	// 1:
	{
		f >> tk;
		for (int q = 0; q < tk; q++)
		{
			f >> coi >> coj;
			board[coi][coj] = "1";
		}
	}
	// 0:
	{
		f >> tk;
		for (int q = 0; q < tk; q++)
		{
			f >> coi >> coj;
			board[coi][coj] = "0";
		}
	}
	// Variables:
	{
		f >> Number_of_our_ships;
		f >> Number_of_enemy_ships;

		f >> Number_of_Our_Correct_Shots;
		f >> Number_of_Our_Incorrect_Shoots;
		f >> Number_of_Our_Incorrect_Shoots;

		f >> Number_of_Enemy_Shots;
		f >> Number_of_Enemy_Correct_Shots;
		f >> Number_of_Enemy_Incorrect_Shots;

		f >> Score;
	}
	f.close();
}

//tabe e barraye Peyda kardan Name karbar az file record va load kardan etelaat zakhire shode oon bazikon
void loadcustom()
{
	cout << "Enter the username you want to continue :";
	cin >> Username;
	fstream f("record.txt", ios::in);
	f >> inum;
	string strname, strscore;
	fsign = false;
	for (int i = 0; i < inum; i++)
	{
		fsign = false;
		f >> strname >> strscore;
		if (Username == strname)
		{
			load(Username);
			fsign = true;
		}
	}
	f.close();

	if (!fsign)
	{
		system("cls");
		cout << '\n' << '\t' << "!!! not found !!!" << endl << endl;
		Sleep(2000);
	}
}

//tabe e barraye print menu
void print_Menu()
{
	system("cls");
	cout << "!!! Welcome to Battle of the Seas !!!" << endl;
	cout << '\t' << "What do you want to do?" << endl;
	cout << "  " << "(Enter the desired action number)" << endl;
	cout << "             " << "1.New Game" << endl;
	cout << "             " << "2.Load" << endl;
	cout << "             " << "3.Leaderboard" << endl;
	cout << "             " << "4.Exit the Game" << endl;
	cout << "             " << "Action :";
}

//tabe e barraye anjam bazi (shelik kardan do taraf va ckeck kardan etmam bazi)
void Playing()
{
	bool finish = false;
	while (!finish)
	{
		//Our Shot:
		{
			int ourShootI, ourShootJ;
			cout << "Enter the coordinates you want to Shoot :" << endl;
			cout << "(The coordinates must be in Enemy Sea)" << endl;
			while (true)
			{
				cout << "Row: ";
				cin >> ourShootI;
				cout << "Column: ";
				cin >> ourShootJ;
				if (ourShootI > n || ourShootI < 1 || ourShootJ <= (n + 1) / 2 || ourShootJ > n)
				{
					print(n);
					cout << "Error! The coordinates must be in the Sea of the Enemy." << endl;
					cout << "Enter the firing coordinates again :" << endl;
					continue;
				}
				else if (board[ourShootI][ourShootJ] == "1" || board[ourShootI][ourShootJ] == "0")
				{
					print(n);
					cout << "Error! You can't re-shoot coordinates you've already shot!" << endl;
					cout << "Enter the firing coordinates again :" << endl;
					continue;
				}
				else
				{
					if (board[ourShootI][ourShootJ] == "@")
					{
						board[ourShootI][ourShootJ] = "1";
						Number_of_Our_Correct_Shots++;
						Number_of_enemy_ships--;
					}
					else
					{
						board[ourShootI][ourShootJ] = "0";
						Number_of_Our_Incorrect_Shoots++;
					}
					Number_of_Our_Shots++;
					break;
				}
			}
		}
		print(n);
		//Checking game is finished:
		{
			if ((Number_of_our_ships == 0 || Number_of_enemy_ships == 0))
			{
				finish = true;
				break;
			}
		}
		//Enemy Shoot:
		{
			int enemyShootI, enemyShootJ, LowerBound_I = 1, UpperBound_I = n, LowerBound_J = 1, UpperBound_J = ((n + 1) / 2) - 1;
			while (true)
			{
				enemyShootI = (rand() % (UpperBound_I - LowerBound_I + 1)) + LowerBound_I;
				enemyShootJ = (rand() % (UpperBound_J - LowerBound_J + 1)) + LowerBound_J;
				if (board[enemyShootI][enemyShootJ] == "1" || board[enemyShootI][enemyShootJ] == "0")
				{
					continue;
				}
				else
				{
					if (board[enemyShootI][enemyShootJ] == "*")
					{
						board[enemyShootI][enemyShootJ] = "1";
						Number_of_our_ships--;
						Number_of_Enemy_Correct_Shots++;
					}
					else
					{
						board[enemyShootI][enemyShootJ] = "0";
						Number_of_Enemy_Incorrect_Shots++;
					}
					Number_of_Enemy_Shots++;
					break;
				}
			}
		}
		//Checking game is finished:
		{
			if ((Number_of_our_ships == 0 || Number_of_enemy_ships == 0))
			{
				finish = true;
				break;
			}
		}
		print(n);
	}
	print(n);
	string YesorNO;
	bool flag = false;
	if (Number_of_our_ships == 0)
	{
		while (true)
		{
			print(n);
			cout << "     GAME OVER" << endl;
			cout << "     You LOSE" << endl;
			cout << "     Your Score :" << (double)Score << endl;
			cout << " Want to do something else?" << endl;
			cout << "     (Enter yes or no)" << endl;
			cin >> YesorNO;
			if (YesorNO == "yes" || YesorNO == "YES")
			{
				flag = true;
				break;
			}
			else if (YesorNO == "no" || YesorNO == "NO")
			{
				Exit = true;
				cout << "Thanks for playing :)" << endl;
				break;
			}
		}
	}
	else if (Number_of_enemy_ships == 0)
	{
		while (true)
		{
			print(n);
			cout << "You WIN" << endl;
			cout << "Good Job Captain" << endl;
			cout << "Your Score :" << (double)Score << endl;
			cout << " Want to do something else?" << endl;
			cout << "     (Enter yes or no)" << endl;
			cin >> YesorNO;
			if (YesorNO == "yes" || YesorNO == "YES")
			{
				flag = true;
				break;
			}
			else if (YesorNO == "no" || YesorNO == "NO")
			{
				Exit = true;
				cout << "Thanks for playing :)" << endl;
				break;
			}
		}
		if (flag)
		{
			print_Menu();
		}
	}
}

int main()
{
	while (!Exit)
	{
		print_Menu();
		string input;
		cin >> input;
		read();
		//New Game
		if (input == "1")
		{
			system("cls");
			cout << "Enter Your Username :";
			cin >> Username;
			system("cls");
			Placing_ships();
			Playing();
			if (Exit == false)
			{
				continue;
			}
		}
		//Load
		else if (input == "2")
		{
			system("cls");
			cout << "\t     " << "Saves" << endl;
			showrecord();

			loadcustom();
			if (!fsign) {
				continue;
			}
			if (Number_of_our_ships == 0 || Number_of_enemy_ships == 0)
			{
				print(n);
				cout << "This game is over." << endl;
				cout << "Please choose another save." << endl;
				showrecord();
			}
			else
			{
				print(n);
				Playing();
			}
		}
		//Leaderboard
		else if (input == "3")
		{
			string YesorNO;
			bool flag = false;
			while (true)
			{
				system("cls");
				cout << "\t " << "Leaderboard" << endl;
				showrecord();
				cout << " Want to do something else?" << endl;
				cout << "     (Enter yes or no)" << endl;
				cin >> YesorNO;
				if (YesorNO == "yes" || YesorNO == "YES")
				{
					break;
				}
				else if (YesorNO == "no" || YesorNO == "NO")
				{
					Exit = true;
					system("cls");
					cout << "Thanks for playing :)" << endl;
					break;
				}
			}
		}
		//Exit the Game
		else if (input == "4")
		{
			Exit = true;
			system("cls");
			cout << "Thanks for playing :)" << endl;
		}
	}
	return 0;
}
