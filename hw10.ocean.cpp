
#include <iostream>
#include "hw10.ocean.h"
#include <vector>
#include <thread>
#include "hw10.sea.h"

int seaSize;
Ocean::Ocean(){
   Sea* Sptr = new Sea(0,0,true);
   seas.push_back(Sptr);
};

auto f = [](Sea* s) {
   s->SimulateOneStep();
};

int Ocean::seaExist(int x,int y){
   int  temp=INT_MAX;
   for (int i=0; i<seas.size(); ++i)  {
      if(seas[i]!=nullptr){
         if(seas[i]->startx== x && seas[i]->starty== y)
            temp=i;
      }
   }
   return temp;
}

bool Ocean::checSize(){
  return seas.size()>=max_seas;
}



void Ocean::SimulateOneStep() throw(int){
   seaSize= static_cast<int>(seas.size()) ;
   for (int i=0; i<seas.size(); ++i) {
      if(seas[i]==NULL){
         seas.erase(seas.begin()+1, seas.begin() + i);
         i=i-1;
         continue;
      }
      std::thread t(f, seas[i]);
      ThreadVector.push_back(std::move(t));
   }

   for(auto &t: ThreadVector){
      if (ThreadVector.size()>1) {
         if (t.joinable()) {
            t.join();
         }
      }
   }

   //   for (int i=0; i<seas.size(); ++i) {
   //      seas[i]->SimulateOneStep();
   //   }

   
   for (int i=0; i<seas.size(); ++i) {
     // checSize();
      if(seas[i]==NULL){
         seas.erase(seas.begin()+i, seas.begin() + i);
         i=i-1;
         continue;
      }

      if(seas[i]->up_buffer->size()!=0 ){
         int k;
         int index=seaExist(seas[i]->startx,seas[i]->starty-SIZE);
         if(index == INT_MAX){
            seas[i]->above = new Sea(seas[i]->startx,seas[i]->starty-SIZE,false);
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->up_buffer->size(); ++k) {
                  if (seas[i]->above->cells[m][k].empty()) {
                     seas[i]->above->cells[m][k]=seas[i]->up_buffer[k];
                     if (k == seas[i]->up_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->up_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->above);
         }else{
            int k;
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->up_buffer->size(); ++k) {
                  if (seas[index]->cells[m][k].empty()) {
                     seas[index]->cells[m][k]=seas[i]->up_buffer[k];
                     if (k == seas[i]->up_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->up_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->above);
         }
      }

      if(seas[i]->down_buffer->size()!=0 ){
         int k;
         int index=seaExist(seas[i]->startx,seas[i]->starty+SIZE);
         if(index == INT_MAX){
            seas[i]->below = new Sea(seas[i]->startx,seas[i]->starty+SIZE,false);
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->down_buffer->size(); ++k) {
                  if (seas[i]->below->cells[m][k].empty()) {
                     seas[i]->below->cells[m][k]=seas[i]->down_buffer[k];
                     if (k == seas[i]->down_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->down_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->below);
         }else{
            int k;
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->down_buffer->size(); ++k) {
                  if (seas[index]->cells[m][k].empty()) {
                     seas[index]->cells[m][k]=seas[i]->down_buffer[k];
                     if (k == seas[i]->down_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->down_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->below);
         }
      }

      if(seas[i]->left_buffer->size()!=0 ){
         int k;
         int index=seaExist(seas[i]->startx-SIZE,seas[i]->starty);
         if(index == INT_MAX){
            seas[i]->left = new Sea(seas[i]->startx-SIZE,seas[i]->starty,false);
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->left_buffer->size(); ++k) {
                  if (seas[i]->left->cells[m][k].empty()) {
                     seas[i]->left->cells[m][k]=seas[i]->left_buffer[k];
                     if (k == seas[i]->left_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->left_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->left);
         }else{
            int k;
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->left_buffer->size(); ++k) {
                  if (seas[index]->cells[m][k].empty()) {
                     seas[index]->cells[m][k]=seas[i]->left_buffer[k];
                     if (k == seas[i]->left_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->left_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->left);
         }
      }

      if(seas[i]->right_buffer->size()!=0 ){
         int k;
         int index=seaExist(seas[i]->startx+SIZE,seas[i]->starty);
         if(index == INT_MAX){
            seas[i]->right = new Sea(seas[i]->startx+SIZE,seas[i]->starty,false);
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->right_buffer->size(); ++k) {
                  if (seas[i]->right->cells[m][k].empty()) {
                     seas[i]->right->cells[m][k]=seas[i]->right_buffer[k];
                     if (k == seas[i]->right_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->right_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->right);
         }else{
            int k;
            for(int m=0 ;m<SIZE;m++){
               for ( k=0; k<seas[i]->right_buffer->size(); ++k) {
                  if (seas[index]->cells[m][k].empty()) {
                     seas[index]->cells[m][k]=seas[i]->right_buffer[k];
                     if (k == seas[i]->right_buffer->size()) {
                        break;
                     }
                  }else{
                     m++;k--;
                  }
               }
               if (k == seas[i]->right_buffer->size()) {
                  break;
               }
            }
            seas.push_back(seas[i]->right);
         }
      }
   }
};


// 4. (4 points)
// First, print the min and max x and y coordinates of the ocean.
// Then, print the matrix of the number of fish in each cell.
// If no sea exists, then print x for all the cells in the sea.
// Top left is (minx, miny).
void Ocean::Print(){
   int stx=0, sty=0, lax=0,lay=0;
   for (int i=0; i<seas.size(); ++i) {
      if (seas[i]->starty<=sty)
         sty=seas[i]->starty;
      if (seas[i]->startx<=stx)
         stx=seas[i]->startx;
      if (seas[i]->starty>=lay)
         lay=seas[i]->starty+7;

      if (seas[i]->startx>=lax)
         lax=seas[i]->startx+7;
   }
   cout<<"min_x: "<<stx<<endl;
   cout<<"max_x:: "<<lax<<endl;
   cout<<"min_y: "<<sty<<endl;
   cout<<"max_y:: "<<lay<<endl;
   cout<<"num_seas: "<<seas.size()<<endl;
   int incrisY=0;

   for (int i=0; i<seas.size(); ++i) {
      for (int i=0; i<SIZE; ++i) {

         int indx1 =seaExist(-8,sty+incrisY);
         int indx2 =seaExist(0,sty+incrisY);
         int indx3 =seaExist(8,sty+incrisY);

         if(indx1 != INT_MAX || indx2 != INT_MAX || indx3 != INT_MAX){
            for (int n=0; n<SIZE; ++n) {
               if((indx1 == INT_MAX && (indx2 != INT_MAX || indx3 != INT_MAX)) && seas.size()!=1){
                  cout<< "X";
               }else{ if(seas.size()!=1)cout<<seas[indx1]->cells[i][n].size();}
            }
            for (int n=0; n<SIZE; ++n) {
               if((indx1 != INT_MAX  || indx3 != INT_MAX) && indx2 == INT_MAX){
                  cout<< "X";
               }else cout<<seas[indx2]->cells[i][n].size();
            }

            for (int n=0; n<SIZE; ++n) {
               if(((indx1 != INT_MAX || indx2 != INT_MAX) && indx3 == INT_MAX )&& seas.size()!=1){
                  cout<< "X";
               }else { if(seas.size()!=1)cout<<seas[indx3]->cells[i][n].size();}
            }
            cout<<""<<endl;
         }
      }
      incrisY=incrisY+SIZE;
   }
   incrisY=0;
};


int Ocean::sumfish(int startx, int endx) {
   int  nfish = 0;
   for (int n=0; n<seas.size(); ++n) {
      for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
            for (Fish* fptr : seas[n]->cells[i][j]) {
               if (fptr->IsEdible() && fptr->IsAlive()) {
                  nfish++;
               }
            }
         }
      }
   }
   return nfish;

}
int Ocean::sumshark(int startx, int endx) {
   int nshark = 0;
   for (int n=0; n<seas.size(); ++n) {
      for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
            for (Fish* fptr : seas[n]->cells[i][j]) {
               if (fptr->IsEdible() && fptr->IsAlive()) {
                  if (!fptr->IsEdible()) {
                     nshark++;
                  }
               }
            }
         }
      }
   }
   return nshark;
}


// 5a. (1 point)
// Find total number of fish and sharks in all seas.
// b. (2 points)
// Make threads to run in parallel. Make sure no race conditions.
// Use lambda expression.
// To use member variables in lambda expression, capture this.
void Ocean::PopulationCensus(int& nshark, int& nfish){
   nshark = 0;
   nfish = 0;

   int s1, s2, s3, s4;
   thread t1([&s1,this](int s, int e) { s1 = sumfish(s, e); }, 0, seas.size()/2 - 1);
   thread t2([&s2,this](int s, int e) { s2 = sumshark(s, e); }, 0, seas.size()/2 - 1);
   thread t3([&s3,this](int s, int e) { s3 = sumfish(s, e); }, seas.size()/2, seas.size() - 1);
   thread t4([&s4,this](int s, int e) { s4 = sumshark(s, e); }, seas.size()/2, seas.size() - 1);

   t1.join();
   t2.join();
   t3.join();
   t4.join();
   nshark=s2+s4;
   nfish=s1+s3;

};
