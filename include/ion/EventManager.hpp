#pragma once

#include "pch.hpp"

namespace ion
{
	template<typename T>
	class EventManager
	{
	public:
		using Handler = void(*)(const T&);

		EventManager(): handlers_(), onceHandlers_() {};
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = delete;
		~EventManager() {}

		void emit(std::size_t type, const T& event)
		{
			if (handlers_.contains(type))
				for (auto& callback : handlers_.at(type))
					callback(event);

			if (onceHandlers_.contains(type))
			{
				for (auto& callback : onceHandlers_.at(type))
					callback(event);

				onceHandlers_.clear();
			}
		}

		void on(std::size_t event, Handler handler)
		{
			if (!handlers_.contains(event))
				handlers_.emplace(std::piecewise_construct, std::forward_as_tuple(event), std::forward_as_tuple());

			handlers_.at(event).emplace_back(handler);
		}

		void once(std::size_t event, Handler handler)
		{
			if (!onceHandlers_.contains(event))
				onceHandlers_.emplace(std::piecewise_construct, std::forward_as_tuple(event), std::forward_as_tuple());

			onceHandlers_.at(event).emplace_back(handler);
		}

		void remove(std::size_t event, Handler handler)
		{
			if (handlers_.contains(event))
			{
				auto& handlers = handlers_.at(event);

				if (std::find(handlers.begin(), handlers.end(), handler) != handlers.end())
					handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
			}
		}

		void removeOnce(std::size_t event, Handler handler)
		{
			if (onceHandlers_.contains(event))
			{
				auto& handlers = onceHandlers_.at(event);

				if (std::find(handlers.begin(), handlers.end(), handler) != handlers.end())
					handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
			}
		}


	private:
		std::unordered_map<std::size_t, std::vector<Handler>> handlers_;
		std::unordered_map<std::size_t, std::vector<Handler>> onceHandlers_;
	};
}
