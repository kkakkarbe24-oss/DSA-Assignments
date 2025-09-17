#include <iostream>
using namespace std;

class ARRAY{
    int cap, len;
    int* ary;
    
    public:
    ARRAY(int cap, int len){
        this->cap= cap;
        this->len= len;
        
        ary= new int[cap];
        cout<<"\nArray created of "<<cap<<" capacity"<<endl;
        Show();
    }
    
    void Input(){
        for(int i=0;i<len; i++){
            cout<<"\nEnter value at "<<i+1<<" position:";
            cin>>ary[i];
        }
    }
    
    void Show(){
        cout<<"\nOUTPUT\n";
        for(int i=0;i<len; i++){
            cout<<ary[i]<<" ";
        }
        cout<<endl;
    }
    
    
    
    void DelDuplicate(){
    	for(int i=0;i<len;i++){
    		cout<<"\ni="<<i<<"Len="<<len;
    		for(int j=0; j<len; j++){
    			cout<<"\nj="<<j<<"Len="<<len;
    			if((i!=j) && (ary[i]==ary[j])){
    				if(i<len){
    					doDelete(j);
    				    j--;
					}
    				
				}
			}
		}
    	
	}
};

int main()
{
    ARRAY obj(11,11);
    obj.Input();
    obj.Show();
    
    
    
    
    
    obj.DelDuplicate();
    


}
