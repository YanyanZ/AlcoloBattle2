#ifndef IMPLEMENTATION_LIBRARY_H
#define IMPLEMENTATION_LIBRARY_H
#include "setEntityBooleanAction.h"
#include "Component.h"

#include <mlv/simulation/configuration/AbstractImplementationLibrary.h>

namespace alcolo
{
	class ImplementationLibrary : public mlv::simulation::configuration::AbstractImplementationLibrary
	{
	public:
		ImplementationLibrary();
		virtual ~ImplementationLibrary();
	private:

		virtual bool doLoad(mlv::utils::AbstractLogger* logger);
		virtual bool doUnload(mlv::utils::AbstractLogger* logger);

		//Custom Action
		SetEntityBoolean setEntityBoolean_;

		templates::impl_lib::Component* component_;
	}; 
}

#endif
