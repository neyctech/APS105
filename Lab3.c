/* Name : Guozhen Ding (1005760749)
 * Lab Submission for APS105H1
 * Input : The letter represent the color of the resistant (8 letters)
 * Output : The color (in words) of the resistance and the resistance's value and tolorance \
 * 		and the correct series and parallel connect value of the resistance 
 * Assumption : All the input from the user is a char one time but may be not vaild char
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
double value1 = 0;	
double value2 = 0;
char band1[4] = {0,};
char band2[4] = {0,};
struct {
	char name[10];
	char tolerance[15];
}colors[13];													//create the storage struct of the names and tolerances 
const double eps = 1e-5; 										// infinite small value 

//------ function for find a char and return its related value, and report it errors-----//
int find_value(const char input, int _type, int _num){
	char index[13]="kbroeguvywls";
	int ret ;
	for ( ret = 0; ret < 12; ret++){
		if ( index[ret] == input || index[ret] == input + 32 ){
			break;
		}
	}
	if (_type == 1 && (ret == 12 || ret >9)){
		printf("\nInvalid colour for the 1st band of resistor %d. Exiting the program...\n",_num);
		exit(0);
	}
	if (_type == 2 && (ret == 12 || ret>9)){
		printf("\nInvalid colour for the 2nd band of resistor %d. Exiting the program...\n",_num);
		exit(0);
	}
	if (_type == 3&& !_num && (ret >= 8)){
		if (ret == 10) return -1;
		if (ret == 11) return -2;
		printf("\nInvalid colour for the multiplier band of resistor %d. Exiting the program...\n",_num);
		exit(0);
	}
	if (_type == 4 && (ret == 12 || ret==3 || ret==4 || ret==9) ){
		printf("\nInvalid colour for the tolerance band of resistor %d. Exiting the program...\n",_num);
		exit(0);
	}
	return ret ;
}
//----- function for process the value and print in the correct units -----// 
int val_proc(double value){	
	if (log10(value) >= 6.0-eps){
		value *= 1e-6;
		printf("%.2lf MOhms ",(double)value);
	} else if (log10(value) >= 3.0-eps ){
		value *= 1e-3;
		printf("%.2lf KOhms ",(double)value);
	}else {
		printf("%.2lf Ohms ",(double)value);
	}
	return 0;
}

int main(int argc, char const *argv[]){
	strcpy(colors[0].name,"Black");												// init all the variables according to the given table
	strcpy(colors[1].name,"Brown");
	strcpy(colors[1].tolerance,"+/- 1.00%");
	strcpy(colors[2].name,"Red");
	strcpy(colors[2].tolerance,"+/- 2.00%");
	strcpy(colors[3].name,"Orange");
	strcpy(colors[4].name,"Yellow");
	strcpy(colors[5].name,"Green");
	strcpy(colors[5].tolerance,"+/- 0.50%");
	strcpy(colors[6].name,"Blue");
	strcpy(colors[6].tolerance,"+/- 0.25%");
	strcpy(colors[7].name,"Violet");
	strcpy(colors[7].tolerance,"+/- 0.10%");
	strcpy(colors[8].name,"Grey");
	strcpy(colors[8].tolerance,"+/- 0.05%");
	strcpy(colors[9].name,"White");
	strcpy(colors[10].name,"Gold");
	strcpy(colors[10].tolerance,"+/- 5.00%");
	strcpy(colors[11].name,"Silver");
	strcpy(colors[11].tolerance,"+/- 10.00%");
	
	printf("Please enter the 1st band of resistor 1: \n");						//guide the user input 8 digit color and remove the extra '\n'
	scanf("%c",&band1[0]);getchar();
	printf("Please enter the 2nd band of resistor 1: \n");
	scanf("%c",&band1[1]);getchar();
	printf("Please enter the multiplier band of resistor 1:\n");
	scanf("%c",&band1[2]);getchar();
	printf("Please enter the tolerance band of resistor 1:\n");
	scanf("%c",&band1[3]);getchar();
	printf("Please enter the 1st band of resistor 2: \n");
	scanf("%c",&band2[0]);getchar();
	printf("Please enter the 2nd band of resistor 2: \n");
	scanf("%c",&band2[1]);getchar();
	printf("Please enter the multiplier band of resistor 2: \n");
	scanf("%c",&band2[2]);getchar();
	printf("Please enter the tolerance band of resistor 2: \n" );
	scanf("%c",&band2[3]);getchar();
	
	value1 = 10*find_value(band1[0],0,0)+find_value(band1[1],0,0);						//calc the values and check the vaildity of the input 
	value1 *= pow(10,find_value(band1[2],3,0));
	value2 = 10*find_value(band2[0],0,0)+find_value(band2[1],0,0);
	value2 *= pow(10,find_value(band2[2],3,0));
	
	printf("Colour bands for resistor 1: \n");									//give out the colors 
	printf("%s ",colors[find_value(band1[0],1,1)].name);
	printf("%s ",colors[find_value(band1[1],2,1)].name);
	printf("%s ",colors[find_value(band1[2],3,1)].name);
	printf("%s\n",colors[find_value(band1[3],4,1)].name);
	printf("Colour bands for resistor 2: \n");
	printf("%s ",colors[find_value(band2[0],1,2)].name);
	printf("%s ",colors[find_value(band2[1],2,2)].name);
	printf("%s ",colors[find_value(band2[2],3,2)].name);
	printf("%s\n",colors[find_value(band2[3],4,2)].name);
																					//do calc for the second part and output the answer
	printf("Value in ohms of resistor 1: " );val_proc((double)value1);printf("%s\n", colors[find_value(band1[3],0,0)].tolerance);
	printf("Value in ohms of resistor 2: " );val_proc((double)value2);printf("%s\n", colors[find_value(band2[3],0,0)].tolerance);
	printf("The Equivalent in series is ");val_proc(value1+value2); printf("\n");
	printf("The Equivalent in parallel is ");val_proc( value1+value2 ? (double)value1*value2/(double)(value2+value1) : 0 );printf("\n");
	return 0;
}
