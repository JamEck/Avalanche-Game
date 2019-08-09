#ifndef List_hpp
#define List_hpp

#include <iostream>

#define NODE List<T>::Node
#define ITER List<T>::Iterator

template <typename T>
class List{
private:
    struct Node{
        T data;
        Node* ptr = nullptr;
    };
    
    NODE* head = nullptr;
    NODE* tail = nullptr;
    
    NODE* walk(int index);
    
    void append (Node* inp);
    void append (Node& inp);
    void prepend(Node* inp);
    void prepend(Node& inp);
    void insert (Node* inp, int index);
    void insert (Node& inp, int index);
    
    int length = 0;
public:
    
    List();
    List(List* inp);
    List(List& inp);
    ~List();
    
    void wipe();
    
    void copy(List* inp);
    void copy(List& inp);
    void operator= (List* inp);
    void operator= (List& inp);
    
    bool isempty();
    int count();
    
    T& operator[](int index);
    
    void append();
    void append(T& inp);
    void append(T&& inp);
    void append(List* inp);
    void append(List& inp);
    
    void prepend();
    void prepend(T& inp);
    void prepend(List* inp);
    void prepend(List& inp);
    
    void insert(int index);
    void insert(T& inp, int index);
    void insert(List* inp, int index);
    void insert(List& inp, int index);
    
    void popEnd();
    void popEnd(int num);
    void popFront();
    void popFront(int num);
    void remove(int index);
    void remove(T* inp);
    
    int len();
    T& front();
    T& back();
    
    void print   (bool mem = false);
    void printHaT(bool mem = false);
    
    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, List<U>& inp);
    
    
    class Iterator{
    private:
        NODE* head;
        NODE* curr;
        bool end;
    public:
        Iterator();
        Iterator(ITER& iter);
        Iterator(ITER&& iter);
        void copy(ITER& iter);
        void copy(ITER&& iter);
        
        void next();
        
        bool atEnd();
        void reset();
        
        T& data();
        void operator= (T& inp);
        void operator= (T&& inp);
        void operator= (ITER& iter);
        void operator= (ITER&& iter);
        
        friend ITER List<T>::getIter();
    };
    
    ITER getIter();
};

//////// CONSTRUCTOR ////////////////////////

template <typename T>
List<T>::List(){
}
template <typename T>
List<T>::List(List* inp){
    copy(inp);
}
template <typename T>
List<T>::List(List& inp){
    copy(&inp);
}

//////// DESTRUCTOR ////////////////////////

template <typename T>
List<T>::~List(){
    wipe();
}

//////// WIPE ////////////////////////

template <typename T>
void List<T>::wipe(){
    NODE* curr = head;
    while(curr != nullptr){
        curr = curr->ptr;
        delete head;
        head = curr;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;
}

//////// COPY ////////////////////////

template <typename T>
void List<T>::copy(List* inp){
    NODE* curr = inp->head;
    while(curr != nullptr){
        NODE* temp = new NODE;
        temp->data = curr->data;
        append(temp);
        curr = curr->ptr;
    }
    length = inp->length;
}
template <typename T>
void List<T>::copy(List& inp){
    copy(&inp);
}

template <typename T>
void List<T>::operator=(List* inp){
    copy(inp);
}
template <typename T>
void List<T>::operator=(List& inp){
    copy(&inp);
}

//////// ISEMPTY ////////////////////////////////

template <typename T>
bool List<T>::isempty(){
    //    return (head == nullptr || tail == nullptr);
    return length == 0;
}

//////// COUNT ////////////////////////////////

template <typename T>
int List<T>::count(){
    NODE* curr = head;
    int i = 0;
    while (curr != nullptr){
        i++;
        curr = curr->ptr;
    }
    //    length = i;
    return i;
}

//////// WALK ////////////////////////////////

template <typename T> // gets the index'th node
typename NODE* List<T>::walk(int index){
    NODE* curr = head;
    for(int i = 0; i < index; i++){
        if(curr != nullptr){
            curr = curr->ptr;
        }
        if(curr == nullptr){
            curr = tail;
        }
    }
    return curr;
}

template <typename T> // gets the item in the index'th node
T& List<T>::operator[] (int index){
    return walk(index)->data;
}

//////// APPEND ////////////////////////////////

template <typename T>
void List<T>::append(Node* inp){
    if(isempty()){
        head = inp;
    }else{
        tail->ptr = inp;
    }
    tail = inp;
    length++;
}
template <typename T>
void List<T>::append(Node& inp){
    append(&inp);
}

template <typename T>
void List<T>::append(){
    NODE* n = new NODE;
    append(n);
}
template <typename T>
void List<T>::append(T& inp){
    append();
    tail->data = inp;
}
template <typename T>
void List<T>::append(T&& inp){
    append();
    tail->data = inp;
}
template <typename T>
void List<T>::append(List* inp){
    List<T> temp(inp);
    
    if(isempty()){
        head = temp.head;
    }else{
        tail->ptr = temp.head;
    }
    if(!temp.isempty()){
        tail = temp.tail;
    }
    
    length += inp->length;
    
    // prevents temp list from freeing nodes
    temp.head = nullptr;
}
template <typename T>
void List<T>::append(List& inp){
    append(&inp);
}

//////// PREPEND ////////////////////////////////

template <typename T>
void List<T>::prepend(Node* inp){
    if(isempty()){    // if this list is empty
        tail = inp;  // set inp as results tail
    }else{
        inp->ptr = head; // the inp points to curr head
    }
    head = inp;      // inp becomes the new head
    
    length++;
}
template <typename T>
void List<T>::prepend(Node& inp){
    prepend(&inp);
}

template <typename T>
void List<T>::prepend(){
    NODE* n = new NODE;
    prepend(n);
}
template <typename T>
void List<T>::prepend(T& inp){
    prepend();
    head->data = inp;
}
template <typename T>
void List<T>::prepend(List* inp){
    List<T> temp(inp);
    if(isempty()){              // if this list is empty
        tail = temp.tail;      // this tail is the inp's tail
    }else{
        if(!temp.isempty()){        // so long as inp isnt empty
            temp.tail->ptr = head; // the inp's tail points to our head
        }
    }
    if(!temp.isempty()){        // so long as inp isnt empty
        head = temp.head;      // set the results head to inp's head
    }
    
    length += inp->length;
    
    // prevents temp list from freeing nodes
    temp.head = nullptr;
}
template <typename T>
void List<T>::prepend(List& inp){
    prepend(&inp);
}

//////// INSERT ////////////////////////////////

template <typename T>
void List<T>::insert(Node* inp, int index){
    if(isempty()){
        append(inp);
    }else{
        NODE* prev = walk(index);
        
        inp->ptr = prev->ptr;
        prev->ptr = inp;
        length++;
    }
}
template <typename T>
void List<T>::insert(Node& inp, int index){
    insert(&inp, index);
}

template <typename T>
void List<T>::insert(int index){ // insert new node at (index + 1)th position
    NODE* n = new NODE;
    insert(n, index);
}
template <typename T>
void List<T>::insert(T& inp, int index){ // insert new node at (index + 1)th position
    NODE*n  = new NODE;
    n->data = inp;
    insert(n, index);
}
template <typename T>
void List<T>::insert(List* inp, int index){
    if(isempty()){
        append(inp);
    }else{
        List<T> temp(inp);
        
        NODE* prev = walk(index);
        
        if(!temp.isempty()){
            temp.tail->ptr = prev->ptr;
            prev->ptr = temp.head;
        }
        
        length += inp->length;
        
        temp.head = nullptr; // prevent tempList from deleting nodes
    }
}
template <typename T>
void List<T>::insert(List& inp, int index){
    insert(&inp, index);
}

//////// DELETING ////////////////////////////////
template <typename T>
void List<T>::popEnd(){
    if(!isempty()){
        NODE* curr = head;
        while(curr->ptr != tail){
            curr = curr->ptr;
        }
        delete tail;
        tail = curr;
        tail->ptr = nullptr;
        length--;
    }
}
template <typename T>
void List<T>::popEnd(int num){
    if(!isempty()){
        for(int i = 0; i < num; i++){
            popEnd();
        }
    }
}
template <typename T>
void List<T>::popFront(){
    if(!isempty()){
        NODE* temp = head->ptr;
        delete head;
        head = temp;
        length--;
    }
}
template <typename T>
void List<T>::popFront(int num){
    if(!isempty()){
        for(int i = 0; i < num; i++){
            popFront();
        }
    }
}

template <typename T>
void List<T>::remove(int index){
    if(length > 1){
        if(index < 1){
            popFront();
            return;
        }
        if(index >= length){
            popEnd();
            return;
        }
        NODE* save = walk(index-1);
        NODE* temp = save->ptr;
        save->ptr = temp->ptr;
        delete temp;
        length--;
    }else{
        wipe();
    }
}
template <typename T>
void List<T>::remove(T* inp){
    using namespace std;
    if(!isempty()){
        if(&(head->data) == inp){ // check first node
            popFront();
            return;
        }else
            if(&(tail->data) == inp){ // check last node
                popEnd();
                return;
            }
        
        NODE* prev = head;
        while(prev->ptr != nullptr && &(prev->ptr->data) != inp){
            prev = prev->ptr; // search through list
        }
        
        if(prev->ptr == nullptr) return; // if reached end, no op
        
        
        NODE* targetNode = prev->ptr; // save what prev points to
        prev->ptr = targetNode->ptr; // link prev to post
        delete targetNode;
        length--;
    }
}

//////// ACCESSORS ////////////////////////////////

template <typename T>
int List<T>::len(){
    return length;
}
template <typename T>
T& List<T>::back(){
    return tail->data;
}
template <typename T>
T& List<T>::front(){
    return head->data;
}

//////// PRINT ////////////////////////////////

template <typename T>
void List<T>::print(bool mem){
    using namespace std;
    
    cout << "List: " << hex << this << endl;
    if(isempty()){
        cout << "empty";
    }else{
        NODE* curr = head;
        while(curr != nullptr){
            if(mem){
                cout << hex << curr;
            }else{
                //                cout << dec << curr->data;
            }
            if(curr->ptr != nullptr){
                cout << " -> ";
            }
            curr = curr->ptr;
        }
    }
    cout << endl;
}

template <typename T>
void List<T>::printHaT(bool mem){
    using namespace std;
    
    cout << "List: " << hex << this << endl;
    
    if(mem){
        cout << "head: " << hex << head << endl;
        cout << "tail: " << hex << tail << endl;
    }else{
        cout << "head: " << hex << head->data << endl;
        cout << "tail: " << hex << tail->data << endl;
    }
}

template <typename T>
std::ostream& operator<< (std::ostream& os, List<T>& inp){
    os << "List: " << std::hex << &inp << std::endl;
    if(inp.isempty()){
        os << "empty";
    }else{
        for(int i = 0; i < inp.len()-1; i++){
            os << inp[i] << " -> ";
        }
        
        os << inp[inp.len()-1];
        
    }
    os << std::endl;
    return os;
}

//////// ITERATOR ////////////////////////////////

template <typename T> typename
ITER List<T>::getIter(){
    ITER iter;
    iter.curr = head;
    iter.head = head;
    iter.end = isempty()?true:false;
    return iter;
}
template <typename T>
List<T>::Iterator::Iterator(){
    curr = nullptr;
    head = nullptr;
    end  = true;
}
template <typename T>
List<T>::Iterator::Iterator(ITER& iter){
    copy(iter);
}
template <typename T>
List<T>::Iterator::Iterator(ITER&& iter){
    copy(iter);
}
template <typename T>
void List<T>::Iterator::copy(ITER& iter){
    curr = iter.curr;
    head = iter.curr;
    end  = iter.end;
}
template <typename T>
void List<T>::Iterator::copy(ITER&& iter){
    copy(iter);
}

template <typename T>
void List<T>::Iterator::next(){
    if(!end && curr->ptr != nullptr){
        curr = curr->ptr;
    }else{
        end = true;
    }
}

template <typename T>
bool List<T>::Iterator::atEnd(){
    return end;
}
template <typename T>
void List<T>::Iterator::reset(){
    if(head != nullptr){
        curr = head;
        end  = false;
    }
}
template <typename T>
T& List<T>::Iterator::data(){
    return curr->data;
}
template <typename T>
void List<T>::Iterator::operator=(T& inp){
    curr->data = inp;
}
template <typename T>
void List<T>::Iterator::operator=(T&& inp){
    curr->data = inp;
}
template <typename T>
void List<T>::Iterator::operator=(ITER& iter){
    copy(iter);
}
template <typename T>
void List<T>::Iterator::operator=(ITER&& iter){
    copy(iter);
}

#endif
