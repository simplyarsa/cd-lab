#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void display(int n, int m, vector<vector<vector<int > > > arr){
    cout<<"Transition table: "<<endl;
	for(int i=-1; i<m; i++){
		if(i==-1) cout<<"\t | ";
		else
		cout<<i<<"\t | ";
	}
	cout<<endl;
    for(int i=0; i<n; i++){
		cout<<'q'<<i<<"\t | ";
    	for(int j=0; j<m; j++){
    		for(int k=0; k<arr[i][j].size(); k++){
    			cout<<arr[i][j][k]<<" ";	
    		}
			cout<<"\t | ";	
    	}
    	cout<<endl;
    }
}

int mystoi(string t){
    int sign=1, ans=0;
	for(int i=0; i<t.size(); i++){
		char c=t[i];
		if(c=='-'){
			sign=-1;
		}
		else if(c>='0' && c<='9'){
			ans*=10;
			ans+=(c-'0');
		}
	}
	return ans*sign;
}

void check(vector<int> l, vector<int> &final, int &states){
    for(int i=0; i<l.size(); i++){
        for(int j=0; j<final.size(); j++){
            if(l[i]==final[j] && find(final.begin(), final.end(), states)==final.end()){

                final.push_back(states);
            }
        }
    }
}

void solve(int i, int j, int &n, int &m, int &states, vector<vector<vector<int > > > &arr, map<int, string> &state_map, map<vector<int>, string> &map, vector<int> &final){
	
    vector<int> l=arr[i][j];
    check(l, final, states);
	string temp="";
	for(int i=0; i<l.size(); i++){
		temp+=to_string(l[i]);
	}
	map[l]=temp;
	state_map[states]=temp;
	states++;
	vector<vector<int> > row;
	vector<set<int> >st(m);
	int k=0;
	
    for(int i=0; i<l.size(); i++){
        for(int j=0; j<m; j++){
            for(int k=0; k<arr[l[i]][j].size(); k++){
                if(arr[l[i]][j][k]!=-1){
                    st[j].insert(arr[l[i]][j][k]);
                }
            }
        }
    }

    for(int i=0; i<m; i++){ 
    	vector<int> curr;
    	for(auto it: st[i]){
    		curr.push_back(it);
    	}
        if(st[i].size()==0){
            curr.push_back(-1);
        }
    	row.push_back(curr);
    }

    arr.push_back(row);
    n++;

}

int main(){
	fstream myfile;
	myfile.open("nfa.txt", ios::in);
    string line;
    int linenumber=1;
    int s;
    vector<vector<vector<int > > > arr;
	
    vector<int> final;

    map<vector<int>, string> mymap;
    map<int, string> state_map;

        while (getline(myfile, line))
        {
            if(linenumber==1){
            	s=mystoi(line);
            }
            else if(linenumber==2){
            	string temp="";
            	for(int i=0; i<line.size(); i++){
            	
            		if(line[i]==' '){
            			final.push_back(mystoi(temp));
            			temp="";
            		}
            		else{
            			temp+=line[i];
            		}
            	}   
				if(temp!="") final.push_back(mystoi(temp));         	
            }
            else{
            	string temp="";
            	vector<vector<int > > row;
				vector<int> curr;
            	for(int i=0; i<line.size(); i++){
            		
            		if(line[i]==','){
            			curr.push_back(mystoi(temp));
            			temp="";
            		}
            		else if(line[i]==' '){
            			curr.push_back(mystoi(temp));
            			row.push_back(curr);
            			temp="";
            			curr={};
            		}
            		else{
            			temp+=line[i];
            		}
            	}
            	curr.push_back(mystoi(temp));
            	row.push_back(curr);
            	arr.push_back(row);
            }
            linenumber++;
        }
    myfile.close();
    
    
    int n=arr.size(), m=arr[0].size();

    cout<<"Initial state: "<<s<<endl;
    cout<<"Final states: ";
    for(int i=0; i<final.size(); i++){
    	cout<<final[i]<<" ";
    }
    cout<<endl;
    
    display(n, m, arr);

	int states=arr.size();

    for(int i=0; i<n; i++){
    	for(int j=0; j<m; j++){
            if(arr[i][j].size()>1 && mymap.find(arr[i][j])==mymap.end()){
    		    solve(i, j, n, m, states, arr, state_map, mymap, final);
            }
    	}
    }




	cout<<endl<<"Final states: ";
    for(int i=0; i<final.size(); i++){
    	if(state_map.find({final[i]})!=state_map.end()){
			cout<<state_map[{final[i]}]<<" ";
		}else{
			cout<<final[i]<<" ";	
		}

    }

	n=states;
	vector<vector<string> > newarr(n, vector<string>(m));

	for(int i=0; i<n; i++){
    	for(int j=0; j<m; j++){
            if(arr[i][j].size()>1){
    		    newarr[i][j]=(mymap[arr[i][j]]);
            }	
			else{
				if(arr[i][j][0]==-1)
					newarr[i][j]="-1";
				else
				newarr[i][j]='0'+(arr[i][j][0]);
			}
    	}
    }

	cout<<endl<<"Transition table: "<<endl;
	for(int i=-1; i<m; i++){
		if(i==-1) cout<<"\t | ";
		else
		cout<<i<<"\t | ";
	}
	cout<<endl;
	for(int i=0; i<n; i++){
		if(state_map.find(i)!=state_map.end()){
			cout<<'q'<<state_map[i]<<"\t | ";
		}
		else{
			cout<<'q'<<i<<"\t | ";
		}
		for(int j=0; j<m; j++){
			cout<<newarr[i][j]<<"\t | ";	
		}
		cout<<endl;
	}

    
	return 0;
}