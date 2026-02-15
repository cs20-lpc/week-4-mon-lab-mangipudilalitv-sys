template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) {
    this->length = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj)
: head(nullptr) {
    this->length = 0;
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    } else {
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
    }

    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* prev = nullptr;

    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }

    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    // start clean (safe even if already empty)
    clear();

    // if copyObj empty
    if (copyObj.head == nullptr) {
        head = nullptr;
        this->length = 0;
        return;
    }

    // copy first node
    head = new Node(copyObj.head->value);
    Node* myCurr = head;
    Node* copyCurr = copyObj.head->next;

    // copy rest
    while (copyCurr != nullptr) {
        myCurr->next = new Node(copyCurr->value);
        myCurr = myCurr->next;
        copyCurr = copyCurr->next;
    }

    this->length = copyObj.length;
}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }

    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        throw string("insert: error, position out of bounds");
    }

    Node* n = new Node(elem);

    // insert at front
    if (position == 0) {
        n->next = head;
        head = n;
        this->length++;
        return;
    }

    // walk to node before insertion point
    Node* prev = head;
    for (int i = 0; i < position - 1; i++) {
        prev = prev->next;
    }

    n->next = prev->next;
    prev->next = n;

    this->length++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        throw string("remove: error, position out of bounds");
    }

    // remove front
    if (position == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        this->length--;
        return;
    }

    // walk to node before the one to delete
    Node* prev = head;
    for (int i = 0; i < position - 1; i++) {
        prev = prev->next;
    }

    Node* victim = prev->next;
    prev->next = victim->next;
    delete victim;

    this->length--;
}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    } else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}