#include <iostream>
using namespace std;
//comment actualizado
class ProcessNode
{
public:
	ProcessNode();//Default constructor
	ProcessNode(ProcessNode* p, int id, int burst, int arrival, ProcessNode* n);//Special constructor
	int getPID();
	int getBT();
	int getAT();
	ProcessNode* getNext();
	ProcessNode* getPrev();
	void setInfo(int id, int burst, int arrival);
	void setBT(int burst);
	void setNext(ProcessNode*);
	void setPrev(ProcessNode*);

private:
	ProcessNode* prev;
	int PID;
	int BT;
	int AT;
	ProcessNode* next;

};

//Deffault contructor
ProcessNode::ProcessNode() 
{	next = prev = 0;	}

//Special Constructor
ProcessNode::ProcessNode(ProcessNode* p, int id, int burst, int arrival, ProcessNode* n)
{	
	prev = p;
	PID = id;
	BT = burst;
	AT = arrival;
	next = n;
}

int ProcessNode::getPID()
{	return PID;		}
int ProcessNode::getBT()
{	return BT;		}
int ProcessNode::getAT()
{	return AT;		}

ProcessNode* ProcessNode::getNext()
{	return next;	}
ProcessNode* ProcessNode::getPrev()
{	return prev;	}

void ProcessNode::setInfo(int id, int burst, int arrival)
{
	PID = id;
	BT = burst;
	AT = arrival;
}

void ProcessNode::setBT(int burst)
{	BT = burst;		}

void ProcessNode::setPrev(ProcessNode* p)
{
	prev = p;
}

void ProcessNode::setNext(ProcessNode* n)
{
	next = n;
}


//--------------------------------------------------------------------------------------------------------


class ProcessList //DubbleLinkedList that contains each process including: Process Id, Burst Time y su Arraival Time
{
public:
	//constructor
	ProcessList();
	//Constructor con parametros
	//ProcessList(int Pamount);
	//destructor
	~ProcessList();

	void addToHead(int, int, int);

	void addToTail(int, int, int);

	void deleteFromHead();

	void deleteFromTail();

	bool isEmpty();

	void printList(int amount, int arrival);

private:
	ProcessNode* head;
	ProcessNode* tail;
	ProcessNode* ptrTemp; //pointer temporal para usar en distintas funciones
};

ProcessList::ProcessList()
{
	tail = head = 0;
}

ProcessList::~ProcessList()
{
	ptrTemp = head;

	while (ptrTemp != 0)
	{
		ptrTemp = head->getNext();
		delete head;
		head = ptrTemp;
	}

	ptrTemp = 0;
}
void ProcessList::addToTail(int id, int burst, int arrival)
{
	ptrTemp = new ProcessNode(tail, id, burst, arrival, 0);

	if (tail != 0)
	{
		tail->setNext(ptrTemp);
		tail = ptrTemp;
	}
	else
	{
		head = tail = ptrTemp;
	}

	ptrTemp = 0;
}

void ProcessList::addToHead(int id, int burst, int arrival)
{
	ptrTemp = new ProcessNode(0, id, burst, arrival, head);

	if (head != 0)
	{
		head->setPrev(ptrTemp);
		head = ptrTemp;
	}
	else
	{
		head = tail = ptrTemp;
	}

	ptrTemp = 0;
}

void ProcessList::deleteFromHead()
{
	ptrTemp = head->getNext();
	delete head;
	head = ptrTemp;
	ptrTemp = 0;
	delete ptrTemp;
}

void ProcessList::printList(int amount, int arrival)
{
	ptrTemp = head;
	cout << "Here are all your processes:\n\n";

	if (arrival == 1)
	{
		for (int i = 0; i < amount; i++)
		{
			cout << i + 1 << ". PID: " << ptrTemp->getPID() << ", Burst Time : " << ptrTemp->getBT() << ", Arrival Time: " << ptrTemp->getAT() << "\n";
			ptrTemp = ptrTemp->getNext();
		}
	}
	else
	{
		for (int i = 0; i < amount; i++)
		{
			cout << i + 1 << ". PID: " << ptrTemp->getPID() << ", Burst Time : " << ptrTemp->getBT() << "\n";
			ptrTemp = ptrTemp->getNext();
		}
	}
}


//--------------------------------------------------------------------------------------------------------------

int main()
{
	int pAmount, PID, BT, AT,aTime, Queue, Quant;
	bool checkInfo = true;
	ProcessList Processes;
	
	cout << "Welcome to the process simulator\n" << "Type the ammount of processes:";
	cin >> pAmount;

	cout << "Do you want to use Arrival Time or Not? \nType [1] to Use Arrival Time or type [0] to not:";
	cin >> aTime;
	cout << endl;

	cout << "Now tell us about your processes:\n\n";

	for (int i = 1; i <= pAmount; i++)
	{
		checkInfo = true;
		while (checkInfo == true)
		{
			PID = i;
			cout << "Process " << i << " PID:" << i << "\nEnter Burst Time:";
			cin >> BT;

			if (aTime == 1)
			{
				cout << "Enter Arrival Time:";
				cin >> AT;
			}
			else
				AT = 1;

			Processes.addToTail(PID, BT, AT);

			if (BT <= 0 || AT <= 0)//check error
				cout << "You cannot asign 0 or negative numbers to eaither the Process Burst Time or Arrival Time.\nPlease reenter the information for Process PID: " << PID << ".\n";
			else
				checkInfo = false;

			PID = BT = AT = 0;
			cout << endl;
		}
	}

	Processes.printList(pAmount, aTime);

}
