//                                                          PROJECT

// NAME --> SHAURYA SINGHAL
// SAP ID --> 590023883
// BATCH NO. --> 60

// PROJECT TOPIC --> Result Management System (with Ranking & GPA)
//   • Enter marks of multiple students.
//   • Calculate GPA/percentage.
//   • Rank students based on marks.
//   • Search student records.
//   • Generate report card to file.

#include<stdio.h>     //library(header file)

//this structure will save all the subject marks of all the students
struct subject{
    int C_PROGRAMMING;
    int LINUX;
    int EVS;
    int MATHS;
    int PROB_SOLVING;
};

//this is the main structure that will store all the main information like student name or student roll no. etc.
struct student{
    char name[100];
    int roll;
    struct subject sub; //nested structure so we can store marks of 5 subjects in the main structure
    int totalmarks;
    float percentage;  
    float gpa;
    int rank;         
};

//this function helps to find the student info with the help of their roll no. 
int searchstudent( struct student stu[] , int size , int roll ){
    for(int i = 0 ; i < size ; i++){                              //here size is referring to the structure size 
        if(stu[i].roll == roll){
            return i;
        }
    }
    return -1;  //it will return -1 if no same roll no. is found in the structure 
}

//this function will sort students in descending order so we can rank them.
void sortbymarks(struct student stu[] , int size){
    struct student temp;                  //temporary structure is created so we can store a structure in it to switch positions
    for(int i = 0 ; i < size - 1 ; i++){
        for(int j = 0 ; j < size - 1 -i ; j++){
            if(stu[j].totalmarks < stu[j+1].totalmarks){
                temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
}

//this will sort students in descending order so we can rank them.
void assignranks( struct student stu[] , int size){
    stu[0].rank = 1;
    for(int i = 1 ; i < size ; i++ ){
        if(stu[i].totalmarks == stu[i-1].totalmarks){
            stu[i].rank = stu[i-1].rank;             //if the total marks are equal then both will be given the same rank
        }
        else{
            stu[i].rank = i + 1;
        }
    }
}

//this function will grade each subject so we can calculate GPA
int grade(int marks){
    if(marks >= 90) return 10;
    else if(marks >= 80) return 9;
    else if(marks >= 70) return 8;
    else if(marks >= 60) return 7;
    else if(marks >= 50) return 6;
    else if(marks >= 40) return 5;
    else return 0;
}

//this function will store the GPA of each student 
float calgpa(struct student s){
    int gpa1 = grade(s.sub.C_PROGRAMMING);
    int gpa2 = grade(s.sub.LINUX);
    int gpa3 = grade(s.sub.EVS);
    int gpa4 = grade(s.sub.MATHS);
    int gpa5 = grade(s.sub.PROB_SOLVING);

    return (float)(gpa1+gpa2+gpa3+gpa4+gpa5) / 5.0;
}

//function so the user can get every deatil of the student they want to search for
void stuoutput(int index , struct student stu[]){   //index is 
    printf("\n");
    printf("name: %s\n",stu[index].name);
    printf("roll no.: %d\n",stu[index].roll);
    printf("marks:\n");

    printf( " C PROGRAMMING : %d\n",stu[index].sub.C_PROGRAMMING);     //    |    
    printf( " LINUX         : %d\n",stu[index].sub.LINUX);             //    |  
    printf( " EVS           : %d\n",stu[index].sub.EVS);               //    | --> marks output
    printf( " MATHS         : %d\n",stu[index].sub.MATHS);             //    | 
    printf( " PROB_SOLVING  : %d\n",stu[index].sub.PROB_SOLVING);      //    | 

    printf( "total marks: %d\n",stu[index].totalmarks);
    printf( "percentage : %.2f%%\n",stu[index].percentage);
    printf( "GPA  :  %.2f\n",stu[index].gpa);
    printf( "rank: %d\n",stu[index].rank);
    printf( "---------------------------------\n\n");
}

//main code starts from here
int main(){

    int num;
    printf("enter the number of students in the class: ");
    scanf("%d",&num);

    struct student stu[num];                             //structure (we have initialized the size of the structure)

    //loop so we can input information about the students like :- (name , roll no. , marks of 5 subjects abtained by them)
    for(int i = 0 ; i < num ; i++){

        printf("enter the name of %d student: ",i+1);
        scanf("%99s", stu[i].name);                      //%99s will directly store the name in the structure without the help of (strcmp)

        printf("enter the roll number of the student: ");
        scanf("%d",&stu[i].roll);               

        //here we are taking input of all 5 subject marks obtained by the student in order (C_PROGRAMMING , LINUX , EVS , MATHS , PROB_SOLVING)
        printf("enter marks of (C_PROGRAMMING , LINUX , EVS , MATHS , PROB_SOLVING ): ");
        scanf("%d %d %d %d %d", &stu[i].sub.C_PROGRAMMING, &stu[i].sub.LINUX, &stu[i].sub.EVS, &stu[i].sub.MATHS, &stu[i].sub.PROB_SOLVING);

        printf("\n");
    }

    //loop so we can calculate the percentage , GPA , totalmarks of each student
    for(int i = 0 ; i < num ; i++){
        int sum = stu[i].sub.C_PROGRAMMING + stu[i].sub.LINUX + stu[i].sub.EVS + stu[i].sub.MATHS + stu[i].sub.PROB_SOLVING;
        //(float) is used to type cast the result in float values because the marks are integer datatype
        stu[i].percentage = (float)(sum/5.0);
        stu[i].totalmarks = sum;              
        stu[i].gpa = calgpa(stu[i]);
    }

    sortbymarks(stu , num);  //this function will sort the students on the basis of there marks

    assignranks(stu , num);  //this function is assinging rank to students on the basis of there total marks

    char ques;

    //taking input if the user want to search any student's record.
    printf("do you want to search any student record (y/n): ");
    scanf(" %c",&ques);

    if( ques == 'y' || ques == 'Y'){     

        int no;

        printf("enter the number of students you want to see the record of: ");
        scanf("%d",&no);      

        for(int i = 0 ; i < no ; i++){
            int find;

            printf("enter the roll no. of the student you want to see the record of: ");
            scanf("%d",&find);    

            int index = searchstudent(stu , num , find); //this function will find the students index which the user wants to see the info of

            if(index != -1){
                stuoutput(index,stu); //function only executed if the roll no. is found and it gives a complete output of the student info
            }
            else{
                printf("student not found with that roll number");
            }
        }
    }

    FILE *fptr = fopen("RESULT.txt" , "w"); //gives output of the program in a different file (RESULT.txt) {opens it}

    //loop to print all the information of all the students present in the class and rank them on the basses of there total marks
    for(int i = 0 ; i< num ; i++){
    fprintf(fptr, "rank: %d\n\n",stu[i].rank);
    fprintf(fptr, "name: %s\n",stu[i].name);
    fprintf(fptr, "roll no.: %d\n",stu[i].roll);
    fprintf(fptr,"marks:\n");

    fprintf(fptr, " C PROGRAMMING : %d\n",stu[i].sub.C_PROGRAMMING);   //    |    
    fprintf(fptr, " LINUX         : %d\n",stu[i].sub.LINUX);           //    |  
    fprintf(fptr, " EVS           : %d\n",stu[i].sub.EVS);             //    | --> marks output
    fprintf(fptr, " MATHS         : %d\n",stu[i].sub.MATHS);           //    | 
    fprintf(fptr, " PROB_SOLVING  : %d\n",stu[i].sub.PROB_SOLVING);    //    | 

    fprintf(fptr, "total marks: %d\n",stu[i].totalmarks);
    fprintf(fptr, "percentage : %.2f%%\n",stu[i].percentage);
    fprintf(fptr, "GPA        : %.2f\n", stu[i].gpa);
    fprintf(fptr, "---------------------------------\n\n");
    }

    fprintf(fptr, "THANK YOU");

    fclose(fptr);   //closes the file after executing the commands above

    return 0;
}               //end 