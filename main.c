#define _CRT_SECURE_NO_WARNINGS
#define true 1
#define false 0
#define and &&
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define R 10000
#define M 100000

////////////////////////////// GET_A //////////////////////////////////////////

//1)find dels of number m 2)simple or not 3)number a-1 divided into a simple divisor m 
//1)
int delitel(int m, int* dels) {
	int cnt = 0;
	double rad_m = sqrt(m);
	for (int i = 2; i < rad_m; i++) {
		if (i * i == m) {
			if (isPrime(i) == 1) {
				dels[cnt] = i;
				cnt++;
			}
		}
		else if (m % i == 0) {
			if (isPrime(i) == 1) {
				dels[cnt] = i;
				cnt++;
			}
			if (isPrime(m / i) == 1) {
				dels[cnt] = m / i;
				cnt++;
			}
		}
	}
	return cnt;

}
//2)
int isPrime(int i) {
	for (int q = 2; q * q <= i; q++) {
		if (i % q == 0) {
			return false;
		}
	}
	return true;
}
//3) and check divided or not a number by 4 and a < m 
int a_del(int dels[], int m, int* a, int cnt) {
	int tmp = 0;
	for (int a1 = 2; a1 < m; a1++) {
		for (int i = 0; i < cnt; i++) {
			if (dels[i] != 0 && (a1 - 1) % dels[i] == 0) {
				if (m % 4 == 0) {
					if ((a1 - 1) % 4 == 0 && a1 != 0) {
						a[tmp] = a1;
						return;
					}
				}
			}
		}
	}
}
/////////////////////////////  GET_A //////////////////////////////////////

////////////////////////////      GET_C     ////////////////////////////////////////////////////////////
int Nod(int a, int b)
{
	while (a && b)
		if (a >= b)
			a -= b;
		else
			b -= a;
	return a | b;
}

int get_c(int cmin, int cmax, int m, int* c) {
	int cnt = 0;
	for (int i = cmin; i < cmax && i < m; i++) {
		int nod = Nod(i, m);
		if (nod == 1) {
			c[cnt] = i;
			cnt++;
		}
	}
	return cnt;
}
////////////////////////////      GET_C     ////////////////////////////////////////////////////////////

/////////////////////////////////Gluing numbers to numbers///////////////////////////////////////////////////////////////////////////
int gluing(char* c) {
	int i = 0;
	int res = 0;
	while (c[i] != '\0') {
		res = res * 10 + (c[i] - '0');
		++i;
	}
	return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


int lcg(int x0, int m, int n, int a, int c, int* x) {
	//   x(n) = (x(n-1) * a + c)mod m   //
	int cnt = 0;
	if (0 <= a <= 18446744073709551615 && 0 <= x0 <= 18446744073709551615 &&
		0 <= c <= 18446744073709551615 && 0 <= m <= 18446744073709551615 &&
		0 < n <= 18446744073709551615 && a < m && c < m && x0 < m) {

		x[0] = x0;

		for (int i = 1; i <= n; i++) {
			x[i] = (x[i - 1] * a + c) % m;
			cnt++;
		}
	}
	return cnt;
}



int main() {

	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");

	char* string = (char*)malloc(sizeof(char) * R);
	fgets(string, R, input);


	while (*(string) == ' ') {
		++string;
	}
	/////////////////////  get_c  //////////////////////////////////////////////////////////////////////////////////////
	if (strstr(string, "get_c") != 0) {
		char cmin[R] = { '\0' }, cmax[R] = { '\0' }, m[M] = { '\0' };
		int cmin1 = 0, cmax1 = 0, m1 = 0;
		for (int i = 0; string[i] != '\0'; i++) {
			if (string[i] == ' ')
				continue;
			else if (string[i] == 'n' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					cmin[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == 'm' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					m[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == 'x' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					cmax[j] = string[i];
					i++;
					j++;
				}
			}
		}
		if (cmin[0] == '\0' || cmax[0] == '\0' || m[0] == '\0') {
			fprintf(output, "incorrect command");
		}
		else {

			cmin1 = gluing(cmin);
			cmax1 = gluing(cmax);
			m1 = gluing(m);
			int c[R] = { 0 };
			int cnt = get_c(cmin1, cmax1, m1, c);
			for (int i = 0; i < cnt; i++) {
				fprintf(output, "%d\n", c[i]);
			}
		}
	}

	////////////////////   get_a   ////////////////////////////////////////////////////////////////////////
	else if (strstr(string, "get_a") != 0) {
		char m[M] = { '\0' };
		int m1 = 0;
		for (int i = 0;string[i] != '\0'; i++) {
			if (string[i] == ' ') {
				continue;
			}
			else if (string[i] == 'm' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					m[j] = string[i];
					i++;
					j++;
				}
				break;
			}
		}
		if (m[0] == '\0') {
			fprintf(output, "incorrect command");
		}
		else {
			m1 = gluing(m);
			int a2[R] = { 0 };
			int dels[R] = { 0 };

			int count = delitel(m1, dels);
			a_del(dels, m1, a2, count);
			if (a2[0] == 0) {
				fprintf(output, "no solution\n");
			}
			else {
				int* a = (int*)malloc(sizeof(int) * R);
				a[0] = 0;

				int cnt = 0;
				for (int i = 0; i < R; i++) {
					if (a2[i] != 0) {
						a[cnt] = a2[i];
						fprintf(output, "%d\n", a[cnt]);
						cnt++;
					}
					else {
						if (cnt != 0 and a2[i] == 0) {
							break;
						}
						else {
							fprintf(output, "No solution\n");
						}
					}
				}
				free(a);
			}
		}
	}
	/////////////////////////  lcg  ///////////////////////////////
	else if (strstr(string, "lcg") != 0) {

		char n[R] = { '\0' }, x0[R] = { '\0' },
			c[R] = { '\0' }, a[R] = { '\0' }, m[R] = { '\0' };
		int n1 = 0, x01 = 0, c1 = 0, a1 = 0, m1 = 0;

		for (int i = 0;string[i] != '\0'; i++) {

			if (string[i] == ' ')
				continue;
			else if (string[i] == 'n' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					n[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == '0' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					x0[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == 'm' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					m[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == 'a' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					a[j] = string[i];
					i++;
					j++;
				}
			}
			else if (string[i] == 'c' && string[i + 1] == '=') {
				i += 2;
				int j = 0;
				while (string[i] != ' ' && string[i] != '\n') {
					c[j] = string[i];
					i++;
					j++;
				}
			}
		}
		if (c[0] == '\0' || a[0] == '\0' || m[0] == '\0' ||
			x0[0] == '\0' || n[0] == '\0') {
			fprintf(output, "incorrect command");
		}
		else {
			c1 = gluing(c);
			a1 = gluing(a);
			n1 = gluing(n);
			x01 = gluing(x0);
			m1 = gluing(m);
			int x[R] = { 0 };
			int cnt = lcg(x01, m1, n1, a1, c1, x);
			if (cnt == 0) {
				fprintf(output, "no solution");
			}
			else {
				for (int i = 0; i < cnt; i++) {
					fprintf(output, "%d\n", x[i]);
				}
			}

		}
	}


	free(string);
	fclose(input);
	return 0;
}