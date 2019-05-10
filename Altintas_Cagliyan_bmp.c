
/*
* Auteur 1: Metehan Altintas
* Auteur 2: Ahmet Yasin Cagliyan
* Link naar github repository: https://github.com/meto51/bmp
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Simplified declaration of used types
typedef uint32_t DWORD; 
typedef int32_t  LONG; 
typedef uint16_t WORD;

#pragma pack(push, 1) //Disable padding
	typedef struct teInverteren //Struct to temporarily save 1 byte value
	{
		unsigned char tempByte;
	}RGBSAVE;
	#pragma pack(pop)


//Struct to save infoheader
#pragma pack(push, 1) //Disable padding
typedef struct INFOHeader
{
	DWORD infoGrootte;		//Struct size (byte)
	LONG infoBreedte;		//Bitmap width (pixel)
	LONG infoHoogte;		//Bitmap height (pixel)
	WORD kleurPlane;	//Amount of color planes (1)
	WORD bitPerPixel;			//Amount of bits per pixel
	DWORD compressieType;	//Compression type
	DWORD bestandGrootte;	//Image size (byte)
	LONG xResolutie;			//X axis pixels per meter
	LONG yResolutie;			//Y axis pixels per meter
	DWORD bmpKleuren;		//Amount colors used in bitmap
	DWORD bmpKleurenImp;	//Amount important colors
}INFOHEADER;
#pragma pack(pop)
	
//Struct to save fileheader
#pragma pack(push, 1) //Disable padding
typedef struct BMPHeader
{
	WORD bestandType; 	//File type
	DWORD bestandGrootte; 	//File size (byte)
	WORD reserved1; 	//Reserved (0)
	WORD reserved2;	//Reserved (0)
	DWORD headerOffset;	//Offset fileheader to actual bitmap (bit)
}HEADER;
#pragma pack(pop)

int main()
{
	FILE *filePointerIn = NULL;
	
	filePointerIn = fopen("input.bmp", "rb"); //Open input file as read-only (binary)
	if(filePointerIn == NULL)
	{
			printf("Kan bestand niet openen\n");
			exit(EXIT_FAILURE);
			return 0;
	}
	
	FILE *filePointerOut = NULL;
	
	filePointerOut = fopen("output.bmp", "wb"); //Open/create output file as writable (binary)
	if(filePointerOut == NULL)
	{
		printf("Kan bestand niet aanmaken\n");
		exit(EXIT_FAILURE);
		return 0;
	}
	
	HEADER headFile;
	INFOHEADER infoHead;
	
	//Next 4 lines copy header information
	fread(&headFile, sizeof(headFile), 1, filePointerIn);
	fwrite(&headFile, sizeof(headFile), 1, filePointerOut);
	fread(&infoHead, sizeof(infoHead), 1, filePointerIn);
	fwrite(&infoHead, sizeof(infoHead), 1, filePointerOut);
	
	RGBSAVE saveVariable;
	/*for(unsigned int loopTilEnd = 0; loopTilEnd < infoHead.bestandGrootte; loopTilEnd++)
	{
		fread(&saveVariable.tempByte, 1, 1, filePointerIn);
		
		fwrite(&saveVariable.tempByte, 1, 1, filePointerOut);
	}*/
	unsigned char testClause = 1; //Variable to check error at end of file to stop loop
	while(testClause == 1)
	{
		testClause = fread(&saveVariable.tempByte, 1, 1, filePointerIn); //Read value
		saveVariable.tempByte = ~saveVariable.tempByte; //Invert value
		fwrite(&saveVariable.tempByte, 1, 1, filePointerOut); //Write value
	}
	
	//Next 2 lines end transmission
	fclose(filePointerIn);
	fclose(filePointerOut);
	return 0;
}

//------------------------------------------------------------
//
//	Bronvermelding
//	https://stackoverflow.com/questions/23725180/pixel-manipulation-on-bitmap-file-in-c
//
//
//
//
