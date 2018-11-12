/*
* OrrSJFT.c
* John Z. Orr
* Sorts the jobs from smallest to largest
* Then applies algorithm to perform this task in a fixed and live environment
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100


float MAXCHAR1 = 100;


// create a struct I can use for each process
typedef struct process
{
    int id;
    int tau;
    float alpha;
    int times[MAXCHAR];
} process;

int findWaitingTime(int wt2[], int n)
{
    int total = 0;
    for(int i = 0; i < n; i++)
        total += wt2[i];
    return total;
}

int main()
{
    FILE *file; // create a new FILE var
    char str[MAXCHAR]; // make string of size MAXCHAR
    //char* fileName = "/home/zac/Desktop/SER-334/Unit 7/data1.txt"; // var fileName to hold address of the .txt file to be opened
    char* fileName = "/home/john/Desktop/Unit7/data1.txt"; // file location on VirtualBox
    int count = 0, ticks = 0, pCount = 0, start_of_process, turn_time = 0, wait_time = 0;
    
    file = fopen(fileName, "r"); // define the value of file
    
    // if the file is not available, print the following
    if(file == NULL)
    {
        printf("Could not open the file %s", fileName);
        return 1;
    }
   
    float countArray[MAXCHAR]; //create array of size MAXCAHR
    int j = 0;
   
    //print every line within the txt file, store and print it as an int, and increment the count of lines
    while(fgets(str, MAXCHAR1, file) != NULL)
    {
       
        float i; // create int var: int
        // convert the strings in to integers
        i = strtof(str, NULL); // convert the str to an int atoi()
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
    pro_array[a].tau = (float)countArray[3];
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
        printf("tau = %d, alpha = %f\n", pro_array[q].tau, pro_array[q].alpha);
        for(r = 0; r < ticks; r++)
            printf("pro_array[%d].times[%d] = %d\n", q, r, pro_array[q].times[r]);
        
        printf("\n");
    }

//----------------------------------------------- SJF non-Live -------------------------------------------------------
    printf("== Shortest Job First ==\n");
    int m, tickTotal = 0;
    int sub_array[pCount][ticks];
    start_of_process = 0;
    int wt[ticks];
    wt[0] = 0;
    for(m = 0; m < ticks; m++)
    {
        
        // - implement the display of the two processes compare and sort
        printf("Simulating %dth tick of process @ time %d: \n", (m % ticks), start_of_process);
        
        //create sub_arrays for each tick with the number of processes
        // i.e. - if we have three processes (0,1,2) sub_array[0] will have pro 1, pro2, pro 3 for 0th tick
        
        int e, f, g, value = 0;
        for(e = 0; e < pCount; e++){
            sub_array[e][m] = pro_array[e].times[m];
            
            // unsorted printing
            printf("Unsorted - Process %d took %d. \n", e, sub_array[e][m]);
        }
        
        //sort the sub_arrays in ascending but maintain process # integrety
        int a1, i1, i2, h, pValue=0; 
        for (i1 = 0; i1 < pCount; ++i1) 
        {   
            pValue = i1;
            for (i2 = i1 + 1; i2 < pCount; ++i2)
            {
                //pValue = 0;
                if (sub_array[i1][m] > sub_array[i2][m]) //if there needs to be a switch
                {
                    pValue = i2;
                    a1 =  sub_array[i1][m];
                    sub_array[i1][m] = sub_array[i2][m];
                    sub_array[i2][m] = a1;
                }
                
                value = sub_array[i1][m];
            }
            tickTotal += sub_array[i1][m];
            start_of_process += sub_array[i1][m];
            printf("Sorted - Process %d took %d. \n", pValue, sub_array[i1][m]); // print the remaining processes in descending // replacing i1
            
        }
        tickTotal += value;    
        wt[m] = value;
        
        printf("\n");
    }
    turn_time = tickTotal;
    printf("Turnaround time: %d \n", turn_time);
    
    //waiting time
    int wt_total = 0; //wt1
    wt_total = findWaitingTime(wt, ticks);
    printf("Waiting time: %d \n", wt_total);
    
    
    //----------------------------------------------------SJFL--------------------------------------------------------------
    printf("\n");
    printf("\n");
    printf("== Shortest Job First Live ==\n\n");


    /* using vars below in calculation
    int tau
    float alpha
    */
    int tau = 0, start_of_process1, turn_time1 = 0, wait_time1 = 0, est_error = 0;
    float alpha = 0;
    int m1, tickTotal1 = 0, est_time = 0, last_ = 0;
    int sub_array1[pCount][ticks];
    start_of_process1 = 0;
    int wt1[ticks];
    wt1[0] = 0;
    int value2 = 0;
    for(m1 = 0; m1 < ticks; m1++)
    {
        // - implement the display of the two processes compare and sort
        printf("Simulating %dth tick of process @ time %d: \n", (m1 % ticks), start_of_process1);
        
        
        //create sub_arrays for each tick with the number of processes
        // i.e. - if we have three processes (0,1,2) sub_array[0] will have pro 1, pro2, pro 3 for 0th tick
        
        int e1, f1, g1, value1 = 0;
        for(e1 = 0; e1 < pCount; e1++)
        {
            tau = pro_array[e1].tau;
            alpha = pro_array[e1].alpha;
            sub_array1[e1][m1] = pro_array[e1].times[m1];

        }
        
        //sort the sub_arrays in ascending but maintain process # integrety
        int a2, i3, i4, h1, pValue1=0; 
        for (i3 = 0; i3 < pCount; ++i3) 
        {   
            pValue1 = i3;
            for (i4 = i3 + 1; i4 < pCount; ++i4)
            {
                if (sub_array1[i3][m1] > sub_array1[i4][m1]) //if there needs to be a switch
                {
                    pValue1 = i4;
                    a2 =  sub_array1[i3][m1];
                    sub_array1[i3][m1] = sub_array1[i4][m1];
                    sub_array1[i4][m1] = a2;
                }
                value1 = sub_array1[i3][m1];
            }
            if(m1 == 0)
            {
                last_ = tau;
                est_time = tau;
                printf("last_ = %d\n", last_);
            } else
            {   
                last_ = value2;
                est_time = ((alpha*last_) + (1-alpha)*est_time);
                printf("last_ = %d\n", last_);            
                
            }
            tickTotal1 += sub_array1[i3][m1];
            start_of_process1 += sub_array1[i3][m1];
            //est_time = ((alpha*last_) + (1-alpha)*tau);
            printf("Sorted - Process %d was estimated for %d and took %d. \n", pValue1, est_time, sub_array1[i3][m1]); // print the remaining processes in descending // replacing i1
            value2 = sub_array1[i3][m1];
            est_error = est_error + abs(sub_array1[i3][m1] - est_time);
            printf("est_error = %d\n", est_error);
        }
        tickTotal1 += value1;    
        wt1[m1] = value1;
        printf("\n");
    }
    turn_time1 = tickTotal1;
    printf("Turnaround time: %d \n", turn_time1);

    //waiting time
    int wt_total1 = 0; //wt2
    wt_total1 = findWaitingTime(wt1, ticks);
    printf("Waiting time: %d \n", wt_total);

    //Estimation Error
    printf("Estimation Error = %d\n", est_error);
    
    fclose(file); // close the file from reading
    return 0;

}
