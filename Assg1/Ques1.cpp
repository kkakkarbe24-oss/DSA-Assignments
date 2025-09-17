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
    
    void Append(int val){
        if(len==cap){
            doScale();
            cout<<"\nScaled";
        }
        ary[len]=val;
        len++;
        cout<<"\nNew Length="<<len<<endl;
        Show();
    }
    
    void Insert(int val, int loc){
        if(loc>=len){
            cout<<"\nInvalid syntax";
        }
        
        if(len==cap){
            cout<<"\nNo Space";
            return;
        }
        
        for(int i=len-1; i>=loc; i--){
            ary[i+1]=ary[i];
        }
        
        ary[loc]=val;
        len++;
        Show();
    }
    
    
    void doDelete(int loc){
        for(int i =loc;i<len-1;i++){
            ary[i]=ary[i+1];
        }
        len--;
        cout<<"\nNew Length="<<len<<endl;
        Show();
    }
    
    void doScale(){
        cap=cap*2;
        int*nwAry= new int[cap];
        for(int i=0;i<cap;i++){
            nwAry[i]=ary[i];
        }
        
        delete ary;
        ary=nwAry;
    }
    
    int Find(int wanted){
        for (int i=0; i<len; i++){
            if(wanted== ary[i]){
                cout<<"\n"<<wanted<<" found at "<<i;
                return(i);
            }
            
            
        }
        cout<<"Not Found";
    }
};

int main()
{
    ARRAY obj(6,6);
    obj.Input();
    obj.Show();
    
    obj.Append(90);
    obj.Append(900);
    
    
    obj.Insert(20,2);
    obj.Insert(9,7);
    obj.Insert(8,0);
    
    obj.doDelete(0);
    obj.doDelete(1);
    obj.Show();
    
    obj.Find(90);
    obj.Find(3);
    


}
