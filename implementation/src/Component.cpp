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

			// Bar interaction handling :
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

			// Battle handling :
			for (std::size_t i = 0; i < simulation_->countEntities() ; ++i)
			{
				const mlv::utils::DynamicObject& entityKnowledge = knowledge_->getFramework().getEntityKnowledge(simulation_->getEntities()[i]);

				if (entityKnowledge.hasProperty ("battleIndex") && entityKnowledge.getInt ("battleIndex") != -1 && entityKnowledge.getBool ("fistBattle"))
				{
					knowledge_->getFramework().getEntityWorkingKnowledge(simulation_->getEntities()[i]).setBool ("fistBattle", false);

					if (entityKnowledge.getInt ("battleIndex") == 0)
						globalKnowledge.setInt ("battleCount[0]", globalKnowledge.getInt ("battleCount[0]") + 1);
					if (entityKnowledge.getInt ("battleIndex") == 1)
						globalKnowledge.setInt ("battleCount[1]", globalKnowledge.getInt ("battleCount[1]") + 1);
					if (entityKnowledge.getInt ("battleIndex") == 2)
						globalKnowledge.setInt ("battleCount[2]", globalKnowledge.getInt ("battleCount[2]") + 1);
					if (entityKnowledge.getInt ("battleIndex") == 3)
						globalKnowledge.setInt ("battleCount[3]", globalKnowledge.getInt ("battleCount[3]") + 1);
				}

				if (entityKnowledge.hasProperty ("videurPlace") && entityKnowledge.getInt ("videurPlace") != -1)
				{
					uint64_t videurPlace = entityKnowledge.getInt ("videurPlace");

					for (std::size_t j = 0; j < simulation_->countEntities() ; ++j)
					{
						const mlv::utils::DynamicObject& entityKnowledge2 = knowledge_->getFramework().getEntityKnowledge(simulation_->getEntities()[j]);

						if (entityKnowledge2.hasProperty ("battleIndex") && entityKnowledge.getInt ("battleIndex") == videurPlace)
						{
							knowledge_->getFramework().getEntityWorkingKnowledge(simulation_->getEntities()[j]).setBool ("isAlive", false);

							if (videurPlace == 0)
								globalKnowledge.setInt ("battleCount[0]", 0);
							if (videurPlace == 1)
								globalKnowledge.setInt ("battleCount[1]", 0);
							if (videurPlace == 2)
								globalKnowledge.setInt ("battleCount[2]", 0);
							if (videurPlace == 3)
								globalKnowledge.setInt ("battleCount[3]", 0);
						}
					}
				}
			}

            return true;
        }
    }
}
