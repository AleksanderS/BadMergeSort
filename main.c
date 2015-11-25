/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on February 16, 2015, 11:54 AM
 */
int * sortArray( char *);
int searchArrayStart(int *, char *, char *);
void sortArrayFunc( int, int *);
void writeSort(int , int * );
void searchArrayFunc(int , int , int , int * , int , int * );
void printResults(unsigned long , unsigned long , char *, char *, int);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc != 3){
        fprintf(stderr,"Arguments invalid! Exiting.\n");
        exit(1);
    }
   unsigned long start_t = 0, end_t = 0 , total_t = 0;
   start_t = clock();
   int *sorted_array;
   sorted_array = sortArray(argv[1]);
  
   end_t = clock();
   total_t = (double)((end_t - start_t) / (CLOCKS_PER_SEC/1000));
 
   unsigned long start_search_t = clock();
   int numbers_found = searchArrayStart( sorted_array, argv[1], argv[2]);
   unsigned long end_search_t = clock() - start_search_t;
   
   printResults(total_t, end_search_t, argv[1], argv[2], numbers_found);
 
   
    
    
    
    
    return (0);
}


void printResults(unsigned long sort_time, unsigned long search_time, char * sort_file, char * search_file, int numbers_found){
    int sort_size;
    int search_size;
    FILE *search_in = fopen (search_file, "rb");
    FILE *sort_in = fopen(sort_file, "rb");
    fread( &sort_size, sizeof(int), 1, sort_in);
    fread( &search_size, sizeof(int), 1, search_in);
    
   fprintf(stderr,"Sort Algorithm   : MergeSort\n");
   fprintf(stderr,"Search Algorithm : Binary\n");
   fprintf(stderr,"Sort File        : %s\n", sort_file);
   fprintf(stderr,"Sort File Size   : %i\n", sort_size);
   fprintf(stderr,"Sort Time        : %lu\n", sort_time);
   fprintf(stderr,"Search File      : %s\n", search_file);
   fprintf(stderr,"Search File Size : %i\n", search_size);
   fprintf(stderr,"Search Time      : %lu\n", search_time);
   fprintf(stderr,"Numbers Found    : %i\n", numbers_found);
    
    return;
}
//returns amount of numbers found
int searchArrayStart(int * sorted_array, char * sort_file_name, char * search_file_name){
    FILE *search_in = fopen (search_file_name, "rb");
    FILE *sort_in = fopen(sort_file_name, "rb");
    int sort_count_size;
    fread( &sort_count_size, sizeof(int), 1, sort_in);
    int search_count_size;
    fread( &search_count_size, sizeof(int), 1, search_in);
    int * search_array = (int *) malloc(sizeof(int) * search_count_size);
    fread(search_array, sizeof(int), search_count_size, search_in);
    
    
    
    int match_count = 0;
    int first_element = 0;
    int last_element = sort_count_size - 1;
    int mid_element = (last_element + first_element)/2;
    int i;
    for(i = 0; i<search_count_size; i++)
        searchArrayFunc(first_element, mid_element, last_element, sorted_array, search_array[i], &match_count);
    return match_count;
}

void searchArrayFunc(int first, int mid, int last, int * sorted_array, int search_number, int * match_count){
    if(search_number == sorted_array[mid]){
        (*match_count)++;
        return;
    }
    else if(first == mid && mid == last) return;
    else if(first == mid){
        mid++;
        searchArrayFunc(mid, (mid+last)/2, last, sorted_array, search_number, match_count);
    }
    else if(search_number > sorted_array[mid]){
        searchArrayFunc(mid, (mid+last)/2, last, sorted_array, search_number, match_count);
    }
    else if(search_number < sorted_array[mid]){
        searchArrayFunc(first, (first+mid)/2, mid, sorted_array, search_number, match_count);
    }
    
    
}


int * sortArray(char * sort_file_name){
    FILE *in;
    in = fopen(sort_file_name, "rb");
    int sort_count_size;
    fread( &sort_count_size, sizeof(int), 1, in);
    int *sort_array = (int *) malloc(sizeof(int) * sort_count_size);
    fread(sort_array, sizeof(int), sort_count_size, in);
    sortArrayFunc(sort_count_size, sort_array);
    writeSort(sort_count_size, sort_array);

    
    return sort_array;
}

void writeSort(int count, int * sort_array){
    FILE *out;
    out = fopen("out.txt", "w");
    int i;
    for(i = 0; i<count; i++){
      fprintf(out, "%i\n", sort_array[i]);  
    }
    fclose(out);
    
    return;
}



void sortArrayFunc(int size, int * array){
    if(size<=1) return;
    int *left_array = (int *) malloc(sizeof(int)*size/2);
    int *right_array = (int *) malloc(sizeof(int)*(size-(size/2)));
    int i;
    for(i=0; i<(size/2); i++){
        left_array[i] = array[i];
       // fprintf(stderr, "Num %i = %i\n", i,  left_array[i]);
    }
    
    
    
    int j = size-(size/2);
    int k = 0;
    
    for(;i<size; i++, k++){
        //fprintf(stderr, "K = %i\n J = %i\n L = %i", k, j, l );
        right_array[k] = array[i];
       // fprintf(stderr, "Num %i = %i\n", k , right_array[k]);
    }

    sortArrayFunc(size/2, left_array);
    sortArrayFunc(j, right_array);
    int m = 0, n = 0, o = 0;
    while(o<size){
        if(left_array[m]<=right_array[n]){
            array[o] = left_array[m];
            m++;
            o++;
            if(m == size/2){
                while(n<(size-(size/2))){
                    array[o] = right_array[n];
                    n++;
                    o++;
                            
                }
            }
        
        }
        else{
            array[o] = right_array[n];
            o++;
            n++;
            if(n == size-(size/2)){
                while(m<size/2){
                    array[o] = left_array[m];
                    m++;
                    o++;
                }
            }
        }
    }
    
    free(left_array);
    free(right_array);
 
    return;
}

