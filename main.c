#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>


#define SPACE ' '

//Function used by libcurl to allocate memory to data received from the HTTP response

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
int main () 
{

  char str[1000], *start, pv, location[1000],youtube[1000],songs[1000],cal[100],search[100],instance_type[1000],instance_name[1000],phone_number[1000],message[1000],s3_folder[100],s3_bucket_name[100];
  int c, d, len=0;

  //Getting home directory out of configuration file
  FILE *fp;
  fp=fopen("config","rw");
  if(fp == NULL)
  {
    fprintf(stderr,"Unable to open config file\n");
    return 1;
  }
  int i=0;
  char cfg_line[1000];
  cfg_line[i]=fgetc(fp);
  i++;
  while(cfg_line[i-1]!='\n'&&cfg_line[i-1]!=EOF)  
  {
  	cfg_line[i]=fgetc(fp);
  	i++;
  }
  cfg_line[i-1]='\0';
  char * HOME_DIR = strchr(cfg_line, '=');
  HOME_DIR = HOME_DIR+2;

//Get preferred media player from config file
 i=0;
 char media_player[1000];
 media_player[i]=fgetc(fp);
 i++;
 while(media_player[i-1]!='\n'&&media_player[i-1]!=EOF)
 {
 	media_player[i]=fgetc(fp);
 	i++;
 }

media_player[i-1]='\0';
 char * M_P = strchr(media_player, '=');
 M_P = M_P+2;
 //-----------------------
 //Get preferred Webbrowser out of config file
 i=0;
 char webbrowser[1000];
 webbrowser[i]=fgetc(fp);
 i++;
 while(webbrowser[i-1]!='\n'&&webbrowser[i-1]!=EOF)
 {
 	webbrowser[i]=fgetc(fp);
 	i++;
 }
 
 webbrowser[i-1]='\0';
 char * WebBrowser = strchr(webbrowser, '=');
 WebBrowser = WebBrowser+2;
 
 
  fclose(fp);
 
//Inform user about preferred media player, as to config file
 char preferred_media_player[1000];
 sprintf(preferred_media_player,"say Your preferred media player is %s",M_P);
 system(preferred_media_player);
 //Inform user about preferred web browser, as to config file
 char preferred_webbrowser[1000];
 sprintf(preferred_webbrowser,"say Your preferred webbrowser is %s",WebBrowser);
 system(preferred_webbrowser);

  do
  {
int i1=0,j1=0;

   system("tput setaf 3; echo How can I help you?");
    char * x="Hey, How can I help you?";
    system("tput setaf 6");
    //printf("%s\n",x);
    fgets (str, 1000, stdin);
    if ((strlen(str)>0) && (str[strlen (str) - 1] == '\n'))
        str[strlen (str) - 1] = '\0';

    //change uppercase letters in str to lowercase for convenience
    int i, s = strlen(str);
    for (i = 0; i < s; i++)
        str[i] = tolower(str[i]);  

    char buf[9999];
    char buffer[9999];
    char buff[9999];
    char weather[9999];
    char song[9999];
    

//---------------------------------------------------------------------------------------------------------------------
//Artificial Intelligence
    
    char example[1000];
    strcpy(example,str);
	  int compare[10];
    char split[10][10]={0};
    int k=0,n,j=0,w=0,g=0,go=0,me=0,res=0,c=0,u=0,h=0,temp=0,hos=0,ins=0,wa=0,db=0,yt=0,s3=0;
    char result[20];
    int weather_score=0,greeting_score=0,media_score=0,google_score=0,youtube_score=0,help_score=0,hospital_score=0,restaurant_score=0,instance_score=0,whatsapp_score=0,rds_score=0,s3_score=0;

    //for weather---------------

    char *weather_class[10][10]={{"please","show","outside","condition"},
          {"how"," ","weather","today"},
          {"weather"," ","desired","place"}};
   //for Ec2 instance------------
    char *instance_class[10][10]={{"please","launch","an","ec2","instance"},
          {"launch"," ","ec2","instance"},
          {"create"," ","ec2","instance"}};

//for S3 bucket------------
    char *s3_class[10][10]={{"please","create","a","s3","bucket"},
          {"create"," ","s3","bucket"},
          {"launch"," ","s3","bucket"}};

//for Whatsapp-----------
    char *whatsapp_class[10][10]={{"please","a","write","whatsapp","message"},
          {"type"," ","whatsapp","message"},
          {"type"," ","whatsapp","msg"}};

//for RDS-----------
    char *rds_class[10][10]={{"please","launch","a","rds","instance"},
          {"Launch"," ","rds","instance"},
          {"create"," ","database","instance"}};


    //for greeting--------------

    char *greeting_class[10][10]={{"hey","how","are","you"},
          {"how"," "," ","doing"},
          {"hello","there"," "," "}};

    //for google----------------

    char *google_class[10][10]={{"open","google","for","me"},
          {"I","want","search","browse"},
          {"can","you","open","google"}};

    //for media-----------------

    char *media_class[10][10]={{"can","you","list","media"},
          {"video","listen","play","music"},
          {"play","something","nice","song "}};

    //for Restaurant

    char *restaurant_class[10][10]={{"Please","find","some","restaurants"},
          {"Find"," ","some","restaurants"},
          {"Show"," "," ","restaurants"},
          {"Find","places","to","eat"}};
    //for Hospital

    char *hospital_class[10][10]={{"Please","find","some","hospitals"},
          {"Find"," ","some","hospitals"},
          {"Show"," "," ","hospitals"},
          {"hospitals","near","","me"}};


    //for youtube----------------

    char *youtube_class[10][10]={{"open","youtube","for","me"},
          {"I","want","search","youtube"},
          {"can","you","open","youtube"}};


    for(int i=0;i<strlen(example);i++)
    {
      if(example[i]==' ')
      { 
        if(example[i+1]!=' ')
        {
           split[k][j]='\0';
           j=0;
           k++;
        }
        continue;
      }
      else
      {
        split[k][j++]=example[i];       
      }       
    }

    split[k][j]='\0';


weather_score=0,greeting_score=0,media_score=0,google_score=0,youtube_score=0,help_score=0,hospital_score=0,restaurant_score=0,instance_score=0,whatsapp_score=0,rds_score=0;
      
    
    //For Weather---------------------------------------

    for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(weather_class[b][c],split[v])== 0)
              {
                 w++;
          
              }   
          }
        }
        weather_score=w;

//for ec2----

for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(instance_class[b][c],split[v])== 0)
              {
                 ins++;
          
              }   
          }
        }
        instance_score=ins;

//for s3----

for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(s3_class[b][c],split[v])== 0)
              {
                 s3++;
          
              }   
          }
        }
        s3_score=s3;

//for youtube----

for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(youtube_class[b][c],split[v])== 0)
              {
               yt++;
          
              }   
          }
        }
        youtube_score=yt;



//for Whatsapp----

for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(whatsapp_class[b][c],split[v])== 0)
              {
                 wa++;
          
              }   
          }
        }
        whatsapp_score=wa;

    //For Greeting-----------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        { 
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(greeting_class[b][c],split[v])== 0)
                {
                   g++;  
                }    
            }
        }
        greeting_score=g;

 //For RDS-----------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        { 
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(rds_class[b][c],split[v])== 0)
                {
                   db++;  
                }    
            }
        }
        rds_score=db;


    //For Google-------------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
    {
      for(int c=0;c< 4 ;c++)
      {
          if(strcmp(google_class[b][c],split[v])== 0)
          {
             go++; 
          }   
      }
    }
    google_score=go;


    //For Media---------------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        {
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(media_class[b][c],split[v])== 0)
                {
                   me++; 
                }   
            }
        }
        media_score=me;

    //For Restaurant-----------------------------------
    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        {
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(restaurant_class[b][c],split[v])== 0)
                {
                   res++; 
                }   
            }
        }
        restaurant_score=res;
 //For Hospital-----------------------------------
    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        {
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(hospital_class[b][c],split[v])== 0)
                {
                   hos++; 
                }   
            }
        }
        hospital_score=hos;



j1=0;
int k1=0;
int score[10]={whatsapp_score,instance_score,hospital_score,greeting_score,google_score,restaurant_score,weather_score,rds_score,youtube_score,s3_score};

for(i1=0;i1<=9;i1++)
{
//printf("%d",score[i1]);
if(k1<=score[i1])
{k1=score[i1];
j1=i1;
//printf("%d",j1);
}
}


if(j1==0){
strcpy(result,"whatsapp");
}
else if(j1==1)
strcpy(result,"instance");
else if(j1==2)
strcpy(result,"hospital");
else if(j1==3)
strcpy(result,"greeting");
else if(j1==4)
strcpy(result,"google");
else if(j1==5)
strcpy(result,"restaurant");
else if(j1==6)
strcpy(result,"weather");
else if(j1==7)
strcpy(result,"rds");
else if(j1==8)
strcpy(result,"youtube");
else if(j1==9)
strcpy(result,"s3");





    if((strcmp(result, "greeting") == 0))
    {
        system("say I am good");
        printf("I am good \n");
    } 

    else if(strcmp(str, "firefox") == 0 || strcmp(str, "open firefox") == 0 || strcmp(str,"run firefox") == 0 || strcmp(str, "start firefox") == 0)
    {
            system("say opening firefox");
            system("firefox");
    }
    else if((strcmp(str, "vlc") == 0) || (strcmp(str, "open vlc") == 0) || (strcmp(str,"run vlc") == 0) || (strcmp(str, "start vlc") == 0))
    {
            system("say opening vlc");
            system("vlc");
    }
   // Weather
    else if((strcmp(result, "weather") == 0))
    {
            printf("Please enter location to get weather forecast \n" );
            fgets (location, 1000, stdin);
            system("say showing weather");
            sprintf(weather,"curl wttr.in/\%s",location);
            system(weather);
    }
   //instance
    else if((strcmp(result,"instance")==0))
    {   system("tput bold; echo -----------------------------------------------------------------------------------------Input------------------------------------------------------------------------------------------");

        system("tput bold; echo Enter the instance type");

	fgets (instance_type, 1000, stdin);
	printf("\n");
	system("tput bold; echo Enter the instance name");

	fgets (instance_name, 1000, stdin);
printf("\n");

	

        sprintf(buf, "%s http://13.127.98.80/cgi-bin/testec2.py?j=t2.micro&l=%s", WebBrowser,instance_name);
        system(buf);

   }

  //S3
    else if((strcmp(result,"s3")==0))
    {   system("tput bold; echo -----------------------------------------------------------------------------------------Input------------------------------------------------------------------------------------------");

        system("tput bold; echo Enter the bucket name");

	fgets (s3_bucket_name, 100, stdin);
	printf("\n");
sprintf(buf,"aws s3api create-bucket  --create-bucket-configuration LocationConstraint=ap-south-1 --query {\"Location:Location\"} --output text --bucket %s",s3_bucket_name);
        system(buf);
        /*printf("\n\nIf you want to sync the bucket with a folder press1 otherwise press2\n");
int choice;
        scanf("%d",&choice);
        if(choice==1){
system("tput bold; echo Enter the folder path");
	fgets (s3_folder, 100, stdin);
	printf("\n");
buf="aws s3 sync "+s3_folder+" s3://"+s3_bucket_name;
system(buf);
system("echo Synced Successfully");
}*/
   }
 //Whatsapp
     else if((strcmp(result,"whatsapp")==0))
    {  
    system("tput bold; echo -----------------------------------------------------------------------------------------Input------------------------------------------------------------------------------------------");
    printf("Enter the phone number ");
    fgets(phone_number, 1000, stdin);
printf("\n");
    printf("Enter the message ");
    fgets(message,1000,stdin);
    system("say writing the message");


        sprintf(buf, "%s http://web.whatsapp.com/send?phone=%s&text=%s", WebBrowser,phone_number,message);
   
        system(buf);
   
   
   }

    //RDS
    else if((strcmp(result,"rds")==0))
    {  
        system("tput bold; echo Wait for few seconds RDS instance is launching");
        sprintf(buf, "%s http://65.0.74.63/cgi-bin/rdstest.py", WebBrowser);
        system(buf);
   
   }
    else if((strcmp(result,"youtube")==0))
    {
           




fgets (search, 1000, stdin);
                //-------------------------------------------------
                start = malloc(strlen(str)+1);


                pv = 0;//previous character
                for(d=c=0; search[c]; ++c)
                {
                    if(search[c] == SPACE)
                    {
                       if(pv != SPACE)
                          start[d++] = '+';
                          pv = SPACE;
                    } 
                    else 
                    {
                          pv = start[d++] = search[c];
                    }
                }
                start[d] = '\0';





            //--------------------------------
            sprintf(buff,"say searching youtube for \%s",search);
            system(buff);
            sprintf(buf, "%s https://www.youtube.com/results?search_query=\%s", WebBrowser,start);
            system(buf);

    }
    else if((strcmp(result, "media") == 0))
    {
    		system("say here are the list of available media");
            printf("Here are the list of available media\n");
          	char * sys_cmd1;
          	char sys_cmd[1000];
          	sys_cmd1 = "ls ";
          	sprintf(sys_cmd,"%s%s%s",sys_cmd1,HOME_DIR,"media/");
            system(sys_cmd);
            system("say which media do you want me to play");
            printf("Which media do you want me to play? \n");
            fgets (songs, 1000, stdin);
            sprintf(song,"%s %smedia/\%s",M_P,HOME_DIR,songs);
            system(song);

    }
    
    //Restaurant
    else if((strcmp(result,"restaurant"))==0)
    {

		find_restaurants();

    }
//Hospital
    else if((strcmp(result,"hospital"))==0)
    {

		find_hospitals();

    }
    //Help
    else if((strcmp(str, "help") == 0))
    {
	        char * help1 = "less ";
          	char help[1000];
          	sprintf(help,"%s%s%s",help1,HOME_DIR,"help.txt");
            system(help);
    }
    else if((strcmp(result, "google") == 0))
    {
            /*if( (google_score==0) && (greeting_score==0) && (weather_score==0) && (media_score==0))
            {
      
                // fgets (search, 1000, stdin);
                //-------------------------------------------------
                start = malloc(strlen(str)+1);
                pv = 0;//previous character
                for(d=c=0; str[c]; ++c)
                {
                    if(str[c] == SPACE)
                    {
                       if(pv != SPACE)
                          start[d++] = '+';
                          pv = SPACE;
                    } 
                    else 
                    {
                        pv = start[d++] = str[c];
                    }
                }
                start[d] = '\0';
                //--------------------------------
                sprintf(buff,"say Do you mean \%s",str);
                system(buff);
                sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
                system(buf);
            }
            else 
            {*/
                printf("What can I search for you on Google?\n");
                fgets (search, 1000, stdin);
                //-------------------------------------------------
                start = malloc(strlen(str)+1);


                pv = 0;//previous character
                for(d=c=0; search[c]; ++c)
                {
                    if(search[c] == SPACE)
                    {
                       if(pv != SPACE)
                          start[d++] = '+';
                          pv = SPACE;
                    } 
                    else 
                    {
                          pv = start[d++] = search[c];
                    }
                }
                start[d] = '\0';



                //--------------------------------

                sprintf(buf, "%s https://www.google.co.in/search?q=%s",WebBrowser, start);
                system(buf);

             

    }
}	
 
while((strcmp(str,"stop")!=0));
return 0;
}
