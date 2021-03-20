#include <bits/stdc++.h>
using namespace std;

#define DEBUG false
#define _(x) if (DEBUG){cout << #x << " = " << x << endl;}
#define __(x) if (DEBUG){cout << #x << " = " << x << " ";}
#define println(x) if (DEBUG){cout << x << endl;}
#define print(x) if (DEBUG){cout << x;}

typedef long long ll;

static int DOWN = 1;
static int UP = 2;
static int LEFT = 3;
static int RIGHT = 4;

bool finish = false;

map<string, bool> visited;

array<char, 9> puzzle {'2', '8', '3', '1', '6', '4', '7', ' ', '5'};
array<char, 9> goal_puzzle {'1', '2', '3', '8', ' ', '4', '7', '6', '5'};

array<bool, 9> DOWN_ENABLE  {false, false, false, true, true, true, true, true, true};
array<bool, 9> UP_ENABLE    {true, true, true, true, true, true, false, false, false};
array<bool, 9> LEFT_ENABLE  {true, true, false, true, true, false, true, true, false};
array<bool, 9> RIGHT_ENABLE {false, true, true, false, true, true, false, true, true};

void print_puzzle(array<char, 9> p) {
    printf("+ - + - + - +\n");
    printf("| %c | %c | %c |\n", p[0], p[1], p[2]);
    printf("+ - + - + - +\n");
    printf("| %c | %c | %c |\n", p[3], p[4], p[5]);
    printf("+ - + - + - +\n");
    printf("| %c | %c | %c |\n", p[6], p[7], p[8]);
    printf("+ - + - + - +\n");
}

bool check(array<char, 9> to_check){
    string str = "";
    for(int i=0; i<9; i++){
        str = str + to_check[i];
    }

    if ( visited.find(str) == visited.end() ) {
        visited.insert({str, true});
        return false;
    } else {
        return true;
    }
}

void solve(int space_loc, array<char, 9> current, int cost, int depth){
    if(current == goal_puzzle || finish){
        printf("FINISH\n");
        finish = true;
        return;
    }
    
    printf("Size of visited : %d\n", visited.size());
    if(check(current)){
        printf("SUDAH DIKUNJUNGI\n");
        return;
    };

    __(space_loc); __(cost); _(depth);
    print_puzzle(current);
    printf("\n");

    array<char, 9> temp = current;

    if(DOWN_ENABLE[space_loc]){
        // _(DOWN);
        temp[space_loc] = temp[space_loc-3];
        temp[space_loc-3] = ' ';
        solve(space_loc - 3, temp, cost+1, depth+1);
    }

    temp = current;
    
    if(UP_ENABLE[space_loc]){
        // _(UP);
        temp[space_loc] = temp[space_loc+3];
        temp[space_loc+3] = ' ';
        solve(space_loc + 3, temp, cost+1, depth+1);
    }

    temp = current;

    if(LEFT_ENABLE[space_loc]){
        // _(LEFT);
        temp[space_loc] = temp[space_loc+1];
        temp[space_loc+1] = ' ';
        solve(space_loc + 1, temp, cost+1, depth+1);
    }

    temp = current;
    
    if(RIGHT_ENABLE[space_loc]){
        // _(RIGHT);
        temp[space_loc] = temp[space_loc-1];
        temp[space_loc-1] = ' ';
        solve(space_loc - 1, temp, cost+1, depth+1);
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int space_loc = 0;
    for(int i=0; i<9; i++){
        if(puzzle[i] == ' '){
            space_loc = i;
            break;
        }
    }

    solve(space_loc, puzzle, 0, 0);

    return 0;
}
