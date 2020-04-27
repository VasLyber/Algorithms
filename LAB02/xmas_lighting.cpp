#include <iostream> 
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

struct node{
    int key=-1;
    bool root=false;
    int lights_on = 0, lights_out = 0;
    node *parent;
    vector<node *> childs;
};

class Create_tree{
    public:
        Create_tree(int num_nodes){
            tree_deep = num_nodes;
        }

    int getTree() const{
        return tree_deep;
    }

    void all_tree(int num, ifstream & fpin){
        
        node *tree = new node[num];
        int parin, childin ;
        string line;
        
        while(!fpin.eof()){
            getline(fpin,line);
            if (line.length()==0) break;
            fpin >> parin >> childin;
            cout<< "parent "<<parin<<" child "<< childin <<endl;
            if (parin-1==0) tree[parin-1].root=true;
            if (tree[parin-1].key <0) tree[parin-1].key = parin;
            if (tree[childin-1].key <0) tree[childin-1].key = childin;

            tree[parin-1].childs.insert( tree[parin-1].childs.begin(), &tree[childin-1]);
            tree[childin-1].parent = &tree[parin-1];
            
        }
         for (int i=0; i<num; i++){
            cout<< "My value is "<<tree[i].key<< " and my child size "<< tree[i].childs.size()<< " and my childs \n";
            if (tree[i].childs.size()>0){
                for (int j=0; j <tree[i].childs.size(); j++){
                    child = tree[i].childs[j];
                    cout<<child->key<<" ";
                }
             
                cout<<endl;
            }
                par = tree[i].parent;
                if (tree[i].root == true) cout << "I am the root \n";
                else cout<<"And my parent is " << par->key<<endl;
            
        }
    }
    
    private:
         int tree_deep;
         node *par;
         node *child;

};

int main(int argc, char **argv){
 
 int  N , K;
 string line;
 ifstream file(argv[1]);
 file >> N >> K;
 Create_tree test(N);

 test.all_tree(test.getTree(), file);
 
 return 0;
}
