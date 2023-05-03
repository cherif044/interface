
#include <iostream>
#include <fstream>
#include <vector>
struct index
{
    int sentence_x, sentence_y, index_x, index_y;

};
using namespace std;
struct trials {
    int a, b;
};
class file {
private:
    ifstream file_x, file_y;

public:

    virtual void readFile() = 0;
    ifstream& const getFile_x() {
        return file_x;
    }
    ifstream& const getFile_y()
    {
        return file_y;
    }
    void setFile_x(string fileName)
    {
        file_x.open( fileName );
    }
    void setFile_y(string fileName)
    {
        file_y.open(fileName);
    }
};
struct logs
{
    string text;
    int index_x;
    int index_y;
};


class brute_force:public file
{
private:
    
    vector<char> filex, filey;
    vector<index>plagiarised;
public:
    brute_force(string xfilename, string yfilename)
    {
        setFile_x(xfilename);
        setFile_y(yfilename);
        readFile();
    }
    void readFile()
    {
        cout << "first file content: " << endl;
        char tempc;
        int countspace = 0;
        while (getFile_x().get(tempc))
        {
            if (tempc == '\n')
            {
                tempc = ' ';
            }
            {
                if (tempc == ' ')
                {
                    countspace++;
                }
                else
                {
                    countspace = 0;
                }
            }
            if (countspace < 2)
            {
                filex.push_back(tempc);
                cout << tempc;
            }

        }
        countspace = 0;
        cout << endl;
        cout << endl << endl << endl;
        cout << "file 2 content: " << endl;
        while (getFile_y().get(tempc))
        {
            if (tempc == '\n')
            {
                tempc = ' ';
            }
            {
                if (tempc == ' ')
                {
                    countspace++;
                }
                else
                {
                    countspace = 0;
                }
            }
            if (countspace < 2)
            {
                filey.push_back(tempc);
                cout << tempc;
            }

        }
    }
    bool const ishamming(string x, string y, int threshold)
    {
        int mismatches = 0;
        if (x.length() == y.length())
        {
            for (int i = 0; i < y.size(); i++)
            {
                if (tolower(x.at(i)) != tolower(y.at(i)) && x.at(i) != ' ')
                {
                    mismatches++;
                }
            }
            return mismatches < threshold;
        }
        return false;
        
    }
    int const brute_check(vector<char> txt2, vector<char> txt)
    {
        string text = "", pattern = "",temps="";
        if (txt2.size() > txt.size())
        {
            for (int i = 0; i < txt.size(); i++)
            {
                pattern += txt[i];
            }
            for (int i = 0; i < txt2.size(); i++)
            {
                text += txt2[i];
            }
        }
        else if (txt2.size() <= txt.size())
        {
            for (int i = 0; i < txt.size(); i++)
            {
                text += txt[i];
            }
            for (int i = 0; i < txt2.size(); i++)
            {
                pattern += txt2[i];
            }
        }
        int count = 0;
        for (int i = 0; i < pattern.length(); i++)
        {
            if (pattern.at(i) == ' ')
                count++;
        }
        if (count > 1)
        {
            for (int i = 0; i <= text.length() - pattern.length(); i++)
            {
                string temp = "";
                temp = text.substr(i, pattern.length());
                if (ishamming(pattern, temp, 1))
                {

                    return i;
                }
            }
        }
        return -999;
    }
    vector<logs> const trial(vector<char> tempy, vector<char> tempx)
    {
        trials temp;
        string text = "", pattern = "", temps = "";
        if (tempx.size() > tempy.size())
        {
            for (int i = 0; i < tempy.size(); i++)
            {
                pattern += tempy[i];
            }
            for (int i = 0; i < tempx.size(); i++)
            {
                text += tempx[i];
            }
        }
        else if (tempx.size() <= tempy.size())
        {
            for (int i = 0; i < tempy.size(); i++)
            {
                text += tempy[i];
            }
            for (int i = 0; i < tempx.size(); i++)
            {
                pattern += tempx[i];
            }
        }
        int count_phrases = 0, wordsp = 0, wordst = 0;
        for (int i = 0; i < pattern.length(); i++)
        {
            if (pattern.at(i) == ' ')
            {
                wordsp++;
            }
        }
        wordsp++;
        for (int i = 0; i < text.length(); i++)
        {
            if (text.at(i) == ' ')
            {
                wordst++;
            }
        }
        wordst++;
        temp.a = -999;
        temp.b = -999;
        vector<logs> plagiarized;
        logs m;
        for (int i = 1; i <= wordsp - 2; i++)
        {
            for (int z = 1; z <= wordst - 2; z++)
            {


                if (ishamming(getphrase(pattern, i), getphrase(text, z), 1))
                {
                    if (tempx.size() > tempy.size())
                    {
                        m.text = getphrase(pattern, i);
                        m.index_x = z;
                        m.index_y =i ;
                        plagiarized.push_back(m);
                    }
                    else if(tempx.size()<=tempy.size())
                    {
                        
                            m.text = getphrase(pattern, i);
                            m.index_x = i;
                            m.index_y = z;
                            plagiarized.push_back(m);
                        
                    }
                }
            }
        }
       
        return plagiarized;
    }
    string getword(string x, int z)
    {
        vector<int> index;
        int temp = 0;
        index.push_back(0);

        for (int i = 0; i < x.length(); i++)
        {
            if (x.at(i) == ' ')
            {
                temp++;
                index.push_back(i + 1);
            }
        }
        temp++;

        for (int i = 1; i <= temp; i++)
        {
            if (z == i)
            {
                int c = 1;
                int h = index[i - 1];
                while (h < x.length() && x.at(h) != ' ')
                {
                    h++;
                    c++;
                }
                return x.substr(index[i - 1], c-1);
            }
        }

        return "";
    }

    string getphrase(string x, int z)
    {
        int temp = 0;
        string h;
        for (int i = 0; i < x.length(); i++)
        {
            if (x.at(i) == ' ')
            {
                temp++;
            }
        }
        temp++;
        for (int i = 1; i <= temp - 2; i++)
        {
            if (i == z)
            {
                h = getword(x, i) + ' ' + getword(x, i + 1) + ' ' + getword(x, i + 2);
                return h;
            }
        }
    }

    vector<char> const getsentence_filex(int z)
    {
        vector<char> tempv;
        int sentencecount = 0, end = -1, l = 0;
        for (int i = 0; i < filex.size(); i++)
        {
            if (filex.at(i) == '.' || filex.at(i) == '?' || filex.at(i) == ',' || filex.at(i) == ';' || filex.at(i) == '!' || filex.at(i) == ':')
            {
                sentencecount++;
                if (sentencecount == z)
                {
                    end = i - 1;
                }
            }

        }

        if (end != -1)
        {
            int j = end;
            while (j >= 0 && filex.at(j) != '.' && filex.at(j) != '?' && filex.at(j) != ',' && filex.at(j) != ';' && filex.at(j) != '!' && filex.at(j) != ':')
            {
                j--;
            }
            j++;
            while (filex.at(j) == ' ')
            {
                j++;
            }
            while (filex.at(end) == ' ')
            {
                end--;
            }
            for (int i = j; i <= end; i++)
            {
                tempv.push_back(filex[i]);
            }
            return tempv;
        }


    }
    vector<char> const getsentence_filey(int z)
    {
        vector<char> tempv;
        int sentencecount = 0, end = -1, l = 0;
        for (int i = 0; i < filey.size(); i++)
        {
            if (filey.at(i) == '.' || filey.at(i) == '?' || filey.at(i) == ',' || filey.at(i) == ';' || filey.at(i) == '!' || filey.at(i) == ':')
            {
                sentencecount++;
                if (sentencecount == z)
                {
                    end = i - 1;
                }
            }

        }

        if (end != -1)
        {
            int j = end;
            while (j >= 0 && filey.at(j) != '.' && filey.at(j) != '?' && filey.at(j) != ',' && filey.at(j) != ';' && filey.at(j) != '!' && filey.at(j) != ':')
            {
                j--;
            }
            j++;
            while (filey.at(j) == ' ')
            {
                j++;
            }
            while (filey.at(end) == ' ')
            {
                end--;
            }
            for (int i = j; i <= end; i++)
            {
                tempv.push_back(filey[i]);
            }
            return tempv;
        }


    }
    int const number_of_phrases_filex()
    {
        int count = 0;
        for (int i = 0; i < filex.size(); i++)
        {
            if (filex.at(i) == '.' || filex.at(i) == '?' || filex.at(i) == ',' || filex.at(i) == ';' || filex.at(i) == '!' || filex.at(i) == ':')
                count++;
        }
        return count;
    }
    int const number_of_phrases_filey()
    {
        int count = 0;
        for (int i = 0; i < filey.size(); i++)
        {
            if (filey.at(i) == '.' || filey.at(i) == '?' || filey.at(i) == ',' || filey.at(i) == ';' || filey.at(i) == '!' || filey.at(i) == ':')
                count++;
        }
        return count;
    }
    void push_plagiarized_indexes(int x, int y, int i, int j)
    {
        index temp;
        temp.sentence_x = x;
        temp.sentence_y = y;
        temp.index_x = i;
        temp.index_y = j;
    }
    vector<char> const getfilex()
    {
        return filex;
    }
    vector<char> const getfiley()
    {
        return filey;
    }
    

};
void stringmatching(brute_force& a, vector<char> pattern, int index)
{

    int count = 0;
    for (int i = 1; i <= a.number_of_phrases_filey(); i++)
    {

        vector<char> temp = a.getsentence_filey(i);


        vector<logs> tempI = a.trial(temp, pattern);

        if (tempI.size() > 0)
        {
            cout << "sentence: " << index << endl;
            for (int j = 0; j < tempI.size(); j++)
            {
                cout << "the phrase : (" << tempI[j].text << ") is similar to a phrase in sentence: " << i << " of the second file"<<" this phrase starts from word number: "<<tempI[j].index_x<<" of the first file sentence and starts from the word: "<<tempI[j].index_y<<" of the second file sentence"<< endl;
            }
            count++;
        }

    }
    
    
}
void plagiarism_check(brute_force& a)
{
    cout << endl;
    cout << "checking every sentence in file 1 " << endl;
    cout << endl;
    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {
        
        stringmatching(a, a.getsentence_filex(j), j);
    }

}
int main()
{
    brute_force  a("fff.txt", "ff.txt");
    plagiarism_check(a);
}




