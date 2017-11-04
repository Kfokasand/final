#include "simulation.hpp"
#include <array>
#include <list>

Simulation::Simulation(double sim_time)
			:H(0.1),
			SimTime(sim_time),
			StepTime(0)
			{ 
					int n;
					do {
					cout << "Enter number of desired neurons in network : " ;
					cin >> n;
					} while(n<=0);
					
					int ne;
					int ni;
					
					int ce;
					int ci;
					int cext;
					
					double je;
					double ji;
					
					cout << "Number of excitatory neurons : ";
					cin>> ne;
					
					cout << "Number of inhibitory neurons : ";
					cin>> ni;
					
					cout << "Excitatory connections : ";
					cin>> ce;
					
					cout << "Inhibitory conenctions : ";
					cin>> ci;
					
					cout << "External conenctions: ";
					cin>> cext;
					
					cout << "weight of excitation: ";
					cin>> je;
					
					cout << "wight of inhibition: ";
					cin>> ji;
					
					network = new Network(n,ne,ni,ce,ci,cext,je,ji);
					
			}
			
Simulation::Simulation()
			:H(0.1),
			SimTime(1000),
			StepTime(0)
{
	network = new Network();
	
}
			
Simulation::~Simulation()
{
	delete network;
	network = nullptr;
}

void Simulation::SetSimTime()
{
	do {
		cout << endl << "Set simulation time in ms : ";
		cin>> SimTime;	
	} while(SimTime<0);

}



void Simulation::SetCurrent(double a, double b, double I)
{
	abound=a;
	bbound=b;
	Iext=I;
}

void Simulation::Run()
{
	
	//updating cell
	do{
		network->Network::UpdateNetwork(Iext,StepTime);
		//incremeting simulation Time in steps
		StepTime+=1;
	}
	while(RealTime(StepTime)< SimTime); //checking if simulation has reached it's end in ms	
}


double Simulation::RealTime(double time) const
{
	return time*H;
}

void Simulation::StoreState()
{
	vector<double> state (network->Network::StoreState());
	for(unsigned int i(0); i< state.size(); ++i)
	{
		//:TODO joli tableau +temps +history as attribute + gerer Network as attribute (intialisation dyn ?)
	}
}

