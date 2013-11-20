#include "ImplementationLibrary.h"

namespace alcolo
{
	ImplementationLibrary::ImplementationLibrary()
		: AbstractImplementationLibrary("alcolo")
		, setEntityBoolean_()
		, component_ (NULL)
		, increment_ ()
	{
		// NOTHING
	}

	ImplementationLibrary::~ImplementationLibrary()
	{
		if (isLoaded())
			forceUnload();
	}

	bool ImplementationLibrary::doLoad(mlv::utils::AbstractLogger* logger)
	{
		bool success = true;
		
		//Actions
		success = success && registerType<SetEntityBooleanParams>(logger);
		success = success && registerAction(setEntityBoolean_, logger);		
		
		success = success && registerType<IncrementParams>(logger);
		success = success && registerAction(increment_, logger);	
		
		//Components
		if (getSimulationFramework() == 0)
		{
			MLV_LOG_WARNING(logger, "Unable to load the component from implementation library.");
			success = true;
		}
		else
		{
			//create components
			component_ = MLV_NEW templates::impl_lib::Component(*getSimulationFramework());
			success = addComponent(*component_, logger);
		}

		return success;
	}

	bool ImplementationLibrary::doUnload(mlv::utils::AbstractLogger* logger)
	{
		bool success = true;
		
		//Actions
		success = success && unregisterAction(setEntityBoolean_, logger);
		if (success)
			unregisterType<SetEntityBooleanParams>();
			
		success = success && unregisterAction(increment_, logger);
		if (success)
			unregisterType<IncrementParams>();
			
		//Components
		success = success && removeComponent(*component_, logger);
		if (success)
		{
			MLV_DELETE component_;
			component_ = 0;
		}

		return success;
	}
}
