#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int readfile(char []);
void printlist(int);
void sort_contact(int,int);
int filelength(char []);
int partition(int left,int right);

//directory structure
typedef struct directory{
	char firstname[50];
	char lastname[50];
	char phoneno[16];


}directory;

directory d[100];
void swap(directory *,directory *);
void search(directory, int, int);
int lowerboundsearch(directory, int, int);
int upperboundsearch(directory, int, int);
int delete(directory, int);
int insert(directory, int);
int main(int argc,char *argv[])
{
	int ch;
	char fname[50],lname[50],no[14],record[50];

	char *token;
	directory searchd;
	int size=0;
	char filename[50];
	//storing command line arg filename
	strcpy(filename,argv[1]);
	//seeding for rand()
	srand(time(NULL));
	size=readfile(filename);
	do
	{
		printf("\n-----------------------------------------\n");
		printf("\n\n1.sort_contact\n2.search\n3.delete\n4.Insert\n5.exit\n");
		printf("\nPlease Enter the Choice:\n");
		scanf("%d",&ch);

		switch(ch){

		case 1:
		sort_contact(0,size-1);
//		printf("\n\nlist after sorting..");
		printlist(size);
		break;
		case 2:
		
		printf("\nEnter the name to search:");
		scanf("%s %s",fname,lname);
		strcpy(searchd.firstname,fname);
		strcpy(searchd.lastname,lname);
		search(searchd,0,size-1);
		break;

		case 3:
		printf("\nEnter the name to be deleted:");
		scanf("%s %s",fname,lname);
		strcpy(searchd.firstname,fname);
		strcpy(searchd.lastname,lname);
		size=delete(searchd,size);
		break;

		case 4:
		printf("\nEnter the record to insert:\n");
		scanf("%s %s %s",searchd.firstname,searchd.lastname,searchd.phoneno);	
		strcpy(lname,searchd.lastname);
		token=strtok(lname,", ");
		strcpy(searchd.lastname,token);
		size=insert(searchd,size);
		break;
		case 5:
		exit(0);
		default:
		printf("\nInvalid choice\n");

	}
	}while(ch!=5);
return 0;


}

//Reading file line by line and tokenising it to store in structure object
int readfile(char filename[50])
{
	char buffer[1000];
	char tempstr[1000];
	char *token=NULL;
//	directory d; //=null;
	char arr[50], name[50], no[50];
	int i=0,lines=0;
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("\nThe file pointer is null");
		return -1;
	}	
	//reading file line by line till EOF
		while (fgets(buffer,1000, fp)!=NULL)
		{
	//tokenizing the line using strtok
		token=strtok(buffer, " ");
		strcpy(d[i].firstname,token);
		token =strtok(NULL, ", ");
		strcpy(d[i].lastname,token);
		token =strtok(NULL, "\n ");
		strcpy(d[i].phoneno,token);
		i++;
	//counting no of lines to keep track of size of array
		lines++;
		}
		fclose(fp);
		return lines;
}

//printing the array
void printlist(int size)
{
	int i=0;
	printf("\n---------------------------------------------------");
	for(i=0;i<size;i++)
	{
		printf("\n%s %s, %s",d[i].firstname,d[i].lastname,d[i].phoneno);
	}
	printf("\n");
}

//sorting the contacts using randomized quicksort

void sort_contact(int left,int right)
{
	if(left<right)
	{
		
		int index=partition(left,right);
		sort_contact(left,index-1);
		
		sort_contact(index+1,right);
	}
}

int partition(int left,int right)
{
	int i, j=0;
	//finding the random no for pivot
	int randomno=left + rand()%(right - left + 1);
	directory pivot;
	
	i=left-1;
	
	pivot=d[randomno];

	//swapping pivot with last element
	swap(&d[randomno],&d[right]);
	for(j=left;j<right;j++)
	{
		if(strcmp(d[j].firstname,pivot.firstname)<0)   //if d[j] is less than pivot then swap
		{
			i++;
			swap(&d[i],&d[j]);
		}
		else if(strcmp(d[j].firstname,pivot.firstname)==0)
		{
			if(strcmp(d[j].lastname,pivot.lastname)<0)          //sort on lastname if first name is equal but not the lastname
			{
				i++;
				//printf("\nswapping %s, %s",d[i].lastname,d[j].lastname);
			swap(&d[i],&d[j]);
			}
			else if(strcmp(d[j].lastname,pivot.lastname)==0)
			{
				if(strcmp(d[j].phoneno,pivot.phoneno)<0)   //sort on phone no if firstname and lastname are equal
				{
					i++;
					//printf("\nswapping %s, %s",d[i].phoneno,d[j].phoneno);
					swap(&d[i],&d[j]);
				}
		}	}
			
	}

	swap(&d[i+1],&d[right]);           
	return i+1;
    
 
}

// Swap the elements at two indices i and j in array d.
void swap(directory *d1,directory *d2) {
 
    directory temp;
    temp=*d1;
    *d1=*d2;
    *d2=temp;

  //  printf("\nd1 is %s, d2 is %s",d1->firstname,d2->firstname);
}

void search(directory record,int left,int right)
{
	int lb=lowerboundsearch(record,left,right);
	int ub=upperboundsearch(record,left,right);

	 if(ub==-1 && lb==-1)
        {
                printf("\nName not found!");
        }


	else if((lb==-1)|| (ub==-1)){
	if(lb==-1)
		printf("\n%s %s, %s",d[ub].firstname,d[ub].lastname,d[ub].phoneno);

	else if(ub==-1)
		printf("\n%s %s, %s",d[lb].firstname,d[lb].lastname,d[lb].phoneno);
	}

	else if(ub!=-1 && lb!=-1 ) 
	{
		if(ub==lb)
		printf("\n%s %s, %s",d[ub].firstname,d[ub].lastname,d[ub].phoneno);

			else{

		printf("\n%s %s, %s",d[ub].firstname,d[ub].lastname,d[ub].phoneno);
		printf("\n%s %s, %s",d[lb].firstname,d[lb].lastname,d[lb].phoneno);
	}


	}
	/*if(ub==-1 && lb==-1)
	{
		printf("\nName not found!");
	}*/


}

//searching to get the start index of occurence of contact
int lowerboundsearch(directory record,int left,int right)
{

if (left > right)
                return -1;
          int middle = (left + right) / 2;
          if ((strcmp(d[middle].firstname,record.firstname)==0) && (strcmp(d[middle].lastname,record.lastname)==0))
        {
        	if((strcmp(d[middle-1].firstname,d[middle].firstname)<0)){ //&& (strcmp(d[middle-1].lastname,d[middle].lastname)<0))
                        return middle;
                    }
            else
                return lowerboundsearch(record, left, middle - 1);
        }
          else if ((strcmp(d[middle].firstname,record.firstname)>0) ) //|| (strcmp(d[middle].lastname,record.lastname)>0))
                return lowerboundsearch(record, left, middle - 1);
          else
                return lowerboundsearch(record, middle + 1, right);           
    
}

//to get the last index of contact searched
int upperboundsearch(directory record,int left,int right)
{
	 if (left > right)
                return -1;
          int middle = (left + right) / 2;
          if ((strcmp(d[middle].firstname,record.firstname)==0) && (strcmp(d[middle].lastname,record.lastname)==0))
        {
        	        	if((strcmp(d[middle].firstname,d[middle+1].firstname)<0)) // (strcmp(d[middle].lastname,d[middle+1].lastname)<0))
                return middle; 
                 else

                    return upperboundsearch(record, middle + 1, right);           
        }
          else if ((strcmp(d[middle].firstname,record.firstname)>0)) // || (strcmp(d[middle].lastname,record.lastname)>0))
                return upperboundsearch(record, left, middle - 1);
          else
                return upperboundsearch(record, middle + 1, right); 
}


//deleting record by copying the last element into the record index and reducing the size by 1,then calling sort on it
int delete(directory record,int size)
{
 int i=0,k=0,temp;
 int deleted=-1;
 //directory temp[100];
 temp=size-1;
 for(i=0;i<size;i++) 
{
	if(strcmp(d[i].firstname,record.firstname)==0)
	{
		if((strcmp(d[i].lastname,record.lastname)==0))
		{
			//d[i]=d[size];
			d[i]=d[temp];
			//d[temp]=NULL;
			temp--;
			deleted=1;
			//printf("\n deleted valiue is:%d",deleted);
		}

	} 	
	
}
if(deleted==-1)
	printf("\nRecord not Found!!");
else{
	sort_contact(0,temp);
	printf("\ntemp size is:%d",temp+1);
	printlist(temp+1);
	}
	return temp+1;
}

//inserting a new record on next index given by size variable and sorting it
int insert(directory record, int size)
{
	d[size]=record;
	sort_contact(0,size);
	printlist(size+1);
return size+1;
}
