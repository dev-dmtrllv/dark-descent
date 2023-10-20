#pragma once

#include "ion/Config.hpp"
#include "ion/Logger.hpp"
#include "ion/EventManager.hpp"

#define SUB_SYSTEM_CTORS(__NAME__, __EVENT__) __NAME__(Engine& engine) : SubSystem<__NAME__, __EVENT__>(engine) {} \
		__NAME__(const __NAME__&) = delete; \
		__NAME__(__NAME__&&) = delete; \
		virtual ~__NAME__() {}
namespace ion
{
	class Engine;

	class SubSystemBase
	{
	public:
		virtual ~SubSystemBase() {}

		virtual const char* name() const = 0;
		virtual const std::size_t hash() const = 0;

		virtual void initialize(const Config& config) {}
		virtual void terminate() {}
	};

	template<typename T, typename Event>
	class SubSystem : public SubSystemBase
	{
	public:
		SubSystem(Engine& engine) : SubSystemBase(), engine_(engine), eventManager_() {}
		virtual ~SubSystem() {}

		virtual const char* name() const override { return typeid(T).name(); }
		virtual const std::size_t hash() const override { return typeid(T).hash_code(); }

		void initialize(const Config& config)
		{
			static_cast<T*>(this)->onInitialize(config);
		}

		void terminate()
		{
			static_cast<T*>(this)->onTerminate();
		}

		virtual void onInitialize(const Config& config) = 0;
		virtual void onTerminate() = 0;

		inline EventManager<Event>& events() { return eventManager_; }

	protected:
		Engine& engine_;
		EventManager<Event> eventManager_;
	};

	class SubSystemRegistry
	{
	public:
		enum class Status {
			Constructed,
			Initialized,
			Terminated
		};

		SubSystemRegistry(Engine& engine) :
			engine_(engine),
			status_(Status::Constructed),
			subSystems_()
		{}

		~SubSystemRegistry() {}

		template<typename T>
		T& registerSystem()
		{
			const std::size_t hash = typeid(T).hash_code();
			if (subSystems_.contains(hash))
			{
				std::string error = std::format("Subsystem {} is already registered!", typeid(T).name());
				throw std::runtime_error(error.c_str());
			}
			
			Logger::get().debug("Registered SubSystem ", typeid(T).name());

			T* system = new T(engine_);
			subSystems_.emplace(std::piecewise_construct, std::forward_as_tuple(hash), std::forward_as_tuple(system));
			return *system;
		}

		template<typename T>
		T& getSystem() const
		{
			if (status_ != Status::Initialized)
				throw std::runtime_error("SubSystems are not initialized yet!");

			const std::size_t hash = typeid(T).hash_code();
			
			if (!subSystems_.contains(hash))
			{
				std::string error = std::format("Could not get subsystem {}!", typeid(T).name());
				throw std::runtime_error(error.c_str());
			}

			return *static_cast<T*>(subSystems_.at(hash));
		}

		void initialize(Config& config)
		{
			if (status_ == Status::Initialized)
				throw std::runtime_error("SubSystems are already initialized!");

			if (status_ == Status::Terminated)
				throw std::runtime_error("All subSystems are terminated!");

			status_ = Status::Initialized;

			for (const auto& [key, value] : subSystems_)
			{
				Logger::get().debug("Initializing SubSystem ", value->name(), "...");
				value->initialize(config);
				initializationOrder_.emplace_back(value);
				Logger::get().debug("SubSystem ", value->name(), " initialized!");
			}
		}

		void terminate()
		{
			if (status_ == Status::Terminated)
				throw std::runtime_error("All subSystems are already terminated!");

			if (status_ == Status::Constructed)
				throw std::runtime_error("SubSystems are not initialized yet!");

			std::reverse(initializationOrder_.begin(), initializationOrder_.end());

			for (const auto& system : initializationOrder_)
			{	
				const char* name = system->name();
				Logger::get().debug("Terminating SubSystem ", name, "...");
				system->terminate();
				delete system;
				Logger::get().debug("SubSystem ", name, " terminated!");
			}

			status_ = Status::Terminated;
		}

	private:
		Engine& engine_;
		Status status_;
		std::unordered_map<std::size_t, SubSystemBase*> subSystems_;
		std::vector<SubSystemBase*> initializationOrder_;
	};
}
