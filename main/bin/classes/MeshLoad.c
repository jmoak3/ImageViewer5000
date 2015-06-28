#include "MeshLoad.h"
#include "Assets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

int LoadMesh(char * fileName, unsigned short ** pindices, Vector3 ** ppoints, int *numInds, int *numPts)
{
	char *header;
	char text[8192];
	int length;
	GetAsset(fileName, &text, &length);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "MESH %4096s", text);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "MESH %i", length);
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
