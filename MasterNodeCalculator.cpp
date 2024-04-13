#include "Libraries.h"
#include "Functions.cpp"

using namespace std;

int main()
{
	int ActiveMn{ 0 }, RunForHowLong{ 0 }, MnRunByUser{ 0 };
	double PaymentTime{ 0 }, TotalRewards{ 0 };
	int const MnReward{ 2250 };
	char IsCompounding{ ' ' };

	b:
	cout << "Enter the number of masternodes that you plan on running: ";
	cin >> MnRunByUser;

	if (MnRunByUser < 1)
	{
		cout << "\n\nNumber of masternodes that are being run by you cannot be less than zero, try again\n\n";
		goto b;
	}

	cout << "\nEnter how long you plan to run your masternode for in days: ";
	cin >> RunForHowLong;

	ActiveMn = GetMasterNodeCount();

	if (ActiveMn == 0)
	{
		cout << "Failed to masternode count automatically\n";
		cout << "Asking for mannual input...\n";
		cout << "\nEnter the number of masternodes currently on the network: ";
		cin >> ActiveMn;
	}

	PaymentTime = static_cast<double>(ActiveMn / 60) / 24;		//payment time per masternode in days

	a:
	cout << "\nAre you compounding the rewards? (Y/N): ";
	cin >> IsCompounding;

	IsCompounding = toupper(IsCompounding);

	if (IsCompounding == 'Y')
	{
		int AdditionalNeoxa{ 0 }, AfterHowManyDays{ 0 };

		cout << "\nEnter the additional amount of Neoxa that you would be adding to the shared node if any (Enter 0 if you don't plan to add any additional Neoxa): ";
		cin >> AdditionalNeoxa;

		if (AdditionalNeoxa > 0)
		{
			cout << "Enter after how many days you plan to add this Neoxa: ";
			cin >> AfterHowManyDays;
		}

		for (int i{ 0 }, Add{0}; i < RunForHowLong; i++, Add++)
		{
			if (Add == AfterHowManyDays)
			{
				TotalRewards += AdditionalNeoxa;
				Add = 0;
			}
			TotalRewards += (MnReward / PaymentTime) * 2;
			TotalRewards += (MnReward / PaymentTime) * (TotalRewards / 1000000);
		}
	}
	else if (IsCompounding == 'N')
	{
		TotalRewards = ((RunForHowLong / PaymentTime) * MnReward) * MnRunByUser;
	}
	else
	{
		cout << "Invalid choice, Try again\n";
		goto a;
	}

	cout << "Total rewards: " << fixed << setprecision(2) << TotalRewards << endl;

	char Again{ ' ' };

	cout << "Would you like to run the program again? (Y/N): ";
	cin >> Again;

	Again = toupper(Again);

	if (Again == 'Y')
	{
		system("CLS");
		goto b;
	}
	else
	{
		cout << "\nGoodbye :)\n\n";
		system("pause");
	}

	return 0;
}