#include "neuron.hpp"

Neuron::Neuron(bool ex)
	: MembPot(0),
	SpikeNumb(0),
	CellTime(0), 
	Cap(1.0),
	Res(20.0), 
	Tau(20.0),
	Stim(0),
	TauRef(2.0), 
	Vres(0), 
	SpikeThreshold(20.0),
	Delay(1.5/0.1), //time of delay /time step of simulation
	Excitatory(ex)
{
	//initialising buffer with all 0 values (could be turned into an array or kept as a vector to simulated different delays in the future)
	Buffer=(vector<double> (Delay+1,0));
}

		
double Neuron::getMembPot() const
{
	return MembPot;
}

void Neuron::setMembPot(double value)
{
	MembPot=value;
}

double Neuron::getSpikeNumb() const 
{
	return SpikeNumb;
}


bool Neuron::UpdateNeuron(double TimeStep, double Iext)
{
	double C1 (exp(-TimeStep/Tau));
	double C2 (Res*(1-C1));
	
			//checking the refractory period has passed since last spike 
			//or that there has been no spike yet
			if((!SpikeHistory.empty() and CellTime>=getLastSpike()+TauRef) or SpikeHistory.empty()) //+poison_gen(med)) 
			{
				static random_device rd;
				static mt19937 gen(rd());
				static poisson_distribution<> noise (20*TimeStep);
				
				//either updates with an external membrane potential or without (allows to stimulate only one cell at a time)
				if (Stim) {	MembPot= (C1*MembPot+C2*Iext+Buffer[Index(CellTime)]); } ///tested only noise gen imput looks fine and random
				else { MembPot= (C1*MembPot+Buffer[Index(CellTime)]+noise(gen)*0.1); }

				if(MembPot>SpikeThreshold) // if the membrane potential crosses the threshold an action potential is Fired
				{
					Fire(TimeStep);
					return true;
				}
				
			} 
			
			//if the neuron is still in its refractory period the membrane potential stays at reset value
			else if (!SpikeHistory.empty() and CellTime*TimeStep<=getLastSpike()+TauRef)
			{ 
				Reset();
			}

			//resetting used buffer value (or non used if refractory)
			assert(Index(CellTime)<Buffer.size());
			Buffer[Index(CellTime)]=0;
			
			//incrementing cell's clock
			CellTime+=1;

			return false;
	
}

void Neuron::Reset()
{
	MembPot=Vres;
}


void Neuron::Fire(double H)
{
	//storing event
	//soring time of spike in Spikehistory directly using RealTime in ms
	storeSpikeTime(H);
	//reseting membrane potential
	Reset();
	//increments Spike Counter
	SpikeNumb+=1;
}

double Neuron::getLastSpike() const
{
	return SpikeHistory[SpikeHistory.size()-1];
}

void Neuron::Receive(double charge, unsigned int time)
{
	///cout << "received a spike at " << time*0.1 << " tab index " << Index(time) << endl;
	///cout << "will be read at " << (time+Delay)*0.1 << " tab index " << Index(time+Delay) << endl <<endl;
	
	Buffer[Index(time+Delay)]+=charge;
}


unsigned int Neuron::Index(unsigned int time)
{
	return time%Buffer.size();
}


void Neuron::setStim(bool stim)
{
	Stim=stim;
}


void Neuron::storeSpikeTime(double H)
{
	SpikeHistory.push_back(CellTime*H);	
}

bool Neuron::isEx() const
{
	return Excitatory;
}

void Neuron::RepeatUpdate(int i, double H, double Iext)
{
	for(int rep(0); rep<i; ++rep)
	{
		this->UpdateNeuron(H,Iext);
	}
}
		
