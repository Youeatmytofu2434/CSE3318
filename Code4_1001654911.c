/* Coding Assignment 4 */
/*
    Man Luu
    1001654911
*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <limits.h>
#define MAX 50



typedef struct 
{
    char label[5];
    int distance;
    int previous;
    int visited;    
} 
Vertex;

int ReadFileIntoArray (int argc, char *argv[], Vertex VertexArray[MAX], int AdjMatrix[MAX][MAX]);
void Dijsktra (Vertex VertexArray[MAX], int AdjMatrix[MAX][MAX], int VertexCount, int StartVertex);
void addEdge (int start, int end, int weight, int AdjMatrix[MAX][MAX]);
void addVertex (char label[5], Vertex VertexArray[MAX], int *VertexCount);
void CreateArray (int AdjMatrix[MAX][MAX]);
int GettingIndex (Vertex VertexArray[MAX], char IndexLabel[5], int VertexCount);
void PrintMatrix (int AdjMatrix[MAX][MAX], int VertexCount);
void PrintVertexArray (Vertex VertexArray[MAX], int VertexCount);



int ReadFileIntoArray (int argc, char *argv[], Vertex VertexArray[MAX], int AdjMatrix[MAX][MAX])
{
    FILE *fp;
    int VertexCount = 0, i, neighbor, weight;
    char filecontent [50], *token;
    if (argc >= 2) // Checks if argv[1] is provided
    {
        fp = fopen (argv[1], "r");
        if (fp != NULL) // Checks if file exists
        {
            while (fgets (filecontent, sizeof(filecontent), fp) != NULL) // goes thru the file
            {
                //Separates the string
                token = strtok (filecontent, ","); // Label
                addVertex (token, VertexArray, &VertexCount); 
                token = strtok (NULL, ","); // Neighbor
                
                while (token != NULL)
                {
                             
                    neighbor = atoi (token);
                    token = strtok (NULL, ","); // Weight
                    weight = atoi (token);
                    addEdge (VertexCount - 1, neighbor, weight, AdjMatrix);
                    token = strtok (NULL, ","); // Neigbor
                    
                }
                
            }
            fclose (fp);
            return VertexCount;
        }
        else
        {
            perror ("File does not exist!Exiting...");
            exit(0);
        }
    }
    else
    {
        perror ("File must be provided on the command line! Exiting...");
        exit(0);
    }
    
}

void Dijsktra (Vertex VertexArray[MAX], int AdjMatrix[MAX][MAX], int VertexCount, int StartVertex)
{
    int x, i, dofu, cofuv, dofv, SmallestVertexIndex;
    int CurrentVertex = StartVertex;
    VertexArray[StartVertex].distance = 0;
    VertexArray[StartVertex].previous = -1;
    VertexArray[StartVertex].visited = 1;
    
    for (x = 0; x < VertexCount - 1; x++)
    {
        
        // 1st for loop
        for (i = 0; i < VertexCount; i++)
        {
            if (AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
            {                
                
                dofu = VertexArray[CurrentVertex].distance;
                cofuv = AdjMatrix[CurrentVertex][i];
                dofv = VertexArray[i].distance;
                
                if (dofu + cofuv < dofv)
                {
                    dofv = dofu + cofuv;
                    VertexArray[i].distance = dofv;
                    VertexArray[i].previous = CurrentVertex;
                }
                
            }
        }
        // End 1st for loop
        SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        
        // 2nd for loop

        for (i = 0; i < VertexCount; i++)
        {
            if (!VertexArray[i].visited)
            {
                if (VertexArray[i].distance < SmallestVertex)
                {
                    SmallestVertex = VertexArray[i].distance;
                    SmallestVertexIndex = i;
                }
            }
        }
        // End 2nd for loop  
        CurrentVertex = SmallestVertexIndex;
        VertexArray[CurrentVertex].visited = 1;
    }
}


void addEdge (int start, int end, int weight, int AdjMatrix[MAX][MAX])
{
    AdjMatrix[start][end] = weight;
}

void addVertex (char label[5], Vertex VertexArray[MAX], int *VertexCount)
{
    strcpy (VertexArray[*VertexCount].label, label);
    VertexArray[*VertexCount].visited = 0;
    VertexArray[*VertexCount].previous = -1;
    VertexArray[*VertexCount].distance = -1;
    (*VertexCount)++;
    
}

void CreateArray (int AdjMatrix[MAX][MAX])
{
    int i, j;
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            AdjMatrix[i][j] = -1;
        }
    }
}

int GettingIndex (Vertex VertexArray[MAX], char IndexLabel[5], int VertexCount)
{
    int index = 0;
    while (index < VertexCount && strcmp (IndexLabel, VertexArray[index].label) != 0)
    {
        index++;
    }
    return index;
}

void PrintMatrix (int AdjMatrix[MAX][MAX], int VertexCount)
{
    int i, j;
    for (i = 0; i < VertexCount; i++)
    {
        for (j = 0; j < VertexCount; j++)
        {
            printf ("%5d\t", AdjMatrix[i][j]);
        }
        printf ("\n");
    }
}

void PrintVertexArray (Vertex VertexArray[MAX], int VertexCount)
{
    printf ("\n\n\tI\tL\tD\tP\tV\n");
    for (int i = 0; i < VertexCount; i++)
    {
        printf ("\t%d\t%s\t%d\t%d\t%d\n", i,
                    VertexArray[i].label, VertexArray[i].distance,
                    VertexArray[i].previous, VertexArray[i].visited);
    }
    printf ("\n");
}



int main (int argc, char *argv[])
{
    char StartVertexLabel[5], DestIndexLabel[5];
    int VertexCount, StartVertex = 0, DestIndex = 0;
    int AdjMatrix[MAX][MAX];
    Vertex VertexArray [MAX];
    CreateArray (AdjMatrix);
    
    
    VertexCount = ReadFileIntoArray (argc, argv, VertexArray, AdjMatrix);
    
    PrintMatrix (AdjMatrix, VertexCount);
    
    // Getting the index of starting vertex
    printf ("\nWhat is the starting vertex? ");
    scanf ("%s", StartVertexLabel);
    StartVertex = GettingIndex (VertexArray, StartVertexLabel, VertexCount);
    
    //Dijsktra
    Dijsktra (VertexArray, AdjMatrix, VertexCount, StartVertex);
    
    
    
    PrintVertexArray (VertexArray, VertexCount);
    return 0;
}
