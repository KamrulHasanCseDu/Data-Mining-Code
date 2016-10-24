#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int min_level=0;
struct Node{
    Node *ptr[5];
    string str[4];
    int cnt[4]={0};
    int num_of_keys;
    int isleave;
    Node *parent;
    int level;
    Node *next;
};
Node *root;
void insert_into_bplustree(string);
void split_leave(Node *);
Node *split_non_leave(Node *);
void display(Node *);
void display_leaves(Node *);
void delete_from_bplustree(string);
void merge_now(Node *,int ,int );
int merge_non_leave(Node *,Node *);

int main(){
    root =  new Node();
    root->isleave = 0;
    root->level = 0;
    root->next = NULL;
    while(1){

        cout<<endl<<" 1 for insert"<<endl<<" 2 for delete"<<endl<<" 3 for display"<<endl;
        int x;
        cin>>x;
        if (x==1){
            cout<<"give data for insert"<<endl;
            string s;
            cin>>s;
            insert_into_bplustree(s);
        }
        if (x==2){
           cout<<"give data for deletion"<<endl;
            string s;
            cin>>s;
            delete_from_bplustree(s);
        }
        if (x==3){
           display(root);
        }
        if(x==4)
            display_leaves(root);
        cin.clear();
        cin.ignore(100, '\n'); //100 --> asks cin to discard 100 characters from the input stream.
    }
return 0;
}

void display(Node *d){
    cout<<endl;
    queue<struct Node *> q;

    for(int i=0;i<d->num_of_keys;i++)
        cout<<" |"<<d->str[i]<<"| ";

    int levl = d->level;

    if(d->ptr[0] != NULL){
        for(int j=0;j<=d->num_of_keys;j++){
            q.push(d->ptr[j]);
        }
    }
    Node *n;
    n=new Node();

     while(!q.empty() ){
        n = q.front();
        q.pop();
        if(levl != n->level){
            levl = n->level;
            cout<<endl;
        }
        for(int i=0;i<n->num_of_keys;i++)
            cout<<"|"<<n->str[i]<<"|";

        if(n->level == 0)
            cout<<"->  ";
        else
            cout<<"  ";

        if(n->level != 0){
            for(int j=0;j<=n->num_of_keys;j++)
                q.push(n->ptr[j]);

        }
     }//end while
    cout<<endl;
}//end display()


void display_leaves(Node *root){
    Node *a = new Node();
    a = root;
  while(a->level != 0){
    a = a->ptr[0];
  }
    while(a!=NULL){
        for(int i =0;i<a->num_of_keys;i++)
            cout<<"|"<<a->str[i]<<"|";

    cout<<"-->";
    a = a->next;
    }
}




void insert_into_bplustree(string data){

    if(root->str[0] == ""){
        root->str[0] = data;
        root->num_of_keys = 1;
        root->cnt[0] = 1;
        return;
    }
    else{
        Node *n = new Node();
        Node *l = new Node();
        n=root;
        int f = 0;
        while(f == 0){
            if(n->level == 0 ){
                for(int i=0;i<n->num_of_keys;i++){
                    if(data == n->str[i]){
                        n->cnt[i]++;
                        f = 1;
                        return;
                    }
                   else if(data.compare(n->str[i])<0){
                        string tmp1,tmp2;
                        int c1,c2;
                        tmp1 = n->str[i];
                        c1 = n->cnt[i];
                        n->str[i] = data;
                        n->cnt[i] = 1;
                        for(int j=i+1;j <= n->num_of_keys;j++){
                            tmp2 = n->str[j];
                            c2 = n->cnt[j];
                            n->str[j]=tmp1;
                            n->cnt[j] = c1;
                            c1 = c2;
                            tmp1 = tmp2;
                        }
                        f = 1;
                        n->num_of_keys++;

                        if(n->num_of_keys == 4)
                           split_leave(n);
                       break;
                    }
                }
                if(f==0){
                    n->str[n->num_of_keys] = data;
                    n->cnt[n->num_of_keys] = 1 ;
                    f = 1;
                    n->num_of_keys++;
                    if(n->num_of_keys == 4){
                        split_leave(n);

                    }
                }
            }
            else{
                for(int i=0;i<= n->num_of_keys;i++){
                    if(data.compare(n->str[i])<0){
                        Node *p = new Node();
                        p = n;
                        n = n->ptr[i];
                        n->parent = p;
                        break;
                    }
                    else if(n->str[i] == ""){
                        Node *p = new Node();
                        p = n;
                        n = n->ptr[i];
                        n->parent = p;
                        break;
                    }
                }

            }
        }
    }
}



Node *split_non_leave(Node *n){
    //cout<<" ok "<<root->num_of_keys<<endl;
    Node *pt1, *pt2,*l;
    pt1 = new Node();
    pt2 = new Node();
    l = new Node();
    pt1->str[0] = n->str[0];
    pt1->cnt[0] = n->cnt[0];
    pt1->str[1] = n->str[1];
    pt1->cnt[1] = n->cnt[1];
    pt1->ptr[0] = n->ptr[0];
    pt1->ptr[1] = n->ptr[1];
    pt1->ptr[2] = n->ptr[2];

    pt2->str[0] = n->str[3];
    pt2->cnt[0] = n->cnt[3];
    pt2->ptr[0] = n->ptr[3];
    pt2->ptr[1] = n->ptr[4];
    Node *tmp_root = new Node();
    tmp_root->str[0] = n->str[2];
    //here maybe modified
    tmp_root->ptr[0] = pt1;
    tmp_root->ptr[1] = pt2;
    tmp_root->ptr[0]->parent = tmp_root;
    tmp_root->ptr[1]->parent = tmp_root;
    tmp_root->parent = n->parent;
    tmp_root->ptr[0]->level = n->level;
    tmp_root->ptr[1]->level = n->level;
    tmp_root->ptr[0]->num_of_keys = 2;
    tmp_root->ptr[1]->num_of_keys = 1;

    if(n->parent != NULL){
      l = n->parent;
      string tmp11,tmp22;
      int c1,c2;
      Node *pt3,*pt4;
      pt3 = new Node();
      pt4 = new Node();
      int flag = 0;
      for(int i=0;i<l->num_of_keys;i++){
          if(tmp_root->str[0].compare(l->str[i])<0){
            flag = 1;
            tmp11 = l->str[i];
            c1 = l->cnt[i];
            pt3 = l->ptr[i+1];
            l->str[i] = tmp_root->str[0];
            l->cnt[i] = tmp_root->cnt[0];
            l->ptr[i] = tmp_root->ptr[0];
            l->ptr[i+1] = tmp_root->ptr[1];
            for(int j=i+1;j<=l->num_of_keys;j++){
                string x = l->str[0];
                int c = l->cnt[0];
                tmp22 = l->str[j];
                c2 = l->cnt[j];
                pt4 = l->ptr[j+1];
                l->str[j] = tmp11;
                l->ptr[j+1] = pt3;
                tmp11 = tmp22;
                c1 = c2;
                pt3 = pt4;
                l->str[0] = x;
                l->cnt[0] = c;
            }
            l->num_of_keys++;
            if(l->num_of_keys==4)
                l = split_non_leave(l);

         break;
        }

     }//end of for loop
     if(flag==0){
            l->str[l->num_of_keys] = tmp_root->str[0];
            l->cnt[l->num_of_keys] = tmp_root->cnt[0];

            l->ptr[l->num_of_keys] = tmp_root->ptr[0];
            l->ptr[l->num_of_keys+1] = tmp_root->ptr[1];
            flag = 1;
            l->num_of_keys++;
            if(l->num_of_keys==4)
                l = split_non_leave(l);
             flag = 1;
     }
  }
  else{
    tmp_root->level = n->level-1;
    tmp_root->num_of_keys = 1;
    tmp_root->isleave = 0;
    l=tmp_root;
    if(l->level <min_level)
        min_level = l->level;

  }
  return l;
}
void split_leave(Node *n){
    //cout<<"hi"<<endl;
    //if( n!= root)
      //cout<<"in split "<<n->parent->num_of_keys<<" and "<<n->parent->str[0]<<endl;
      Node *tmp1,*tmp2,*tmp_root;
      tmp1 = new Node();
      tmp2 = new Node();
      tmp_root = new Node();
      tmp1->str[0] = n->str[0];
      tmp1->cnt[0] = n->cnt[0];
      tmp1->str[1] = n->str[1];
      tmp1->cnt[1] = n->cnt[1];
      tmp2->str[0] = n->str[2];
      tmp2->cnt[0] = n->cnt[2];
      tmp2->str[1] = n->str[3];
      tmp2->cnt[1] = n->cnt[3];
      tmp_root->str[0] = n->str[2];
      tmp_root->cnt[0] = n->cnt[2];
      tmp_root->ptr[0] = tmp1;
      tmp_root->ptr[1] = tmp2;
      tmp_root->isleave = 0;
      tmp_root->ptr[0]->isleave = 1;
      tmp_root->ptr[1]->isleave = 1;
      tmp_root->ptr[0]->num_of_keys = 2;
      tmp_root->ptr[1]->num_of_keys = 2;
      tmp_root->parent = n->parent;
      tmp_root->ptr[0]->parent = tmp_root;
      tmp_root->ptr[1]->parent = tmp_root;
      tmp_root->level = n->level-1;
      tmp_root->ptr[0]->level = n->level;
      tmp_root->ptr[1]->level = n->level;
      tmp_root->ptr[0]->next = tmp_root->ptr[1];
      tmp_root->ptr[1]->next = n->next;
      if(n->parent == NULL){
        tmp_root->num_of_keys = 1;
      }
      if(min_level >tmp_root->level)
        min_level = tmp_root->level;
            Node *l = new Node();
      if(n->parent != NULL){
          l = n->parent;
          string tmp11,tmp22;
          int c1,c2;
          Node *pt3,*pt4;
          pt3 = new Node();
          pt4 = new Node();
          int flag = 0;
          for(int i=0;i<l->num_of_keys;i++){
            if(tmp_root->str[0].compare(l->str[i])<0){
                flag = 1;
                tmp11 = l->str[i];
                c1 = l->cnt[i];
                pt3 = l->ptr[i+1];
                l->str[i] = tmp_root->str[0];
                l->cnt[i] = tmp_root->cnt[0];
                l->ptr[i] = tmp_root->ptr[0];
                l->ptr[i+1] = tmp_root->ptr[1];
                for(int j=i+1;j<=l->num_of_keys;j++){
                    Node *y = new Node();
                    tmp22 = l->str[j];
                    c2 = l->cnt[j];
                    pt4 = l->ptr[j+1];
                    l->cnt[j] = c1;
                    l->str[j] = tmp11;
                    l->ptr[j+1] = pt3;
                    if(j != l->num_of_keys){
                        pt3 = pt4;
                        tmp11 = tmp22;
                        c1 = c2;
                    }
                }
                l->num_of_keys++;
                if(l->num_of_keys==4){
                    l = split_non_leave(l);
                }
            break;
            }

        }//end of loop
            if(flag==0){
                l->str[l->num_of_keys] = tmp_root->str[0];
                l->cnt[l->num_of_keys] = tmp_root->cnt[0];
                l->ptr[l->num_of_keys] = tmp_root->ptr[0];
                l->ptr[l->num_of_keys+1] = tmp_root->ptr[1];
                flag = 1;
                l->num_of_keys++;
                if(l->num_of_keys==4)
                    l = split_non_leave(l);
            }
      }
      else{
        l=tmp_root;
        if(l->level<min_level)
            min_level = l->level;
      }

      for(int j=l->level;j>min_level;j--)
                l = l->parent;
      root = l;

 }

void delete_from_bplustree(string data){

    Node *n = new Node();
    Node *p = new Node();
    Node *x = new Node();
    Node *test = new Node();
   // test = root;
    //test = test->ptr[0]->ptr[1];


    n = root;

    int k ;
    while(n->level != 0){
            int flag = 0;
        for(int i=0;i<n->num_of_keys;i++){
            if(data.compare(n->str[i])<0){
                    n->ptr[i]->parent = n;
                    n = n->ptr[i];
                    flag = 1;
                    k= i;
                    break;
            }
        }

        if(flag == 0){
            k = n->num_of_keys;
            n->ptr[n->num_of_keys]->parent = n;
            n = n->ptr[n->num_of_keys];
            flag = 1;
        }
        //cout<<"kk "<<n->num_of_keys<<" so "<<n->str[0]<<" and "<<k<<"then "<<n->level<<endl;
        //int l;
        //cin>>l;
    }
    //cout<<"ssddsdk"<<n->level<<"fff"<<n->parent->num_of_keys<<"ssf"<<n->num_of_keys<<endl;

    p = n->parent;
    int kk;
    bool data_is_exist = false;
    //cout<<"h?"<<p->str[0]<<endl;
    //if(data.compare(p->str[0])<0)
            //cout<<"herree?"<<endl;
        for(int i=0;i<n->num_of_keys;i++){
            if(data == n->str[i]){
                    if(n->cnt[i] > 1)
                    {
                        n->cnt[i]--;
                        return ;
                    }
                    kk = i;
                for(int j=i;j<n->num_of_keys-1;j++){
                    n->str[j] = n->str[j+1];
                }
                n->str[n->num_of_keys-1] = "";
                data_is_exist = true;
            }
        }

        if(data_is_exist == false){
            cout<<"data is not exist"<<endl;
            return;
        }
        n->num_of_keys--;
        if(k==0){
                //cout<<"ww"<<endl;
            if(n->num_of_keys == 1)
               merge_now(p,0,1);

        }
        else {

           if (kk==0){
                  if(n->num_of_keys == 1){
                      p->str[k-1] = n->str[0];
                      merge_now(p,k-1,k);
                  }
                  else{
                    p->str[k-1] = n->str[0];
                    for(int j=p->level;j>min_level;j--)
                    p = p->parent;
                    root = p;
                  }

            }
            else{
                if(n->num_of_keys == 1)
                    merge_now(p,k-1,k);
            }
        }

}

void merge_now(Node *p,int x,int y){

    Node *tmp = new Node();
    int kal = 2;
    //tmp->str[0] = p->ptr[x]->str[0];
    //cout<<"kk "<<endl;
    for(int i=0;i<p->ptr[x]->num_of_keys;i++){
        tmp->str[i] = p->ptr[x]->str[i];
        tmp->cnt[i] = p->ptr[x]->cnt[i];
    }
    //cout<<"there "<<x<<" and "<<y<<endl;
    int j = p->ptr[x]->num_of_keys;
    //cout<<"skdls "<<p->ptr[y]->num_of_keys<<endl;
    for(int i=0;i<p->ptr[y]->num_of_keys;i++){
        tmp->str[j] = p->ptr[y]->str[i];
        tmp->cnt[j] = p->ptr[y]->cnt[i];
        j++;
    }
   // cout<<"there2 "<<endl;

    tmp->num_of_keys = p->ptr[y]->num_of_keys + p->ptr[x]->num_of_keys ;
    tmp->level = p->ptr[y]->level;
    if(p->num_of_keys ==1 && p->level==min_level)
        root = tmp;
    else{

        p->ptr[x] = tmp;

        }

       // cout<<"here?"<<endl;
        if(p->num_of_keys==1 && p->ptr[x]->num_of_keys !=4){
            p->str[0] = tmp->str[0];
            p->cnt[0] = tmp->cnt[0];
           kal = merge_non_leave(p->parent,p);
        }
        p->str[x] = p->str[y];
        p->cnt[x] = p->cnt[y];
       // cout<<"there2 "<<endl;
        for(int i = y;i<p->num_of_keys;i++){
            if(i != p->num_of_keys){
                p->str[i] = p->str[i+1];
                p->cnt[i] = p->cnt[i+1];
            }
            p->ptr[i] = p->ptr[i+1];
        }
       // cout<<"there2 "<<endl;
       // p->str[p->num_of_keys-1] = "";
        //p->ptr[p->num_of_keys] = NULL;
        //cout<<"there4 "<<endl;
         p->num_of_keys--;

        p->ptr[x]->parent = p;
       // cout<<"there2 "<<endl;
        if(p->ptr[x]->num_of_keys == 4){
         //   cout<<"there2 "<<endl;
            split_leave(p->ptr[x]);
        }

        else{
           if(kal == 2){
            for(int j=p->level;j>min_level;j--)
                p = p->parent;
            root = p;
           }
        }




}

int merge_non_leave(Node *gp,Node *p){

     Node *tmp = new Node();
     Node *tmp1 = new Node();
     int  x,y;
     //cout<<"hhh "<<p->str[0]<<endl;
     display(p);
    if(p->str[0].compare(gp->str[0])<0){
        tmp->ptr[0] = p->ptr[0];
        tmp->str[0] = p->str[0];
        tmp->cnt[0] = p->cnt[0];
       // cout<<"gp1 "<<gp->num_of_keys<<endl;
        int j = 1;
        for(int i = 0;i<gp->ptr[1]->num_of_keys;i++){
            tmp->str[j] = gp->ptr[1]->str[i];
            tmp->cnt[j] = gp->ptr[1]->cnt[i];
            tmp->ptr[j]  = gp->ptr[1]->ptr[i];
            j++;
        }
       // cout<<"gp3 "<<gp->num_of_keys<<endl;
        tmp->num_of_keys = gp->ptr[1]->num_of_keys +1;
        tmp->ptr[tmp->num_of_keys] = gp->ptr[1]->ptr[gp->ptr[1]->num_of_keys];
        tmp->level = gp->ptr[1]->level;


       // cout<<"gp4 "<<gp->num_of_keys<<endl;
    }
    else{
            int flag = 0;
        for(int i=1;i<gp->num_of_keys;i++){
            if(p->str[0].compare(gp->str[i])<0){
                 x = i-1;
                 y = i;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            x = gp->num_of_keys-1;
            y = gp->num_of_keys;
        }
        //cout<<"gp6 "<<gp->num_of_keys<<endl;
       // tmp = gp->ptr[x];
       //cout<<x<<endl;

       //cout<<gp->ptr[x]->num_of_keys<<endl;
        display(gp);
       for(int i = 0;i<gp->ptr[x]->num_of_keys;i++){
                  // cout<<"ll "<<endl;

        tmp->str[i] = gp->ptr[x]->str[i];
        tmp->cnt[i] = gp->ptr[x]->cnt[i];
        tmp->ptr[i] = gp->ptr[x]->ptr[i];
        tmp->ptr[i]->level = gp->ptr[x]->ptr[i]->level;

       }
      // cout<<"llg "<<endl;
        tmp->ptr[gp->ptr[x]->num_of_keys] = gp->ptr[x]->ptr[gp->ptr[x]->num_of_keys];
       tmp->num_of_keys = gp->ptr[x]->num_of_keys+1;
       // tmp->num_of_keys++;
         //cout<<"hh"<<endl;
        //tmp->ptr[tmp->num_of_keys] = gp->ptr[x]->ptr[gp->ptr[x]->num_of_keys];
       tmp->ptr[tmp->num_of_keys] = p->ptr[0];
        tmp->ptr[tmp->num_of_keys]->level = gp->ptr[x]->ptr[gp->ptr[x]->num_of_keys]->level;

        //cout<<"kk"<<endl;

        tmp->str[tmp->num_of_keys-1] = p->ptr[0]->str[0];
        tmp->cnt[tmp->num_of_keys-1] = p->ptr[0]->cnt[0];
        tmp->level = gp->ptr[x]->level;
                //cout<<"kk"<<endl;

        //p->ptr[0]->str[0] = p->str[0];
                //cout<<"kk"<<endl;
               // cout<<"non leave tmp: ";
         //for(int i=0;i<tmp->num_of_keys;i++){
           // cout<<tmp->str[i]<<" ";
            //}
    //cout<<endl;

    }
//cout<<"gp7 "<<gp->num_of_keys<<endl;
    if(gp->num_of_keys ==1 && gp->level==min_level){
        root = tmp;
       // root->level++;
        min_level++;

        if(root->num_of_keys == 4)
            root = split_non_leave(root);
        //cout<<"is it: "<<endl;
       //display(tmp);
        return 1;
    }
    else{
       //cout<<gp->ptr[x]->num_of_keys;



        gp->ptr[x] = tmp;

            gp->ptr[x] ->parent = gp;
        if(gp->num_of_keys==1 && gp->ptr[x]->num_of_keys !=4){
            //Node *gp1 = new Node();
            //merge_non_leave(gp->parent,gp);
        }
       // cout<<gp->ptr[x]->num_of_keys;
        gp->str[x] = gp->str[y];
        gp->cnt[x] = gp->cnt[y];
        //cout<<"there2 "<<endl;
        for(int i = y;i<gp->num_of_keys;i++){
            if(i != gp->num_of_keys){
                gp->str[i] = gp->str[i+1];
                gp->cnt[i] = gp->cnt[i+1];
            }
            gp->ptr[i] = gp->ptr[i+1];
        }
        //cout<<"there2 "<<endl;
       // p->str[p->num_of_keys-1] = "";
        //p->ptr[p->num_of_keys] = NULL;
        //cout<<"there4 "<<endl;
         gp->num_of_keys--;

        gp->ptr[x]->parent = gp;
        //cout<<"there2 "<<endl;
       // cout<<"herexx tmp: ";
         //for(int i=0;i<gp->ptr[x]->num_of_keys;i++){
           // cout<<gp->ptr[x]->str[i]<<" ";
            //}
        if(gp->ptr[x]->num_of_keys == 4){
          //  cout<<"there2 "<<endl;
            split_non_leave(gp->ptr[x]);
        }
        return 2;

       /* else{

            for(int j=gp->level;j>min_level;j--)
                gp = gp->parent;
            root = gp;
        }
        */
    }


}












