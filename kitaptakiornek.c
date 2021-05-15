#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_STOCK 1111
#define MAX_STOCK 9999
#define MAX_PRICE 1000.00
#define STR_SIZ 80

typedef struct {
	
	int stock_num;
	char category[STR_SIZ];
	char tech_descript[STR_SIZ];
	double price;
	
}product_t;

typedef struct {

	int low_stock,high_stock;
	char low_category[STR_SIZ],high_category[STR_SIZ];
	char low_tech_descript[STR_SIZ],high_tech_descript[STR_SIZ];
	double low_price,high_price;	
	
}search_params_t;


search_params_t get_params(void);
void display_match(FILE *databasep,search_params_t params);
char menu_choose(search_params_t params);
int match(product_t product,search_params_t params);
void show(product_t product);
void fill_file(product_t*);;
void create_binary_file();
void create_txt_file();
void convert_txtto_bin();
void file_menu(void);
int main(){
	
	char inv_filename[STR_SIZ];
	
	FILE *inventoryp;
	
	search_params_t params;
	
	int sel=0;
	do{
		printf("**** MAIN MENU ***** \n");
	
	
	printf("Please select an operation \n");
	printf("1-File Menu \n");
	printf("2-Product Menu \n");
	printf("3-Exit \n");
	
	scanf("%d",&sel);
	
	if(sel==1)file_menu();
	
	else if(sel==2){
		
	printf("Enter name of inventory file which you want to make operation in it. > \n");
		
	scanf("%s",inv_filename);
	
	inventoryp=fopen(inv_filename,"rb");
	
	params = get_params();
	
	display_match(inventoryp,params);
	
	}
	
	}while(sel != 3);
	
	
		
	return 0;
}

search_params_t get_params(void){
	
	search_params_t params;
	char string[STR_SIZ];
	int number;
	char choice;
	
	params.low_stock = 1111;
	params.high_stock = 9999;
	
	strcpy(params.high_category,"zzzz");
	strcpy(params.low_category,"aaaa");
	strcpy(params.low_tech_descript,"aaaa");
	strcpy(params.high_tech_descript,"zzzz");
	params.low_price = 0.00;
	params.high_price = 1000.0;
	
	choice=menu_choose(params);
	
	while(choice != 'q'){
		
	
		
		switch(choice){
			
			case 'a': 
			printf("New low bound for stock number > ");
			scanf("%d",&number);		
			params.low_stock = number;
			break;
			case 'b': 
			printf("New high bound for stock number >");
			scanf("%d",&number);
			params.high_stock = number;
			break; 
				
			case 'c':
			getchar();
			printf("New low bound for category > ");
			gets(string);
			strcpy(params.low_category,string);
			break;
				
			case 'd': 
			getchar();
			printf("New high bound for category > ");
			gets(string);
			strcpy(params.high_category,string);
			break;
				
			case 'e': 
			getchar();
			printf("New low bound for technical description > ");
			gets(string);
			strcpy(params.low_tech_descript,string);
			break;
				
			case 'f': 
			getchar();
			printf("New high bound for technical description > ");
			gets(string);
			strcpy(params.high_tech_descript,string);
			break;
				
			case 'g': 
			printf("New low bound for price > ");
			scanf("%d",&number);
			params.low_price = number;
			break;
				
			case 'h': 
			printf("New high bound for price >");
			scanf("%d",&number);
			params.high_price = number;
			break;
			
			case 'q': break;
				
		}
		
	choice=menu_choose(params);
		
	}
	
	return params;
	
}

char menu_choose(search_params_t params){
	
	char choice;
	
       printf("q to\naccept parameters shown.\n\n");
       printf(" Search parameter ");
       printf("Current value\n\n");
       printf("[a] Low bound for stock number %4d\n",
       params.low_stock);
       printf("[b] High bound for stock number %4d\n",
       params.high_stock);
       printf("[c] Low bound for category %s\n",
       params.low_category);
       printf("[d] High bound for category %s\n",
       params.high_category);
       printf("[e] Low bound for technical description %s\n",
       params.low_tech_descript);
       printf("[f] High bound for technical description %s\n",
       params.high_tech_descript);
       printf("[g] Low bound for price $%7.2f\n",
       params.low_price);
       printf("[h] High bound for price $%7.2f\n\n",
       params.high_price);
       
 printf("Selection> ");
 scanf(" %c", &choice);

 return (choice);
	
}


void display_match(FILE *databasep,search_params_t params){
	
	product_t next_prod;
	int no_matches = 1;
	
	int status;
	
	for(status = fread(&next_prod, sizeof(product_t), 1 , databasep);
	status == 1 && params.low_stock > next_prod.stock_num;
	status = fread(&next_prod, sizeof(product_t), 1 , databasep)){}
	
	printf("Products satisfying the search parameters: \n");
	
	while(next_prod.stock_num <= params.high_stock && status == 1 ){
		
		if(match(next_prod,params)){
			
			no_matches = 0;
			show(next_prod);
			
		}
		
		status = fread(&next_prod,sizeof(product_t),1,databasep);
	}
	
	if(no_matches){
		printf("Sorry, no products available. \n\n");
	}
	
}
int match(product_t product,search_params_t params){

	return (strcmp(params.low_category,product.category) <= 0 &&
	        strcmp(product.category,params.high_category) <= 0 &&
	        strcmp(params.low_tech_descript,product.tech_descript) <= 0 &&
	        strcmp(product.tech_descript,params.high_tech_descript) <= 0 &&
	        params.low_price <= product.price <= params.high_price);


}
void show(product_t product){
	
	printf(" \n ****** Matched Product ******* \n");
	printf("Stock number of product = %d \n",product.stock_num);
	printf("Price of the product = %d \n",product.price);
	printf("Technic description of the product = %s \n",product.tech_descript);
	printf("Category of product = %s \n",product.category);
	
}


void file_menu(void){
	
	char choice='z';
		
			
	while(choice != 'q'){
			
		getchar();
	
		if(choice == 'a'){
			create_binary_file();
		}
		else if(choice == 'b'){
		create_txt_file();
		}
		else if(choice == 'd'){
		convert_txtto_bin();
		}         
		else if(choice == 'q'){
			return;
		}
		
		
	printf("***** File Menu ***** \n");
	printf("a-Create a binary file: \n");
	printf("b-Create a txt file:  \n");
	printf("d-Convert a txt file to binary file: \n ");
	printf("q-Return the main menu: \n");
	
	scanf("%c",&choice);
		
	
	}; 
	
	return;
}

void create_binary_file(){
	
	FILE *bin;
	char filename[20];
	product_t product;
	
	printf("Please enter your binary file name to keep your inventory of products: \n");
	gets(filename);
	
	
	
	bin=fopen(filename,"wb");
	
	fill_file(&product);

	while(!feof(stdin)){
		
			
		fwrite(&product,sizeof(product_t),1,bin);
		fflush(bin);
		fill_file(&product);
	}
	fclose(bin);
		
}

void create_txt_file(){
	
	FILE *text;
	char filename[20];
	char c;
	product_t product;
	printf("Enter your file name: \n ");
	scanf("%s",filename);
	
	text=fopen(filename,"w");
	
	fill_file(&product);

	while(!feof(stdin)){
		
		
		fprintf(text,"%d -> %s -> %s -> %d \n",product.stock_num,product.category,product.tech_descript,product.price);
		fflush(text);
		fill_file(&product);
		
	}
	
	
	fclose(text);
	return;
}
void fill_file(product_t *product){
	

		
		printf("Enter your product stock num: \n");
		scanf("%d",&(product->stock_num));
		
		if(!feof(stdin)){
			
			printf("Enter your product category: \n");
		getchar();
		gets(product->category);
		
		printf("Enter your product technic description: \n");
		
		gets(product->tech_descript);
		
		printf("Enter your product price: \n");
		scanf("%d", &(product->price));
		
		}else{
			
			
			return;
		}	
		
		
		return;	
		

		
	
}

void convert_txtto_bin(){
	
	char bin[20],txt[20];
	FILE *receiver,*donor;
	printf("Enter name of txt file which will be convert: \n");	
	gets(txt);
	
	printf("Enter name of bin file which will be created at the end of convertation: \n");
	gets(bin);
	product_t product;
	
	donor=fopen(txt,"r");
	receiver=fopen(bin,"wb");
	
	fscanf(donor,"%d -> %s -> %s -> %d",&(product.stock_num),product.category,product.tech_descript,&(product.price));
	
	while(!feof(donor)){
		
		fwrite(&product,sizeof(product_t),1,receiver);
		fflush(receiver);
		fscanf(donor,"%d -> %s -> %s -> %d",&(product.stock_num),product.category,product.tech_descript,&(product.price));		
		
	}
	
	
	
}

