/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
prog2: takes words and puts them into buckets of length given by user in command line
Program #2
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

size_t removeDuplicate(char* line, size_t length, char* duplicate, size_t dupSize);
size_t* addSize_tElement(size_t* list, size_t* size, size_t* capacity, size_t toAdd);
char** addCharElement(char** buckets, size_t* bSize, size_t* Bcapacity, char* bucket);

int main(int argc, char** argv)
{
	//check command line arg is correct
	int x = 0;
	if(argc == 1)
	{
		x = 100;
	}
	else
	{
		x = atoi(argv[1]);
		if((x < 20) || (x > 100000))
		{
//			fprintf(stderr, "Error: not a valid command line argument\n");
			return 1;
		}
	}

	char* temp = NULL;
	char** buckets = NULL;
	size_t bSize = 0;
	size_t bCapacity = 0;
	size_t size = 0;
	size_t capacity = 0;
	size_t* list = NULL;

	while(fscanf(stdin, "%ms", &temp) != EOF)
	{
		size_t tempLength = strlen(temp);
		if(tempLength >=  x)
		{
			free(temp);
			temp = NULL;
			continue;
			//throw this word out
		}

		//loop through all the buckets
		for(size_t i = 0; i < bSize; i++)
		{
			size_t removeLength = 0;
			removeLength = removeDuplicate(buckets[i], list[i], temp, tempLength);
			if(removeLength != list[i])
			{
				list[i] = removeLength;
				free(temp);
				temp = NULL;
				break;
			}
		}
		if(temp == NULL)
		{
			continue;
		}

		for(int i = 0; i < bSize; i++)
		{
			int freeSpace = x - list[i];
			int actualLen = tempLength + 1;
			if(freeSpace >= actualLen && freeSpace - actualLen != 1)
			{
					strcpy(buckets[i] + list[i], temp);
					list[i] += (tempLength + 1);
					free(temp);
					temp = NULL;
					break;
			}
		}
		if(temp == NULL)
		{
			continue;
		}

		//if it wasnt added, make a new bucket
		char* newBucket = (char*)malloc(x * sizeof(char));
		strcpy(newBucket, temp);

		buckets = addCharElement(buckets, &bSize, &bCapacity, newBucket);
		list = addSize_tElement(list, &size, &capacity, tempLength + 1); 

		free(temp);
		temp = NULL;
	}

	for(int i = 0; i < bSize; i++)
	{
		for(int j = 0; j < list[i]-1; j++)
		{
			if(buckets[i][j] == '\0')
			{
				buckets[i][j] = ' ';
			}
		}
		fprintf(stdout, "%6d: %s\n", (int)list[i], buckets[i]);
	}

	free(list);
	for(size_t j = 0; j < size; j++)
	{
		free(buckets[j]);
	}
	free(buckets);
	return 0;
}


size_t removeDuplicate(char*line, size_t length, char* duplicate, size_t dupSize)
{
	if(strcmp(&line[0], duplicate) == 0)
	{
		for(int j = 0; j < length - dupSize; j++)
		{
			memmove(&line[0], &line[dupSize + 1], length - dupSize - 1);
		}
		return length - (dupSize + 1);
	}

	for(int i = 1; i < length; i++)
	{
		if(line[i - 1] == '\0')
		{
			if(strcmp(&line[i], duplicate) == 0)
			{
				memmove(&line[i], &line[i + dupSize + 1], length - dupSize - 1);
				return length - (dupSize + 1);
			}
		}
	}
	return length;
}

size_t* addSize_tElement(size_t* list, size_t* size, size_t* capacity, size_t toAdd)
{
	if(*size == *capacity)
	{
		size_t newCap = (2 * (*capacity) + 1);
		size_t* newList = (size_t*)malloc(newCap * sizeof(size_t));
		for(int i = 0; i < *size; i++)
		{
			newList[i] = list[i];
		}
		free(list);
		list = newList;
		*capacity = newCap;
	}
	list[*size] = toAdd;
	(*size) += 1;
	return list;
}

char** addCharElement(char** buckets, size_t* bSize, size_t* bCapacity, char* bucket)
{
	if(*bSize == *bCapacity)
	{
		size_t newCap = (2 * (*bCapacity) + 1);
		char** newList = (char**)malloc(newCap * sizeof(char*));
		for(int i = 0; i < *bSize; i++)
		{
			newList[i] = buckets[i];
		}
		free(buckets);
		buckets = newList;
		*bCapacity = newCap;
	}
	buckets[*bSize] = bucket;
	(*bSize) += 1;
	return buckets;
}

