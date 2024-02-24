class Menu{
    public:
        static void displayMenu(){
            cout << "===================================================="<<endl;
            cout << "z : up, s : down, e : create, d : delete, q : quit" <<endl;
        }

        static void displayTitle(){
            cout << "                     TO DO LIST" <<endl;
            cout << "===================================================="<<endl;
        }

        static ToDo createTD(){
            string t, d;
            cout << endl << "title :";
            getline(cin, t);
            cout << "description :";
            getline(cin, d);
            return ToDo(t, d);
        }
};