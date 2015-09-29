// Simbiotic and it's source files are (c) 2015, Abject Entertainment
#pragma once

/* Master.h
 * Definition of the distribution architecture Master object.  An instance of 
 * this object represents a single, self-contained simulation.  This object
 * is responsible for managing Slave instances, and communication between
 * them.  Master objects do not interact directly with simulation objects.
 */

#include <string>

namespace simbiotic
{
	class MasterConfiguration;
	class Master
	{
	public:

		/* Constructor
		 *  - simulation_id: A string uniquely identifying this simulation.
		 *  - config: A MasterConfiguration object containing the simulation
		 * details as pertains to the Master object.
		 */
		Master(const ::std::string &simulation_id, MasterConfiguration *config);


	private:
		::std::string _simulation_id;
	};
}
