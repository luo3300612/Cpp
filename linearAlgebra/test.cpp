#include "Matrix_Vector.h"
#include <stdio.h>
int main(){
	/*
	Matrix A=Matrix(); 
	Matrix B=Matrix();
	A.print();
	B.print();
	A.Merge(B,2);
	//B.adjointM().det();
	printf("逆矩阵为\n");
	(!B).print();
	printf("乘积为\n");
	Matrix C=!B;
	
	(C*B).print();
	B.getRow(2);
	B.getCol(3);
	B.release();
	*/
	/* 
	B.T().print();
	Matrix D=Matrix();
	D.print();
	D.T().print();
	
	Matrix C=B.T()*D;
	C.print();*/

	Matrix A=Matrix();
	Matrix B=A.getRow(1);
	B.print();
	printf("析构前\n");
} 


/*
2 3
1 2 3
4 5 6

2 4
1 2 3 4
5 6 7 9

A+-B
3 3
1 2 3
4 5 6
7 8 9
3 3
3 2 1
6 5 4
9 8 7
*/