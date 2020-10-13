#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE*fp=fopen("formmine", "w");

	int i,n,j,r,s,k;
	
	for(i=1; i<=9; i++)
		for(n=1; n<=9; n++)
			for(j=1; j<=9; j++)
				fprintf(fp,"(declare-const p%d%d%d Bool)\n",i,n,j);
	
	char c;
	int c_i;
	fprintf(fp,"; S0\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=9; i++){
		for(j=1; j<=9; j++){
			scanf("%c",&c);
			c_i= c-'0';
			if(c_i > 0 && c_i<10){
				fprintf(fp,"p%d%d%d ",i,j,c_i);
			}
			if(c == ' ' || c== '\n'){
				j--;
			}
		}
	}
	fprintf(fp,"))\n");


	
	//S2
	fprintf(fp,"; S2\n");
	fprintf(fp,"(assert (and ");
	for(j=1; j<=9; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=9; n++){
			fprintf(fp,"(or ");
			for(i=1; i<=9; i++){
				fprintf(fp,"p%d%d%d ",i,j,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");		
	}
	fprintf(fp,"))\n");
	
	//S4
	fprintf(fp,"; S4\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=9; i++){
		fprintf(fp,"(and ");
		for(n=1; n<=9; n++){
			fprintf(fp,"(and ");
			for(j=1; j<=8; j++){
				fprintf(fp,"(and ");
				for(k=j+1; k<=9; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,i,k,n);
				}
				fprintf(fp,")");
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");

	

	

	

	
	fprintf(fp,"(check-sat)\n(get-model)\n");

	fclose(fp);
	FILE*fin= popen("z3 formmine", "r");
	char buf[128];
	char pnum[128];
	char tru[128]="true)";
	int mine[20][20];
	int confirm=0;
	int con_num=0;
	int x_1, y_1,num_1;
	printf("\n");
	fscanf(fin,"%s %s", buf, buf);
	while(!feof(fin)){
		fscanf(fin, "%s", buf) ;// printf("%s ", buf);
		fscanf(fin, "%s", pnum) ; //printf("%s ", pnum);
		fscanf(fin, "%s", buf) ;// printf("%s ", buf);
		fscanf(fin, "%s", buf) ;// printf("%s ", buf);
		fscanf(fin, "%s", buf) ;// printf("%s\n", buf);
		if(confirm == strcmp( buf, tru)){
			con_num++;
			x_1=pnum[1]-'0';
			y_1=pnum[2]-'0';
			num_1=pnum[3]-'0';
			mine[x_1][y_1]=num_1;
		} 
	}
	pclose(fin);
	for(int x_mine=1; x_mine<10; x_mine++){
		for(int y_mine=1; y_mine<10; y_mine++){
			printf("%d ",mine[x_mine][y_mine]);
		}
		printf("\n");
	}
}
