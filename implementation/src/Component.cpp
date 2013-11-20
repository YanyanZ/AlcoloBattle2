#include "Component.h"

#include <mlv/simulation/components/KnowledgeComponent.h>

#include <mlv/simulation/SimulationFramework.h>

#include <mlv/behavior/EntityProperties.h>

#include <algorithm>
#include <iterator>

namespace templates
{
    namespace impl_lib
    {
        Component::Component( mlv::simulation::SimulationFramework& simulation )
            : mlv::simulation::AbstractComponent(simulation)
			, entities_ ()
            , knowledge_(0)   
        {
            // NOTHING
        }

        Component::~Component()
        {
            // NOTHING
        }

        void Component::reserveEntityCount(std::size_t /*size*/)
        {
            // NOTHING
        }

        void Component::enableDebugger(bool state)
        {
            // NOTHING
        }

        bool Component::isDebuggerEnable() const
        {
            return false;
        }

        bool Component::areEntitiesRegistered(const mlv::utils::EntityIndex entities[], std::size_t entitiesSize) const
        {
			return true;
            /*for (std::size_t i(0) ; i < entitiesSize ; ++i)
            {
                if (catchers_.find(entities[i]) == catchers_.end())
                    return false;
            }
            return true;*/
        }

        bool Component::doInitializeContext(mlv::utils::AbstractLogger* logger)
        {
            knowledge_ = simulation_->getComponent<mlv::simulation::components::KnowledgeComponent>();
            if (!knowledge_)
            {
                MLV_LOG_ERROR(logger, mlv::utils::error::invalidConfiguration,"No knowledge component.");
                return false;
            }
            return true;
        }

        void Component::doTerminateContext()
        {
            knowledge_ = 0;
        }

        bool Component::doRegisterEntities(const mlv::utils::EntityIndex entities[], std::size_t entitiesSize, mlv::utils::AbstractLogger*)
        {
            entities_.insert(entities, entities + entitiesSize);
            return true;
        }

        bool Component::doUnregisterEntities(const mlv::utils::EntityIndex entities[], std::size_t entitiesSize, mlv::utils::AbstractLogger*)
        {
            entities_.erase(entities, entities + entitiesSize);
            return true;
        }

        bool Component::doInitializeEntities(const mlv::utils::EntityIndex*, std::size_t, mlv::utils::AbstractLogger*)
        {
            return true;
        }

        void Component::doTerminateEntities(const mlv::utils::EntityIndex*, std::size_t)
        {
            // NOTHING
        }

        bool Component::doUpdateEntities( const mlv::utils::Time& dt, const mlv::utils::EntityIndex entities[], std::size_t entitiesSize, mlv::utils::AbstractLogger* logger)
        {
            mlv::utils::DynamicObject& globalKnowledge = knowledge_->getFramework().getGlobalWorkingKnowledge();

			bool command1 = false;
			bool command2 = false;
			bool command3 = false;
			bool command4 = false;

			for (std::size_t i = 0; i < simulation_->countEntities() ; ++i)
			{
				const mlv::utils::DynamicObject& entityKnowledge = knowledge_->getFramework().getEntityKnowledge(simulation_->getEntities()[i]);

				if (entityKnowledge.hasProperty ("command1"))
					command1 |= entityKnowledge.getBool ("command1");
				if (entityKnowledge.hasProperty ("command2"))
					command2 |= entityKnowledge.getBool ("command2");
				if (entityKnowledge.hasProperty ("command3"))
					command3 |= entityKnowledge.getBool ("command3");
				if (entityKnowledge.hasProperty ("command4"))
					command4 |= entityKnowledge.getBool ("command4");
			}

			globalKnowledge.setBool("command1", command1);
			globalKnowledge.setBool("command2", command2);
			globalKnowledge.setBool("command3", command3);
			globalKnowledge.setBool("command4", command4);

            return true;
        }
    }
}
