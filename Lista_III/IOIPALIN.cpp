#include <bits/stdc++.h>

#define MAX_STRING_SIZE 5001

#define max(A, B) (A > B ? A : B)

using namespace std;

char str1[MAX_STRING_SIZE];
char str2[MAX_STRING_SIZE];

int lcs_matrix_1[MAX_STRING_SIZE + 1] = { 0 };
int lcs_matrix_2[MAX_STRING_SIZE + 1] = { 0 };
int *lcs_previous_matrix;
int *lcs_actual_matrix;

int main(){
	int lcs;
	int size_str;

	scanf("%d", &size_str);
	scanf("%*c%s%*c", str1);
	int size_str1 = strlen(str1);
	int size_str2 = size_str1;

	for(int i = 0, j = size_str1 - 1; i < size_str1; i++, j--){
		str2[j] = str1[i];
	}

	int z;

	for(int i = 1; i <= size_str1; i++){
		if(i % 2){
			lcs_previous_matrix = lcs_matrix_1;
			lcs_actual_matrix = lcs_matrix_2;
		}
		else{
			lcs_previous_matrix = lcs_matrix_2;
			lcs_actual_matrix = lcs_matrix_1;	
		}

		for(int j = 1; j <= size_str2; j++){
			if(str1[i - 1] == str2[j - 1]){
				lcs_actual_matrix[j] = lcs_previous_matrix[j - 1] + 1;
			}
			else{
				lcs_actual_matrix[j] = max(	lcs_previous_matrix[j],
											lcs_actual_matrix[j - 1]);
			}
		}
	}

	lcs = lcs_actual_matrix[size_str2];

	printf("%d\n", (size_str - lcs));

	return EXIT_SUCCESS;
}