class ToDo{
    private:
        string title;
        string description;
    public:

        ToDo(){}

        ToDo(string t, string d): title(t), description(d){}

        string getTitle(){
            return this->title;
        }

        string getDesc(){
            return this->description;
        }

        void setTitle(string t){
            this->title = t;
        }

        void setDesc(string d){
            this->description = d;
        }

};

class ToDoList{
    private:
        vector<ToDo> toDoList;
        size_t selector = toDoList.size()-1;
    public:

        ToDoList(){}

        vector<ToDo> getTDL(){
            return this->toDoList;
        }

        void load(){
            ifstream fileModel("../data.td");
            string text, symbol;
            if(fileModel.is_open()){
                while(fileModel){
                    ToDo buff;
                    for(int i = 0; i < 2; i++){
                        getline(fileModel, text);
                        cout << text << " | " << text.size() << endl;
                        if(!text.size())
                            break;
                        symbol = text.substr(0,2);
                        text = text.substr(3,text.size());
                        if(symbol == "-t")
                            buff.setTitle(text);
                        if(symbol == "-d")
                            buff.setDesc(text);   
                    }
                    this->addTD(buff);
                }
            }
            this->clean();
            this->selector = 0;
        }

        void save(){
            ofstream newFile("../data.td");
            for(int i = 0; i < this->toDoList.size(); i++){
                newFile << "-t "<< this->toDoList[i].getTitle() << endl;
                newFile << "-d "<< this->toDoList[i].getDesc();
                if(i != this->toDoList.size()-1)
                    newFile << endl;
            }
            newFile.close();
        }

        void clean(){ //delete every toDo where the title is null
            for(int i = 0; i < this->toDoList.size(); i++){
                if(this->toDoList[i].getTitle().size() < 1){
                    this->toDoList.erase(this->toDoList.begin()+i);
                }
            }
        }

        void addTD(ToDo td){
            this->toDoList.push_back(td);
            this->selector = this->toDoList.size()-1; 
        }

        void removeTD(){
            this->toDoList.erase(this->toDoList.begin()+this->selector);
            this->selector = 0;
        }

        void clearTD(){
            this->toDoList.clear();
        }

        void display(){
            for(int i = 0; i < this->toDoList.size(); i++){
                if(i == this->selector)
                    cout << "> ";
                cout << i+1 << "-";
                cout << "title : " << this->toDoList[i].getTitle() << endl;
                cout << "description : " << this->toDoList[i].getDesc() << endl << endl;
            }
        }

        void addSelector(size_t n){
            this->selector = (this->selector + n ) % this->toDoList.size();
        }
};
