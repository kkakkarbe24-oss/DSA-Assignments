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
    
    
    
	void Reverse(){
		cout<<len/2;
		for(int i=0; i<len/2; i++){
			int temp= ary[i];
			ary[i]=ary[len-(i+1)];
			ary[len-(i+1)]=temp;
		}
	}
	
	
	void MatrixMult() {
		
		int RA,RB,CA,CB,i,j;
		cout<<\n"Enter no of rows and columns of matrixA";
		cin>>RA>>CA;
		
		cout<<\n"Enter no of rows and columns of matrixB";
		cin>>RB>>CB;
		
		if(CA!=RB)
		for(int i=0; i<RA; i++){
			for(int j=0; j<CA; j++){
				
			}
		}
	}
};

int main()
{
    ARRAY obj(11,11);
    obj.Input();
    obj.Show();
    
    
    
    
    
    obj.Reverse();
    obj.Show();
    


}
