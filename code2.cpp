//Author Akshaya CMPE:209

# include <stdint.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <fstream>


using namespace std;

void convertDectoHex(char output[],int ip_addr[]) {
	FILE *myfile;
   
   
	myfile = fopen("testRandomization.txt", "a");	
	// converting hexadecimal IP address into user readable format.
	
	int i,newArr[6],k,ctr;
	for ( i=0; i<6; i++) {
		newArr[i] = 0;
		switch(output[i]) {
			case 'A': newArr[i]=10;
					  break;
			case 'B': newArr[i]=11;
					  break;
			case 'C': newArr[i]=12;
					  break;
			case 'D': newArr[i]=13;
					  break;
			case 'E': newArr[i]=14;
					  break;
			case 'F': newArr[i]=15;
					  break;
			default: newArr[i] = int(output[i])-48;
		}
	}
    
	// 000001 will be take as 000001
	// now we will get 00001 as  0 0 0 0 0 1 as int array newArr.
	// we will now obtain the 4 bit binary representation of each of the 6 elements of array (each 4 bit i.e 6x4 = 24 bits).
	int j=3;
	ctr = j;
   
	for (i=0; i<6; i++) {
		for (k=0; k<4; k++) {
		 ip_addr[j] = newArr[i] %2;
		 newArr[i] /= 2;
		 j--;
		 ctr++;
		}
		j=ctr;
	}
	i=0;
	int arr[3];
	// now the reverse, i.e grouping into 8 bits each = 3 groups so as to form an ip address = 0.0.1
	fprintf(myfile,"11");
	for (k=0;k<1; k++) {
		 ctr = 128;
		 arr[k] = 0;
		for (int j=0; j<8; j++) {
			arr[k] += ip_addr[i]*ctr;
			ctr /=2;
			i++;
		}
         printf(".%d",arr[k]);
        //ping here
		   // remove this comment --> this will print the IP address. If you could pause the randomization
		// output for 1 min here then we could see if the flow rules are getting modified.
		//fprintf(myfile,".%d",arr[k]);
         //printf(".%d",arr[k]);
	}
   
	//fprintf(myfile,"\n");
}
int main(void)
{
    uint64_t start_state = 0x05;  /* Any nonzero start state will work. */
    uint64_t lfsr = start_state;
    int ip_addr[24];
    char output[6];
    unsigned long int period = 0;
    clock_t begin, end;
    double time_spent;	
	int clockCycle=0;
    begin = clock();

    do{
    do
    {
        unsigned lsb = lfsr & 1;  /* Get LSB (i.e., the output bit). */
        lfsr >>= 1;               /* Shift register */
        if (lsb == 1)             /* Only apply toggle mask if output bit is 1. */
            lfsr ^= 0x40u;      /* Apply toggle mask, value has 1 at bits corresponding
                                   * to taps, 0 elsewhere. */
		sprintf(output,"%X",lfsr);
		//printf("%X \n", lfsr);
    	convertDectoHex(output,ip_addr);       // conversion as in printing out the output. output holds the hex value of lfsr variable.                            
        ++period;
    } while (lfsr != start_state && period != 1); // remove period conditio for full operation
    //printf(" period cycle %d : %lu \n",clockCycle+1,period);
    period =0;
    clockCycle ++;
    }
    while(clockCycle != 1);
    end = clock();
    time_spent = (double)(end - begin);
    //printf("\n the time taken %lf",time_spent);
    return 0;
}
