#include "IncrementAction.h"

#include <mlv/behavior/EntityKnowledgeFacade.h>
#include <mlv/behavior/EntityProperties.h>

namespace alcolo
{
		IncrementParams::IncrementParams()
			: key ("")
			, value (0)
        {
            // Initialization of the parameters
        }

        bool IncrementParams::setMetadata(mlv::utils::TypeManager& manager, mlv::utils::AbstractLogger* logger)
        {
            return manager.registerProperty("key", &IncrementParams::key, logger)
				&& manager.registerProperty("value", &IncrementParams::value, logger);
        }

        Increment::Increment()
            : mlv::behavior::AbstractTypedAction<IncrementParams>("Increment") //Name used in the BT editor to create an instance of this action
        {
            // Initialization of the action
        }

        Increment::~Increment()
        {
            // Destruction of the action
        }
	
        mlv::behavior::action::Status Increment::doStart(mlv::behavior::EntityKnowledgeFacade& entity, mlv::behavior::ActionRequestHandle requestId, const IncrementParams& params)
        {			
			// The action begin
			mlv::utils::DynamicObject& entityKnowledge = entity.getKnowledge();
			mlv::utils::DynamicObject::PropertyHandle p = entityKnowledge.getProperty(params.key.c_str(),params.key.length());

			if (p == 0)
			{
				p = entityKnowledge.addProperty(params.key.c_str(),params.key.length());
				if (p==0)
				{
					//MLV_LOG_ERROR(logger, mlv::utils::error::invalidConfiguration, "Unable to add a property " << params.key << " to the entity knowledge.");
					return mlv::behavior::action::canceled;
				}
			}
			
			if (entityKnowledge.isTypeCompatible(p,mlv::utils::type::integer))
			{
				uint64_t res = entityKnowledge.getInt(p) + params.value;
				entityKnowledge.setInt(p, res);
				return mlv::behavior::action::running;
			}
			else
			{
				//MLV_LOG_ERROR(logger, mlv::utils::error::invalidConfiguration, "Unable to put the set value to" << params.key << "'.");
				return mlv::behavior::action::canceled;
			}
			
			return mlv::behavior::action::running;
        }

        mlv::behavior::action::Status Increment::doUpdate(mlv::behavior::EntityKnowledgeFacade& entity, mlv::behavior::ActionRequestHandle requestId, const IncrementParams& params, const mlv::utils::Time& dt)
        {
            // The action continue
			
            return mlv::behavior::action::succeeded;
        }

        mlv::behavior::action::Status Increment::doCancel(mlv::behavior::EntityKnowledgeFacade& entity, mlv::behavior::ActionRequestHandle requestId, const IncrementParams& params, const mlv::utils::Time& dt)
        {
            //The action is canceled
			
            return mlv::behavior::action::canceled;
        }
}
