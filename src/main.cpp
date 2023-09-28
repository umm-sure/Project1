#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "avl.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

using namespace std;

bool isNumber(string& s)
{
    //check if each char in string is a digit
    for(char i : s)
    {
        if(isdigit(i) == 0)
            return false;
    }
    return true;
}

bool isName(string& s)
{
    //check if each char in string is either in the alphabet or is a space
    for(char i : s)
    {
        if(!isalpha(i) && !isspace(i))
            return false;
    }
    return true;
}

bool isID(string s)
{
    //check if string is proper length and each char is a digit
    if(s.length() != 8)
        return false;

    for(char i : s)
    {
        if(isdigit(i) == 0)
            return false;
    }
    return true;
}

int main(){

    int ids[] = {86605962,53451725,99403409,53940880,91657404,82016348,27658956,64400694,65860039,75740255,91481400,98454630,26183109,82235756,57398873,36906738,42615522,20814368,91138805,86748719,80399360,26621183,15530692,11899101,48729295,4684002,1295297,54733580,56583621,45447830,32194565,74278787,61838705,73401779,14639669,11523231,72363533,4916154,39712623,29448680,18069412,77488139,20126541,67993112,21061874,18050708,42610679,8472673,99117528,48014984,8984198,43113299,31707876,69791364,16267227,55655821,10894120,23570372,81546436,16439829,62120709,10418695,67645233,39923758,47926079,88972313,58723255,6078161,64538495,59886863,23250842,29558130,31914515,92519204,33150273,10637347,42107104,93458958,51506177,24338170,62512375,4422275,15248312,77260611,96922828,81249711,66728028,2008135,82331097,13255677,9080921,98839352,20441832,78465157,78499598,80225814,2862196,45651362,47601297,67653624};

    string names[] = {" alive","chivalrous","thankful","adaptable","hateful","boiling","like","clip","milky","partner","deserted","snail","arch","distance","macabre","moor","action","ugliest","page","dime","melted","pour","wood","hang","baby","bury","maniacal","cover","hollow","word","simple","tight","scale","winter","chase","absorbing","twig","discover","proud","momentous","nutty","ladybug","wiry","fanatical","madly","careful","air","tow","drink","fry","salty","purring","stuff","courageous","descriptive","move","visit","kneel","crush","guard","continue","queen","fantastic","tender","incompetent","locket","hug","teeth","limit","plug","oven","can","wakeful","longing","tramp","skinny","cattle","somber","acrid","launch","talk","wriggle","arrange","playground","rabbits","repeat","voracious","shrug","country","week","stupendous","finger","material","nosy","unable","redundant","lock","penitent","numerous","different"};
    int n = sizeof(ids) / sizeof(ids[0]);
    //sort(ids, ids + n);
    //enter number of commands to be entered
    int num_commands = 0;
    cin >> num_commands;
    cin.ignore();

    avlTree tree; //instantiate avl tree

    for(int i = 0; i < num_commands; i++)
    {
        string line;
        getline(cin, line);

        istringstream in(line);

        string command;
        in >> command; //get command

        if(command.length() > 6) //if for commands longer than 6 characters
        {
            if(command == "test100")
            {
                for(int j = 0; j < 100; j++)
                {
                    cout << "insert " << '"' << names[j] << '"' << ' ' << to_string(ids[j]) << endl;
                    cout << tree.insert(names[j], to_string(ids[j])) << endl;
                    if (j%5 == 0 || j%3 == 0)
                    {
                        cout << "printPreorder" << endl;
                        tree.printPreorder();
                        cout << endl;
                    }
                }
            }
            else if(command == "printInorder") {
                tree.printInorder();
                cout << endl;
            }
            else if(command == "printPreorder") {
                tree.printPreorder();
                cout << endl;
            }
            else if(command == "printPostorder") {
                tree.printPostorder();
                cout << endl;
            }
            else if(command == "printLevelCount")
                tree.printLevelCount();
            else if(command == "removeInorder")
            {
                string num;
                in >> num; //enter number of removeinorder
                if(!num.empty() && isNumber(num))
                    cout << tree.removeInorder(stoi(num)) << endl;
                else
                    cout << "unsuccessful" << endl;
            }
            else
                cout << "unsuccessful" << endl;
        }
        else if(command == "insert")
        {
            string space;
            getline(in, space, '"'); //get space char before first quote

            string name;
            getline(in, name, '"'); //get name

            if(isName(name)) //check name
            {
                string id;
                getline(in, id); //get id for insert

                if(isID(id.substr(1))) //check id string (index 0 is a space)
                {
                    cout << tree.insert(name, id.substr(1)) << endl;
                }
                else
                {
                    cout << "unsuccessful" << endl;
                }
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if(command == "search")
        {
            string searchParam;
            in >> searchParam; //get search param

            string name = searchParam.substr(1, searchParam.length()-2); //strip quotes for name checking

            if(isID(searchParam)) //check if param is ID
            {
                cout << tree.search(searchParam) << endl;
            }
            else if(searchParam[0] == '"' && searchParam[searchParam.length()-1] == '"' && isName(name))
            {
                //check if param is name with ends being quotes
                cout << tree.searchName(name) << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if(command == "remove")
        {
            string id;
            in >> id; //get ID, remove param must be ID and not name

            if(isID(id))
            {
                cout << tree.remove(id) << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }

	return 0;
}

