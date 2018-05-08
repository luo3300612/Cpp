/*矩阵库说明
支持的操作： (A、B、C都代表矩阵类的一个对象)
1.创建矩阵 						-> Matrix A()，创建矩阵A，用户接下来需要输入A的行数列数，以及其中的元素
2.创建矩阵 						-> Matrix A(int dim1,int dim2)，创建一个dim1×dim2的矩阵，元素的值未赋
3.矩阵加法 						-> Matrix C=A+B，C的各元素为 A、B各元素之和，不改变 A、B
4.矩阵减法 						-> Matrix C=A-B, C的各元素为 A、B各元素之差，不改变A、B
5.矩阵乘法 						-> Matrix C=A*B, 代数中的矩阵乘法，不改变 A、B
6.数乘   							-> Matrix C=A*k，k为一个数字，必须放在右边
7.求逆     						-> Matrix B=!A， B为A的逆，不可逆时 B = A
8.转置     						-> Matrix B=A.T()，B为A的转置  
9.求行列式 						-> double det=A.det()，A不为方阵时，输出提示信息并返回0
10.求代数余子式 				-> double algebraicCom(int i,int j) ，求代数余子式 
11.求伴随矩阵 					-> Matrix B=A.adjointM()，非方阵则返回A 
12.删除矩阵的第m行，第n列 		-> Matrix B=A.delmn(int m,int n)
13.提取矩阵的某一行或某一列， 	-> Matrix B=A.getRow(m) , Matrix B=A.getCol(n)
14.矩阵合并 					-> Matrix C=A.Merge(B,int mode)，合并A B，mode=1，纵向合并，mode=2横向合并
15.得到某个元素 				-> A.getElem(i,j)
16.得到矩阵的维数 				-> A.getDim1()，A.getDim2() 
17.手动析构					-> A.release()
注意:
大多数操作都是新建矩阵返回，并且不影响原来的矩阵，涉及到高维或者多数的矩阵的操作中，要手动析构一些不需要的矩阵。 
*/ 
#ifndef _MARK_
#define _MARK_
#include<stdio.h>
class Matrix{
	private:
	static int ALLSPACE;
	int dim1;//矩阵的行数 
	int dim2;//矩阵的列数 
	double **A;
	public:
	friend Matrix operator +(const Matrix &M1,const Matrix &M2);
	Matrix (){//构造函数，构造的时候同时输入 
		printf("输入矩阵行列:\n");
		scanf("%d%d",&dim1,&dim2);
		A = new double*[dim1+1];
		for(int i = 1; i <= dim1; i++){
			A[i] = new double[dim2+1];
		}
		for(int i = 1; i <= dim1; i++){
			for(int j = 1; j <= dim2; j++){
				scanf("%lf", &A[i][j]);
			}
		}
		Matrix::ALLSPACE+=dim1*dim2;
		printf("SPACE : %d\n",ALLSPACE);
	}
	
	Matrix (int dim1,int dim2){//构造函数，无输入的构造函数 
		this->dim1=dim1;
		this->dim2=dim2;
		A = new double*[dim1+1];
		for(int i = 1; i <= dim1; i++){
			A[i] = new double[dim2+1];
		}
		Matrix::ALLSPACE+=dim1*dim2;
		printf("SPACE : %d\n",ALLSPACE);		
	}
	
	Matrix (const Matrix &C){//深拷贝 
		dim1=C.dim1;
		dim2=C.dim2;
		A = new double*[dim1+1];
		for(int i = 1; i <= dim1; i++){
			A[i] = new double[dim2+1];
		}
		for(int i = 1; i <= dim1; i++){
			for(int j = 1; j <= dim2; j++){
				A[i][j]=C.A[i][j];
			}
		}
		Matrix::ALLSPACE+=dim1*dim2;
		printf("SPACE : %d\n",ALLSPACE);
	}
	Matrix operator+(Matrix &B){//加法重载 
		printf("in\n");
		if(this->dim1!=B.dim1||this->dim2!=B.dim2){
			printf("加法矩阵的行宽不一致from Matrix + Matrix\n");
			return *this;
		} 
		Matrix C=Matrix(this->dim1,this->dim2);
		for(int i=1;i<=dim1;i++){
			for(int j=1;j<=dim2;j++){
				C.A[i][j]=this->A[i][j]+B.getElem(i,j);
			}
		}
		printf("before copy\n");
		return C;
	}
	Matrix operator-(Matrix &B){//减法重载 
		if(this->dim1!=B.dim1||this->dim2!=B.dim2){
			printf("减法矩阵的行宽不一致 from Matrix - Matrix\n");
			return *this;
		} 
		Matrix C=Matrix(this->dim1,this->dim2);
		for(int i=1;i<=dim1;i++){
			for(int j=1;j<=dim2;j++){
				C.A[i][j]=this->A[i][j]-B.getElem(i,j);
			}
		}
		return C;
	}
	Matrix operator*(Matrix &B){//乘法重载 
		if(this->dim2!=B.dim1){
			printf("乘法矩阵的行宽不一致 from Matrix*Matrix\n");
			return *this;
		} 
		Matrix C=Matrix(this->dim1,B.dim2);
		for(int i=1;i<=C.dim1;i++){
			for(int j=1;j<=C.dim2;j++){
				C.A[i][j]=0;
				for(int k=1;k<=B.dim1;k++)
				C.A[i][j]+=this->A[i][k]*B.A[k][j];
			}
		}
		return C;
	}
	
	Matrix operator*(double k){//数乘重载 
		Matrix C=Matrix(dim1,dim2);
		for(int i=1;i<=dim1;i++){
			for(int j=1;j<=dim2;j++){
				C.A[i][j]=k*A[i][j];
			}
		}
		return C;
	}
	
	Matrix operator=(Matrix &B){
		if(this->A!=NULL){
			this->release();
		}
		return B;
	}
	
	Matrix operator!(){//求逆 
		if(dim1!=dim2){
			printf("非方阵没有逆 from !Matrix\n");
			return *this;
		}
		double d=this->det();
		if(d==0){
			printf("不可逆矩阵 from !Matrix\n");
			return *this;
		}
		Matrix C=this->adjointM()*((double)1/d);
		return C;
	}
	Matrix T (){//转置 
		Matrix B(dim2,dim1);
		for(int i=1;i<=B.dim1;i++){
			for(int j=1;j<=B.dim2;j++){
				B.A[i][j]=A[j][i];
			}
		}
		return B;
	} 
	double det(){//求行列式 
		if(dim1!=dim2){
			printf("非方阵不可求行列式 from Matrix::det()\n");
			return 0;
		}
		if(dim1==1){
			return A[1][1];
		}
		else{
			double sum=0;
			for(int i=1;i<=dim1;i++){
				sum=sum+A[1][i]*sig(i)*this->delmn(1,i).det();
			}
			return sum;
		}
	}
	double algebraicCom(int i,int j){//求代数余子式 
		return sig(i,j)*this->delmn(i,j).det();
	} 
	Matrix adjointM(){//求伴随矩阵 
		if(dim1!=dim2){
			printf("非方阵不存在伴随矩阵 from Matrix::adjointM\n");
			return *this;
		}
		Matrix C(dim1,dim2);
		for(int i=1;i<=dim1;i++){
			for(int j=1;j<=dim2;j++){
				C.A[i][j]=this->algebraicCom(j,i);
			}
		}
		printf("伴随矩阵为:\n");
		C.print();
		return C;
	} 
	Matrix delmn(int m,int n){//删除矩阵的第m行，第n列 
		if(dim1-1==0||dim2-1==0){
			printf("删除后为空 from Matrix::delmn()\n");
			return *this;
		}
		Matrix C(dim1-1,dim2-1);
		int row=1;
		int col=1;
		for(int i=1;i<=dim1;i++){
			for(int j=1;j<=dim2;j++){
				if(i==m||j==n){
					continue;
				}
				C.A[row][col++]=A[i][j];
				if(col>dim2-1){
					col=1;
					row++;
				} 
			}
		}
		printf("删去第%d行和第%d列得到\n",m,n);
		C.print();
		return C;
	}
	Matrix getRow(int m){//提取矩阵的第m行，返回行向量 
		Matrix C(1,dim2);
		for(int i=1;i<=dim2;i++){
			C.A[1][i]=A[m][i];
		}
		//printf("第%d行为\n",m);
		C.print();
		return C;
	}
	Matrix getCol(int n){//提取矩阵的第n列，返回列向量 
		Matrix C(dim1,1);
		for(int i=1;i<=dim1;i++){
			C.A[i][1]=A[i][n];
			//printf("C[%d][%d]=A[%d][%d]=%lf\n",i,1,i,n,A[i][n]);
		}
		//printf("第%d列为\n",n);
		C.print();
		return C;
	}
	Matrix Merge(Matrix &B,int mode){//矩阵合并 
		if(mode==1){
			printf("纵向排列\n");
			if(dim2!=B.dim2){
				printf("维数不匹配 from Matrix::Merge()\n");
				return *this;
			} 
			Matrix C(dim1+B.dim1,dim2);
			for(int i=1;i<=dim1;i++){
				for(int j=1;j<=dim2;j++){
					C.A[i][j]=A[i][j];
				}
			}
			for(int i=1;i<=B.dim1;i++){
				for(int j=1;j<=dim2;j++){
					C.A[i+dim1][j]=B.A[i][j]; 
				}
			}
			printf("合并后:\n");
			C.print();
			return C;
		}
		else if(mode==2){
			printf("横向排列\n");
			if(dim1!=B.dim1){
				printf("维数不匹配 form Matrix::Merge()\n");
				return *this;
			}
			Matrix C(dim1,dim2+B.dim2);
			for(int i=1;i<=dim1;i++){
				for(int j=1;j<=dim2;j++){
					C.A[i][j]=A[i][j];
				}
			}
			for(int i=1;i<=dim1;i++){
				for(int j=1;j<=B.dim2;j++){
					C.A[i][j+dim2]=B.A[i][j];
				}
			}
			printf("合并后:\n");
			C.print();
			return C;
		}
		else{
			printf("没有这种操作 from Matrix::Merge()\n");
			return *this;
		}
	}
	double getElem(int i,int j){//得到矩阵的元素 
		return A[i][j];
	}
	int getDim1(){//得到矩阵的行数 
		return dim1;
	}
	int getDim2(){//得到矩阵的列数 
		return dim2;
	}
	void print(){//打印矩阵 
		for(int i = 1; i <= dim1; i++){
			for(int j = 1; j <= dim2; j++){
				printf("%lf ",A[i][j]);
			} 
			printf("\n");
		}
		printf("\n");
	}
	~Matrix (){//析构函数 
		if(A==NULL)
		return;
		for(int i = 1; i <= dim1; i++){
			delete []A[i]; 
		}	
		delete []A;
		A=NULL; 
		Matrix::ALLSPACE-=dim1*dim2;
		printf("SPACE : %d\n",ALLSPACE);
	}
	void release(){
		if(A==NULL)
		return;
		for(int i = 1; i <= dim1; i++){
			delete []A[i]; 
		}	
		delete []A;
		A=NULL; 
		Matrix::ALLSPACE-=dim1*dim2;
		printf("SPACE : %d\n",ALLSPACE);
	}
	int sig(int i){//符号函数 -1 的 i 次方 
		if(i%2){
			return 1;
		}
		else{
			return -1;
		}
	}
	int sig(int i,int j){//符号函数 代数余子式 
		if((i+j)%2){
			return -1;
		}
		else{
			return 1;
		}
	}
	
};
int Matrix::ALLSPACE = 0;

#endif 
