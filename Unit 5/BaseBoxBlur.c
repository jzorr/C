////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//TODO: finish me


////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

#pragma warning(disable: 4996)

//problem assumptions
#define BMP_HEADER_SIZE_BYTES 14
#define BMP_DIB_HEADER_SIZE_BYTES 40
#define MAXIMUM_IMAGE_SIZE 256

//bmp compression methods
//none:
#define BI_RGB 0

//TODO: finish me


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

typedef struct BMP_Header
{
    char signature[2];        //ID field
    int size;               //Size of the BMP file
    short reserved1;        //Application specific
    short reserved2;        //Application specific
    int dataOffset;  //Offset where the pixel array (bitmap data) can be found
};

typedef struct BMP_Info
{
    //BMP_Header fileHeader;
    int size;
    long width;
    long height;
    int planes;
    int bitsPerPixel;
    long compression;
    long imageSize;
    long hResolution;
    long vResolution;
    long colors;
    long importantColors;
};

struct RGB
{
    unsigned int red, green, blue;
};

////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE


//TODO: finish me

void main(int argc, char* argv[])
{

    //TODO: finish me

    //sample code to read first 14 bytes of BMP file format
    FILE* file = fopen("test1wonderbread.bmp", "rb");
    FILE* outFile;
   
    // read the file name given by the user and open it.
    char fileName[128];
    char *data;
    int n;
    
    //printf("Enter .bmp file name\n");
    //scanf("%123s", fileName); //%123s is a buffer size for 124 bytes
    //strcat(fileName, ".bmp"); //string contatinate on the file passed by the user
    //FILE *file = fopen(fileName, "rb"), 
    
    //check if the fileName is valid
    if(fileName == NULL)
        return NULL;
    int imageIdx = 0; // image index counter
    unsigned char tempRGB; // swap variable
    //create an exit if it is null
   
    //create the struct's to pass information into
    struct BMP_Header header; //header struct
    struct BMP_Info info; //info struct
    struct RGB rgb; //rgb struct

    //read bitmap file header (14 bytes)
    fread(&header.signature, sizeof(char)*2, 1, file);
    fread(&header.size, sizeof(int), 1, file);
    fread(&header.reserved1, sizeof(short), 1, file);
    fread(&header.reserved2, sizeof(short), 1, file);
    fread(&header.dataOffset, sizeof(int), 1, file);
   
    //read bitmap file info (40 bytes)
    fread(&info.size, sizeof(int), 1, file);
    fread(&info.width, sizeof(long), 1, file);
    fread(&info.height, sizeof(long), 1, file);
    fread(&info.planes, sizeof(int), 1, file);
    fread(&info.bitsPerPixel, sizeof(int), 1, file);
    fread(&info.compression, sizeof(long), 1, file);
    fread(&info.imageSize, sizeof(long), 1, file);
    fread(&info.hResolution, sizeof(long), 1, file);
    fread(&info.vResolution, sizeof(long), 1, file);
    fread(&info.colors, sizeof(int), 1, file);
    fread(&info.importantColors, sizeof(int), 1, file);
   
    //read pixel file info (3 bytes, 1 reserved but not used)
    fread(&rgb.red, sizeof(int), 1, file);
    fread(&rgb.green, sizeof(int), 1, file);
    fread(&rgb.blue, sizeof(int), 1, file);
    
    
    //------------------------------------begin code from https://stackoverflow.com/questions/11129138/reading-writing-bmp-files-in-c
    // read the input file header
//     header = (BMP_Header*)malloc(sizeof(BMP_Header));
//     if(header == NULL)
//         return 1;
    
//     //read the info from the image
//     data = (char*)malloc(sizeof((char)*info->imageSize));
//     if(data == NULL)
//     {
//         //figure more stuff output  
//     }
    
//     fseek(file, sizeof(char)*header->dataOffset,SEEK_SET);
//     n = fread(data,sizeof(char),(*info).imageSize, file);
//     if(n < 1)
//     {
//         //do more stuff
//     }
//     
//     // configure the file output
//     if(outFile == NULL)
//     {
//      // return 0;
//     }
    
    outFile = fopen("test1wonderbread.bmp", "wb");
    
    
    n = fwrite(header,sizeof(char),sizeof(header),outFile);
    if(n < 1)
    {
        //do more stuff\
    }
    
    fseek((outFile, sizeof(char)*BMP_Header->header.dataOffset, SEEK_SET);
    
      
        

 ////////////////////////make sure the data is loading //////////////////////// 
    // printing the info on the BMP_Header
    printf("\nsignature: %c%c\n", header.signature[0], header.signature[1]);
    printf("size: %d\n", header.size);
    printf("reserved1: %d\n", header.reserved1);
    printf("reserved2: %d\n", header.reserved2);
    printf("dataOffset: %d\n", header.dataOffset);
   
    // printing the info on the BMP_Info
    printf("\nsize: %d\n", info.size);
    printf("width: %ld\n", info.width);
    printf("height: %ld\n", info.height);
    printf("number of planes: %d\n", info.planes);
    printf("bits per pixel: %d\n", info.bitsPerPixel);
    printf("compression: %ld\n", info.compression);
    printf("image size: %ld\n", info.imageSize);
    printf("horizontal resolution: %ld\n", info.hResolution);
    printf("vertical resolution: %ld\n", info.vResolution);
    printf("colors: %d\n", info.colors);
    printf("important colors: %d\n", info.importantColors);
   
    // printing the info on the RBG file
    printf("red: %u\n", rgb.red);
    printf("green: %u\n", rgb.green);
    printf("blue: %u\n", rgb.blue);

//----------------------------------------------------------------------
    //output file trial
   
    fclose(file);
}