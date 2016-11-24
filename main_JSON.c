/*
 This is the coding challenge for the application of the Software Developer position at Sortable
 created by Hongyan Wang on November 23, 2016
 Coding Challenge: http://sortable.com/challenge/
 Idea: for each product, check all the listings to see which ones match the product
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./cJSON/cJSON.h"

/* a price listing matches a product when the "product_title" contains "product_name"
   If "title" contains "product_name", the following function returns 1, otherwise, it returns 0
*/
int name_in_title(char*, char*);

int main()
{
        char *lineP, *lineL;
	char *name, *title; 
	size_t sizep=0, sizel=0; 
	cJSON *parseP, *parseL;
	// open the file "products.txt" for reading
	FILE* rp=fopen("./products.txt","r"); 
	// open the file "results.txt" for writing
	FILE* wf=fopen("./results.txt","w");

	// go through every product to find all listings that match the product
 	while(getline(&lineP,&sizep,rp)!=-1){
		int k=0;
		cJSON *result=cJSON_CreateObject();
		cJSON *lists=cJSON_CreateArray();
		cJSON *head=cJSON_CreateArray(); 
		// parse the object line
		parseP=cJSON_Parse(lineP);
		// extract the product_name
		name=cJSON_GetObjectItem(parseP,"product_name")->valuestring;
		// add "name" to the result object
		cJSON_AddItemToObject(result, "product_name", cJSON_CreateString(name));	

		FILE* rl=fopen("./listings.txt","r");
		while(getline(&lineL,&sizel,rl)!=-1){
			parseL=cJSON_Parse(lineL);
			// extract the product title
			title=cJSON_GetObjectItem(parseL,"title")->valuestring;
			// if "name" is in "title", then add this listing object to "listings"
			if(name_in_title(name,title)==1){
				lists->next=cJSON_Parse(lineL);
				if(k==0)
					head->child=lists->next;
				lists=lists->next;
				k++; 
			}
		}
		fclose(rl);
		// add "listings" to the result object
		cJSON_AddItemToObject(result, "listings",head);
		// print the result object in file "result"
		fprintf(wf,"%s\n",cJSON_PrintUnformatted(result));
	}
	fclose(wf); 
	fclose(rp); 
	return 0;
}

// product_name only contains letters and numbers
// we need to check if the corresponding letter or number is the same in "title"
int name_in_title(char* name, char*title){
	for(int i=0;i<(int)strlen(name);i++){
		if(name[i]>='0'&&name[i]<='9'){
			if(name[i]!=title[i])
				return 0;
		}
		if(name[i]>='a'&&name[i]<='z'){
			if((name[i]-title[i]!=0)&&(name[i]-title[i]!=32))
				return 0;
		}
		if(name[i]>='A'&&name[i]<='Z'){
			if((name[i]-title[i]!=0)&&(title[i]-name[i]!=32))
				return 0;
		}
	}
	return 1;
}
