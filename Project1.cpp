// Gökay Sarı 150180727
#include<iostream>
#include<fstream>
#include <string>
#include <chrono> // time
#include <vector> // vectors
#include <queue>

using namespace std;


//global variables for player inputs
string algorithm;
int x_start;
int y_start;
int b, num;
int* ship_coordinates = new int[4 * num];

//node class 
class node 
{
    public:
        char index[20][20];
        node *next;
        node();
        bool visited;   
        vector<node*> children;
       

};

//Player class 
//player1 and player2 
class Player
{
    public:
        Player();
        string method;
        int board_Size;
        int num_OfShips;
        
};

node::node()
{

}

//default 
Player::Player()
{
    method =" ";
    board_Size=0;
    num_OfShips=0;
}

//read from file function
void Read(string file, int& start_x, int& start_y)
{
    //open file
    ifstream f(file);

    string temp_a,temp_b,temp_c,temp_d;
    //read variables as temp string 
    getline(f, algorithm);
    getline(f, temp_a, ' ');
    getline(f, temp_b);
    getline(f, temp_c, ' ');
    getline(f, temp_d);

    //string to int
    x_start = stoi(temp_a);
    y_start = stoi(temp_b);
    b = stoi(temp_c);
    num = stoi(temp_d);

    //to get the coordinates of the ships owned by the players
    //i is the number of ships
    // int* ship_coordinates = new int[4 * num];
    int j = 0;
    for(int i = 0; i < num; i++){
        getline(f, temp_a, ' ');
        getline(f, temp_b, ' ');
        getline(f, temp_c, ' ');
        getline(f, temp_d);
        ship_coordinates[j++] = stoi(temp_a);
        ship_coordinates[j++] = stoi(temp_b);
        ship_coordinates[j++] = stoi(temp_c);
        ship_coordinates[j++] = stoi(temp_d);
    }

    // return the player
    return;
}



//DFS algorithm with recursive approach
void DFS(node* n)
{
    //n is the root 
    if (!n)
    {
        return;
    }
    
    n->visited = true;

    for (node* child: n->children) {
        if (!child->visited)
        {
            DFS(child); //recursive
        }
    }
}



//bfs traversal for tree
void BFS(node* n)
{
    queue<node*> q;
    q.push(n);
    //add to the end of queue
 
    while(!q.empty())
    {
        
        node* next = q.front();
        q.pop();    //remove from the front of the queue
        next->visited = true;
        for (node* child: next->children)
        {
            if (!child->visited)
            {
                child->visited = true;
                q.push(child);
            }
        }
    }
}


int main(int argc, char* argv[])
{
    chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());//clock starts
    //two files
    string first= argv[1];
    string second = argv[2];
   
    //for debug
    // Read("games/game0/player1.txt",x_start,y_start);

    //read function to read variables 
    //first is games/gameN/player1.txt
    //second is games/gameN/player2.txt

    Read(first,x_start,y_start);
    Read(second,x_start,y_start);
    
    //player1 and player2 
    //hold variables from the file
    Player *Player1 = new Player;
    Player1->method=algorithm;
    Player1->board_Size=b;
    Player1->num_OfShips=num;

    Player *Player2 = new Player;
    Player2->method=algorithm;
    Player2->board_Size=b;
    Player2->num_OfShips=num;

    chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());//clock ends
    
    cout << "The algorithm: ";
    cout << "The algorithm: " << "Player 1: " << Player1->method << "Player 2: " << Player2->method << endl;
    cout << "The number of visited nodes: " << "Player 1: " << "Player 2:" <<endl;
    cout << "The number of nodes kept in the memory: " << "Player 1: " << "Player 2:" <<endl;
    cout << "The result: " <<endl;
    cout << "The running time: " << std::chrono::duration_cast<std::chrono::duration<double> >(_end - _start).count()<<endl;

    return 0;
}