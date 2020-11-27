#include "Fordev.h"

void menu1() {
	cout << "-------Menu-------" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Show persons" << endl;
	cout << "4. Save all" << endl;
	cout << "5. Quit" << endl;
	cout << endl;
}

void menu2() {
	cout << "-------Menu-------" << endl;
	cout << "1. Logout" << endl;
	cout << "2. Follow" << endl;
	cout << "3. Show following" << endl;
	cout << "4. Delete following" << endl;
    cout << "5. Show biography" << endl; 
	cout << "6. Add Post" << endl;
	cout << "7. Interact with post" << endl;
    cout << "8. Trends" << endl;
    cout << "9. Filters" << endl;
	cout << endl;
}

string getDate() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return to_string(1900 + now->tm_year) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);
}

int main() {
	Fordev *fordev = new Fordev();
  
	string email, name,date;
	bool login;
	int id, option, option2, option3;
	string aux1, aux2, aux3, aux4;
	do {
		login = false;
		menu1();
		cout << "Option: ";
		cin >> option;
		cout << endl;

		if (option == 1) {
			cout << "Email: ";
			cin >> email;

			if (fordev->login(email)) {
				login = true;
			}
		} else if (option == 2) {
			cin.ignore();
			cout << "Email: ";
            cin >> email;
			cout << "Name: ";
            cin >> name;
            if (fordev->registerPerson(email, name, getDate())) {
                login = true;
            } 
		} else if (option == 3) {
			fordev->showPersons();
		} else if (option == 4) {
			fordev->saveInfo();
		}

		if (login) {
			do {
				system("cls");

				fordev->infoUser();

				fordev->showPosts();

				menu2();
				cout << "Option: ";
				cin >> option2;
				cout << endl;

				if (option2 == 2) {
					fordev->showUsers();
					cout << endl << "Email: ";
					cin >> aux1;
					fordev->addFollowUser(aux1);
				} else if (option2 == 3) {
					fordev->getUser()->showFollowed();
				} else if (option2 == 4) {
					fordev->getUser()->showFollowed();
					cout << endl << "Email: ";
					cin >> aux1;
					fordev->deleteFollowUser(aux1);
				} else if (option2 == 5) {
                    cout << "Email: " << endl;
                    cin.ignore();
                    getline(cin, email);
                    fordev->showBiography(email);
                } else if (option2 == 6) {
					cout << "Title: ";
					cin.ignore();
					getline(cin, aux1);
					cout << "What do you think " << fordev->getUser()->getName() << "?: ";
					getline(cin, aux2);
					fordev->addPost(aux1, aux2, getDate()) ;
				} else if (option2 == 7) {
					cout << "Post name: ";
					cin.ignore();
					getline(cin, aux1);

					if (fordev->searchPost(aux1)) {
						cout << endl << "Actions: " << endl;
						cout << "1) Comment" << endl;
						cout << "2) Reaction " << endl;
                        cout << "3) Shared post " << endl << endl;
						cout << "Option: ";
						cin >> option3;
						cout << endl;

						if (option3 == 1) {
							cout << "Comment: ";
							cin.ignore();
							getline(cin, aux2);
							fordev->addComment(aux1, aux2, getDate());
						} else if (option3 == 2) {
							fordev->reactPost(aux1);
						} else if (option3 == 3) {
                            fordev->sharePost(aux1);
                        }
					} 
                } else if (option2 == 8) {
                    cout << "Type of filters: " << endl;
                    cout << "1: Filter by recent activity" << endl;
                    cout << "2: Filter by likes" << endl;
                    cout << "3: Filter by relevance" << endl;
                    cout << "Option: "; cin >> option3;
                    cout << endl;
                    if (option3 >= 1 && option3 <= 3) {
                        fordev->setFilterPost(option3);
                    }
                } else if (option2 == 9) {
                    cout << "Type of filters: " << endl;
                    cout << "1. None" << endl;
                    cout << "2. Equal" << endl;
                    cout << "3. Start with" << endl;
                    cout << "4. Finish with" << endl;
                    cout << "5. Contained in" << endl;
                    cout << "6. Not contained in" << endl;
                    cout << "Option: "; cin >> option3;
                    cout << endl;
                    if (option3 >= 1 && option3 <= 6) {
                        fordev->setTypeFilter(option3);
                        if (option3 > 1) {
                            cout << "Word key: ";
                            cin.ignore();
                            getline(cin, aux1);
                            fordev->setWordKey(aux1);
                        }
                    }
                }
				system("pause");
			} while (option2 != 1);
		}

		fordev->logout();

		system("pause");
		system("cls");
	} while (option != 5);

	fordev->~Fordev();

	return 0;
} 