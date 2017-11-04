#include "network.hpp"
#include <cstdlib>

Network::Network()
	:N(12500),
	Ne(10000),
	Ni(2500),
	Ce(Ne*0.1),
	Ci(Ni*0.1),
	Cext(Ce),
	Je(0.1),
	Ji(-0.5),
	H(0.1)
	{
		
		Connections = vector<vector<int>> (N); /**creating N vectors of ints (1 for each neuron in simulation) */
		CreateNeurons();
		LinkNetwork();
		setDataAcquisition();

	}
Network::Network(int n,int ne, int ni, int ce, int ci, int cext, double je, double ji)
	:N(n),
	Ne(ne),
	Ni(ni),
	Ce(ce),
	Ci(ci),
	Cext(cext),
	Je(je),
	Ji(ji),
	H(0.1)
	

	{
		
		Connections = vector<vector<int>> (N); /**creating N vectors of ints (1 for each neuron in simulation) */
		CreateNeurons();
		LinkNetwork();
		setDataAcquisition();

	}

Network::~Network()
{
	writeSpikes();
	for(auto& cell: Cells)
	{
		delete cell;
		cell=nullptr;
	}
}

void Network::CreateNeurons()
{
	for(int i(1); i<=N; ++i)
		{	
			if (i<=Ne ) {Cells.push_back(new Neuron(1));} //makes Ne excitatory neurons
			else {Cells.push_back(new Neuron(0));} //the rest N-Ne are inhibitory
		};
	cout << N << " neurons were created " << endl;
}

void Network::LinkNetwork()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distExci(0, Ne-1);
	uniform_int_distribution<> distInhi(Ne, Ne+Ni-1);
	int j;
	int u;
	
	//for every daughter (receiver) neuron in the simulation
	
	for(unsigned int i(0); i<Cells.size(); ++i)
	{


	///linking excitatory parents
		for(int c(0); c<Ce; ++c)
		{
			j=distExci(gen);
			assert(j<Connections.size());
			Connections[j].push_back(i); //means ith neuron is affected by jth neuron

		}
		
	///linking inhibitory parents	
		for(int c(0); c<Ci; ++c)
		{
			u=distInhi(gen);
			u=rand()%Ni +Ne; //random int in [Ne, Ne+Ni-1]
			assert(u<Connections.size());
			Connections[u].push_back(i);
		}
	}
	cout << "Network was built" << endl;
}

void Network::UpdateNetwork(double Iext_, unsigned int time)
{
	int counterSpikes (0);
	
	//updating all neurons in simulation
	for (unsigned int i(0); i<Cells.size(); ++i)
	{
		if(Cells[i]->Neuron::UpdateNeuron(H, Iext_))
		{
			///cout << "a neuron is spiking" << endl;
			counterSpikes+=1;

			if (time>= Start/H and time<=Stop/H) {StoreSpike(time,i);} 
			
			//sending imput to all daughter cells
			///cout << "connection of neuron " << i << " : " << Connections[i].size() << endl;
			for(auto daughter_index : Connections[i])
			{
				//cout << "sending to daughters" << endl;
				assert(daughter_index<Cells.size());
				if(Cells[i]->isEx())
				{
					Cells[daughter_index]->Receive(Je, time);
					
				} else {
					
					Cells[daughter_index]->Receive(Ji, time);
				}
			}
		}
	}
	cout << "number of spikes at " << time << " : " << counterSpikes << endl;
}

vector<double> Network::StoreState() const
{
	vector<double> state;
	for(auto cell:Cells)
	{
		state.push_back(cell->getMembPot());
	}
	
	return state;	
}

void Network::StoreSpike(unsigned int time, unsigned int i)
{
	///cout << "storing a spike" << endl;
	SpikeTimes.push_back(time);
	indexes.push_back(i);
}

void Network::writeSpikes() const
{
	///cout << "Final writing";
	ofstream ble;
	ble.open("ble.txt");
	
	for (unsigned int j(0); j<SpikeTimes.size();++j)
	{	
			ble << SpikeTimes[j] << '\t' << indexes[j]<< '\n' ;
	}
}

void Network::setDataAcquisition()
{
	cout << "Set recording boundaries (in ms)" << endl;
	cout << "Start : " ;
	cin>> Start;
	cout << "Stop : ";
	cin >> Stop;
	
}
