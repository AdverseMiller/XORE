char ch;
using std::fstream, std::cout, std::endl, std::noskipws, std::string;
fstream fin, fout;



void encrypt(int value, string file, string output, int lastChar) {
    if(output == "") output = file+".crpt";
    fin.open(file, fstream::in);
    if(!fin)
    {
        cout<<"\nUnable to open "<< file;
        exit(1);
    }

    fout.open(output, fstream::out);
    if(!fout)
    {
        cout<<"\nUnable to create " << output;
        exit(1);
    }

    while(fin>>noskipws>>ch)
    {
        ch = ch+(value^lastChar);
        fout<<ch;
    }
    fin.close();
    fout.close();
    cout << "Writing output to " << output << endl;
    
}


void decrypt(int value, string file, string output, int lastChar) {
    if(output == "") output = "output.dcrpt";
    
    fin.open(output, fstream::out);
    if(!fin)
    {
        cout<<"\nUnable to open " << output;
        
    }
    fout.open(file, fstream::in);
    if(!fout)
    {
        cout<<"\nUnable to open " << file;
        
    }
    while(fout>>noskipws>>ch)
    {
        ch = ch-(value^lastChar);
        fin<<ch;
    }
    fin.close();
    fout.close();
    
    cout << "Writing output to " << output << endl;
    
}








/*namespace crypt {
    void encrypt(int value, std::string file, std::string output);
    void decrypt(int value, std::string file, std::string output);
}*/