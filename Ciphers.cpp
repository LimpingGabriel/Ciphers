#include <iostream>

namespace {
	void upperString(std::string& inString) {
		for (auto& c : inString) {
			c = toupper(c);
		}
	}

	bool upperAlphaPredicate(char& c) {
		return (int)c < 65 || (int)c > 90;
	}

	void upperAlphaString(std::string& inString) {
		upperString(inString);
		inString.erase(std::remove_if(inString.begin(), inString.end(), upperAlphaPredicate), inString.end());
	}
	template <typename T>
	struct DNode {
		T value;
		DNode* next;
		DNode* prev;
		DNode(T elem) {
			value = elem;
		}
		DNode() {
			value = 0;
		}
	};
	template <typename T>
	struct DLinkedList {
	public:
		DNode<T>* dummyTail;
		DLinkedList<T>() {
			dummyHead = new DNode<T>();
			dummyTail = new DNode<T>();
			dummyHead->next = dummyTail;
			dummyTail->prev = dummyHead;
			size = 0;
		}

		DNode<T>* head;
		DNode<T>* tail;
		int size;
		void addToFront(T elem) {
			DNode<T>* newNode = new DNode<T>(elem);
			if (size == 0) {
				newNode->next = dummyTail;
				newNode->prev = dummyHead;
				dummyHead->next = newNode;
				dummyTail->prev = newNode;
				head = newNode;
				tail = newNode;
			}
			else {
				newNode->prev = dummyHead;
				newNode->next = head;

				head->prev = newNode;
				
				dummyHead->next = newNode;

				head = newNode;
			}
			size++;

			
		}
		void addToBack(T elem) {
			DNode<T>* newNode = new DNode<T>(elem);
			if (size == 0) {
				newNode->next = dummyTail;
				newNode->prev = dummyHead;
				dummyHead->next = newNode;
				dummyTail->prev = newNode;
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				newNode->prev = tail;

				newNode->next = dummyTail;
				dummyTail->prev = newNode;
				
				tail = newNode;
			}

			size++;
		}
		void remove(int i) {
			DNode<T>* node = getNode(i);
			node->prev->next = node->next;
			node->next->prev = node->prev;
			
			head = dummyHead->next;
			tail = dummyTail->prev;
			size--;
		}

		void swap(DNode<T>* firstNode, DNode<T>* secondNode) {

			//Temporary nodes
			DNode<T>* rightNode = secondNode->next;
			DNode<T>* leftNode = firstNode->prev;

			//Set the outer nodes correctly
			rightNode->prev = firstNode;
			leftNode->next = secondNode;

			//First node
			firstNode->prev = secondNode;
			firstNode->next = rightNode;

			//Second node
			secondNode->prev = leftNode;
			secondNode->next = firstNode;

			head = dummyHead->next;
			tail = dummyTail->prev;

		}
		void movePrev(DNode<T>* node) {
			DNode<T>* prevNode = node->prev;
			DNode<T>* nextNode = node->next;

			if (prevNode == dummyHead) {
				//Remove from front
				head = node->next;
				head->prev = dummyHead;
				dummyHead->next = head;

				//Move to back
				prevNode = tail->prev;
				nextNode = tail;

				nextNode->prev = node;
				prevNode->next = node;

				node->next = nextNode;
				node->prev = prevNode;
			}
			else {
				//Main node
				node->next = prevNode;
				node->prev = prevNode->prev;

				//Previous node
				prevNode->prev->next = node;
				prevNode->next = nextNode;
				prevNode->prev = node;

				nextNode->prev = prevNode;
			}
			head = dummyHead->next;
			tail = dummyTail->prev;
			
		}
		void moveNext(DNode<T>* node) {
			DNode<T>* prevNode = node->prev;
			DNode<T>* nextNode = node->next;
			if (nextNode == dummyTail) {
				tail = node->prev;
				tail->next = dummyTail;
				dummyTail->prev = tail;

				prevNode = head;
				nextNode = head->next;

				prevNode->next = node;
				nextNode->prev = node;

				node->next = nextNode;
				node->prev = prevNode;
				
			}
			else {
				node->prev = nextNode;
				node->next = nextNode->next;

				nextNode->next->prev = node;
				nextNode->prev = prevNode;
				nextNode->next = node;

				prevNode->next = nextNode;
			}
			head = dummyHead->next;
			tail = dummyTail->prev;
		}

		void tripleCut(DNode<T>* A, DNode<T>* B) {
			
			DLinkedList<T> aboveFirst;
			DLinkedList<T> belowSecond;
			DNode<T>* node;
			
			node = dummyHead->next;
			while (!(node == A || node == B)) {
				aboveFirst.addToBack(node->value);
				node = node->next;
				remove(0);
			}

			node = dummyTail->prev;
			while (!(node == A || node == B)) {
				belowSecond.addToFront(node->value);
				node = node->prev;
				remove(size - 1);
			}


			node = aboveFirst.head;
			for (int i = 0; i < aboveFirst.size; i++) {
				addToBack(node->value);
				node = node->next;
				
			}

			node = belowSecond.tail;
			for (int i = belowSecond.size; i > 0; i--) {
				addToFront(node->value);
				node = node->prev;
			}

			//Memory management to do

		}
		void display() {
			DNode<T>* currentNode = dummyHead->next;
			while (currentNode != dummyTail) {
				std::cout << currentNode->value << "->";
				currentNode = currentNode->next;
			}
			std::cout << std::endl;
		}

	private:
		DNode<T>* dummyHead;
		DNode<T>* getNode(int i) {
			DNode<T>* node;
			if (i < size / 2) {
				node = dummyHead->next;
				for (int k = 0; k < i; k++) {
					node = node->next;
				}
			}
			else {
				node = dummyTail->prev;
				for (int k = 0; k > i; k--) {
					node = node->prev;
				}
			}
			return node;
		}
	};

}

namespace ciphers::classic {
	std::string caesar(std::string& inText, int shift, bool encode) {
		const char* lower = "abcdefghijklmnopqrstuvwxyz";
		const char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		if (!encode) {
			shift = 0 - shift;
		}
		char newChar;
		int normalizedChar;

		bool charUpper;
		bool charLower;

		std::string outString = std::string();
		for (auto &currentChar : inText) {
			charUpper = isupper(currentChar);
			charLower = islower(currentChar);
			normalizedChar = charLower ? (int)currentChar - 97 : (int)currentChar - 65;
			const char* usealpha = charLower ? lower : upper;
			bool shouldShift = charLower || charUpper;
			if (shouldShift) {
				if (normalizedChar + shift < 0) {
					newChar = usealpha[normalizedChar + shift + 26];
				}
				else if (normalizedChar + shift > 25) {
					newChar = usealpha[normalizedChar + shift - 26];
				}
				else {
					newChar = usealpha[normalizedChar + shift];
				}
			}
			else {
				newChar = currentChar;
			}
			outString += newChar;
		}
		return outString;
	}
}

namespace ciphers::modern {
	std::string solitaire(std::string& inText, std::string& key, bool encode) {
		DLinkedList<int> cards;

		for (int i = 1; i < 55; i++) {
			cards.addToBack(i);
		}
		
		cards.display();
		
		DNode<int>* B = cards.tail;
		DNode<int>* A = cards.tail->prev;

		cards.moveNext(A);
		cards.moveNext(B);
		cards.moveNext(B);
		
		cards.display();

		cards.tripleCut(A,B);

		cards.display();
		return "";
	}
}
