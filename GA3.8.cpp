/*
GA 3.8
特性：
在原代GA3.4的基础上，改变变异的方法，交换或者单点变，可以在3000轮内达到最优解,462.975
*/


#include<iostream>
#include<time.h>
#include <stdlib.h>
#include<memory.h>
#include<math.h>
#include<fstream>
using namespace std;
double X[]={0,34,56,27,44,4,10,55,14,28,12,16,68,24,29,49,51,45,78,82,32,95,53,7,64,88,23,87,34,71,98};
double Y[]={0,57,64,82,94,18,64,69,30,54,70,40,46,82,38,15,26,31,56,33,11,8,46,94,62,52,61,76,58,41,69};
const int NUM_OF_CITY=30;
const int SIZE_OF_GROUP=50;
const int MAX_ARRAY=2*SIZE_OF_GROUP+1;
const int CROSSLEN=15;
int MUTATION_POSSIBILITY=20;
int MUTATION_NUM=1;
const int turn=2000;
int G[SIZE_OF_GROUP+1][NUM_OF_CITY+1];
int Baby[SIZE_OF_GROUP*2+1][NUM_OF_CITY+1];
int DecodedG[SIZE_OF_GROUP+1][NUM_OF_CITY+1];
int K[SIZE_OF_GROUP+1][NUM_OF_CITY+1];
double D[NUM_OF_CITY+1][NUM_OF_CITY+1];
int overallArray[MAX_ARRAY];
ofstream outfile("output.txt");
double bestRec=999999;


int rd(int a,int b);
template<class T>
void BubbleSort(T *array,int len,int *index);
void permutation(int *per,int len);
void CalculateD();
void printD();
void printDecodedG();
void printG();
void printBaby1();
void printBaby2();
void GenerateGroup0();
void DecodeG();
void printGline(int row);
void printBabyline(int row);
void CrossOver();
void Mutation();
double RouteLength(int *route1);
void Choose();
void write();
void CrossJudge();
bool subCross(int i,int j,int p,int q);

int rd(int a,int b){
    return rand()%(b-a+1)+a;
}




/*void CrossJudge(){
    int index[NUM_OF_CITY+1];
    BubbleSort(G[1],NUM_OF_CITY,index);
    for(int i = 1; i <= NUM_OF_CITY-1; i++){
        for(int j = i+1;j <= NUM_OF_CITY-1;j++){
            if(subCross(index[i],index[i+1],index[j],index[j+1])){
                int G1[NUM_OF_CITY+1],G2[NUM_OF_CITY+1];
                for(int k = 1;k<=NUM_OF_CITY;k++){
                    G1[k] = G2[k] = G[1][k];
                }
                int tmp;
                tmp = index[i];
                index[i] = index[j+1];
                index[j+1] = tmp;
                for(int k=1;k<=NUM_OF_CITY;k++){
                    G[SIZE_OF_GROUP-1][k]=G1[]
                }

                tmp = G2[index[j]];
                G2[index[j]] = G2[index[i]];
                G2[index[i]]=tmp;
                cout<<"From "<<RouteLength(G[1])<<" 交换 "<<index[i]<<" "<<index[i+1]<<" "<<RouteLength(G1)<<" and 交换 "<<index[j]<<" "<<index[j+1]<<" "<<RouteLength(G2)<<endl;
                for(int k = 1;k<=NUM_OF_CITY;k++){
                    G[SIZE_OF_GROUP][k] = G2[k];
                    G[SIZE_OF_GROUP-1][k] = G1[k];
                }
            }
        }
    }
}


bool subCross(int i,int j,int p,int q){
    double s=(Y[j]-Y[i])*(X[p]-X[q])-(X[i]-X[j])*(Y[q]-Y[p]);
    if(s==0){
        return false;
    }
    else{
        double b1 = X[i] * Y[j] - X[j] * Y[i];
        double b2 = X[p] * Y[q] - X[q] * Y[p];
        double y = b1 * (Y[p] - Y[q]) + b2 * (Y[j] - Y[i]);
        double x = b1 * (X[p] - X[q]) + b2 * (X[j] - X[i]);
        x = x / s;
        y = y / s;
        //cout << "( " <<x<<" , "<<y<<" )"<<endl;
        double minX = min(X[i],min(X[j],min(X[p],X[q])));
        double maxX = max(X[i],max(X[j],max(X[p],X[q])));
        if (x > minX && x < maxX && x!=X[i]&&x!=X[j]&&x!=X[p]&&x!=X[q]){
            return true;
        }
        return false;
    }
}*/

template<class T>
void BubbleSort(T *array,int len,int *index){
    T b[MAX_ARRAY];
    for(int i=1;i<=len;i++){
        b[i]=array[i];
    }
    for(int i=1;i<=len;i++){
        index[i]=i;
    }
    T tmp1;
    T tmp2;
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len-i;j++){
            if(b[j]>b[j+1]){
                tmp1=b[j];
                b[j]=b[j+1];
                b[j+1]=tmp1;
                tmp2=index[j];
                index[j]=index[j+1];
                index[j+1]=tmp2;
            }
        }
    }
}
void permutation(int *per,int len){
    for(int i=1;i<=len;i++){
        overallArray[i]=rand();
    }
    BubbleSort(overallArray,len,per);
}

void CalculateD(){
	memset(D,0,sizeof(D));
	for(int i = 1; i <= NUM_OF_CITY; i++){
		for(int j = i+1; j <= NUM_OF_CITY;j++){
            D[i][j]=D[j][i]=sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]));
           // cout<<D[i][j]<<' ';
		}
	}
}


void printD(){
    cout<<"Here is D"<<endl;
	for(int i=1;i<=NUM_OF_CITY;i++){
		for(int j=1;j<=NUM_OF_CITY;j++){
			cout<<D[i][j]<<' ';
		}
		cout<<endl;
	}
}

void printDecodedG(){
    cout<<"Here is DecodedG"<<endl;
	for(int i=1;i<=SIZE_OF_GROUP;i++){
		for(int j=1;j<=NUM_OF_CITY;j++){
			cout<<DecodedG[i][j]<<' ';
		}
		cout<<endl;
	}
}

void printG(){
    cout<<"Here is G"<<endl;
	for(int i=1;i<=SIZE_OF_GROUP;i++){
		for(int j=1;j<=NUM_OF_CITY;j++){
			cout<<G[i][j]<<' ';
		}
		cout<<endl;
	}
}

void printBaby1(){
    cout<<"Here is Baby1"<<endl;
	for(int i=1;i<=SIZE_OF_GROUP;i++){
		for(int j=1;j<=NUM_OF_CITY;j++){
			cout<<Baby[i][j]<<' ';
		}
		cout<<endl;
	}
}

void printBaby2(){
    cout<<"Here is Baby2"<<endl;
	for(int i=1;i<=SIZE_OF_GROUP*2;i++){
		for(int j=1;j<=NUM_OF_CITY;j++){
			cout<<Baby[i][j]<<' ';
		}
		cout<<endl;
	}
}

void GenerateGroup0(){
    for(int t=1;t<=SIZE_OF_GROUP;t++){
        int minn=9999;
        int rec;
        for(int i=1;i<=SIZE_OF_GROUP;i++){
            for(int j=1;j<=NUM_OF_CITY;j++){
                G[i][j]=rand();
            }
            if(RouteLength(G[i])<minn){
                rec=i;
            }
        }
        for(int j=1;j<=NUM_OF_CITY;j++){
            K[t][j]=G[rec][j];
        }   
    } 

    for(int i=1;i<=SIZE_OF_GROUP;i++){
        for(int j=1;j<=NUM_OF_CITY;j++){
            G[i][j]=K[i][j];
        }
    }
}

void DecodeG(){
    for(int i=1;i<=SIZE_OF_GROUP;i++){
        BubbleSort(G[i],NUM_OF_CITY,DecodedG[i]);
    }
}

void printGline(int row){
    for(int i=1;i<=NUM_OF_CITY;i++){
        cout<<G[row][i]<<' ';
    }
    cout<<endl;
}
void printBabyline(int row){
    for(int i=1;i<=NUM_OF_CITY;i++){
        cout<<Baby[row][i]<<' ';
    }
    cout<<endl;
}
void CrossOver(){
    int which2[MAX_ARRAY];
    permutation(which2,SIZE_OF_GROUP);
    /*for(int i=1;i<=100;i++){
        cout<<i<<' '<<which2[i]<<endl;
    }*/
    int st;
    for(int i=1;i<=SIZE_OF_GROUP/2;i++){
        st=rd(1,NUM_OF_CITY-CROSSLEN+1);
        //cout<<"Cross over st= "<<st<<endl;
        for(int j=1;j<=NUM_OF_CITY;j++){
            if(j<st||j>=st+CROSSLEN){
                Baby[2*i-1][j]=G[2*i-1][j];
                Baby[2*i][j]=G[2*i][j];
            }
            else{
                Baby[2*i-1][j]=G[2*i][j];
                Baby[2*i][j]=G[2*i-1][j];
            }
        }
        /*printGline(which2[2*i-1]);
        printGline(which2[2*i]);
        cout<<"to"<<endl;
        printBabyline(2*i-1);
        printBabyline(2*i);*/
    }
}

void Mutation(){
    for(int i=1;i<=SIZE_OF_GROUP;i++){
        if(rd(1,100)<MUTATION_POSSIBILITY){
            //printBabyline(i);
            for(int j=1;j<=MUTATION_NUM;j++){
                if(rd(1,2)<=1){
                    int rd1 = rd(1,NUM_OF_CITY);
                    int rd2 = rd(1,NUM_OF_CITY);
                    int tmp=Baby[i][rd1];
                    Baby[i][rd1] = Baby[i][rd2];
                    Baby[i][rd2] = tmp;
                }
                else{
                    Baby[i][rd(1,NUM_OF_CITY)]=rand();
                }
                
            }
            //printBabyline(i);
        }
    }
}

double RouteLength(int *route1){
    int route[NUM_OF_CITY+1];
    BubbleSort(route1,NUM_OF_CITY,route);
    double rtlen=0;
    for(int i=1;i<=NUM_OF_CITY-1;i++){
        rtlen+=D[route[i]][route[i+1]];
       // cout<<rtlen<<' ';
    }
    rtlen+=D[route[NUM_OF_CITY]][route[1]];
    /*cout<<rtlen<<endl;
    for(int i=1;i<=NUM_OF_CITY;i++){
        cout<<route[i]<<"->";
    }
    cout<<route[1];
    cout<<endl;*/
    return rtlen;
}

void Choose(){
    for(int i=51;i<=2*SIZE_OF_GROUP;i++){
        for(int j=1;j<=NUM_OF_CITY;j++){
            Baby[i][j]=G[i-50][j];
        }
    }
    double lenRec[2*SIZE_OF_GROUP+1];
    for(int i=1;i<=2*SIZE_OF_GROUP;i++){
       lenRec[i]=RouteLength(Baby[i]);
      // cout<<lenRec[i]<<' ';
    }
    //cout<<endl;
    int index[SIZE_OF_GROUP+1];
    BubbleSort(lenRec,2*SIZE_OF_GROUP,index);
    for(int i=1;i<=SIZE_OF_GROUP;i++){
        for(int j=1;j<=NUM_OF_CITY;j++){
            G[i][j]=Baby[index[i]][j];
        }
      //  cout<<RouteLength(G[i])<<' ';
    }

}

void write(){
    if(RouteLength(G[1])<bestRec){
        bestRec=RouteLength(G[1]);
    }
    else{
        return ;
    }
    int index[NUM_OF_CITY+1];
    BubbleSort(G[1],NUM_OF_CITY,index);
    for(int i=1;i<=NUM_OF_CITY;i++){
        outfile<<index[i]<<' ';
    }
    outfile<<endl;
}


int main(){
    srand((unsigned)time(NULL));
    CalculateD();
    GenerateGroup0();
    //DecodeG();
    
        int M=turn;
        
        while(M--){
            CrossOver();
            Mutation();
            //printG();
            //printBaby1();
            Choose();
            cout<<"Turn "<<turn-M<<"  now pathlen is "<<RouteLength(G[1])<<endl;
            //printBaby2();
            write();
            if((turn-M)%turn/10){
                MUTATION_POSSIBILITY+=10;
            }
            /*if(turn-M>5000){
                CrossJudge();
            }*/
        }
 

    DecodeG();
    printDecodedG();
    


    write();
    cout<<"shortest is "<<RouteLength(G[1])<<endl;
    cout<<"done!"<<endl;
    //printDecodedG();
    //printG();
    //printD();
   
}

/*
clc,clear
X=[34,56,27,44,4,10,55,14,28,12,16,68,24,29,49,51,45,78,82,32,95,53,7,64,88,23,87,34,71,98];
Y=[57,64,82,94,18,64,69,30,54,70,40,46,82,38,15,26,31,56,33,11,8,46,94,62,52,61,76,58,41,69];
for i=1:30
for j=1:30
D(i,j)=sqrt((X(i)-X(j))^2+(Y(i)-Y(j))^2);
end
end
load output.txt
ind=output;
h=plot([X(ind),X(ind(1))],[Y(ind),Y(ind(1))],'-*');
s=0;
for i=1:29
s=s+D(ind(i),ind(i+1));
end
s=s+D(ind(1),ind(30))
set(h,'LineWidth',1.5)
*/





/*
close all
clc,clear
X=[34,56,27,44,4,10,55,14,28,12,16,68,24,29,49,51,45,78,82,32,95,53,7,64,88,23,87,34,71,98];
Y=[57,64,82,94,18,64,69,30,54,70,40,46,82,38,15,26,31,56,33,11,8,46,94,62,52,61,76,58,41,69];
for i=1:30
for j=1:30
D(i,j)=sqrt((X(i)-X(j))^2+(Y(i)-Y(j))^2);
end
end
load output.txt
for j=1:size(output,1)
ind=output(j,:);
h=plot([X(ind),X(ind(1))],[Y(ind),Y(ind(1))],'-*');
s=0;
for i=1:29
s=s+D(ind(i),ind(i+1));
end
s=s+D(ind(1),ind(30))
set(h,'LineWidth',1.5)
pause(0.1)
end


for i=1:30
text(X(ind(i)),Y(ind(i)),num2str(ind(i)))
end
*/