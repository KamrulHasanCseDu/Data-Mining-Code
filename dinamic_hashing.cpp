#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int bucket[4] = {0} ;
    int num_of_element ;
    int local_checkbit;
    Node *extra_index;
};
Node *index[16];

int pos = 0;
int check = 0;
int check_bit = 0;
void insert_into_hashing_table(int);
void split(int);
int get_int(int[]);
int get_bin(int);
int initial_bucket[4];
int init_element = 0;
void display();

int main(){


    for(int j=0;j<16;j++){
        index[j] = new Node();
        index[j]->num_of_element = 0;
    }
    int i,x;
    while(1){
        cout<<"1 for insert "<<endl;
        cout<<"2 for display"<<endl;
        cin>>i;
        if(i == 1){
            cin>>x;

            insert_into_hashing_table(x);
        }
        else if(i == 2){
            display();
        }
        cin.clear();
        cin.ignore(100, '\n');
    }



return 0;
}

void insert_into_hashing_table(int data){
    if(init_element < 4){
        initial_bucket[init_element] = data;
        init_element++;
    }
    if(init_element == 4){
            index[0]->local_checkbit++;
            index[1]->local_checkbit++;
            check_bit++;
        for(int i=0;i<4;i++){
             int x = initial_bucket[i];
             string x_string = bitset<4>(x%16).to_string();

             if(x_string[0] == '0'){
                index[0]->bucket[index[0]->num_of_element] = x;
                index[0]->num_of_element++;
                if(index[0]->num_of_element == 4)
                    split(0);
            }
            else if(x_string[0]=='1'){
                index[1]->bucket[index[1]->num_of_element] = x;
                index[1]->num_of_element++;
                if(index[1]->num_of_element == 4)
                    split(1);
            }
        }

        init_element++;
    }
   else if(init_element >4){
        string data_string = bitset<4>(data%16).to_string();
        int n = pow(2,check_bit);
        for(int i = 0;i<n;i++){
            string i_string = bitset<4>(i ).to_string();
            int k = 4-check_bit;
            int check_flag = 0;
            for(int j = 0;j<index[i]->local_checkbit;j++){
                if(data_string[j] != i_string[k])
                    check_flag = 1;
                k++;
            }
            if(check_flag == 0){
                index[i]->bucket[index[i]->num_of_element] = data;
                index[i]->num_of_element++;
                if(index[i]->num_of_element == 4){
                    split(i);
                }
                break;
            }

        }
    }
    return;

}




/*string get_bin(int x){
    string binary = bitset<3>(x).to_string(); //to binary
    return binary;
}*/

void split(int indx){


    int new_indx;
    int another_indx;
    if(index[indx]->local_checkbit == check_bit){
            if(check_bit== 4){
              index[indx]->num_of_element--;
              return;
            }
        Node *tmp[16];
        for(int i =0;i<16;i++)
            tmp[i] = new Node();
        for(int i =0;i<pow(2,check_bit);i++){


                tmp[2*i] = index[i];
                tmp[(2*i)+1]->local_checkbit = index[i]->local_checkbit;
                //tmp[2*i]->num_of_element = index[i]->num_of_element;


        }
        for(int i =0;i<16;i++){
            index[i] = tmp[i];
        }

         check_bit++;
         new_indx = 2*indx;
         another_indx = 2*indx + 1;
    }
    else{
         new_indx = indx;
         another_indx = indx+pow(2,index[indx]->local_checkbit);
    }


    index[new_indx]->num_of_element = 0;


    index[new_indx]->local_checkbit++;
    index[another_indx]->local_checkbit++;
    cout<<"here check bit"<<endl;
    string first_index = bitset<4>(new_indx).to_string();

    for(int i = 0;i<4;i++){
            int data = index[new_indx]->bucket[i];
            string data_string = bitset<4>(data%16).to_string();
            int k = 4-check_bit;
            int check_flag = 0;
            for(int j = 0;j<index[new_indx]->local_checkbit;j++){
                if(data_string[j] != first_index[k])
                    check_flag = 1;
                k++;
            }
            if(check_flag == 0){
                index[new_indx]->bucket[index[new_indx]->num_of_element] = data;
                index[new_indx]->num_of_element++;
                if(index[new_indx]->num_of_element == 4){
                    if(check_bit == 4){

                    }
                    split(new_indx);
                }
            }
            else {
                index[another_indx]->bucket[index[another_indx]->num_of_element] = data;
                index[another_indx]->num_of_element++;
                if(index[another_indx]->num_of_element == 4)
                    split(another_indx);
            }
    }

}
void display(){
    if(init_element < 4){
        cout<<"initial bucket [ ";
        for(int i = 0;i<init_element;i++){
            cout<<initial_bucket[i]<<" ";
        }
        cout<<"]"<<endl;
    }
    else{
        for(int i=0;i<pow(2,check_bit) ;i++){
            string i_string = bitset<4>(i).to_string();
            int k = 4-check_bit;
            for(int j=k;j<4;j++){
                cout<<i_string[j];
            }
            cout<<" [ ";
            if(index[i]->num_of_element == 0 && index[i]->local_checkbit != check_bit)
                cout<<"combined";
            for(int j=0;j<index[i]->num_of_element;j++){
                cout<<index[i]->bucket[j]<<"  ";
            }
            cout<<"]"<<endl;
        }
    }
}


