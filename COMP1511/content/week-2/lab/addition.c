// Addition
// Addition.c
//
// This program was written by Lucas Cheung (z5763342)
// on date
//
// Add two numbers and print the output

#include <stdio.h>

int main(void) {
	int students;
	int tutors;

	printf("Please enter the number of students and tutors: ");
	scanf("%d %d", &students, &tutors);

	int sum = students + tutors;
	printf("%d + %d = %d\n", students, tutors, sum);

	return 0;
}
