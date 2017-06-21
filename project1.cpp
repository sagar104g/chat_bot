#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string.h>

using namespace std;
//download the page
void getPage(char *url)
{
    char urlbuffer[300]={0};
    strcat(urlbuffer, "curl -o /home/sagar/try/data.txt ");     //put sownload comand in url buffer
    strcat(urlbuffer, url);
    system(urlbuffer);                                          //gives command to system to execute

}
//open the file and put whole data in a string
string toBuffer() {
string s;
string line;
 ifstream myfile ("/home/sagar/try/data.txt");        //open the file
 if (myfile.is_open())
 {
   while ( getline (myfile,line) )                    //gets whole lin at a time
   {
     s+=line;
   }
   myfile.close();
 }
 else cout << "Unable to open file";
return s;
}
//put dict,places,news files data in vector
vector<string> places_vect(char* str) {
vector<string> v;
string line;
 ifstream myfile (str);                   //opens the file given in str
 if (myfile.is_open())
 {
   while ( getline (myfile,line) )        //gets data line by line
   {
     v.push_back(line);
   }
   myfile.close();
 }
 else cout << "Unable to open file";
return v;
}
//find lat and lng according to city
char* lat_lng(){
  string file1=toBuffer();             //gets file data
  int npos=0,p=0;
  char* data=new char[50];
  npos = file1.find("lat",npos);       //find lat and return its position
  if(npos>0){
    npos+=7;
    while(file1[npos]!=','){
      data[p]=file1[npos];
      p++;
      npos++;
    }
  npos = file1.find("lng",npos);     //find lng and return its position
  npos+=7;
  data[p]=',';
  p++;
  while(file1[npos]!=' '){
    data[p]=file1[npos];
    p++;
    npos++;
  }
  data[p]='\0';
  return data;                      // lat and lng stored in it
}
return NULL;
}
//download file according to city and returns lat lng
char* file_download(char *place){
  int a=200+strlen(place);
  char url[a]={0};

  strcat(url, "https://maps.googleapis.com/maps/api/geocode/json?address=");
 int b=strlen(url);
  for(int i=0;place[i]!='\0';i++){
    if(place[i]!=' '){
      url[b]=place[i];
    }else{
      url[b]='+';
    }
    b++;
  }
  url[b]='\0';
  strcat(url, ",+CA&key=AIzaSyCSEr1eNRZVFnINIilygYBCuccmLju5YWg");    //in url whole link is stored to get city data
  getPage(url);                                                       //download page according to url
  for(int i=0;i<1000000;i++){
    for(int j=0;j<1000;j++){
         //use to delay time in program
    }
  }
  char*p=lat_lng();                                                  //gets lat lng from downloaded file
  return p;
}
//gets weathers detail;
char* weather_data(){
  string file1=toBuffer();                                          //gets files data in string
  int npos=0,p=0;
  char* data=new char[50];
  npos = file1.find("icon",npos);                                  //find icon and returns its position
  if(npos>0){
    npos+=7;
    while(file1[npos]!='"'){
      data[p]=file1[npos];
      p++;
      npos++;
    }
    data[p]='+';
    p++;
  npos = file1.find("temperature",npos);                          //find temprature and return its position
  npos+=12;
  data[p]=',';
  p++;
  while(file1[npos]!=','){
    data[p]=file1[npos];
    p++;
    npos++;
  }
  data[p]='\0';
  return data;                                                  //returns weather details
}
}
//genrate weather url according to its city
char* weather_url(char* data){
  int a=200+strlen(data);
  char url[a]={0};

  strcat(url, "https://api.darksky.net/forecast/752770327547cb53dc960c9b1c9d69d6/");
 int b=strlen(url);
  for(int i=0;data[i]!='\0';i++){
      url[b]=data[i];
    b++;
  }
  url[b]='\0';
  strcat(url, "?exclude=minutely,hourly,daily,alerts,flags");
  getPage(url);                                                         //geting page from web for the given urls
  for(int i=0;i<1000000;i++){
    for(int j=0;j<1000;j++){
          //to delay time
    }
  }
  char* p=weather_data();                                     //gets weathers data in p
  return p;
}
//return news information
char* news_data(){
  string file1=toBuffer();                                           //gets files data in a string
  int npos=0,p=0;
  char* data=new char[5000];
  npos = file1.find("description",npos);                              //find description and find it position
  while(npos>0&&p<4000){
    npos+=14;
    while(p<4000){
      if(file1[npos]=='"'&&file1[npos+1]==','&&file1[npos+2]=='"'){
        break;
      }
      data[p]=file1[npos];
      p++;
      npos++;
    }
    data[p]='+';
    p++;
  npos = file1.find("description",npos);                             //find description and find its position
}
  data[p]='\0';
  return data;
}
//genatate url according to news type
char* news_url(string data){
  int a=200;
  char url[a]={0};
  char type[data.length()+2];
  for(int i=0;i<=data.length();i++){
    type[i]=data[i];
  }
  strcat(url, "https://newsapi.org/v1/sources?category=");
  strcat(url,type);
  getPage(url);                                             //downlaod page for the given url
  for(int i=0;i<1000000;i++){
    for(int j=0;j<1000;j++){
        //time delay
    }
  }
  char* p=news_data();                                      //gets the news fom file
  if(p[0]=='\0'){
    return NULL;
  }else{
  return p;
    }
}
//find place nearby as u want it
char* nearby_data(){
  string file1=toBuffer();              //gets file data to string
  int npos=0,p=0;
  char* data=new char[5000];
  npos = file1.find("name",npos);        //find name and return it position
  if(npos>=0){
  while(npos>0&&p<400){
    npos+=9;
    while(p<400){
      if(file1[npos]=='"'&&file1[npos+1]==','){
        break;
      }
      data[p]=file1[npos];
      p++;
      npos++;
    }
    data[p]='=';
    p++;
    npos = file1.find("vicinity",npos);   //find vicinity and return it position
    npos+=13;
    while(p<4000){
      if(file1[npos]=='"'&&file1[npos+1]==' '){
        break;
      }
      data[p]=file1[npos];
      p++;
      npos++;
    }
    data[p]='+';
    p++;
  npos = file1.find("name",npos);         //find name and return its position
}
}else{
  data[0]='N';
  data[1]='O';
  p=2;
}
  data[p]='\0';
  return data;
}
//genarate url according to user choice nearby
char* nearby_url(char* data,string data1){
  int a=200;
  char url[a]={0};
  char type[data1.length()+2];
  for(int i=0;i<=data1.length();i++){
    type[i]=data1[i];
  }
  strcat(url, "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=");
  strcat(url,data);
  strcat(url,"'&'radius=5000'&'type=");
  strcat(url,type);
  strcat(url,"'&'key=AIzaSyA2YxqZFS3wLCmUWl1ku9souErJPfUP1po");
  getPage(url);                                                    //downlaod page according to given url
  for(int i=0;i<1000000;i++){
    for(int j=0;j<1000;j++){
          //to delay time
    }
  }
  char* p=nearby_data();                                          //gets nearby data
  return p;
}
//match data of user input to files data
string data_finder(char* data,char* temp,vector<string> places,vector<string> dict,vector<string> news){
  vector<string> data1;                           //put user input in vector word by word
  char* token = strtok(data, " ");
  string a1,b1,c1,d1;
    while( token != NULL )
    {
      string token1;
      int i=0;
      for(i;token[i]!='\0';i++){
        token1+=token[i];
      }
      token1[i]='\0';
      if(i>2){
      data1.push_back(token1);
    }
       token = strtok(NULL, " ");
    }
    for(int i=0;i<data1.size();i++){
      a1=data1[i];
      for(int j=0;j<places.size();j++){           //compareing nearby palces data
        string b1=places[j];

        if(b1==a1){
          b1+="1";
          return b1;
        }
      }

      for(int j=0;j<dict.size();j++){            //compareing dict data
        c1=dict[j];
        if(c1==a1){
          a1+="2";
          return a1;
        }
      }

      for(int j=0;j<news.size();j++){             //compareing news data
        d1=news[j];
        if(d1==a1){
          d1+="3";
          return d1;
        }
      }

    }
    return " ";
}
//responce to user given here
char*  another_function(string token,vector<string> v){
  char city[20];
  char rule=token[token.length()-1];
  token[token.length()-1]='\0';
  char* b;
  char *e;
  char* c;
  char *d;
  switch(rule){
    case '1': cout<<"i will find "<<token<<" nearby just enter the city name :)"<<endl;
              cin.getline(city,20);           //getting city
                b=file_download(city);        //download city data
                if(b!=NULL){
                e=nearby_url(b,token);        //getting nearby data
                if(e[0]=='N' && e[1]=='O' && e[2]=='\0'){
                 cout<<"oops there is no "<<token<<" nearby"<<endl;
                }else{
                return e;
              }
              }else{
              cout<<"r u sure this city exist because m not able to see it :/";
              }
               break;
    case '2': cout<<"i will find "<<token<<" just enter the city name :)"<<endl;
              cin.getline(city,20);            //getting city
              b=file_download(city);           //downlaod city data
              if(b!=NULL){
              c=weather_url(b);                //getting weathers data
              return c;
            }else{
              cout<<"r u sure this city exist because m not able to see it :/";
            }
              break;
    case '3': if(token[0]=='n'&&token[1]=='e'&&token[2]=='w'&&token[3]=='s'&&token[4]=='\0'){
      cout<<"i will find "<<token<<" just enter the type which type of news u want :)"<<endl;
      for(int i=0;i<v.size();i++){
        cout<<i<<" "<<v[i]<<endl;
      }
        cin.getline(city,20);         //getting news type
        d=news_url(city);              //gets news data
         if(d!=NULL){
        return d;
      }else{
        cout<<"i dont have that stuff :/"<<endl;
      }
                }else{
                    cout<<"i will find u "<<token<<endl;
                    d=news_url(token);
                    return d;
                    }

              break;
    default : cout<<"sorry m not getting u T.T"<<endl;    //if m not getting user
                return NULL;
  }
    return NULL;
  }
void formated_output(char a,char* b){
  int o=0;
switch(a){
  case '1':
              cout<<"name = ";
            for(int i=0;b[i]!='\0';i++){
              if(b[i]=='+'||b[i]=='='){
                cout<<endl;
                  if(b[i]=='+'){
                    cout<<"name = ";
                  }else{
                    cout<<"address = ";
                  }

                }else{
                 cout<<b[i];
           }
          }
          cout<<endl;
            break;
  case '2':

            cout<<"summary = ";
            for(o=0;b[o]!='\0';o++){
              if(b[o]=='+'){
                break;
                }else{
                 cout<<b[o];
           }
          }
          cout<<endl;
            cout<<"temprature = ";
            o+=3;
            for(o;b[o]!='\0';o++){
                 cout<<b[o];
          }
          cout<<endl;



            break;
  case '3':
            for(int i=0;b[i]!='\0';i++){
              if(b[i]=='+'){
                cout<<endl;
              }else{
              cout<<b[i];
            }
            }
          cout<<endl;
            break;
}
}
int main(){
vector<string> places;
vector<string> others;
vector<string> news;
string token;
char data[1000],temp[5];
temp[0]=' ';
temp[1]='\0';
char value;
places=places_vect("/home/sagar/try/places.txt"); //put palces data in vector
others=places_vect("/home/sagar/try/dict.txt");   //put dict data in vector
news=places_vect("/home/sagar/try/news.txt");     //put news data in vector
while(1){
  cin.getline(data,1000);                         //gettting users input
  token=data_finder(data,temp,places,others,news);//finds data is simmilr or not
  value=token[token.length()-1];
  char* a=another_function(token,news);          //user will intract here

   if(a!=NULL){
   formated_output(value,a);
      }
    }
return 0;
}
