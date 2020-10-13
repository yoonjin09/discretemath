#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "intset.h"
intset *
intset_alloc ()
{	
	intset * s = (intset *) malloc(sizeof(intset)) ;
	s->n_elems = 0 ;
	s->elems = 0x0 ;
	return s ;
}

intset * 
intset_clone (intset * orig) 
{
	if (orig == 0x0)
		return 0x0 ;

	intset * s = intset_alloc() ;
	
	s->n_elems = orig->n_elems ;
	s->elems = 0x0 ;
	if (s->n_elems > 0) {
		s->elems = (int *) calloc(s->n_elems, sizeof(int)) ;
		memcpy(s->elems, orig->elems, s->n_elems * sizeof(int)) ;
	}
	return s ;
}

void
intset_print (FILE * fp, intset * s)
{
	fprintf(fp, "{") ;
	for (int i = 0 ; i < s->n_elems ; i++) {
		char * delim = (i > 0) ? ", " : "" ;
		fprintf(fp, "%s%d", delim, s->elems[i]) ;
	}
	fprintf(fp, "}") ;
}

void
intset_free (intset * s) 
{
	free(s->elems) ;
	free(s) ;
}

int
intset_size (intset * s) 
/*
 * returns the number of elements contained in s.
 */
{
	return s->n_elems;
}

int
intset_add (intset * s, int e) 
/*
 * insert a new integer value e to s.
 * return 0 if succeeded. return 1 if it fails.
 * 
 * hint: use realloc. note that s->elems is NULL when it has no element.
 */
{
    if(s->elems == 0x0){
        s->elems = (int *)malloc(sizeof(int));
        s->elems[0]=e;
        s->n_elems=1;
    }
    else{
        for(int i=0; i<s->n_elems; i++){
            if(s->elems[i] == e){
                printf("A: %d\n",s->elems[i]);
                return 1;
                
            }        
        }
        s->elems=(int*)realloc(s->elems,sizeof(int)*((s->n_elems)+1));
        s->elems[s->n_elems]=e;
        s->n_elems++;
        
        return 0;
    }
}

int
intset_remove (intset * s, int e) 
/*
 * remomve e from s.
 * return 0 if succeeded. return 1 if failed.
 *
 * s->elems must be set to NULL if s->n_elems == 0.
 *
 * hint: use realloc.
 */
{
    int confirm=-1;
    if((intset_contains(s,e)) == 0){
        return 0;
    }
	for(int i=0; i<s->n_elems; i++){
        if(s->elems[i] == e){
            confirm=i;
        }
    }
    if(s->elems == 0x0) 
        return 1;
    else{
        
            for(int i=confirm; i<(s->n_elems)-1; i++){
                s->elems[i] = s->elems[i+1];
            }
            s->elems=(int *)realloc(s->elems,sizeof(int)*((s->n_elems)-1));
            s->n_elems--;
        
       
        return 0;
    }
}


int
intset_contains (intset * s, int e) 
/*
 * return 1 if e is contained in s. return 0 otherwise.
 */
{
    int confirm=0;
	for(int i=0; i< s->n_elems; i++){
        if(s->elems[i] == e){
            confirm=1;
        }
    }
    
    return confirm;
}


int
intset_equals (intset *s1, intset *s2) 
/*
 * return 1 if two sets s1 and s2 are equivalent.
 * return 0 otherwise.
 */
{
    int count=0;
	if(s1->n_elems != s2->n_elems){
        return 0;
    }
    for(int i=0; i<s2->n_elems;i++){
        count+=intset_contains(s1, s2->elems[i]);
    }
    if(count == s2->n_elems)
        return 1;
    else
        return 0;
    
}


intset *
intset_union (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the union of s1 and s2.
 *
 * return NULL if the operation fails.
 */
{
    if(s1->n_elems < 0 || s2->n_elems <0){
        return NULL;
    }
    int count=0;
	intset *s3=intset_alloc();
    intset *s4=intset_alloc();
    s3= intset_clone(s1);
    
    for(int i=0; i< s2->n_elems;i++){
        if(intset_contains(s1,s2->elems[i]) != 1){
            intset_add(s3,s2->elems[i]);
        }
    }
    return s3;
    
}


intset *
intset_intersection (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the intersection of s1 and s2.
 *
 * return NULL if the operation fails.
 */
{
    if(s1->n_elems < 0 || s2->n_elems <0){
        return NULL;
    }
	intset * s3= intset_alloc();
    for(int i=0; i<s1->n_elems;i++){
        if(intset_contains(s2, s1->elems[i])==1){
            intset_add(s3,s1->elems[i]);
        }
    }
    return s3;
}


intset *
intset_difference (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the set difference of s1 and s2 (i.e., s1 \ s2).
 *
 * return NULL if the operation fails.
 */
{
    if(s1->n_elems < 0 || s2->n_elems <0){
        return NULL;
    }
    intset * s3 = intset_alloc();
    s3=intset_clone(s1);

	for(int i=0; i<s1->n_elems; i++){
        if(intset_contains(s2,s1->elems[i])==1){
            intset_remove(s3,s1->elems[i]);
        }
    }

    return s3;
}


intset **
intset_subsets (intset * s, size_t k , size_t * n_subsets) 
/*
 * return a new intset array that contains all distinct subsets
 * of s having k elements. The size of the result array must be
 * given to n_subsets.
 * 
 * this operation must be implemented with a recursion.
 *
 * return NULL if the operation fails.
 */
{
    if(k<0 || s->n_elems <k){
        return NULL;
    }
	intset ** ps = (intset **)malloc(sizeof(intset *)*pow(2,intset_size(s)));
    intset ** ps1 = (intset**)malloc(sizeof(intset*) * pow(2,intset_size(s)));
    for(int i=0; i<pow(2,intset_size(s)); i++){
        ps[i]=intset_alloc();
        ps1[i]=intset_alloc();
    }
    if(k == 0){

        return ps;
    }
    int num=0; //ps1 index 올리는 용.
    for(int i=0; i< s->n_elems; i++){
        intset * n = intset_clone(s);
        intset_remove(n,s->elems[i]);
        ps=intset_subsets(n, k-1, n_subsets);
        

        int num_subsets=1;
        for(int i= s->n_elems; i>s->n_elems-k; i--){
            num_subsets= num_subsets*i;
        }
        for(int i=k; i>0; i--){
            num_subsets= num_subsets/i;
        }
        *n_subsets = num_subsets;

        int prev_num_subsets=1;
        for(int i= s->n_elems-1; i>s->n_elems-k; i--){
            prev_num_subsets= prev_num_subsets*i;
        }
        for(int i=k-1; i>0; i--){
            prev_num_subsets= prev_num_subsets/i;
        }

        for(int a=0; a<prev_num_subsets;a++){
            intset_add(ps[a],s->elems[i]);           
        }    

        for(int i=0; i<prev_num_subsets; i++){
            int confirm=0;
            for(int j=0; j<num;j++){
                if(intset_equals(ps[i],ps1[j]) == 1){
                    confirm=1;
                    continue;
                }
            }
            if(confirm == 0)
                    ps1[num++]=intset_clone(ps[i]);
        }

    }
    return ps1;
}
        


intset ** 
intset_powerset (intset * s, size_t * n_subsets) 
/*
 * return a new intset array that contains all distinct subsets
 * of s having. The size of the result array must be given to
 * n_subsets.
 * 
 * this operation must be implemented with a recursion.
 *
 * return NULL if the operation fails.
*/
{
    if(s->n_elems < 0){
        return NULL;
    }
    intset ** ps = (intset **)malloc(sizeof(intset *)*pow(2,intset_size(s)));
    intset ** ps1 = (intset**)malloc(sizeof(intset*) * pow(2,intset_size(s)));

    for(int i=0; i<pow(2,intset_size(s)); i++){
        ps[i]=intset_alloc();
        ps1[i]=intset_alloc();
    }

    if(s->n_elems == 0){
        //return 0;
        return ps;
    }
    else{
        intset * n = intset_clone(s);
        intset_remove(n,s->elems[0]);
        //printf("%d \n", s->n_elems);

        ps = intset_powerset(n, n_subsets);
        //return 0;
        int num=0;
        
        for(int i=0; i<pow(2, intset_size(s)-1); i++){
            ps1[num]=intset_clone(ps[i]);
            num++;
        }
        
        for(int i=0; i<(pow(2, intset_size(s)-1)); i++){
            intset_add(ps[i],s->elems[0]);
        }

        for(int i=0; i<pow(2, intset_size(s)-1); i++){
            ps1[num]=intset_clone(ps[i]);
            num++;
        }
        *n_subsets = pow(2,intset_size(s));
        return ps1;
    }
}

