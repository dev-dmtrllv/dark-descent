#pragma once

#include "ion/Config.hpp"

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

	template<typename T>
	class SubSystem : public SubSystemBase
	{
	public:
		SubSystem() : SubSystemBase() {}
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

			T* system = new T();
			subSystems_.emplace(std::piecewise_construct, std::forward_as_tuple(hash), std::forward_as_tuple(system));
			return *system;
		}

		template<typename T>
		T& getSystem() const
		{
			if (status_ == Status::Constructed)
				throw std::runtime_error("SubSystems are not initialized yet!");

			if (status_ == Status::Terminated)
				throw std::runtime_error("All subSystems are terminated!");

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

			for (const auto& [key, value] : subSystems_)
			{
				Logger::get().debug("Initializing SubSystem ", value->name(), "...");
				value->initialize(config);
				Logger::get().debug("SubSystem ", value->name(), " initialized!");
			}

			status_ = Status::Initialized;
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
				Logger::get().debug("Terminating SubSystem ", system->name(), "...");
				system->terminate();
				delete system;
				Logger::get().debug("SubSystem ", system->name(), " terminated!");
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
