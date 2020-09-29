#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE*fp=fopen("sudoform", "w");

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


	//S1
	fprintf(fp,"; S1\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=9;i++){
		fprintf(fp,"(and ");
		for(n=1; n<=9; n++){
			fprintf(fp,"(or ");
			for(j=1; j<=9; j++){
				fprintf(fp,"p%d%d%d ", i,j,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
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


	//S3
	fprintf(fp,"; S3\n");
	fprintf(fp,"(assert ");
	fprintf(fp,"(and ");
	for(r=0; r<=2; r++){
		fprintf(fp,"(and ");
		for(s=0; s<=2; s++){
			fprintf(fp,"(and ");
			for(n=1; n<=9; n++){
				fprintf(fp,"(or ");
				for(i=1; i<=3; i++){
					fprintf(fp,"(or ");
					for(j=1;j<=3;j++){
						fprintf(fp,"p%d%d%d ",3*r+i,3*s+j,n);
					}
					fprintf(fp,")");
				}
				fprintf(fp,")");
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

	//S5
	fprintf(fp,"; S5\n");
	fprintf(fp,"(assert (and ");
	for(j=1; j<=9; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=9; n++){
			fprintf(fp,"(and ");
			for(i=1; i<=8; i++){
				fprintf(fp,"(and ");
				for(k=i+1; k<=9; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,k,j,n);
				}
				fprintf(fp,")");
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");

	//S6
	fprintf(fp,"; S6\n");
	fprintf(fp," (assert (and ");
	for(n=1; n<=9; n++){
		fprintf(fp,"(and ");
		for(i=1; i<=8; i++){
			fprintf(fp,"(and ");
			for(k=i+1; k<=9; k++){
				fprintf(fp,"(not (and p%d%d%d p%d%d%d))", i,i,n,k,k,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");


	//S7
	fprintf(fp,"; S7\n");
	fprintf(fp," (assert (and ");
	for(n=1; n<=9; n++){
		fprintf(fp,"(and ");
		for(i=9; i>=1; i--){
			fprintf(fp,"(and ");
			for(k=i-1; k>=1; k--){
				fprintf(fp,"(not (and p%d%d%d p%d%d%d))", i,10-i,n,k,10-k,n);
			}
			fprintf(fp,")");
		}
		fprintf(fp,")");
	}
	fprintf(fp,"))\n");


	//S8
	fprintf(fp,"; S8\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=9; i++){
		fprintf(fp,"(and ");
		for(j=1; j<=9; j++){
			fprintf(fp,"(and ");
			for(n=1; n<=8; n++){
				fprintf(fp,"(and ");
				for(k=n+1; k<=9; k++){
					fprintf(fp,"(not (and p%d%d%d p%d%d%d))",i,j,n,i,j,k);
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
	FILE*fin= popen("z3 sudoform", "r");
	char buf[128];
	char pnum[128];
	char tru[128]="true)";
	int sudo[10][10];
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
			sudo[x_1][y_1]=num_1;
		} 
	}
	pclose(fin);
	for(int x_sudo=1; x_sudo<10; x_sudo++){
		for(int y_sudo=1; y_sudo<10; y_sudo++){
			printf("%d ",sudo[x_sudo][y_sudo]);
		}
		printf("\n");
	}
}

