#include "simulation.h"
#include "server_type.h"
#include "simulation.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;


int main(int argc, char *argv[]){
    try{
        if (argc<3)
        {
            ostringstream oStream;
            oStream<<"Error: Wrong number of arguments!" <<endl;
            oStream<<"Usage: ./p2 <username> <logfile>" <<endl;
            throw Exception_t(INVALID_ARGUMENT, oStream.str());
        }
       }
    catch (Exception_t &exception){
        cout << exception.error_info;
        return 0;
        }
    ifstream ifile;
// Check whether we can open the files given. If not,end the program.
    try {
            fileopen(argv[1]);
            fileopen(argv[2]);
        }
    catch (Exception_t &exception)
        {
            return 0;
        }  
     /////////////////////////////////////////////////////////////////////////////
    // Read username file
    ifile.open(argv[1]);
    string file1;
    getline(ifile,file1);
    int usernum=0;
    string line;
    User_t user[MAX_USERS];
    while(getline(ifile, line))
    {
        try
        {
            overmaxuser_(usernum,"Users",user[0]);
        }   
        catch (Exception_t &exception)
        {
            cout << exception.error_info;
                return 0;
        }        
      user[usernum++].username=line;
    }    
    ifile.close();
    for (int i=0;i<usernum;i++)// Read files like "zhuzhuoer" //"user_info"
    {
        ostringstream directory;
        directory<<file1<<"//"<<user[i].username<<"//"<<"user_info";
        try {
                fileopen1(directory.str(),user[i],file1);
        }
        catch (Exception_t &exception) {return 0;}

        ifile.open(directory.str());
        ifile>>user[i].num_posts;
        try
        {
            overmaxuser_(user[i].num_posts,"Post",user[i]);
        }   
        catch (Exception_t &exception)
        {
            cout << exception.error_info;
                return 0;
        }   
        ifile>>user[i].num_following;
        try
        {
            overmaxuser_(user[i].num_following,"Following",user[i]);
        }   
        catch (Exception_t &exception)
        {
            cout << exception.error_info;
            return 0;
        }  
        getline (ifile,line);
        for (unsigned int ii=0;ii<user[i].num_following;ii++)
        {
            getline(ifile,line);
            user[i].following[ii]=&user[findrank(user,line,usernum)];
            //string pp=(*user[i].following[ii]).username;
        }
        ifile>>user[i].num_followers;
        try
        {
            overmaxuser_(user[i].num_followers,"Follower",user[i]);
        }   
        catch (Exception_t &exception)
        {
            cout << exception.error_info;
            return 0;
        }  
        getline(ifile,line);
        for (unsigned int ii=0;ii<user[i].num_followers;ii++)
        {
            getline(ifile,line); 
            user[i].follower[ii]=&user[findrank(user,line,usernum)];
        }
        ifile.close();// End of reading user_info
        ///////////////////////////////////////////////////////////////////////////////////
        //Begin at reading post;
        for (unsigned int ii=0;ii<user[i].num_posts;ii++)
        {
            ostringstream dir_post;
            dir_post<<file1<<"//"<<user[i].username<<"//"<<"posts"<<"//"<<ii+1;
            try {
                fileopen2(dir_post.str(),user[i],ii+1,file1);
            }
            catch (Exception_t &exception) {return 0;}  //Read post files error
            ifile.open(dir_post.str());
            user[i].posts[ii].owner=&user[i];
            getline(ifile,line);
            user[i].posts[ii].title=line;
            getline(ifile,line);
            user[i].posts[ii].num_tags=0;
            while (judgetag(line)) //Reading tags
            {
                try 
                {
                   overmaxpost_tag(user[i].posts[ii].num_tags,"tags",user[i].posts[ii],line);
                }
                catch (Exception_t &exception) 
                {
                    cout << exception.error_info;
                    return 0;
                }
               posttagconstruct(&user[i].posts[ii],&user[i].posts[ii].num_tags,line);
               getline(ifile,line);
            }
            user[i].posts[ii].text=line;
            ifile>>user[i].posts[ii].num_likes;
            try 
            {
                overmaxpost(user[i].posts[ii].num_likes,"likes",user[i].posts[ii]);
            }
            catch (Exception_t &exception) 
            {
                cout << exception.error_info;
                return 0;
            }
            getline(ifile,line); //read "\n"
            int likenum=0;
            for (unsigned int iii=0;iii<user[i].posts[ii].num_likes;iii++)
            {
                getline(ifile,line); 
                user[i].posts[ii].like_users[likenum++]=&user[findrank(user,line,usernum)];
            }
            ifile>>user[i].posts[ii].num_comments;
            try 
            {
                overmaxpost(user[i].posts[ii].num_comments,"comments",user[i].posts[ii]);
            }
            catch (Exception_t &exception) 
            {
                cout << exception.error_info;
                return 0;
            }
            getline(ifile,line); //read "\n"
            for (unsigned int iii=0;iii<user[i].posts[ii].num_comments;iii++)
            {
                getline(ifile,line); 
                user[i].posts[ii].comments[iii].user=&user[findrank(user,line,usernum)];
                getline(ifile,line); 
                user[i].posts[ii].comments[iii].text=line;
            }
            ifile.close();
        }
    }//End of read username file;
    /////////////////////////////////////////////////////////////////////  
    //Read logfile;
    ifile.open(argv[2]);
    while(getline(ifile, line))
    {
    try{
      trending(user,usernum,line);
      follow(line,user,usernum);
      unfollow(line,user,usernum);
      like(user,usernum,line);
      unlike(user,usernum,line);
      if (line.find("comment")!=string::npos&&line.find("uncomment")==string::npos)//comment fucntion;
      {
          string line_;
          getline(ifile,line_);
          comment(user,usernum,line,line_);
      }
      uncomment(user,usernum,line);
      if (line.find("post")!=string::npos) //Post function 
      {
          istringstream istream;
          istream.str(line);
          string name;
          istream>>name;
          int p1=findrank(user,name,usernum);
          getline(ifile,line); 
          user[p1].posts[user[p1].num_posts].owner=&user[p1];
          user[p1].posts[user[p1].num_posts].title=line;
          getline(ifile,line);
          while (judgetag(line))
          {
              posttagconstruct(&user[p1].posts[user[p1].num_posts],&user[p1].posts[user[p1].num_posts].num_tags,line);
               getline(ifile,line);
          }
          user[p1].posts[user[p1].num_posts++].text=line;
          cout<<">> post"<<endl;
      }
       delet(user,usernum,line);
       refresh(user,usernum,line);
       visit(user,usernum,line);
    }
    catch (Exception_t &exception) 
    {
        cout << exception.error_info;
    } 
    }
    ifile.close();
} 