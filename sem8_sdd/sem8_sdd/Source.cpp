#include <stdio.h>
#include <iostream>
using namespace std;

struct student
{
	int varsta;
	char *nume;
	float medie;
};

struct heap
{
	student *vect;
	int nrElem;
};

void filtrare(heap h, int index)
{
	int indexMax = index;
	int indexS = 2*index+1;
	int indexD = 2*index+2;

	if(indexS < h.nrElem && h.vect[indexS].varsta > h.vect[indexMax].varsta)
		indexMax = indexS;
	if(indexD < h.nrElem && h.vect[indexD].varsta > h.vect[indexMax].varsta)
		indexMax = indexD;

	if(index != indexMax)
	{
		student temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare(h, indexMax);
	}
}

void inserare(heap *h, student elem)
{
	student *vect1 = (student*)malloc(((*h).nrElem+1) * sizeof(student));
	for(int i=0;i<(*h).nrElem;i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vect1;

	(*h).vect[(*h).nrElem-1] = elem;

	for(int i=((*h).nrElem-1)/2; i>=0; i--)
		filtrare((*h), i);
}

void extragere(heap *h, student *elem)
{
	student *vect1 = (student*)malloc(((*h).nrElem-1) * sizeof(student));

	student temp = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem-1];
	(*h).vect[(*h).nrElem-1] = temp;

	*elem = (*h).vect[(*h).nrElem-1];

	for(int i=0;i<(*h).nrElem-1;i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem--;
	free((*h).vect);
	(*h).vect = vect1;

	for(int i=((*h).nrElem-1)/2; i>=0; i--)
		filtrare((*h), i);
}


void afisare(heap h)
{
	printf("\nElementele heap-ului: ");
	for(int i=0;i<h.nrElem;i++)
		printf("\n%d %s %5.2f", h.vect[i].varsta, h.vect[i].nume, h.vect[i].medie);
}

void main()
{
	heap h;

	printf("Nr. elemente: ");
	scanf("%d", &h.nrElem);

	char buffer[20];

	h.vect = (student*)malloc(h.nrElem * sizeof(student));
	for(int i=0;i<h.nrElem;i++)
	{
		printf("\nElement %d: ", i+1);
		printf("\nVarsta: ");
		scanf("%d", &h.vect[i].varsta);
		printf("\nNume: ");
		scanf("%s", buffer);
		h.vect[i].nume = (char*)malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(h.vect[i].nume, buffer);
		printf("\nMedie: ");
		scanf("%f", &h.vect[i].medie);
	}

	for(int i=(h.nrElem-1)/2;i>=0;i--)
		filtrare(h, i);

	afisare(h);

	student s = {23, "Marcel", 8.5f};
	inserare(&h, s);
	//inserare(&h, 6);

	afisare(h);

	student elem;
	extragere(&h, &elem);
	printf("\nElement extras are varsta %d", elem.varsta);

	afisare(h);
}

				/*15
		7             12
	3     4       10      3*/


				/*15
		7               12
   6		4      10        3
3*/

				/*12
		7             10
	6      4      3        3*/




