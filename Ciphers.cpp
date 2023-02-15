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
		//Memory management
		~DLinkedList<T>() {

			while (size > 0) {
				remove(0);
			}
			delete dummyHead;
			delete dummyTail;
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
			++size;
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

			++size;
		}
		void remove(int i) {
			DNode<T>* node = getNode(i);
			if (size == 1) {
				dummyHead->next = dummyTail;
				dummyTail->prev = dummyHead;
			}
			else {
				node->prev->next = node->next;
				node->next->prev = node->prev;

				head = dummyHead->next;
				tail = dummyTail->prev;
			}
			delete node;
			--size;
		}
		void removeLast() {
			DNode<T>* node = tail;
			node->prev->next = node->next;
			node->next->prev = node->prev;

			head = dummyHead->next;
			tail = dummyTail->prev;
			--size;
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
				DNode<T>* nextNextNode = nextNode->next;
				prevNode->next = nextNode;
				nextNode->prev = prevNode;
				nextNode->next = node;

				node->prev = nextNode;
				node->next = nextNextNode;

				nextNextNode->prev = node;

			}
			head = dummyHead->next;
			tail = dummyTail->prev;
		}

		//Redo to save time, since that's bad.
		//Should move the whole block at once
		void tripleCut(DNode<T>* A, DNode<T>* B) {
			DNode<T>* node;

			DNode<T>* firstAbove;
			DNode<T>* firstBelow;

			int countA = 0;
			int countB = 0;

			firstAbove = head;
			firstBelow = tail;


			node = head;
			while (!(node == A || node == B)) {
				++countA;
				node = node->next;
			}

			node = tail;
			while (!(node == A || node == B)) {
				++countB;
				node = node->prev;
			}

			DNode<T>* nextNode;
			for (int i = 0; i < countA; ++i) {
				nextNode = firstAbove->next;
				moveToBack(firstAbove);
				firstAbove = nextNode;
			}


			for (int i = 0; i < countB; ++i) {
				nextNode = firstBelow->prev;
				moveToFront(firstBelow);
				firstBelow = nextNode;
			}
		}
		void countCut(int i) {
			DNode<T>* lastCard = tail;
			for (int j = 0; j < i; ++j) {
				moveToBack(head);
			}

			moveToBack(lastCard);
		}
		DNode<T>* find(T elem) {
			DNode<T>* currentNode = head;
			while (currentNode->value != elem) {
				currentNode = currentNode->next;
			}

			return currentNode;
		}
		void display() {
			DNode<T>* currentNode = dummyHead->next;
			while (currentNode != dummyTail) {
				std::cout << currentNode->value << "->";
				currentNode = currentNode->next;
			}
			std::cout << std::endl;
		}
		DNode<T>* getNode(int i) {
			DNode<T>* node;
			if (i < size / 2) {
				node = dummyHead->next;
				for (int k = 0; k < i; ++k) {
					node = node->next;
				}
			}
			else {
				node = dummyTail->prev;
				for (int k = size - 1; k > i; --k) {
					node = node->prev;
				}
			}
			return node;
		}

	private:
		DNode<T>* dummyHead;

		void moveToBack(DNode<T>* node) {
			//Heal the old wound
			node->prev->next = node->next;
			node->next->prev = node->prev;

			node->prev = tail;
			node->next = dummyTail;

			tail->next = node;
			dummyTail->prev = node;

			head = dummyHead->next;
			tail = dummyTail->prev;
		}
		void moveToFront(DNode<T>* node) {
			node->prev->next = node->next;
			node->next->prev = node->prev;

			node->prev = dummyHead;
			node->next = head;

			head->prev = node;
			dummyHead->next = node;

			head = dummyHead->next;
			tail = dummyTail->prev;
		}
	};

	void generateDeckFromPassphrase(std::string& key, DLinkedList<int>& cards, DNode<int>*& A, DNode<int>*& B) {
		//Generate deck from key
		for (char& c : key) {
			//Move A Joker down one
			cards.moveNext(A);
			//Move B Joker down twice


			//---------COULD BE FASTER WITH A SPECIFIC FUNCTION------------
			cards.moveNext(B);
			cards.moveNext(B);
			//Triple cut cards
			cards.tripleCut(A, B);

			//Calculate values to cut by
			int lastCardValue = cards.tail->value;
			int adjustedLastCard = lastCardValue < 53 ? lastCardValue : 53;
			int keyVal = ((int)c) - 64;
			//Count cut twice
			cards.countCut(adjustedLastCard);
			cards.countCut(keyVal);
		}
	}

	//Faster modulo - only used when needed
	int modulo(int in, int limit) {
		return in < limit ? in : in % limit;
	}
};

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
		upperAlphaString(key);
		upperAlphaString(inText);
		std::string outString;
		outString.reserve(inText.size());

		//Create deck
		DLinkedList<int> cards;

		for (int i = 1; i < 55; ++i) {
			cards.addToBack(i);
		}

		DNode<int>* A = cards.find(53);
		DNode<int>* B = cards.find(54);
		generateDeckFromPassphrase(key, cards, A, B);
		
		
		//Generate keystream
		std::string keyStream;
		keyStream.reserve(inText.size());
		for (char& inChar : inText) {
			int outValue;
			do {
				//Move A Joker down one
				cards.moveNext(A);
				//Move B Joker down twice
				cards.moveNext(B);
				cards.moveNext(B);
				//Triple cut cards
				cards.tripleCut(A, B);

				int adjustedLastCard = cards.tail->value < 53 ? cards.tail->value : 53;
				//Count cut 
				cards.countCut(adjustedLastCard);

				
				int topValue = cards.head->value < 53 ? cards.head->value : 53;
				outValue = cards.getNode(topValue)->value;

			} while (outValue == 53);

			outValue = modulo(outValue - 1, 26) + 1;

			int inCharVal = ((int)inChar) - 64;
			int outChar;
			if (encode) {
				outChar = modulo((inCharVal + outValue) - 1, 26) + 1;
			}
			else {
				outChar = modulo((inCharVal - outValue) + 25, 26) + 1;
			}


			outChar += 64;
			outString += (char)outChar;

		}
		return outString;
	}
}