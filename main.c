#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main()
{
    char filename []="fruits.bmp";
   FILE *streamIn =fopen(filename,"rb");
   strcat(filename,"SepiaFilter_half.bmp");
   FILE *fout =fopen(filename,"wb");
   if(streamIn ==(FILE*)0)
    printf("unable to open\n");

    printf("x");
    unsigned char header[54];
    unsigned char colorTable[1024];

      fread(header,sizeof(unsigned char),54,streamIn);
      fwrite(header,sizeof(unsigned char),54,fout);

    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bitDepth = *(int *)&header[28];
    printf("%d X %d  %d",width,height,bitDepth);
if(bitDepth<=8)
{
    fread(colorTable,sizeof(unsigned char),1024,streamIn);
    fwrite(colorTable,sizeof(unsigned char),1024,fout);

}

int imgsize =width*height;
int r,g,b;
unsigned char buffer[imgsize][3];
for(int i=0;i<imgsize;i++)
{
    r=g=b=0;
    buffer[i][0]=getc(streamIn);
    buffer[i][1]=getc(streamIn);
    buffer[i][2]=getc(streamIn);
    if(i<80)
     printf("%d %d %d :-",buffer[i][0],buffer[i][1],buffer[i][2]);

    r=(buffer[i][0]*0.393) + buffer[i][1]*0.769 + buffer[i][2]*0.189;
    g=(buffer[i][0]*0.349) + buffer[i][1]*0.686 + buffer[i][2]*0.168;
    b=(buffer[i][0]*0.272) + buffer[i][1]*0.534 + buffer[i][2]*0.131;
    if(i<80)
     printf("%d %d %d \n",r,g,b);
    if(r>255) r=255;
    if(g>255) g=255;
    if(b>255) b=255;
    //if(i<imgsize/2){

     putc(r,fout);
     putc(g,fout);
    putc(b,fout);

   // }
   // else{
    //    putc(buffer[i][0],fout);
//p utc(buffer[i][0],fout);
     //   putc(buffer[i][0],fout);

   // }
}
fclose(fout);
fclose(streamIn);

    return 0;
}
