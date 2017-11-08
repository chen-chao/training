#include <stdio.h>

main(){
	float celsius, fahr, lower, upper, step;

	lower = -100;
	upper = 100;
	step = 20;

	printf("Table of Celsius to Fahr\n");
	celsius = lower;
	while (celsius <= upper){
		fahr = 9./5.*celsius+32;
		printf("%5.1f\t%5.1f\n", celsius, fahr);
		celsius = celsius+step;	
	}

}
