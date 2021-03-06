#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE*fp=fopen("inputeasform", "w");

	int i,n,j,r,s,k;
	int set_n=10;	
	printf("here : \n");
	scanf("%d",&set_n);
	for(i=1; i<=set_n; i++)
		for(n=1; n<=set_n; n++)
			for(j=1; j<=set_n; j++)
				fprintf(fp,"(declare-const p%d%d%d Bool)\n",i,n,j);
	//E1
	fprintf(fp,"; E1\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=set_n;i++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(or ");
			for(j=1; j<=set_n; j++){
				fprintf(fp,"p%d%d%d ", i,j,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");

	
	//E2
	fprintf(fp,"; E2\n");
	fprintf(fp,"(assert (and ");
	for(j=1; j<=set_n; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(or ");
			for(i=1; i<=set_n; i++){
				fprintf(fp,"p%d%d%d ",i,j,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");		
	}
	fprintf(fp,"))\n");

	//E3
	fprintf(fp,"; E3\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=set_n; i++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(and ");
			for(j=1; j<=set_n-1; j++){
				fprintf(fp,"(and ");
				for(k=j+1; k<=set_n; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,i,k,n);
				}
				fprintf(fp,")");
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");

	//E4
	fprintf(fp,"; E4\n");
	fprintf(fp,"(assert (and ");
	for(j=1; j<=set_n; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(and ");
			for(i=1; i<=set_n-1; i++){
				fprintf(fp,"(and ");
				for(k=i+1; k<=set_n; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,k,j,n);
				}
				fprintf(fp,")");
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");

	//E5
	fprintf(fp,"; E5\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=set_n; i++){
		fprintf(fp,"(and ");
		for(j=1; j<=set_n; j++){
			fprintf(fp,"(and ");
			for(n=1; n<=4; n++){ //맞는 이야기인건가..?
				fprintf(fp,"(and ");
				for(k=n+1; k<=5; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,i,j,k);
				}
				fprintf(fp,")");
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");
	/*	
	//E6
	fprintf(fp,"; E6\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=6; i++){
		fprintf(fp,"(and ");
		for(j=1; j<=5; j++){
			fprintf(fp,"(and ");
			for(n=6; n<=6; n++){
				fprintf(fp,"(cont p%d%d%d ",i,j,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");		
	}
	fprintf(fp,"))\n");
	*/
	fprintf(fp,"(check-sat)\n(get-model)\n");

	fclose(fp);
	FILE*fin= popen("z3 inputeasform", "r");
	char buf[128];
	char pnum[128];
	char num[128]; //strcpy를 위한.
	int i_num=0; //int 형 number
	char tru[128]="true)";
	int sudo[11][11];
	int confirm=0;
	int con_num=0;
	int x_1, y_1,num_1;
	for(int r_1=0; r_1<11; r_1++){
		for(int r_2=0; r_2<11; r_2++){
			sudo[r_1][r_2]=0;
		}
	}
	fscanf(fin,"%s %s", buf, buf);
	while(!feof(fin)){
		fscanf(fin, "%s", buf) ; //printf("%s ", buf);
		fscanf(fin, "%s", pnum) ;// printf("%s ", pnum);
		fscanf(fin, "%s", buf) ;// printf("%s ", buf);
		fscanf(fin, "%s", buf) ;// printf("%s ", buf);
		fscanf(fin, "%s", buf) ;// printf("%s\n", buf);
		if(confirm == strcmp( buf, tru)){
			con_num++;
			strcpy(num,pnum+1);
			i_num=atoi(num);
		
			if(i_num%10 == 0){
				num_1=10;
				i_num=i_num/100;	
			}
			else{
				num_1=i_num%10;
				i_num=i_num/10;	
			}
		
			if(i_num%10 == 0){
				y_1=10;
				i_num=i_num/100;	
			}
			else{
				y_1=i_num%10;
				i_num=i_num/10;	
			}
			
			if(i_num%10 == 0){
				x_1=10;
			}
			else{
				x_1=i_num%10;
			}
			/*
			x_1=pnum[1]-'0';
			y_1=pnum[2]-'0';
			num_1=pnum[3]-'0';
			*/
			sudo[x_1][y_1]=num_1;
		} 
	}
	pclose(fin);
	for(int x_sudo=1; x_sudo<=set_n; x_sudo++){
		for(int y_sudo=1; y_sudo<=set_n; y_sudo++){
			printf("%d ",sudo[x_sudo][y_sudo]);
		}
		printf("\n");
	}
	printf("%d\n",con_num);
}
