/*--- Author
	  Hasheem Ahmed ---*/

// Iostream for cout cin
#include <iostream>

//Iomanip for the setw and setfill
#include <iomanip>

// Conio.h for the _getch() function to stay on screen until key is pressed
#include <conio.h>
using namespace std;

// Shortest Job First Serve - Preemptive Algorithm Class

class SJFS
{
public:

	// Variables
	int NumberOfProcess;
	int* Temp;
	int* Proc;
	int* AT;
	int* BT;
	int* CT;
	int* WT;
	int* TAT;


	//Default Constructor
	SJFS()
	{
		NumberOfProcess = 0;
		AT = BT = CT = WT = TAT = Proc = Temp =  NULL;
	}

	//Parameterized Constructor
	SJFS(int Process)
	{
		this->NumberOfProcess = Process;
		Proc = new int[Process];
		AT = new int[Process];
		BT = new int[Process];
		CT = new int[Process];
		WT = new int[Process];
		TAT = new int[Process];
		Temp = new int[Process];
	}

	// Input the arrival time and burst time values
	void ATinput()
	{
		cout << "Enter the Arrival and Burst time : ";
		for (int i = 0; i < NumberOfProcess; i++)
		{
			cout << "P" << i + 1 << " - \n";
			this->Proc[i] = i + 1;
			cout << "Arrival Time : ";
			cin >> this->AT[i];
			cout << "Burst Time : ";
			cin >> this->BT[i];

			// Using the temp to not disturb the original array
			this->Temp[i] = this->BT[i];
		}
	}

	// Checking Shortest Job According to Arrival Time

	int ArrivalTimeChecker(int CTValue)
	{
		int value = 0;
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			if (CTValue >= this->AT[i])
			{
				++value;
			}
		}
		return value;
	}

	// Returning Index of Shortest Burst Time 

	int ShortestBurstTime(int index)
	{
		int shortestindex = 0;
		int elements = this->ArrivalTimeChecker(index);

		for (int i = 0; i < elements; i++)
		{
			if (this->Temp[i] != 0)
			{
				shortestindex = i;
				break;
			}
		}
		for (int i = 0; i < elements; i++)
		{	
			
			if (this->Temp[i] != 0 && this->Temp[shortestindex] > this->Temp[i])
			{
				shortestindex = i;
			}
		}

		return shortestindex;
	}

	// Checking that the All process have run

	bool isEmpty()
	{
		bool valid = true;
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			if (this->Temp[i] != 0)
				valid = false;
		}
		return valid;
	}

	// Running the Premmptive process and calculating the CT
	void CalculatingPreempttive(int i, int &CompltionTime)
	{
		int shortestindex = this->ShortestBurstTime(CompltionTime);
		if (CompltionTime + this->Temp[shortestindex] > this->AT[i + 1])
		{
			this->Temp[shortestindex] -= this->AT[i + 1] - CompltionTime;
			CompltionTime += (this->AT[i + 1] - CompltionTime);
		}
		else
		{
			CompltionTime += this->Temp[shortestindex];
			this->Temp[shortestindex] = 0;
			this->CT[shortestindex] = CompltionTime;
		}

	}

	// calculating the completion time
	void CalculatingCT()
	{
		int CompltionTime = 0;

		// Running the Process using Preemptive until
		// all Processes Arrival Time comes in Completion time 
		for (int i = 0; i < this->NumberOfProcess - 1; i++)
		{
			CalculatingPreempttive(i, CompltionTime);
			
			while (CompltionTime < this->AT[i + 1])
			{
				CalculatingPreempttive(i, CompltionTime);
			}

		}


		// Running  the Remaining Burst Time
		while (!isEmpty())
		{
			int shortestindex = this->ShortestBurstTime(CompltionTime);
			CompltionTime += this->Temp[shortestindex];
			this->CT[shortestindex] = CompltionTime;
			this->Temp[shortestindex] = 0;
		}

	}


	// Calculating the waiting time
	void CalculatingWT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->WT[i] = this->CT[i] - (this->AT[i] + this->BT[i]);
		}
	}


	// calculating turn around time
	void CalculatingTAT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->TAT[i] = this->WT[i] + this->BT[i];
		}
	}

	// Swap function for Sorting Values using pass by reference
	void swap(int& x, int& y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	//Sorting the Arrival time values by BUBBLE SORT
	void SortingATandBT()
	{
		bool sort = true;
		while (sort)
		{
			sort = false;
			for (int i = 0; i < this->NumberOfProcess - 1; i++)
			{
				if (this->AT[i] > this->AT[i + 1])
				{
					swap(this->AT[i], this->AT[i + 1]);
					swap(this->BT[i], this->BT[i + 1]);
					swap(this->Temp[i], this->Temp[i + 1]);
					swap(this->Proc[i], this->Proc[i + 1]);
					sort = true;
				}
			}
		}
	}

	// calculating the average waiting time
	float AvgWaitingTime()
	{
		float avgWaitingTime = 0;

		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			avgWaitingTime += this->WT[i];
		}

		return avgWaitingTime / this->NumberOfProcess;
	}

};

// Main Function
int main()
{
	// User Input for Number of Process
	int Process;
	cout << "Enter Number of Process : ";
	cin >> Process;

	// making Object of the FCFS class and initializing the Number of process
	SJFS obj(Process);


	// Taking Input of the Arrival time and Burst time
	obj.ATinput();

	// Sorting the Arrival Time For the First Come First Serve - FCFS
	obj.SortingATandBT();

	// Calculating the Completion time, Waiting Time , Turn Around Time
	obj.CalculatingCT();
	obj.CalculatingWT();
	obj.CalculatingTAT();

	// Use to clear console
	system("cls");

	// MAking the Table for the output
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ') << "|          Shortest Job First Serve - SJFS - Preemptive            |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setfill(' ') << "Process    |    AT    |    BT    |    CT    |   TAT    |    WT    |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ');


	// Outputting the Values of AT, BT, Ct, WT, TAT
	for (int i = 0; i < obj.NumberOfProcess; i++)
	{
		cout << "|";
		cout << setw(10) << "P" << obj.Proc[i] << "|";
		cout << setw(10) << obj.AT[i] << "|";
		cout << setw(10) << obj.BT[i] << "|";
		cout << setw(10) << obj.CT[i] << "|";
		cout << setw(10) << obj.TAT[i] << "|";
		cout << setw(10) << obj.WT[i] << "|\n";
	}


	// Outputting Average Waiting Time
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setw(56) << setfill(' ') << " Average Waiting Time |" << setw(10) << obj.AvgWaitingTime() << "|\n";
	cout << setw(70) << setfill('-') << " \n";

	// To Stay on Screen
	_getch();
	return 0;
}