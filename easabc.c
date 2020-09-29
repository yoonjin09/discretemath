#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE*fp=fopen("easform", "w");

	int i,n,j,r,s,k;
	
	for(i=1; i<=6; i++)
		for(n=1; n<=6; n++)
			for(j=1; j<=6; j++)
				fprintf(fp,"(declare-const p%d%d%d Bool)\n",i,n,j);
	//E1
	fprintf(fp,"; E1\n");
	fprintf(fp,"(assert (and ");
	for(i=1; i<=6;i++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(or ");
			for(j=1; j<=6; j++){
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
	for(j=1; j<=6; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(or ");
			for(i=1; i<=6; i++){
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
	for(i=1; i<=6; i++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(and ");
			for(j=1; j<=5; j++){
				fprintf(fp,"(and ");
				for(k=j+1; k<=6; k++){
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
	for(j=1; j<=6; j++){
		fprintf(fp,"(and ");
		for(n=1; n<=5; n++){
			fprintf(fp,"(and ");
			for(i=1; i<=5; i++){
				fprintf(fp,"(and ");
				for(k=i+1; k<=6; k++){
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
	for(i=1; i<=6; i++){
		fprintf(fp,"(and ");
		for(j=1; j<=6; j++){
			fprintf(fp,"(and ");
			for(n=1; n<=5; n++){
				fprintf(fp,"(and ");
				for(k=n+1; k<=6; k++){
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
			x_1=pnum[1]-'0';
			y_1=pnum[2]-'0';
			num_1=pnum[3]-'0';
			sudo[x_1][y_1]=num_1;
		} 
	}
	pclose(fin);
	for(int x_sudo=1; x_sudo<=6; x_sudo++){
		for(int y_sudo=1; y_sudo<=6; y_sudo++){
			printf("%d ",sudo[x_sudo][y_sudo]);
		}
		printf("\n");
	}
	printf("%d\n",con_num);
}
