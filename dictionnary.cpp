#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct sWord
{
    string data;
    sWord *next;
};

struct dWord
{
    string data;
    sWord *synonym;
    sWord *antonym;
    dWord *next;
    dWord *previous;
};

struct Dictionary
{
    dWord *head;
    dWord *tail;
};

Dictionary *input_data_todoubly(Dictionary *dict, int count_syn, int count_ant, string synonym[][20], string antonym[][20], int row)
{
    dWord *tmp = new dWord;
    tmp->data = synonym[row][0];
    tmp->next = NULL;
    if (dict->head == NULL)
    {
        dict->head = tmp;
        dict->tail = tmp;
        tmp->previous = NULL;
    } // hek eza kenet fadye b5alle tnayneton ykouno tmp
    else
    {
        tmp->previous = dict->tail; // kermel ma nemhe l old tail
        dict->tail->next = tmp;
        dict->tail = tmp;
    }
    // we have syno and anto so for each one we should have a for loop
    // this for the synonym
    for (int i = count_syn; i > 0; i--) // akbar men 0 bas la2en bel 0 fi l big
    {                                   // i balachet from 1 la2en l zero hiye l word mawjoude bi aleb hal synonym
        sWord *point_syn = new sWord;
        point_syn->data = synonym[row][i];
        point_syn->next = dict->tail->synonym;
        dict->tail->synonym = point_syn;
        // tghe for loop is like this to help to priny the synonym in order
    }

    // this for the antonym
    for (int i = count_ant; i >= 0; i--)
    { // i balachet from 1 la2en l zero hiye l word mawjoude bi aleb hal synonym
        sWord *point_ant = new sWord;
        point_ant->data = antonym[row][i];
        point_ant->next = dict->tail->antonym;
        dict->tail->antonym = point_ant;
        // tghe for loop is like this to help to priny the synonym in order
    }
    // aktar men for loop la2en kel wehde yemken ykoun fi 3enda 3adad kalimet synonym w hek 8er ba3ed

    return dict;
}

// ex4
bool isExist(Dictionary *d, string word)
{

    if (d->head == NULL)
    {

        return true;
    }
    else
    {

        dWord *temp = d->head;

        while (temp != NULL)
        {

            if (temp->data == word)
            {
                return true;
            }

            temp = temp->next;
        }
    }

    return false;
}
Dictionary *addWord(Dictionary *l, string word)
{

    if (!isExist(l, word))
    {

        dWord *tmp = new dWord;
        tmp->data = word;
        tmp->next = NULL;
        if (l->head == NULL)
        {
            l->head = tmp;
            l->tail = tmp;
            tmp->previous = NULL;
        } // hek eza kenet fadye b5alle tnayneton ykouno tmp
        else
        {
            tmp->previous = l->tail; // kermel ma nemhe l old tail
            l->tail->next = tmp;
            l->tail = tmp;
        }

        cout << "the word has added successfully" << endl;
        ofstream out("dict.txt", std::ios::app);

        out << endl
            << word;

        out.close();
    }
    else
    {

        cout << "this word already exist";
    }

    return l;
}
// end ex4 //

void printListInFile(Dictionary *dictionary)
{

    if (dictionary->head == NULL)
    {

        cout << "The Dictionary is empty";
    }
    else
    {

        ofstream out;
        out.open("temp.txt");

        dWord *temp = dictionary->tail;

        while (temp != NULL)
        {
            sWord *syn = temp->synonym;
            sWord *ant = temp->antonym;

            if (syn == NULL)
            {
                out << temp->data;
                if (ant != NULL)
                {
                    out << "#";
                }
            }
            else if (ant != NULL)
            {
                out << temp->data + ":";
            }

            bool check;
            while (syn != NULL)
            {
                check = true;

                out << syn->data;
                if (syn->next == NULL && ant != NULL)
                {
                    out << "#";
                    break;
                }
                else
                {

                    out << ":";
                }

                syn = syn->next;
            }

            while (ant != NULL)
            {

                out << ant->data;
                if (ant->next == NULL)
                {

                    break;
                }
                else
                {

                    out << "#";
                }

                ant = ant->next;
            }
            out << endl;
            temp = temp->previous;
        }
        out.close();
    }
}

// function to print all the synonyms for a given word //nb8

void print_synonym(Dictionary *dict, string word)
{
    if (dict->head == NULL)
        cout << "the dictionnary is empty" << endl;
    else
    {
        dWord *search = new dWord;
        search = dict->head;
        while (search != NULL)
        {
            if (search->data == word)
            {
                if (search->synonym == NULL)
                {
                    cout << "no synonym for this word " << endl;
                    break;
                }
                else
                {
                    sWord *search_symo = search->synonym;
                    cout << "the synonyms are ";
                    while (search_symo != NULL)
                    {
                        cout << search_symo->data << " ";
                        search_symo = search_symo->next; // this to read all the syno
                    }
                    cout << endl;
                    break;
                }
            }
            search = search->next; // this is to read the doubly untill she found the word
        }
        if (search == NULL)
        {
            cout << "this word is not exist" << endl;
        } // here we say that the word does not exist so just he print yhis if he search in all the list
    }
}

// to print antonym //nb8
void print_antonym(Dictionary *dict, string word)
{
    if (dict->head == NULL)
        cout << "the dictionnary is empty" << endl;
    else
    {
        dWord *search = new dWord;
        search = dict->head;
        while (search != NULL)
        {
            if (search->data == word)
            {
                if (search->antonym == NULL)
                {
                    cout << "no antonym for this word " << endl;
                    break;
                }
                else
                {
                    sWord *search_anto = search->antonym;
                    cout << "the antonyms are ";
                    while (search_anto != NULL)
                    {
                        cout << search_anto->data << " ";
                        search_anto = search_anto->next; // this to read all the syno
                    }
                    cout << endl;
                    break;
                }
            }
            search = search->next; // this is to read the doubly untill she found the word
        }
        if (search == NULL)
        {
            cout << "this word is not exist" << endl;
        } // here we say that the word does not exist so just he print yhis if he search in all the list
    }
}

// print word begining with a set of letters // nb 7
void print_beg_letter(Dictionary *dict, string letters)
{

    dWord *search = dict->head;
    bool found;
    if (search == NULL)
        cout << "no word strating with this set of letters " << endl;
    else
    {
        while (search != NULL) // hone la nemro2 bi kel l word
        {
            found = true;
            for (int i = 0; i < letters.length(); i++)
            {
                if (search->data[i] != letters[i])
                {
                    found = false;
                    break; // w hone la nemro2 bel kelme hiye zeta bi ahrofa la nofhasa eza fi kelme ahrofa mech metel l ;etter bta3mol break
                }
            }
            if (found == true)
            {
                cout << search->data << " ";
            }
            search = search->next;
        }
    }
}

Dictionary *DeleteFromHead(Dictionary *dict)
{
    dWord *tmp = dict->head->next;
    dict->head->next = NULL; // this is a pointer and we should delete the pointer that point
    tmp->previous = NULL;
    delete dict->head;
    dict->head = tmp;
    return dict;
}

Dictionary *DeleteFromTail(Dictionary *dict)
{
    dWord *tmp = dict->tail->previous;
    tmp->next = NULL;
    delete dict->tail;
    dict->tail = tmp;
    return dict;
}

void DeleteLineFromFile(int line_index_todelete)
{
    int line_counter = 0;
    ofstream outfile;
    outfile.open("tmp.txt");
    ifstream readfile;
    readfile.open("dict.txt");
    string line;
    while (getline(readfile, line))
    {

        if (line_counter != line_index_todelete)
        {
            outfile << line << endl;
        }
        line_counter++;
    }

    remove("dict.txt");
    rename("tmp.txt", "dict.txt");
    outfile.close();
}

Dictionary *delete_beg_letter(Dictionary *dict, string letters)
{

    dWord *search = dict->head;
    bool found;
    int count_line = 0;
    if (search == NULL)
        cout << "no word strating with this set of letters " << endl;
    else
    {
        while (search != NULL) // hone la nemro2 bi kel l word
        {
            found = true;
            for (int i = 0; i < letters.length(); i++)
            {
                if (search->data[i] != letters[i])
                {
                    found = false;
                    break; // w hone la nemro2 bel kelme hiye zeta bi ahrofa la nofhasa eza fi kelme ahrofa mech metel l ;etter bta3mol break
                }
            }
            if (found == true)
            {
                if (search == dict->head)
                {
                    dict = DeleteFromHead(dict);
                    search = dict->head;
                }
                else if (search == dict->tail)
                {
                    dict = DeleteFromTail(dict);
                    DeleteLineFromFile(count_line);
                    return dict;
                }
                else
                {
                    dWord *tmp = search;
                    tmp->previous->next = tmp->next;
                    tmp->next->previous = tmp->previous;
                    search = search->next; // 3melna hek abel ldelete la2en betsir tzid 3a null w hal chi ma byozbat
                    delete tmp;
                }
                DeleteLineFromFile(count_line);
            }
            else
                search = search->next;

            count_line++;
        }
    }
    return dict;
}

Dictionary *delete_beg_letter_contain(Dictionary *dict, string letters)
{

    dWord *search = dict->head;
    int count_line = 0;
    if (search == NULL)
        cout << "no word strating with this set of letters " << endl;
    else
    {
        while (search != NULL) // hone la nemro2 bi kel l word
        {

            if (search->data.find(letters) != -1)
            {
                if (search == dict->head)
                {
                    dict = DeleteFromHead(dict);
                    search = dict->head;
                }
                else if (search == dict->tail)
                {
                    dict = DeleteFromTail(dict);
                    DeleteLineFromFile(count_line);
                    return dict;
                }
                else
                {
                    dWord *tmp = search;
                    tmp->previous->next = tmp->next;
                    tmp->next->previous = tmp->previous;
                    search = search->next; // 3melna hek abel ldelete la2en betsir tzid 3a null w hal chi ma byozbat
                    delete tmp;
                }
                DeleteLineFromFile(count_line);
            }
            else
            {
                search = search->next;
            }

            count_line++;
        }
    }
    return dict;
}

void swapWithLinks(Dictionary *Dict, dWord *a, dWord *b)
{
    if (a->previous == nullptr)
        Dict->head = b;
    else
        a->previous->next = b;

    if (b->next == nullptr)
        Dict->tail = a;
    else
        b->next->previous = a;

    a->next = b->next;
    b->previous = a->previous;
    b->next = a;
    a->previous = b;
}

Dictionary *sort(Dictionary *Dict)
{

    if (Dict->head == NULL || Dict->head->next == NULL)
        return Dict;

    dWord *lastNode = NULL;
    bool swapped;

    do
    {
        swapped = false;
        dWord *cur = Dict->head;

        while (cur->next != lastNode)
        {
            const char *charArray = cur->data.c_str();
            const char *charArray2 = cur->next->data.c_str();

            if (strcmp(charArray, charArray2) > 0)
            {
                swapWithLinks(Dict, cur, cur->next);
                swapped = true;
            }
            else
                cur = cur->next;
        }

        lastNode = cur;

    } while (swapped);

    return Dict;
}

void print_word(Dictionary *dict)
{
    dWord *tmp = dict->head;
    while (tmp != NULL)
    {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

Dictionary *readFromFile(Dictionary *dictio)
{
    string line;
    ifstream read;
    string synonym[20][20]; // awal chi 3melne 2d kermel ne2dar nektob 3a aktar men sater //w bi siro y3abo in paralel
    string antonym[20][20];
    int index = 0;
    int count_syn = 0, count_ant = 0, row = 0; // row 3ada l astor
    read.open("dict.txt");
    while (getline(read, line)) // bye2ra sater sater w bihoton bi aleb  line la yo5laso // bya3mel override bi aleb l line
    {
        count_syn = 0;
        count_ant = 0;
        index = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#') // line[i] 3am nemche fiya haref haref
            // hatayna hek metel base case la hata to2toch men l antonym
            //  l index hatayneha la na3ref men wen lezem ybalech y3abe
            {
                index = i;
                break;
            }
            else if (line[i] != ':')
            {
                synonym[row][count_syn] = synonym[row][count_syn] + line[i]; // line[i] 3am nemche fiya haref haref
            }
            else if ((line[i] == ':'))
            {
                count_syn++; // this the number of column
            }
        }
        for (int j = index + 1; j < line.length(); j++)
        {
            if (line[j] != '#')
            {
                antonym[row][count_ant] = antonym[row][count_ant] + line[j]; // line[i] 3am nemche fiya haref haref
            }
            else if ((line[j] == '#'))
            {
                count_ant++; // this the number of column
            }
        }

        dictio = input_data_todoubly(dictio, count_syn, count_ant, synonym, antonym, row);
        row++; // hone zedna l row la yenzal 3ala sater jdid w lahal l while ha t5ali yerja3 3al loop la2en ma 5allas l loop
    }
    return dictio;
}

int menu()
{
    cout << "1- search the synonym of a word " << endl;
    cout << "2- search the antonym of a word " << endl;
    cout << "3- search the words starting by a given string from the user " << endl;
    cout << "4- delete the words containing the string entered by the user " << endl;
    cout << "5- delete the words starting with a given set of letters entered by the user " << endl;
    cout << "6- sort the words of the dictionnary " << endl;
    cout << "7- write the dictionary in a new tmp file " << endl;
    cout << "8- Add a new word to the dictionnary " << endl;
    cout << " please enter your choice : " << endl;
    int choice;
    do
    {
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8)
            cout << "you can just enter from 1-8 ! " << endl;
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8);

    return choice;
}

int main()
{

    Dictionary *dict = new Dictionary;
    dict = readFromFile(dict);
    int choice;
    print_word(dict);
    cout<<endl;
    choice = menu();
    if (choice == 1)
    {
        string word;
        cout << "please enter the word :" << endl;
        cin >> word;
        print_synonym(dict, word);
    }
    else if (choice == 2)
    {
        string word;
        cout << "please enter the word :" << endl;
        cin >> word;
        print_antonym(dict, word);
    }
    else if (choice == 3)
    {
        string word;
        cout << "please enter the set of letter do you wanna test :" << endl;
        cin >> word;
        print_beg_letter(dict, word);
    }
    else if (choice == 4)
    {
        cout<<"the dictionnary before delete "<<endl;
        print_word(dict);
        string word;
        cout << "please enter the set of letter , to delete all the word conataining this letters :" << endl;
        cin >> word;
        dict=delete_beg_letter_contain(dict, word);
        cout<<"the dictionnary after delete "<<endl;
        print_word(dict);
    }
     else if (choice == 5)
    {
        cout<<"the dictionnary before delete "<<endl;
        print_word(dict);
        string word;
        cout << "please enter the set of letter , to delete all the word starting with theses letters :" << endl;
        cin >> word;
        delete_beg_letter(dict, word);
        cout<<"the dictionnary after delete "<<endl;
        print_word(dict);
    }
    else if (choice == 6)
    {
        cout<<"the dictionnary before sorting "<<endl;
        print_word(dict);
        dict=sort(dict);
        cout<<"the dictionnary after sorting "<<endl;
        print_word(dict);
    }
     else if (choice == 7)
    {
        printListInFile(dict);
    }
  
      else if (choice == 8)
    {
       cout<<"the dictionnary before deleting the word "<<endl;
        print_word(dict);
        cout<<endl;
        string word;
        cout<<"please enter the word to delete"<<endl;
        cin>>word;
        dict=addWord(dict,word);
        cout<<"the dictionnary after deleting the word  "<<endl;
        print_word(dict);
    }
  
}