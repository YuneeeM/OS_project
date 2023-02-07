/* Banker's Algorithm 
* 자원의 갯수(자원 사이에 공백이 존재)
* (빈줄: 자원의 갯수와 Allocation 행렬 구분)
* Allocation: 프로세스 별 할당 자원 (자원 사이에 공백이 존재)
* (빈줄: Allocation과 Max 행렬 구분)
* Max: 프로세스 별 최대 자원 요청 갯수(자원 사이에 공백 존재)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define M 3

FILE* f;

int i, j, k;

void read_resource(int G[], int n)
{
	for (i = 0; i < n; i++)
	{
		fscanf(f, "%d", &G[i]);
	}
}

void read_matrix(int G[][3], int n, int m)
{
	for (i = 0; i < n; i++)
	{
		for ( j = 0; j < m; j++)
		{
			fscanf(f, "%d", &G[i][j]);
		}
	}
}

int main()
{
	//각 종류별로 가용한 자원의 개수를 나타내는 벡터로 크기 3
	int Available[M];
	//각 스레드가 최대로 필요로 하는 자원의 개수를 나타내는 행렬 5x3
	int Max[N][M];
	//각 스레드에 현재 할당된 자원의 개수를 나타내는 행렬 5x3
	int Allocation[N][M];
	//각 스레드가 향후 요청할 수 있는 자원의 개수를 나타내는 행렬 5x3
	int Need[N][M];
	//안정성 알고리즘에서 사용하는 안정상태 검증 변수
	int Finish[N];


	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("파일이 열리지 않습니다.\n");
		exit(1);
	}
	
	read_resource(Available, M);
	read_matrix(Allocation, N, M);
	read_matrix(Max, N, M);


	//안전성 알고리즘 (Work는 Available과 동일하므로 따로 설정하지 않음)
	int value[N], num = 0;

	for (i = 0; i < N; i++) {
		Finish[i] = 0;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	}

	//두 조건을 만족하라 a.Finish[i]==false, b.Need<=Work
	for (k = 0; k < N; k++) {
		for (i = 0; i < N; i++) {
			if (Finish[i] == 0) {

				int flag = 0;

				for (j = 0; j < M; j++) {

					if (Need[i][j] > Available[j]) {
						flag = 1;
						break;
					}
				}

				if (flag == 0) {
					value[num++] = i;
					for (int x = 0; x < M; x++)
						Available[x] += Allocation[i][x];
					Finish[i] = 1;
				}
			}
		}
	}

	int flag = 1;

	for (i = 0; i < N; i++)
	{
		if (Finish[i] == 0)
		{
			flag = 0;
			printf(">>>>>>>>>>>이 시스템은 불안정 상태입니다<<<<<<<<<<<<<<");
			break;
		}
	}

	if (flag == 1)
	{
		printf("이 시스템은 안전합니다!\n<");
		for (i = 0; i < N - 1; i++)
			printf(" T%d, ", value[i]);
		printf(" T%d >", value[N - 1]);
	}
	 

	fclose(f);
	return 0;

}
