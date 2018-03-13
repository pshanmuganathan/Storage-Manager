
//
//
//  storageManager_working.c
//  Created by Vishal, Prasanna Shanmuganathan and Adithya Ramachandran
//  Group 20

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "dberror.h"
#include "storage_mgr.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* Used main() and struct for testing purposes.

typedef struct SM_FileHandle {
  char *fileName;
  int totalNumPages;
  int curPagePos;
  void *mgmtInfo;
} SM_FileHandle;

  #define PAGESIZE 4096

  extern void createPageFile (char *fileName);
  extern void openPageFile (char *fileName, SM_FileHandle *fHandle);
  extern void closePageFile (SM_FileHandle *fHandle);
  extern void destroyPageFile (char *fileName);

  // Write functions

  extern void writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage);
  extern void appendEmptyBlock (SM_FileHandle *fHandle);
  extern void writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
  extern void ensureCapacity()




void main()
{

    FILE *fp;
    char fname[50];
    char filename[100]  = "C:\\Users\\ar1\\Documents\\c folder\\";


    SM_FileHandle filehandle;
    SM_FileHandle *fhandle;

    printf("enter the file name: \n");
    scanf("%s", fname);

    strcat(fname,".txt");
    strcat(filename,fname);

    filehandle.fileName = filename;
   // filehandle.totalNumPages = 0;
   // filehandle.curPagePos =0;
    fhandle = &filehandle;

    printf("filename : %s \n",fhandle->fileName);



   // printf("File name :%s \n total number of pages :%d \n", fhandle->fileName, fhandle->totalNumPages);

//The below function is used to createPageFile. Value being passed from main()
    createPageFile(&filename[0]);
    //openPageFile(&filename,&filehandle);
    //closePageFile(&filehandle);
    //destroyPageFile (&filename[0]);


}
*/

/******************************************************************************************************
 *  Function Name: initStorageManager
 *
 *  Description:
 *      Initializing storage_manager
 *
 * 
 *  Return:
 *      None
 *
 *  Variables:
 *      None
 *  Author:
 *      Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-21-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

void initStorageManager (void)
{
    printf("\nStorage Manager Initialised\n");
}
/******************************************************************************************************
 *  Function Name: createPageFile
 *
 *  Description:
 *     Create a new page file fileName. The initial file size should be one page. This method should fill this single page with '\0' bytes.
 *
 * 
 *  Return:
 *      RC_OK
 *
 *  Variables:
 *      FILE *fp;
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-21-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC createPageFile (char *fileName)
{
   // SM_FileHandle *fhandle =&fhandle;
  // char filename[100];
  // filename = *fileName;

   FILE *fp;
   fp= fopen(fileName, "w");
   fseek(fp,PAGE_SIZE,SEEK_SET);
   fputc('\0',fp);
   fclose(fp);
   return RC_OK;


  //  printf("File name in check function :%s \n total number of pages :%d \n", fhandle->fileName, fhandle->totalNumPages);

}
/******************************************************************************************************
 *  Function Name: openPageFile
 *
 *  Description:
 *     Opens an existing page file. Should return RC_FILE_NOT_FOUND if the file does not exist. 
 The second parameter is an existing file handle. If opening the file is successful, then the fields of this file handle should be initialized with the information about the opened file. 
 For instance, you would have to read the total number of pages that are stored in the file from disk.
 *
 * 
 *  Return:
 *      RC_OK,RC_FILE_NOT_FOUND
 *
 *  Variables:
 *      FILE *fp;
        int pages = 0;
 *  Author:
 *       Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-22-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC openPageFile (char *fileName, SM_FileHandle *fHandle)
{

    // Found out the page size and set the current page position to 0.
    // Need to use the hardcoded page size value from "dberror.h"


    FILE *fp = fopen(fileName,"r");
    int pages = 0;
  //  int pagesize = 1000;
    if(fp!=NULL)
    {
        fseek(fp,0L,SEEK_END);
        pages = (int)(ftell(fp));
        pages= pages/PAGE_SIZE;
        fHandle->totalNumPages = pages;
        fHandle->curPagePos =0;
        fseek(fp,0L,SEEK_SET);
        printf("The length of the file is : %d \n The current page position is : %d  \n", fHandle->totalNumPages, fHandle->curPagePos);
	fHandle->fileName = fileName;
      //  fclose(fp);
        return RC_OK;
    }

    else
    {
            printf("The file %s does not exist. \n",fileName);
          //  fclose(fp);
	    return RC_FILE_NOT_FOUND;
    }

}
/******************************************************************************************************
 *  Function Name: closePageFile
 *
 *  Description:
 *   Close an open page file 
 *
 * 
 *  Return:
 *      RC_OK
 *
 *  Variables:
 *      FILE *fp;
     
 *  Author:
 *       Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-25-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC closePageFile(SM_FileHandle *fHandle)
{
    // check the functionality once. Description not clear.



    FILE *fp = fopen((fHandle->fileName),"r");

    if(fp==NULL)
    {
            printf("The file %s does not exist. \n",fHandle->fileName);
            fclose(fp);
    }
    else
    {
            if(fclose(fp)==0)
            {
                printf("The file is closed: \n");
                return RC_OK;
            }

            else
                printf("Error in closing the file: \n");

    }

}
/******************************************************************************************************
 *  Function Name: destroyPageFile
 *
 *  Description:
 *  Destroy (delete) a page file.
 *
 * 
 *  Return:
 *      RC_OK,RC_FILE_NOT_FOUND,RC_DELETE_ERROR
 *
 *  Variables:
 *      int tempval,tempval1;
        struct stat buffer;
     
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-25-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC destroyPageFile (char *fileName)
{
    int tempval,tempval1;
    struct stat buffer;

   // FILE *fp = fopen((fileName),"w");


     tempval1=stat(fileName,&buffer);

     if(tempval1==0)
     	tempval=remove(fileName);
     else
     {
	printf(" \n File does not exist \n");
        return RC_FILE_NOT_FOUND;
     }


    if(tempval==0)
    {
           printf("The file %s is deleted. \n",fileName);
           return  RC_OK;
    }
    else
    {
        printf("Error in deleting the file %s. \n",fileName);
        return  RC_DELETE_ERROR;
    }

}
/******************************************************************************************************
 *  Function Name: readBlock
 *
 *  Description:
 *  The method reads the pageNumth block from a file and stores its content in the memory pointed to by the memPage page handle.
  If the file has less than pageNum pages, the method should return RC_READ_NON_EXISTING_PAGE.
 *
 * 
 *  Return:
 *      RC_OK,RC_READ_NON_EXISTING_PAGE
 *
 *  Variables:
 		FILE *fp;
 *           
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-22-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
     FILE *fp;

     fp = fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
         fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
          if((pageNum==1))
          {

              fseek(fp, 0, SEEK_SET);
              fread(memPage,PAGE_SIZE,1,fp);
              fHandle->curPagePos=pageNum;
              fclose(fp);
              return RC_OK;


          }
          else if((pageNum>=2)&&(pageNum<=fHandle->totalNumPages))
          {


             fseek(fp, ((fHandle->totalNumPages)-1)*PAGE_SIZE, SEEK_SET);
             fread(memPage,PAGE_SIZE,1,fp);
             fHandle->curPagePos=pageNum;
             fclose(fp);
             return RC_OK;
          }
          else
          {
              fclose(fp);
              return RC_READ_NON_EXISTING_PAGE;

          }
     }

}

/******************************************************************************************************
 *  Function Name: getBlockPos
 *
 *  Description:
 *  Return the current page position in a file
 * * 
 *  Return:
 *      fHandle->curPagePos
 *
 *  Variables:
 		None
 *           
 *  Author:
 *      Prasanna Shanmuganathan
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-24-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/


int getBlockPos (SM_FileHandle *fHandle)
{
    if(fHandle !=NULL)
    {
        return fHandle->curPagePos;
    }


}
/******************************************************************************************************
 *  Function Name: readFirstBlock
 *
 *  Description:
 * Read the first page in a filee
 * * 
 *  Return:
 *      RC_READ_NON_EXISTING_PAGE,RC_OK
 *
 *  Variables:
 		 FILE *fp;
 *           
 *  Author:
 *      Prasanna Shanmuganathan
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-25-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    FILE *fp;

     fp = fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
         fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
         fseek(fp, 0, SEEK_SET);
         fread(memPage,PAGE_SIZE,1,fp);
          fHandle->curPagePos=1;
          fclose(fp);
          return RC_OK;

     }
}
/******************************************************************************************************
 *  Function Name: readPreviousBlock
 *
 *  Description:
 * Read the previous page in a file based on current page
 * * 
 *  Return:
 *      RC_READ_NON_EXISTING_PAGE
 *
 *  Variables:
 		 FILE *fp;
 *           
 *  Author:
 *      Prasanna Shanmuganathan
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-27-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    FILE *fp;

     fp = fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
         fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
          if(((fHandle->curPagePos)-1)<0)
          {
              fclose(fp);
              printf("\n No previous block found: \n");
              return RC_READ_NON_EXISTING_PAGE;

          }
          else
          {


          fseek(fp, ((fHandle->totalNumPages)-1)*PAGE_SIZE, SEEK_SET);
          fread(memPage,PAGE_SIZE,1,fp);
          fHandle->curPagePos=(fHandle->curPagePos)-1;
          fclose(fp);
          return RC_OK;
          }
     }

/******************************************************************************************************
 *  Function Name: readCurrentBlock
 *
 *  Description:
 * Read the Current page in a file based on current page
 * * 
 *  Return:
 *      RC_READ_NON_EXISTING_PAGE,RC_OK;
 *
 *  Variables:
 		 FILE *fp;
 *           
 *  Author:
 *      Prasanna Shanmuganathan
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-27-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

}

 RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
 {
     FILE *fp;

     fp= fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
         fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
         fseek(fp, ((fHandle->curPagePos-1)*PAGE_SIZE), SEEK_CUR);
         fread(memPage,PAGE_SIZE,1,fp);
         fclose(fp);
         return RC_OK;
     }

 }
 /******************************************************************************************************
 *  Function Name: readNextBlock
 *
 *  Description:
 * Read the Next page in a file based on current page
 * * 
 *  Return:
 *      RC_READ_NON_EXISTING_PAGE,RC_OK;
 *
 *  Variables:
 		 FILE *fp;
 *           
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-21-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
 {
     FILE *fp;

     fp= fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
          fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
         if(((fHandle->curPagePos)+1)>(fHandle->totalNumPages))
         {
             fclose(fp);
             printf("\n Current block is the last block: \n");
             return RC_READ_NON_EXISTING_PAGE;
         }
         else
         {
             fseek(fp,((fHandle->curPagePos)+1)*PAGE_SIZE,SEEK_SET);
             fread(memPage,PAGE_SIZE,1,fp);
             fHandle->curPagePos=(fHandle->curPagePos)+1;
             fclose(fp);
             return RC_OK;
         }
     }



 }
 /******************************************************************************************************
 *  Function Name: readLastBlock
 *
 *  Description:
 * Read the Last page in a file based on current page
 * * 
 *  Return:
 *      RC_READ_NON_EXISTING_PAGE,RC_OK;
 *
 *  Variables:
 		 FILE *fp;
 *           
 *  Author:
 *      Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-23-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

 RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
 {
     FILE *fp;

     fp = fopen(fHandle->fileName,"r");
     if(fp==NULL)
     {
         fclose(fp);
         printf("\n File %s not found: \n",fHandle->fileName);
         return RC_READ_NON_EXISTING_PAGE;
     }
     else
     {
          fseek(fp, ((fHandle->totalNumPages)-1)*PAGE_SIZE, SEEK_SET);
          fread(memPage,PAGE_SIZE,1,fp);
          fHandle->curPagePos=fHandle->totalNumPages;
          fclose(fp);
          return RC_OK;
     }



 }
 /******************************************************************************************************
 *  Function Name: writeBlock
 *
 *  Description:
 * Write a page to disk 
 * * 
 *  Return:
 *      RC_WRITE_FAILED,RC_OK;
 *
 *  Variables:
 		int tempval=0;
    	int offset_value = 0;
    	FILE *fp;
 *           
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-23-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/
RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    int tempval=0;
    int offset_value = 0;
    FILE *fp;

    fp=fopen((fHandle->fileName),"w+");

    if(fp==NULL)
    {
        printf("The file %s does not exist",(fHandle->fileName));
        fclose(fp);
        // Invoke the createFile function to create a file
    }
    else
    {
        if(pageNum>=0)
        {
          if(pageNum>(fHandle->totalNumPages))
          {
              fclose(fp);
              printf(" \n Error.Please increase the page size \n");
              return RC_WRITE_FAILED;
          }
          else if(pageNum==0)
          {
              fseek(fp,0,SEEK_SET);
              fwrite(memPage,1,PAGE_SIZE, fp);
              fHandle->curPagePos=pageNum;
              fclose(fp);
              return RC_OK;
          }
          else if((pageNum==1))
          {
              fseek(fp,(((fHandle->totalNumPages)-1)*PAGE_SIZE),SEEK_SET);
              fwrite(memPage,1,PAGE_SIZE, fp);
              fHandle->curPagePos=pageNum;
              fclose(fp);
              return RC_OK;
          }

          else if((pageNum==2)&&(pageNum<=fHandle->totalNumPages))
          {
              fseek(fp,(((fHandle->totalNumPages)-1)*PAGE_SIZE),SEEK_SET);
              fwrite(memPage,1,PAGE_SIZE, fp);
              fHandle->curPagePos=pageNum;
              fclose(fp);
              return RC_OK;
          }
        }
    }





}
 /******************************************************************************************************
 *  Function Name: appendEmptyBlock
 *
 *  Description:
 * Write a page to disk 
 * * 
 *  Return:
 *      RC_WRITE_FAILED,RC_OK;
 *
 *  Variables:
 		int block_size=0;
 		char temp[PAGE_SIZE]= {'\0'};
    	FILE *fp;
 *           
 *  Author:
 *      Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-26-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

 RC appendEmptyBlock (SM_FileHandle *fHandle)
 {
     FILE *fp;

     int block_size=0;

     char temp[PAGE_SIZE]= {'\0'};

     fp = fopen(fHandle->fileName,"w");

     fseek(fp,(fHandle->totalNumPages)*PAGE_SIZE,SEEK_SET);

     block_size= (int)fwrite(temp,1,PAGE_SIZE,fp);

     fHandle->totalNumPages += 1;

     fclose(fp);

     if(block_size>0)
     {
        printf("Block Appended \n");
        return RC_OK;
     }

     else
        return RC_WRITE_FAILED;

 }
 /******************************************************************************************************
 *  Function Name: writeCurrentBlock
 *
 *  Description:
 * Write a current page to disk 
 * * 
 *  Return:
 *      None
 *
 *  Variables:
 		   int pagenum = fHandle->curPagePos;
    
 *           
 *  Author:
 *       Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-26-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

 RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
 {
     int pagenum = fHandle->curPagePos;

     writeBlock(pagenum,fHandle,memPage);

 }
 /******************************************************************************************************
 *  Function Name: ensureCapacity
 *
 *  Description:
 * Write a current page to disk 
 * * 
 *  Return:
 *      RC_INCREASE_CAPACITY_FAILED,RC_OK
 *
 *  Variables:
 		    FILE *fp;
    int newPages;
    char *temp_buffer;

    
 *           
 *  Author:
 *        Prasanna Shanmuganathan,Vishal Kumar Bimal
 *
 *  History:
 *      Date            Search String                           Content
 *      --------------- --------------------------------------- ----------------------
 *      09-27-2016      None                                    Initialization
 *
 *
 ******************************************************************************************************/

  RC ensureCapacity (int numberOfPages, SM_FileHandle *fHandle)
{
    FILE *fp;
    int newPages;
    char *temp_buffer;

    printf("The number of pages %d: /n",fHandle->totalNumPages);
    if(numberOfPages>fHandle->totalNumPages)
    {
        fp=fopen(fHandle->fileName,"r+");

        newPages = numberOfPages - fHandle->totalNumPages;
        fseek(fp,((numberOfPages) * PAGE_SIZE),SEEK_SET);
        fseek(fp,((fHandle->totalNumPages - numberOfPages)*PAGE_SIZE),SEEK_CUR);
        temp_buffer = malloc(((newPages) * PAGE_SIZE) * sizeof(char));
        fwrite(temp_buffer,1,((newPages) * PAGE_SIZE) ,fp);
        fHandle->totalNumPages = fHandle->totalNumPages+newPages;
        fHandle->curPagePos=fHandle->totalNumPages;
        fclose(fp);
        free(temp_buffer);
        return RC_OK;
    }
    else{
        return RC_INCREASE_CAPACITY_FAILED;
    }




}


