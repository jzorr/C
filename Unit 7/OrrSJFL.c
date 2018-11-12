/*
* OrrSJFT.c
* John Z. Orr
* Sorts the jobs from smallest to largest
* Then applies algorithm to perform this task in a fixed and live environment
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

// create a struct I can use for each process
typedef struct process
{
    int id;
    int tau;
    float alpha;
    int times[MAXCHAR];
} process;

int findWaitingTime(int wt2[], int n){
    //wt2[0] = 0;
    int total = 0;
    for(int i = 0; i < n; i++)
        total += wt2[i];
    return total;
}

int main()
{
    FILE *file; // create a new FILE var
    char str[MAXCHAR]; // make string of size MAXCHAR
    char* fileName = "/home/zac/Desktop/SER-334/Unit 7/data2.txt"; // var fileName to hold address of the .txt file to be opened
    //char* fileName = "/home/john/Desktop/Unit7/data1.txt"; // file location on VirtualBox
    int count = 0, ticks = 0, pCount = 0, tau = 0, start_of_process, turn_time = 0, wait_time = 0;
    float alpha = 0;
    
   
    file = fopen(fileName, "r"); // define the value of file
    // if the file is not available, print the following
    if(file == NULL)
    {
        printf("Could not open the file %s", fileName);
        return 1;
    }
   
    int countArray[MAXCHAR]; //create array of size MAXCAHR
    int j = 0;
   
    //print every line within the txt file, store and print it as an int, and increment the count of lines
    while(fgets(str, MAXCHAR, file) != NULL)
    {
        //printf("%s", str); // print each line as a str
        int i; // create int var
        // convert the strings in to integers
        i = atoi(str); // convert the str to an int
        //printf("The value of the entered is: %d.\n", i); // print the new int value
        countArray[j] = i; // store the value of each line into an int array for future use.
       
        count++; // increment count
        j++; // increment j
    }
   
    //test print
    printf("The total number of rows in the file is %d\n", count); //print the line count -1 to account for the \n from the string
   
    ticks = countArray[0];
    printf("# of ticks = %d\n", ticks);
   
    pCount = countArray[1];
    printf("# of processes = %d\n", pCount);
    if(pCount == 0)
        return 1;
 
// create struct process array of size: pCount
    process pro_array[pCount];
    int a = 0, b, c, d;
    b = ticks + 3;
   
    pro_array[a].id = countArray[2];
    pro_array[a].tau = countArray[3];
    pro_array[a].alpha = countArray[4];
    for(c = 0; c < ticks; c++){
        pro_array[a].times[c] = countArray[5 + c];
    }

    for(a = 1; a < pCount; a++){
        pro_array[a].id = countArray[(b*a) + 2];
        pro_array[a].tau = countArray[(b*a) + 3];
        pro_array[a].alpha = countArray[(b*a) + 4];
        for(d = 0; d < ticks; d++){
            pro_array[a].times[d] = countArray[(b*a) + 5 + d];
        }
    }
   
    // test print
    int q, r;
    for(q = 0; q < pCount; q++)
    {
            for(r = 0; r < ticks; r++){
                printf("pro_array[%d].times[%d] = %d\n", q, r, pro_array[q].times[r]);
            }
            printf("\n");
    }

    //start the SJF non-live -----------------------------------------------------------------------------------------
    printf("== Shortest Job First ==\n");
    int m, tickTotal = 0;
    int sub_array[pCount][ticks];
    start_of_process = 0;
    int wt[ticks];
    wt[0] = 0;
    for(m = 0; m < ticks; m++)
    {
        //TODO - set the value of the sum of the previous iterations = start_of_process
        
        
        
        //TODO - implement the display of the two processes compare and sort
        printf("Simulating %dth tick of process @ time %d: \n", (m % ticks), start_of_process);
        
        //TODO - store each process tick and its length, then compare the lengths to display
        
        //create sub_arrays for each tick with the number of processes
        // i.e. - if we have three processes (0,1,2) sub_array[0] will have pro 1, pro2, pro 3 for 0th tick
        
        int e, f, g, value = 0; // working
        for(e = 0; e < pCount; e++){
            sub_array[e][m] = pro_array[e].times[m];
            // unsorted printing
            printf("Unsorted - Process %d took %d. \n", e, sub_array[e][m]);
        }

   
        
        //sort the sub_arrays in ascending but maintain process # integrety
        int a1, i1, i2, h, sum; //count1 = 0,
        for (i1 = 0; i1 < pCount; ++i1) 
        {   
            for (i2 = i1 + 1; i2 < pCount; ++i2)
            {
                //int count1 = 0, count2 = 0;
                if (sub_array[i1][m] > sub_array[i2][m]) //if there needs to be a switch
                {
                    a1 =  sub_array[i1][m];
                    sub_array[i1][m] = sub_array[i2][m];
                    sub_array[i2][m] = a1;
                    
                    //count1++;
                    //printf("Sorted - Process %d took %d. \n", i1, sub_array[i1][m]); // working 
                    //value = sub_array[i1];
                }
                else{ //if there is not switch needed
                    //printf("Sorted - Process %d took %d. \n", i1, sub_array[i1][m]); // working
                    //count2++;
                    //value = sub_array[i1];
                }
                value = sub_array[i1][m];
                //printf("Sorted - Process %d took %d. \n", i1, sub_array[i2][m]); // print the remaining processes in descending order
                //wt[i2] = value;
            }
            tickTotal += sub_array[i1][m];
            start_of_process += sub_array[i1][m];
            //printf("Sorted - Process %d took %d. \n", i2, sub_array[i2][m]); // print the remaining processes in descending order

        }
        tickTotal += value;    
        wt[m] = value;
        //printf("Sorted - Process %d took %d. \n", i1, sub_array[i2][m]); // print the remaining processes in descending order
        // print 2d array
//         int p1, p2, p3;
//         for(p1 = 0; p1 < pCount; p1++){
//             for(p2 = 0; p2 < pCount; p2++){
//                 //sub_array[p1][p2] = '.';
//                 printf(" %d ", sub_array[p1][p2]);
//                 printf("\n");
//             }
// 
//         }
                
    }
    turn_time = tickTotal;
    //turn_time = start_of_process/ticks; 
    printf("Turnaround time: %d \n", turn_time);
    
    //waiting time
    int wt1, wt_total = 0;
    wt_total = findWaitingTime(wt, ticks);
    printf("Waiting time: %d \n", wt_total);



    fclose(file); // close the file from reading
    return 0;

}