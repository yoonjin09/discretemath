#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE*fp=fopen("easform", "w");

	int i,n,j,r,s,k;
	
	int s_n=9;
	
	for(i=0; i<s_n; i++)
		for(n=0; n<s_n; n++)
			for(j=0; j<s_n; j++)
				fprintf(fp,"(declare-const p%d%d%d Bool)\n",i,n,j);
	//E1
	fprintf(fp,"; E1\n");
	fprintf(fp,"(assert (and ");
	for(i=0; i<s_n;i++){
		fprintf(fp,"(and ");
		for(n=0; n<5; n++){
			fprintf(fp,"(or ");
			for(j=0; j<s_n; j++){
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
	for(j=0; j<s_n; j++){
		fprintf(fp,"(and ");
		for(n=0; n<5; n++){
			fprintf(fp,"(or ");
			for(i=0; i<s_n; i++){
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
	for(i=0; i<s_n; i++){
		fprintf(fp,"(and ");
		for(n=0; n<5; n++){
			fprintf(fp,"(and ");
			for(j=0; j<s_n-1; j++){
				fprintf(fp,"(and ");
				for(k=j+1; k<s_n; k++){
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
	for(j=0; j<s_n; j++){
		fprintf(fp,"(and ");
		for(n=0; n<5; n++){
			fprintf(fp,"(and ");
			for(i=0; i<s_n-1; i++){
				fprintf(fp,"(and ");
				for(k=i+1; k<s_n; k++){
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
	for(i=0; i<s_n; i++){
		fprintf(fp,"(and ");
		for(j=0; j<s_n; j++){
			fprintf(fp,"(and ");
			for(n=0; n<4; n++){
				fprintf(fp,"(and ");
				for(k=n+1; k<5; k++){
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
	FILE*fin= popen("z3 easform", "r");
	char buf[128];
	char pnum[128];
	char num[128];
	int i_num=0;
	char tru[128]="true)";
	int sudo[10][10];
	int confirm=0;
	int con_num=0;
	int x_1, y_1,num_1;
	fscanf(fin,"%s %s", buf, buf);
	while(!feof(fin)){
		fscanf(fin, "%s", buf) ; printf("%s ", buf);
		fscanf(fin, "%s", pnum) ; printf("%s ", pnum);
		fscanf(fin, "%s", buf) ; printf("%s ", buf);
		fscanf(fin, "%s", buf) ; printf("%s ", buf);
		fscanf(fin, "%s", buf) ; printf("%s\n", buf);
		if(confirm == strcmp( buf, tru)){
			con_num++;
			strcpy(num,pnum+1);
			i_num=atoi(num);

			x_1=i_num/100;
			i_num= i_num%100;

			y_1=i_num/10;
			i_num= i_num%10;

			num_1=i_num;
			sudo[x_1][y_1]=num_1;
		} 
	}
	pclose(fin);
	for(int x_sudo=0; x_sudo<s_n; x_sudo++){
		for(int y_sudo=0; y_sudo<s_n; y_sudo++){
			printf("%d ",sudo[x_sudo][y_sudo]);
		}
		printf("\n");
	}
	printf("%d\n",con_num);
}	
