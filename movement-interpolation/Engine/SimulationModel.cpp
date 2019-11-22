#include "SimulationModel.h"

template <class T>
SimulationModel<T>::SimulationModel(Configuration<T> _s, Configuration<T> _e) : start(_s), end(_e)
{
	current = start;
}
