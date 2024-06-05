#include<fstream>
#include<algorithm>
#include<cstring>
FILE* in;

void MergeFiles(int f1,int f2,int out){
    //TODO - Merge files
    FILE* file1,*file2,*output;

    std::string name1="./DB/store";
    name1.append(std::to_string(f1));
    name1.append(".txt");
    file1=fopen(name1.c_str(),"r");

    std::string name2="./DB/store";
    name2.append(std::to_string(f2));
    name2.append(".txt");
    file2=fopen(name2.c_str(),"r");
    
    std::string name_out="./DB/store";
    name_out.append(std::to_string(out));
    name_out.append(".txt");
    output=fopen(name_out.c_str(),"w");

    int a,b;

    int size_a,size_b;
    fscanf(file1,"%d",&size_a);
    fscanf(file2,"%d",&size_b);
    fprintf(output,"%d\n",size_a+size_b);

    fscanf(file1,"%d",&a);
    fscanf(file2,"%d",&b);
    
    int i=1,j=1,k=0;
    while(i<size_a && j<size_b){
        if(a<b){
            fprintf(output,"%d ",a);
            fscanf(file1,"%d",&a);
            i++;
        }else{
            fprintf(output,"%d ",b);
            fscanf(file2,"%d",&b);
            j++;
        }
    }
    while(i<size_a){
        fprintf(output,"%d ",a);
        fscanf(file1,"%d",&a);
        i++;
    }
    while (j<size_b)
    {
        fprintf(output,"%d ",b);
        fscanf(file2,"%d",&b);
        j++;
    }
    fclose(file1);
    fclose(file2);
    fclose(output);
}
int main(){
    in=fopen("to_be_sorted.txt","r");


    int *v=(int*)malloc(sizeof(int)*250);
    int n,nr_files=0;
    fscanf(in,"%d",&n);

    for(int i=0;i<n;i+=250){
        for(int j=0;j<std::min(n-i,250);j++){
            fscanf(in,"%d",&v[j]);
        }
        std::sort(v,v+250);

        std::string name="./DB/store";
        name.append(std::to_string(i/250));
        name.append(".txt");
        FILE* store=fopen(name.c_str(),"w");
        fprintf(store,"%d\n",std::min(n-i,250));
        for(int j=0;j<std::min(n-i,250);j++){
            fprintf(store,"%d ",v[j]);
        }
        fclose(store);
        nr_files++;
    }
    free(v);
    fclose(in);
    while(nr_files>1){
        for(int i=0;i<nr_files/2*2;i+=2){
            MergeFiles(i,i+1,-1);
            
            std::string name1="./DB/store";
            name1.append(std::to_string(i));
            name1.append(".txt");

            std::string name2="./DB/store";
            name2.append(std::to_string(i+1));
            name2.append(".txt");

            std::string name_out="./DB/store";
            name_out.append(std::to_string(-1));
            name_out.append(".txt");

            std::string new_name="./DB/store";
            new_name.append(std::to_string(i/2));
            new_name.append(".txt");

            remove(name1.c_str());
            remove(name2.c_str());
            rename(name_out.c_str(),new_name.c_str());
        }
        if(nr_files%2!=0){
            std::string name_out="./DB/store";
            name_out.append(std::to_string(nr_files-1));
            name_out.append(".txt");

            std::string new_name="./DB/store";
            new_name.append(std::to_string((nr_files-1)/2));
            new_name.append(".txt");
            
            rename(name_out.c_str(),new_name.c_str());
        }

        nr_files=(nr_files+1)/2;
    }
    rename("./DB/store0.txt","output.txt");
}