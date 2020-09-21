#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

//Timer
clock_t startTime, endTime;

//template for generic type 
template<typename K, typename V>

//Hashnode class 
class HashNode
{
public:
	V value;
	K key;

	//Constructor of hashnode 
	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
	}
};

//template for generic type 
template<typename K, typename V>

//Our own Hashmap class 
class HashMap
{
	//hash element array 
	HashNode<K, V> **arr;
	int capacity;
	//current size 
	int size;

public:
	HashMap()
	{
		//Initial capacity of hash array 
		capacity = 100000;
		size = 0;
		arr = new HashNode<K, V>*[capacity];
		string empty;

		////Initialise all elements of array as NULL 
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;
	}
	// This implements hash function to find index 
	// for a key 
	int hashCode(K key)
	{
		int value = 0;
		for (int i = 0; i < key.length(); i++)
		{
			value = 0, 37 * value + key[i];
		}

		return value % capacity;
	}

	int findIndex(K key, bool override_duplicate_key = true) {

		int h = hashCode(key), offset = 0, index;

		while (offset < capacity) {
			index = (h + offset) % capacity;

			if (arr[index] == NULL || arr[index]->key.empty() ||
				(override_duplicate_key && arr[index]->key == key))
				return index;

			offset++;
		}
		return -1;
	}

	//Function to add key value pair 
	void insertNode(K key, V value)
	{
		HashNode<K, V> *temp = new HashNode<K, V>(key, value);

		// Apply hash function to find index for given key 
		int hashIndex = findIndex(key);

		if (hashIndex != -1) {
			if (arr[hashIndex] != NULL) {
				arr[hashIndex]->value++;
			}
			else {
				arr[hashIndex] = temp;
				size++;
			}
		}
		else {
			cout << "Table is full, The word is not added!" << endl;
			cout << "The Word : " << key << endl;
			cout << "Size : " << sizeofMap() << endl;
			return;
		}
	}

	//Return current size 
	int sizeofMap()
	{
		return size;
	}

	//Return true if size is 0 
	bool isEmpty()
	{
		return size == 0;
	}

	//Function to display the stored key value pairs 
	void display()
	{
		double diff((double)((float)clock() - (float)startTime) / 1000);
		cout << "Second:" << diff << endl;

		QuickSort(arr, 0, size - 1);

		int topCount = 0;
		for (int i = size; i > size - 11; i--)
		{

			if (arr[i] != NULL && !arr[i]->key.empty()) {
				topCount++;
				cout << topCount << " key = [" << arr[i]->key << "]"
					<< " value = [" << arr[i]->value << "]" << endl;
			}
		}
	}

	string getWords(const string& str)
	{
		size_t position = str.rfind("\",\"");
		if (position != string::npos)
		{
			// Copy substring after pos 
			return str.substr(position + 4);
		}
		return "";
	}

	void QuickSort(HashNode<K, V>* arrayy[], int low, int high) {
		if (low < high) {
			int index = pivoting(arrayy, low, high);

			QuickSort(arrayy, low, (index - 1));
			QuickSort(arrayy, (index + 1), high);
		}
	}

	void swap(HashNode<K, V> **a, HashNode<K, V> **b) {
		HashNode<K, V>* temp = *a;
		*a = *b;
		*b = temp;
	}

	int pivoting(HashNode<K, V>* arrayy[], int low, int high) {
		int pivot = arrayy[high]->value;
		int i = (low - 1);

		for (int j = low; j <= (high - 1); j++) {
			if (arrayy[j]->value <= pivot) {
				i++;
				swap(&arrayy[i], &arrayy[j]);
			}
		}

		swap(&arrayy[i + 1], &arrayy[high]);

		return (i + 1);
	}
};



int main() {

	time_t	srand(time(NULL));
	startTime = clock();

	ifstream input;
	string line;

	input.open("C:\\tweets.csv", ios::in);

	HashMap<string, int> *h = new HashMap<string, int>;

	int tweetCount = 0;
	while (input >> line) {
		getline(input, line);

		string lastSentence = h->getWords(line);
		tweetCount++;
		// word variable to store word 
		string word;

		// making a string stream 
		stringstream iss(lastSentence);

		// Read and print each word. 
		while (iss >> word) {
			h->insertNode(word, 1);
		}
	}

	h->display();

	input.close();

	endTime = clock();
	double diff((double)((float)endTime - (float)startTime) / 1000);
	cout << "Second:" << diff << endl;

	system("PAUSE");
	return 0;

}
