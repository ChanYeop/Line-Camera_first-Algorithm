#include <stdio.h>

#define MAX_SIZE 128*2

int heap[MAX_SIZE][2];
int result[MAX_SIZE][2];
int arr[MAX_SIZE];
int arr0[MAX_SIZE];
int arr2[MAX_SIZE][2];
int real[4];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(int value, int index)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[heapSize][0] = value;
	heap[heapSize][1] = index;

	int current = heapSize;
	while (current > 0 && heap[current][0] < heap[(current - 1) / 2][0])
	{
		int temp = heap[(current - 1) / 2][0];
		int temp1 = heap[(current - 1) / 2][1];
		heap[(current - 1) / 2][0] = heap[current][0];
		heap[(current - 1) / 2][1] = heap[current][1];
		heap[current][0] = temp;
		heap[current][1] = temp1;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int heapPop(int *value , int *index)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0][0];
	*index = heap[0][1];
	heapSize = heapSize - 1;

	heap[0][0] = heap[heapSize][0];
	heap[0][1] = heap[heapSize][1];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1][0] < heap[current * 2 + 2][0] ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current][0] < heap[child][0])
		{
			break;
		}

		int temp = heap[current][0];
		int temp1 = heap[current][1];
		heap[current][0] = heap[child][0];
		heap[current][1] = heap[child][1];
		heap[child][0] = temp;
		heap[child][1] = temp1;

		current = child;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	int T, N;
	int j = 1;
	int check = 0;

	scanf_s("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		int k = 0;
		scanf_s("%d", &N);

		heapInit();

		for (int i = 0; i < N; i++)
		{
			int value;
			scanf_s("%d", &value);
			heapPush(value, i+1);
			arr[i] = value;
		}

		for (int i = 0; i < N; i++)
		{
			int value;
			scanf_s("%d", &value);
			heapPush(value, i + 128);
			arr[i+128] = value;
		}

		/*
		printf("#%d ", test_case);

		for (int i = 0; i < 10; i++) {
			//printf("value: %d\n", heap[i][0]);
			printf("index: %d\n", heap[i][1]);
		}

		int first = heap[0][1];

		for (int i = 1; i < 10; i++) {
			if (heap[i][1] - first >= 5) {
				printf("line is %d\n", heap[i][1]);
			}
		} // 모터 부분인데 어떠한코드를 넣어야될지 감이 안잡히므로 일단 printf로 대체해둠
		*/
		for (int i = 0; i < N*2; i++)
		{
			int value;
			int index;
			heapPop(&value, &index);
			if (arr[index + 1] <= 1600 && arr[index + 2] <= 1600) {
				result[k][0] = value;
				result[k][1] = index;
				k++;
			}

			//printf("%d\n index : %d\n", value, index);
		}

		int j = 0;

		for (int i = 0; i < 128*2; i++) {
			if (arr[i] <= 1600) {
				arr2[j][0]++;
				arr2[j][1] = i;
				check = 1;
			}
			else if (arr[i] > 1500 && check == 1) {
				check = 0;
				j++;
			}
		} // 값 중에 검은선 찾기

		int first = result[0][1];
		printf("%d\n", first);
		printf("%d\n", result[0][1]);
		int cnt = 0;

		for (int i = 1; i < 128*2; i++) {
			if (cnt == 10) {
				break;
			}
			if (result[i][1] - first >= 5 || result[i][1] - first <=-5) {
				arr0[cnt] = result[i][1];
				cnt++;
				first = result[i][1];
			}
		}// 라인의 대략적인 거리 찾기

		/*
		for (int i = 0; i < 10; i++) {
			printf("%d\n", arr2[i][0]);
			printf("line line : %d\n", arr0[i]);
			printf("%d\n", arr2[i][1]);
		}
		*/

		int re = 0;

		for (int i = 0; i < 10; i++) {
			if (re == 3)
				break;
			for (int y = 0; y < 10; y++) {
				if ((arr2[i][1] - arr2[i][0] + 1) == arr0[y]) {
					real[re] = arr0[y];
					re++;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (real[i] == 0) {
				continue;
			}
			else if (real[i] < 128) {
				printf("scanner 2 : %d\n", real[i]);
			}
			else {
				printf("scanner 1 : %d\n", real[i] - 128);
			}
		}
	}
	return 0;
}