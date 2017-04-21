#include <bits/stdc++.h>

#define MAX_STRING_SIZE 2001

#define max(A, B) (A > B ? A : B)
#define min(A, B) (A < B ? A : B)

#define delete_char(MATRIX, A, B) (MATRIX[A - 1][B])
#define insert_char(MATRIX, A, B) (MATRIX[A][B - 1])
#define modify_char(MATRIX, A, B) (MATRIX[A - 1][B - 1])

using namespace std;

char str1[MAX_STRING_SIZE];
char str2[MAX_STRING_SIZE];

int edit_distance[MAX_STRING_SIZE + 1][MAX_STRING_SIZE + 1] = {{ 0 }};

int main(){
	int minimum_edit_distance;

	int n;

	scanf("%d%*c", &n);

	for(int t = 0; t < n; t++){
		scanf("%s%*c", str1);
		scanf("%s%*c", str2);

		int size_str1 = strlen(str1);
		int size_str2 = strlen(str2);

		int max_str_size = max(size_str1, size_str2);

		for(int i = 0; i <= max_str_size; i++){
			if(i <= size_str1){
				edit_distance[i][0] = i;
			}
			if(i <= size_str2){
				edit_distance[0][i] = i;
			}
		}

		for(int i = 1; i <= size_str1; i++){
			for(int j = 1; j <= size_str2; j++){
				if(str1[i - 1] == str2[j - 1]){
					edit_distance[i][j] = edit_distance[i - 1][j - 1];
				}
				else{
					edit_distance[i][j] = 1 + min(	min(delete_char(edit_distance, i, j),
														insert_char(edit_distance, i, j)),
													modify_char(edit_distance, i, j));
				}
			}
		}

#ifdef DEBUG
		printf("%s:%s\n", str1, str2);
		printf("%6c", ' ');
		for(int i = 0; i < size_str2; i++){
			printf("%3c", str2[i]);
		}
		printf("\n");
		for(int i = 0; i <= size_str1; i++){
			printf("%3c", (i == 0 ? ' ' : str1[i - 1]));
			for(int j = 0; j <= size_str2; j++){
				printf("%3d", edit_distance[i][j]);
			}
			printf("\n");
		}
#endif

		minimum_edit_distance = edit_distance[size_str1][size_str2];

		printf("%d\n", minimum_edit_distance);
	}

	return EXIT_SUCCESS;
}