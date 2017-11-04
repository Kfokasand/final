#include "simulation.hpp"

using namespace std;

int main()
{	
	char rep1;
	cout << "Run custom simulation ? [Y/N]:";
	cin >> rep1;
	
	if(rep1=='Y')
	{
		cout<< "You are intialising a simulation" << endl <<"Please enter settings" <<endl;
		
	
		double time;
		do {
		cout << endl << "Set simulation time in ms : ";
		cin>> time;	
		} while(time<0);
		
		Simulation sim={time};
		sim.Run();
		
	} else
	{
		cout << "Your parameters are : " << endl;
		cout << " N =12500" << endl << " Ne =1000 (Je =0.1)" << endl 
			<< " Ni= 2500 (Ji= -0.5)" <<endl
			<< " Ce =1000" << endl << " Ci= 250" << endl 
			<< " Cext=1000" << endl << " Simulation length : 1000 ms" << endl;

		Simulation sim1={};
		sim1.Run();
	}
	
	return 0;	
}



