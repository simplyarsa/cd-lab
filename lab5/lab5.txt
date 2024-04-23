#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void firstfn(char c, unordered_map<char, vector<string> > &mymap, map<char, vector<char>> &first){
    vector<char> arr;
    vector<string> temp=mymap[c];
    for(auto i: temp){
        // case 2
        if(i[0]>='A' && i[0]<='Z'){
            if(first.find(i[0])==first.end()){
                firstfn(i[0], mymap, first);
            }
            //case 3
            for(auto j: first[i[0]]){
                if(j=='#'){
                    for(int k=1; k<i.size(); k++){
                        if(i[k]>='A' && i[k]<='Z'){
                            if(first.find(i[k])==first.end()){
                                firstfn(i[k], mymap, first);
                            }
                            for(auto l: first[i[k]]){
                                arr.push_back(l);
                            }
                        }
                        else{
                            arr.push_back(i[k]);
                            break;
                        }
                    }
                }
                else{
                    arr.push_back(j);
                }
            }
        }
        // case 1
        else{
            arr.push_back(i[0]);
        }
    }
    first[c]=arr;
}

void followfn(char c, unordered_map<char, vector<string> > &mymap, map<char, set<char>> &follow, map<char, vector<char>> &first){
    for(auto it: mymap){
        vector<string> v=it.second;
        for(auto i: v){
            string temp=i;
            int n=temp.size();
            for(int j=0; j<n; j++){
                if(temp[j]==c){
                    if(j==n-1){
                        if(it.first!=c){
                            if(follow.find(it.first)==follow.end()){
                                followfn(it.first, mymap, follow, first);
                            }
                            for(auto k: follow[it.first]){
                                follow[c].insert(k);
                            }
                        }
                    }
                    //case 2
                    if(temp[j+1]>='A' && temp[j+1]<='Z'){
                        for(auto k: first[temp[j+1]]){
                            if(k!='#'){
                                follow[c].insert(k);
                            }
                            else{
                                //tbd
                                for(int l=j+1; l<n; l++){
                                    if(temp[l]>='A' && temp[l]<='Z'){
                                         if(follow.find(temp[l])==follow.end()){
                                            followfn(temp[l], mymap, follow, first);
                                        }
                                        for(auto m: follow[temp[l]]){
                                            if(m!='#'){
                                                follow[c].insert(m);
                                            }
                                        }
                                    }
                                    else{
                                        follow[c].insert(temp[l]);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    //case 1
                    if(temp[j+1]<'A' || temp[j+1]>'Z'){
                        follow[c].insert(temp[j+1]);   
                    }
                }
            }
        }
    }
}



int main(){
	fstream myfile;
	myfile.open("cfg3.txt", ios::in);
    string line;

    vector<char> order;
    unordered_map<char, vector<string> > mymap;
    map<char, vector<char>> first;
    map<char, set<char>> follow;
   
        while (getline(myfile, line))
        {
            string temp="";
            vector<string> arr;
            char index=line[0];
            order.push_back(index);
            	for(int i=2; i<line.size(); i++){
            		if(line[i]=='|'){
            			arr.push_back(temp);
            			temp="";
            		}
            		else{
            			temp+=line[i];
            		}
            	}   
				arr.push_back(temp);         	
            mymap[index]=arr;
            
        }
        myfile.close();
    
    cout<<"Cfg: "<<endl;
    for(auto i: order){
        cout<<i<<"-> ";
        for(auto j: mymap[i]){
            cout<<j<<" | ";
        }
        cout<<endl;
    }


    for(auto i: order){
    	if(first.find(i)==first.end()){
    		firstfn(i, mymap, first);
    	}
    }

    cout<<"------------------------------------------"<<endl;
    cout<<"First: "<<endl;

    for(auto i: order){
    	cout<<i<<"-> ";
    	for(auto j: first[i]){
    		cout<<j<<"  ";
    	}
    	cout<<endl;
    }
    
    
    follow['S'].insert('$');

    for(auto i: order){
        if(follow.find(i)==follow.end()){
            followfn(i, mymap, follow, first);
        }
    }


    cout<<"------------------------------------------"<<endl;
    cout<<"Follow: "<<endl;

    for(auto i: order){
        cout<<i<<"-> ";
        for(auto j: follow[i]){
            cout<<j<<" ";
        }
        cout<<endl;
    }
 
    
    return 0;
}