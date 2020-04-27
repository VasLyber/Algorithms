#include <stdio.h>
#include <stdlib.h>
#define BSIZE 1<<15

struct node{
	long data;
	struct node *left;
	struct node *right;
};
long *heightarr;
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1) {
	if (bpos >= bsize) {
	bpos = 0;
	if (feof(stdin)) return x;
	bsize = fread(buffer, 1, BSIZE, stdin);
	}
	c = buffer[bpos++];
	if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
	else if (d == 1) return x;
	}
	return -1;
}

void insert(struct node *root, struct node *ins){	
	if (root->left == NULL) 
		root->left = ins;
	else 
		root->right = ins;
}


int max(int i, int j){
	
	if (i <= j) 
		return j;
	else
		return i;
	
}

//diameter implementation copied from geeks for geeks
long optDiameter(struct node *root, long *height){
	long lh = 0, rh = 0;
	long ldiam = 0, rdiam = 0;

	if (root == NULL) {
		*height = 0;
		return 0;
	}
	ldiam = optDiameter(root->left, &lh);
	rdiam = optDiameter(root->right, &rh);
	*height = max(lh, rh) + 1 ;

	return max(lh+rh+1, max(ldiam, rdiam));
}


int main(){
	long *heightar, diam = 0, dim, h, maxHeight = 0, P, i, j, C, temp, currentmax = 0, finalmax = 0, indextemp, ind;
	struct node *planets,*tree = NULL;
	
	fscanf(stdin, "%ld ", &P);

	planets = (struct node *) malloc(P * sizeof(struct node));
	heightar = malloc(P * sizeof(long));

	for (i = 0; i < P; ++i){
		fscanf(stdin, "%ld ", &C);
		planets[i].data = 1;
		planets[i].left = NULL;
		planets[i].right = NULL;
		if (C != 1){
			struct node * tree = malloc(C * sizeof(struct node));
			for (j = 0; j < C-1; ++j){
				fscanf(stdin, "%ld", &temp);
				tree[j].data = j + 2;
				tree[j].left = NULL;
				tree[j].right = NULL;
				if (temp == 1)
					insert(&(planets[i]), &tree[j]);
				else
					insert(&(tree[temp-2]), &tree[j]);
			}
		}
		else {
			fscanf(stdin, "%ld", &temp);
		}
		dim = optDiameter(&planets[i], &h) - 1;
		if (dim > diam)
			diam = dim;
		h -= 1;
		heightar[i] = h;
		if (h > maxHeight) {
			ind = i;
			maxHeight = h;
		}
	}
	temp = 0;
	i = 0;
	j = 1;
	indextemp = ind;
	
	currentmax = heightar[i] - i;
	while ((i < P) && (j < P)){
		
		indextemp = heightar[j] + j;
		if ((indextemp + temp) > finalmax)	
			finalmax = (indextemp + temp);
		while (i < j){
			currentmax = heightar[i] - i;
			if ((currentmax + indextemp) > finalmax)
				finalmax = currentmax + indextemp;
			if (currentmax > temp)
				temp = currentmax;
			i++;
		}
		j++;
	}
	i = 0;
	j = 1;
	currentmax = heightar[i] +  P + i;
	temp = currentmax;
	while ((i < P) && (j < P)){
		
		indextemp = heightar[j] - j;

		if ((indextemp + temp) > finalmax)	
			finalmax = (indextemp + temp);

		
		while (i < j){
			currentmax = heightar[i] + P + i;
			if ((currentmax + indextemp) > finalmax)
				finalmax = currentmax + indextemp;
			if (currentmax > temp)
				temp = currentmax;
			i++;
		}
	

		j++;	
	}
	if (finalmax < diam)
		printf("%ld\n", diam);
	else
		printf("%ld\n", finalmax);	

	return 0;
}
