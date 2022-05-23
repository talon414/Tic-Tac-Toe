#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <regex>
using namespace std;

class Player{
	private:
		string name,symbol;
		int points=0;
	public:
		Player(){
		}
		string getName(){
			return name;
		}
		
		string getSymbol(){
			return symbol;
		}
		
		int getPoints(){
			return points;
		}

		void setName(string name){
			this->name=name;
		}
		bool setSymbol(string symbol){
			if(!(symbol.size()>1)and symbol!="_" and symbol!="|"){
				this->symbol=symbol;
				return true;
			}
			else{
				cout<<"Symbol must be a single character like #,1,T,...{except \'_\',\'|\'}\nTry Again!\n";
				return false;
			}
		}
		void setPoints(int point){
			this->points=point;
		}
};

void DrawPoints(vector<Player> players){
	cout<<"\nPoints...\n";
	for(int dp=0;dp<players.size();dp++){
		if(dp%3==0){
			cout<<"\n";
		}
		cout<<"Player "<<players[dp].getName()<<":"<<players[dp].getPoints()<<"\t\t";
	}
	cout<<"\n";
}

void DrawGrid(vector<vector<string>> grid){
	string space_c="\t";
	cout<<"\n\t  |";
	for(int i=0;i<grid.size();i++){
		if(to_string(i+1).length()==2){
			cout<<""<<i+1<<".|";
		}
		else{
			cout<<"."<<i+1<<".|";
		}
	}
	cout<<"\n";
	
	for(int i=0;i<grid.size();i++){
		if(to_string(i+1).length()==2){
			space_c=string(8-(to_string(i+1).length()-1),' ');
		}
		cout<<space_c<<i+1<<"_|";
		for(int j=0;j<grid.size();j++){
			if(grid[i][j].size()==0){
				cout<<"   |";
			}
			else{
				cout<<" "<<grid[i][j]<<" |";
			}	
		}	
		cout<<"\n";
		cout<<"\t  |";
		for(int k=0;k<grid.size();k++){
			cout<<"___|";
		}
		cout<<"\n";
		
	}
	cout<<"\n";
}

bool WinCheck(vector<vector<string>> grid,string symbol,int win_mark){
	
	vector<string> testCases(grid.size());
	
	string checkstrh,checkstrv,checkstrlr,checkstrrl,exp=string(win_mark,char(symbol[0]));

	for(int i=0;i<grid.size();i++){
		checkstrlr+=grid[i][i];
		checkstrrl+=grid[i][grid.size()-1-i];	
		
		for(int c=0;c<grid.size();c++){
			checkstrh+=grid[i][c];
			checkstrv+=grid[c][i]; 
		}
		checkstrh+="_";
		checkstrv+="_";
	}
	
	checkstrlr+="_";
	checkstrrl+="_";
	
	testCases.push_back(checkstrh);
	testCases.push_back(checkstrv);
	testCases.push_back(checkstrlr);
	testCases.push_back(checkstrrl);
	
	regex r(exp);
	
	for(auto it=testCases.begin();it<testCases.end();++it){
		if(bool(regex_search((*it),r))){
			return true;
		}
	}
	return false;
}

bool symfind(vector<string>& v,string element){

    vector<string>::iterator it=find(v.begin(),v.end(),element);

    if(it!=v.end()){
        return false;
    }
    return true;
}

bool filled(vector<vector<string>>& v){

    vector<vector<string>>::const_iterator row;

    for (row=v.begin();row!=v.end();row++){
        if(find(row->begin(),row->end(),"")!=row->end()){
            return false;
        }
    }
    return true;
}


int main(){

	system("clear");
    
    cout<<"Welcome to Tic Tac Toe!\n\n";
    
    
    int gridSize;
	vector<Player> players(2);
	vector<string> csym(players.size());
	
	string name,symbol,opt;
	
	for(int p=0;p<players.size();p++){
		cout<<"Enter name of Player:"<<p+1<<"\n";
		cin>>name;
		players[p].setName(name);
		cout<<"Hello "<<players[p].getName()<<"!\n";
		
		while(1){
			cout<<"Enter symbol for "<<players[p].getName()<<":\n";
			cin>>symbol;
			if(symfind(csym,symbol)==false){
				cout<<"Symbol already used\nChoose another one\n";
			}
			else{
				if(players[p].setSymbol(symbol)){
					csym.push_back(symbol);
					cout<<"Set Symbol to "<<players[p].getSymbol()<<".\n";
					break;
				}
			}
		}
		cout<<"\n";
		
		if(p==players.size()-1){
			cout<<"Do you wanna add new players?\n";
			cout<<"Enter \'y\' for yes or \'n\' for no : ";
			cin>>opt;
			
			if(opt=="y"){
				players.resize(players.size()+1);
			}
		}	
	}
	
	cout<<"\nEnter grid size {Grid size must be 3 and 20}\n";
	while(1){
		cin>>gridSize;
		if(gridSize>2 and gridSize<21){
			cout<<"Creating your grid...\n";
			break;
		}
		cout<<"Try again!\nGrid size must be 3 and 20\nEnter grid size:";
	}
	vector<vector<string>> grid(gridSize,vector<string>(gridSize,""));
	cout<<"Done!\n";
	int win_mark;
	cout<<"Enter number of symbols to win!{Example:### <==> 3}: ";
	while(1){
		cin>>win_mark;
		if(win_mark>2){
			cout<<"Done\n";
			break;
		}
		cout<<"Must be atleast 3\nTry again!\n";
	}
	int x,y;
	string endGame;
	
	system("clear");
	DrawPoints(players);
	DrawGrid(grid);
	while(1){
		for(int p=0;p<players.size();p++){
			cout<<players[p].getName()<<"\'s turn!\n";
			while(1){
				cout<<"Enter row value of the cell you want to put the symbol\""<<players[p].getSymbol()<<"\"\n";
				cin>>x;
				cout<<"Enter column value of the cell you want to put the symbol\""<<players[p].getSymbol()<<"\"\n";
				cin>>y;
				if((x-1)<grid.size()and(x-1)>-1 and(y-1)<grid.size()and(y-1)>-1){
						if(grid[x-1][y-1]==""){
							grid[x-1][y-1]=players[p].getSymbol();
							break;
						}
						cout<<"Cell ("<<x<<","<<y<<") already has the symbol "<<grid[x-1][y-1]<<"\n";
				}
				cout<<"Not a useful input!\nTry Again! :/\n";
			}
			system("clear");
			DrawPoints(players);
			DrawGrid(grid);
			if(WinCheck(grid,players[p].getSymbol(),win_mark)){
				players[p].setPoints(players[p].getPoints()+1);
				system("clear");
				DrawPoints(players);
				DrawGrid(grid);
				cout<<players[p].getName()<<" has won!\n";
				while(1){
					cout<<"Play again?\n";
					cout<<"Enter \'y\' for yes or \'n\' for no : ";
					cin>>endGame;
					if(endGame=="n"){
						cout<<"Exiting...\n";
						exit(EXIT_FAILURE);
					}
					else{
						if(endGame=="y"){
							for(int i=0;i<grid.size();i++){
								for(int j=0;j<grid.size();j++){
									grid[i][j]="";
								}
							}
							system("clear");
							DrawPoints(players);
							DrawGrid(grid);
						}
					}
					break;
					cout<<"Not a useful input!\nTry Again! :/\n";
				}
			}
			if(WinCheck(grid,players[p].getSymbol(),win_mark)==false and filled(grid)==true){
				system("clear");
				DrawPoints(players);
				DrawGrid(grid);
				cout<<"It's a draw!\n";
				while(1){
					cout<<"Play again?\n";
					cout<<"Enter \'y\' for yes or \'n\' for no : ";
					cin>>endGame;
					if(endGame=="n"){
						cout<<"Exiting...\n";
						exit(EXIT_FAILURE);
					}
					else{
						if(endGame=="y"){
							for(int i=0;i<grid.size();i++){
								for(int j=0;j<grid.size();j++){
									grid[i][j]="";
								}
								system("clear");
								DrawPoints(players);
								DrawGrid(grid);
							}
						}
					}
					break;
					cout<<"Not a useful input!\nTry Again! :/\n";
				}
			}	
		}
	}
     
    return 0;
}
