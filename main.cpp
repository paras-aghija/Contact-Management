#include<bits/stdc++.h>
using namespace std;

void printStars(int n) {
  for (int i = 0; i < n; i++)
    cout << "*****";
  cout << endl;
}

void projCredits() {
  cout << endl;
  printStars(7);
  cout << "Project: CONTACT MANAGEMENT SYSTEM \nMade by:\n\t1. Paras Aghija (19103074) \n\t2. Gautam Sachdeva(19103084) \n\t3. Anurag Rai(19103065)" << endl;
  printStars(7);
}

string upperToLower(string S) {
  for (auto i = S.begin(); i != S.end(); i++) {
    if (*i >= 65 && *i <= 90)
      *i += 32;
  }
  return S;
}

class Contact {
  string fname, lname, email, address, bday;
  vector<string> phone_numbers;

public:

  // Constructor
  Contact(string fname, string lname, string pno, string email, string address, string bday) {
    this->fname = fname;
    this->lname = lname;
    this->phone_numbers.push_back(pno);
    this->email = email;
    this->address = address;
    this->bday = bday;
  }

  string getfName() {
    return fname;
  }

  string getlName() {
    return lname;
  }

  vector<string> getPNo() {
    return phone_numbers;
  }

  //  Updates Phone No.
  void updatePNo(string old_pno, string new_pno) {
    auto it = find(phone_numbers.begin(), phone_numbers.end(), old_pno);
    *it = new_pno;
  }

  // Add another Phone No.
  void addPhone(string pno) {
    phone_numbers.push_back(pno);
  }

  // Prints All Details
  void printDetails() {
    cout << endl << "Name : " << fname << " " << lname << endl;
    cout << "Phone Number : ";
    for (auto pno : phone_numbers)
      cout << pno << ", ";
    cout << endl;
    cout << "E-Mail : " << email << endl;
    cout << "Address : " << address << endl;
    cout << "Birthday : " << bday << endl;
    cout << endl;
  }
};



class Node {

public:
  char data;
  map<char, Node*> children;
  Contact* person;  // acts as bool terminal

  Node(char d) {
    data = d;
    person = NULL;
  }
};



class Trie {
  Node* root;
  int count;

public:
  Trie() {
    root = new Node('\0');
    count = 0;
  }

  Contact* insert(string fname, string lname, string pno, string email, string address, string bday) {
    string w = fname + lname;
    w = upperToLower(w);
    Node* temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch)) {
        temp = temp->children[ch];
      }
      else {
        Node* n = new Node(ch);
        temp->children[ch] = n;
        temp = n;
      }
    }
    temp->person = new Contact(fname, lname, pno, email, address, bday);
    return temp->person;
  }

  void printAllBelow(Node* root) {
    if (root == NULL) root = this->root;

    if (root->person) root->person->printDetails();

    for (auto pair : root->children) {
      if (pair.second) printAllBelow(pair.second);
    }
  }

  void find(string w) {
    Node* temp = root;
    w = upperToLower(w);
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "# Contact Not Found #" << endl;
        return;
      }
      else
        temp = temp->children[ch];
    }
    printAllBelow(temp);
    // if(temp->person != NULL) temp->person->printDetails();
  }

  // Update Phone Number Function
  Contact* update(string w1, string w2, string old_pno, string new_pno) {
    string w = w1 + w2;
    w = upperToLower(w);
    Node* temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "# Contact Does not Exist!! #" << endl;
        return NULL;
      }
      else temp = temp->children[ch];
    }
    if (temp->person) temp->person->updatePNo(old_pno, new_pno);

    return temp->person;
  }

  Contact* addPhoneNumber(string w1, string w2, string new_pno) {
    string w = w1 + w2;
    w = upperToLower(w);
    Node* temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "# Contact Does not Exist!! #" << endl;
        return NULL;
      }
      else temp = temp->children[ch];
    }
    if (temp->person) temp->person->addPhone(new_pno);

    return temp->person;
  }

  void deleteContact(string w) {
    Node* temp = root;
    w = upperToLower(w);
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "# Contact Not Found!! #" << endl;
        return;
      }
      else
        temp = temp->children[ch];
    }
    if (temp->person != NULL) {
      Contact *t = temp->person;
      temp->person = NULL;
      delete t;
    }
  }
};



class Trie2 {
  Node* root;
  int count;

public:

  Trie2() {
    root = new Node('x');
    count = 0;
  }

  void insert(string pno, Contact* s) {
    string w = pno;
    Node* temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch))
        temp = temp->children[ch];
      else {
        Node* n = new Node(ch);
        temp->children[ch] = n;
        temp = n;
      }
    }
    temp->person = s;
  }

  void printAllBelow(Node *root) {
    if (root->person)
      root->person->printDetails();

    for (auto pair : root->children) {
      if (pair.second)
        printAllBelow(pair.second);
    }
    cout << "# No More Contacts exists!! #" << endl;
  }

  void print(Node *root) {
    if (root->person)
      root->person->printDetails();
  }

  void find(string w) {
    Node* temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "# Contact Does Not Exits!! #" << endl;
        return;
      }
      else {
        temp = temp->children[ch];
      }
    }
    printAllBelow(temp);
    // if(temp->person != NULL){
    //   temp->person->printDetails();
    // }
  }

  bool isEmpty(Node* root)
  {
    for (int i = 0; i < 10; i++)
      if (root->children[i])
        return false;
    return true;
  }

  void breakLink(string w) {
    Node *temp = root;
    for (auto ch : w) {
      if (temp->children.count(ch) == 0) {
        cout << "# Contact Not Found!! #" << endl;
        return;
      }
      else {
        temp = temp->children[ch];
      }
    }
    temp->person = NULL;
  }

  void update(string oldNo, string newNo, Contact *s) {
    breakLink(oldNo);
    insert(newNo, s);
  }

  string deleteContact(string pno) {
    Node* temp = root;
    string w;
    for (auto ch : pno) {
      if (temp->children.count(ch) == 0) {
        cout << endl << "Contact Not Found" << endl;
        return "none";
      }
      else {
        temp = temp->children[ch];
      }
    }
    if (temp->person != NULL) {
      w = temp->person->getfName() + temp->person->getlName();
      temp->person = NULL;
      return w;
    }
    else {
      return "none";
    }

  }
};

class ContactBook {
  Trie T;
  Trie2 T2;

public:

  void insert(string fname, string lname, string pno, string email, string address, string bday) {
    Contact *x = T.insert(fname, lname, pno, email, address, bday);
    T2.insert(pno, x);
  }

  void update(string fname, string lname, string oldpno, string newpno) {
    Contact *x = T.update(fname, lname, oldpno, newpno);
    T2.update(oldpno, newpno, x);
  }

  void findByName(string w) {
    T.find(w);
  }

  void findByPhoneNumber(string w) {
    T2.find(w);
  }

  void addPhoneNumber(string fname, string lname, string pno) {
    Contact *x = T.addPhoneNumber(fname, lname, pno);
    if (x != NULL) {
      T2.insert(pno, x);
    }
  }

  void printAllContacts() {
    T.printAllBelow(NULL);
  }

  void deleteContact(string pno) {
    string w = T2.deleteContact(pno);
    if (w != "none") {
      T.deleteContact(w);
    }

  }
};


// Driver Code
int main() {

  ContactBook contactBook;
  contactBook.insert("Paras", "Aghija", "9999988888", "aghija.paras@gmail.com", "Delhi", "19 August");
  contactBook.insert("Gautam", "Sir", "7777788888", "sachdeva.gautam@gmail.com", "Prayagraj", "23 June");
  contactBook.insert("Anurag", "Rai", "7777766666", "rai.anurag@gmail.com", "Varanasi", "9 August");
  contactBook.insert("Shaan", "Grover", "5555566666", "grover.shaan@gmail.com", "Delhi", "9 August");

  printStars(5);
  cout << " \t\tPHONEBOOK " << endl;
  printStars(5);

  while (1) {
    int opt;
    cout << endl << "=> Features:\n 1 - Add Contact \n 2 - Add another Phone Number for a Contact \n 3 - Delete Contact \n 4 - Search Contact \n 5 - Update Contact \n 6 - All Contacts \n 7 - Project Details \n 8 - Exit" << endl;
    cout << "Enter your Choice: ";
    cin >> opt;

    switch (opt) {
    case 1: { // Contact Addition
      string cont[6];
      cout << endl << "\tEnter First Name: ";
      cin >> cont[0];
      cout << "\tEnter Last Name: ";
      cin >> cont[1];
      cout << "\tEnter Phone Number: ";
      cin >> cont[2];
      cout << "\tEnter E-Mail: ";
      cin >> cont[3];
      cout << "\tEnter Address: ";
      cin >> cont[4];
      cout << "\tEnter Birthday: ";
      cin.ignore();
      getline(cin, cont[5]);
      contactBook.insert(cont[0], cont[1], cont[2], cont[3], cont[4], cont[5]);
      cout << endl << "Contact Created Successfully!!" << endl;
      break;
    }

    case 2: {
      string findCont_fname, findCont_lname, newPno;
      cout << endl << "\tEnter First Name of Contact: ";
      cin >> findCont_fname;
      cout << "\tEnter Last Name of Contact: ";
      cin >> findCont_lname;

      cout << "\tEnter another Phone Number: ";
      cin >> newPno;

      contactBook.addPhoneNumber(findCont_fname, findCont_lname, newPno);
      cout << endl << "Phone Number added to Contact Successfully!" << endl;
      break;
    }

    case 3: { // Contact Deletion
      string Pno;
      cout << endl << "\tEnter the Phone Number of Contact: ";
      cin >> Pno;

      contactBook.deleteContact(Pno);
      cout << endl << "Contact deleted Successfully!" << endl;
      // contactBook.printAllContacts();
      break;
    }

    case 4: { // Search Contact
      int ch;
      cout << endl << "\t1 - Search by Name\n\t2 - Search by Phone Number\n\tEnter your choice: ";
      cin >> ch;
      if (ch == 1) {
        string findCont_name;
        cout << endl << "\tEnter Name of Contact: ";
        cin >> findCont_name;
        cout << endl;
        contactBook.findByName(findCont_name);
      }
      else if (ch == 2) {
        string findCont_pno;
        cout << endl << "\tEnter Phone Number of Contact: ";
        cin >> findCont_pno;
        contactBook.findByPhoneNumber(findCont_pno);
      }
      break;
    }

    case 5: { // Contact Updation
      string findCont_fname, findCont_lname, oldPno, newPno;
      cout << endl << "\tEnter First Name of Contact: ";
      cin >> findCont_fname;
      cout << "\tEnter Last Name of Contact: ";
      cin >> findCont_lname;

      cout << "\tEnter Old Phone Number: ";
      cin >> oldPno;
      cout << "\tEnter New Phone Number: ";
      cin >> newPno;
      contactBook.update(findCont_fname, findCont_lname, oldPno, newPno);
      cout << endl << "Contact Updated Successfully!" << endl;
      // contactBook.findByName(findCont_fname);
      break;
    }

    case 6: { // Display All Contacts
      contactBook.printAllContacts();
      break;
    }

    case 7: { // Creds
      projCredits();
      break;
    }

    case 8: { // Exit Function
      cout << endl << "Thank You!!" << endl;
      exit(0);
      break;
    }

    default: {
      cout << "Enter a Valid Option";
      break;
    }
    }
  }
  return 0;
}
