#include "MeshLoad.h"
#include "Assets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#include <android/log.h>

static char text[] =
"v 0.000000 -1.000000 0.000000\n"
"v 0.723607 -0.447220 0.525725\n"
"v -0.276388 -0.447220 0.850649\n"
"v -0.894426 -0.447216 0.000000\n"
"v -0.276388 -0.447220 -0.850649\n"
"v 0.723607 -0.447220 -0.525725\n"
"v 0.276388 0.447220 0.850649\n"
"v -0.723607 0.447220 0.525725\n"
"v -0.723607 0.447220 -0.525725\n"
"v 0.276388 0.447220 -0.850649\n"
"v 0.894426 0.447216 0.000000\n"
"v 0.000000 1.000000 0.000000\n"
"v -0.162456 -0.850654 0.499995\n"
"v 0.425323 -0.850654 0.309011\n"
"v 0.262869 -0.525738 0.809012\n"
"v 0.850648 -0.525736 0.000000\n"
"v 0.425323 -0.850654 -0.309011\n"
"v -0.525730 -0.850652 0.000000\n"
"v -0.688189 -0.525736 0.499997\n"
"v -0.162456 -0.850654 -0.499995\n"
"v -0.688189 -0.525736 -0.499997\n"
"v 0.262869 -0.525738 -0.809012\n"
"v 0.951058 0.000000 0.309013\n"
"v 0.951058 0.000000 -0.309013\n"
"v 0.000000 0.000000 1.000000\n"
"v 0.587786 0.000000 0.809017\n"
"v -0.951058 0.000000 0.309013\n"
"v -0.587786 0.000000 0.809017\n"
"v -0.587786 0.000000 -0.809017\n"
"v -0.951058 0.000000 -0.309013\n"
"v 0.587786 0.000000 -0.809017\n"
"v 0.000000 0.000000 -1.000000\n"
"v 0.688189 0.525736 0.499997\n"
"v -0.262869 0.525738 0.809012\n"
"v -0.850648 0.525736 0.000000\n"
"v -0.262869 0.525738 -0.809012\n"
"v 0.688189 0.525736 -0.499997\n"
"v 0.162456 0.850654 0.499995\n"
"v 0.525730 0.850652 0.000000\n"
"v -0.425323 0.850654 0.309011\n"
"v -0.425323 0.850654 -0.309011\n"
"v 0.162456 0.850654 -0.499995\n"
"f 1//1 14//1 13//1\n"
"f 2//2 14//2 16//2\n"
"f 1//3 13//3 18//3\n"
"f 1//4 18//4 20//4\n"
"f 1//5 20//5 17//5\n"
"f 2//6 16//6 23//6\n"
"f 3//7 15//7 25//7\n"
"f 4//8 19//8 27//8\n"
"f 5//9 21//9 29//9\n"
"f 6//10 22//10 31//10\n"
"f 2//11 23//11 26//11\n"
"f 3//12 25//12 28//12\n"
"f 4//13 27//13 30//13\n"
"f 5//14 29//14 32//14\n"
"f 6//15 31//15 24//15\n"
"f 7//16 33//16 38//16\n"
"f 8//17 34//17 40//17\n"
"f 9//18 35//18 41//18\n"
"f 10//19 36//19 42//19\n"
"f 11//20 37//20 39//20\n"
"f 39//21 42//21 12//21\n"
"f 39//22 37//22 42//22\n"
"f 37//23 10//23 42//23\n"
"f 42//24 41//24 12//24\n"
"f 42//25 36//25 41//25\n"
"f 36//26 9//26 41//26\n"
"f 41//27 40//27 12//27\n"
"f 41//28 35//28 40//28\n"
"f 35//29 8//29 40//29\n"
"f 40//30 38//30 12//30\n"
"f 40//31 34//31 38//31\n"
"f 34//32 7//32 38//32\n"
"f 38//33 39//33 12//33\n"
"f 38//34 33//34 39//34\n"
"f 33//35 11//35 39//35\n"
"f 24//36 37//36 11//36\n"
"f 24//37 31//37 37//37\n"
"f 31//38 10//38 37//38\n"
"f 32//39 36//39 10//39\n"
"f 32//40 29//40 36//40\n"
"f 29//41 9//41 36//41\n"
"f 30//42 35//42 9//42\n"
"f 30//43 27//43 35//43\n"
"f 27//44 8//44 35//44\n"
"f 28//45 34//45 8//45\n"
"f 28//46 25//46 34//46\n"
"f 25//47 7//47 34//47\n"
"f 26//48 33//48 7//48\n"
"f 26//49 23//49 33//49\n"
"f 23//50 11//50 33//50\n"
"f 31//51 32//51 10//51\n"
"f 31//52 22//52 32//52\n"
"f 22//53 5//53 32//53\n"
"f 29//54 30//54 9//54\n"
"f 29//55 21//55 30//55\n"
"f 21//56 4//56 30//56\n"
"f 27//57 28//57 8//57\n"
"f 27//58 19//58 28//58\n"
"f 19//59 3//59 28//59\n"
"f 25//60 26//60 7//60\n"
"f 25//61 15//61 26//61\n"
"f 15//62 2//62 26//62\n"
"f 23//63 24//63 11//63\n"
"f 23//64 16//64 24//64\n"
"f 16//65 6//65 24//65\n"
"f 17//66 22//66 6//66\n"
"f 17//67 20//67 22//67\n"
"f 20//68 5//68 22//68\n"
"f 20//69 21//69 5//69\n"
"f 20//70 18//70 21//70\n"
"f 18//71 4//71 21//71\n"
"f 18//72 19//72 4//72\n"
"f 18//73 13//73 19//73\n"
"f 13//74 3//74 19//74\n"
"f 16//75 17//75 6//75\n"
"f 16//76 14//76 17//76\n"
"f 14//77 1//77 17//77\n"
"f 13//78 15//78 3//78\n"
"f 13//79 14//79 15//79\n"
"f 14//80 2//80 15//80\n"
"end";

int LoadMesh(char * fileName, unsigned short ** pindices, Vector3 ** ppoints, int *numInds, int *numPts)
{
	char *header;
	//char text[4096]
	//int length;
	//GetAsset(fileName, &text, &length);
	header = strtok(text, " \n");

	*numPts = 0;
	*numInds = 0;
	int sizePts = 36;
	int sizeInds = 12;
	Vector3 *points = malloc(sizeof(Vector3)*sizePts);
	unsigned short *indices = malloc(sizeof(unsigned short)*sizeInds);
	int done = 0;
	while (!done && header!=NULL)
	{
		char *data;
		if (strcmp(header, "v")==0)
		{
			data = strtok(NULL, " \n");
			points[*numPts].x = atof(data);
			data = strtok(NULL, " \n");
			points[*numPts].y = atof(data);
			data = strtok(NULL, " \n");
			points[*numPts].z = atof(data);
			++(*numPts);
			if (*numPts >= sizePts) 
			{
				Vector3 * temp = malloc(sizeof(Vector3)*sizePts*2);
				memcpy(temp, points, sizeof(Vector3)*sizePts);
				Vector3 * tempPoints = points;
				points = temp;
				free(tempPoints);
				tempPoints = 0;
				temp = 0;
				sizePts = 2*sizePts;
			}
		}
		else if (strcmp(header, "f")==0)
		{
			int i=0;
			for (i=0;i<3;++i)
			{
				char *read;
				char tri[128];
				int j=0;
				for (j=0;j<128;++j)
				{
					tri[j] = 0;
				}
				read = strtok(NULL, " \n");

				
				for (j=0;j<128;++j)
				{
					if (read[j] == '/' && read[j+1] == '/')
					{
						j+=2;
						break;
					}
					tri[j] = read[j];
				}
				int bummy = atoi(tri);
				indices[*numInds] = bummy-1;
				++(*numInds);
				if (*numInds >= sizeInds) 
				{
					unsigned short * temp = malloc(sizeof(unsigned short)*sizeInds*2);
					memcpy(temp, indices, sizeof(unsigned short)*sizeInds);
					unsigned short * tempInds = indices;
					indices = temp;
					free(tempInds);
					tempInds = 0;
					temp = 0;
					sizeInds = 2*sizeInds;
				}
			}
		}
		else if (strcmp(header, "end")==0)
		{
			done = 1;
		}
		header = strtok(NULL, " \n");
	}

	if (*numInds!=sizeInds)
	{
		unsigned short * temp = malloc(sizeof(unsigned short)*(*numInds));
		memcpy(temp, indices, sizeof(unsigned short)*(*numInds));
		unsigned short * tempInds = indices;
		indices = temp;
		free(tempInds);
		tempInds = 0;
		temp = 0;
	}
	

	if (*numPts!=sizePts)
	{
		Vector3 * temp = malloc(sizeof(Vector3)*(*numPts));
		memcpy(temp, points, sizeof(Vector3)*(*numPts));
		Vector3 * tempPoints = points;
		points = temp;
		free(tempPoints);
		tempPoints = 0;
		temp = 0;
	}



	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "num inds: %i", 
													*numInds);
    int i=0;
    for (i=0;i<*numInds;i+=3)
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "ind %i %i %i", 
												indices[i], indices[i+1], indices[i+2]);
	}
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "num verts: %i", 
													*numPts);
    for (i=0;i<*numPts;++i)
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "vert %f %f %f", 
												points[i].x, points[i].y, points[i].z);
	}

	*ppoints = points;
	*pindices = indices;

	return 1;
}
