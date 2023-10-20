#pragma once

namespace ion
{
	template<typename T>
	class Maybe
	{
	private:

	public:
		Maybe() :
			isSet_(false),
			data_()
		{}
		
		Maybe(T&& data):
			isSet_(true),
			data_()
		{
			*ptr() = std::move(data);
		}

		template<typename ...Args>
		Maybe(Args&&... args)
		{
			new (ptr()) T(std::forward<Args>(args)...);
		}

		~Maybe() 
		{
			if(hasValue())
				delete ptr();
		}

		inline bool hasValue() const
		{
			return isSet_;
		}

		inline bool isEmpty() const
		{
			return !isSet_;
		}

		inline T& get()
		{
			if (!hasValue())
				throw std::runtime_error("Maybe<T> is empty!");
			return *ptr();
		}

		inline const T& get() const
		{
			if (!hasValue())
				throw std::runtime_error("Maybe<T> is empty!");
			return *ptr();
		}

		inline void reset()
		{
			if(hasValue())
				delete ptr();
			isSet_ = false;
		}

		inline T& getOr(T& other) const
		{
			if (!hasValue())
				return other;
			return *ptr();
		}

		template<typename Callback>
		inline T& getOrElse(Callback callback) const
		{
			if (!hasValue())
				return callback();
			return *ptr();
		}

		template<typename... Args>
		inline T swap(Args&&... args)
		{
			if (!hasValue())
				throw new std::runtime_error("Maybe<T> is empty!");
			T old = *ptr();
			new (ptr()) T(std::forward<Args>(args)...);
			return old;
		}

		inline T swap(T&& other)
		{
			if (!hasValue())
				throw new std::runtime_error("Maybe<T> is empty!");
			T old = *ptr();
			new (ptr()) T(std::move(other));
			return old;
		}

		template<typename... Args>
		inline T& set(Args&&... args)
		{
			if (hasValue())
				throw new std::runtime_error("Maybe<T> already has a value!");
			new (ptr()) T(std::forward<Args>(args)...);
			return get();
		}

		inline T& set(T&& other)
		{
			if (hasValue())
				throw new std::runtime_error("Maybe<T> already has a value!");
			new (ptr()) T(std::move(other));
			return get();
		}

	private:
		const T* ptr() const
		{
			return static_cast<const T*>(static_cast<const void*>(data_.data()));
		}

		bool isSet_;
		std::array<char, sizeof(T) / sizeof(char)> data_;
	};

	template<typename T>
	class Maybe<T&>
	{
	public:
		Maybe() : ptr_(nullptr) {}
		Maybe(T& ref) : ptr_(std::addressof(ref)) {}
		~Maybe() {}

		inline bool hasValue() const
		{
			return ptr_ != nullptr;
		}

		inline bool isEmpty() const
		{
			return ptr_ == nullptr;
		}

		inline T& get()
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return *ptr_;
		}

		inline const T& get() const
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return *ptr_;
		}

		inline void reset()
		{
			ptr_ = nullptr;
		}

		inline T& getOr(T& other) const
		{
			if (isEmpty())
				return other;
			return *ptr_;
		}

		template<typename Callback>
		inline T& getOrElse(Callback callback) const
		{
			if (isEmpty())
				return callback();
			return ptr_;
		}

		inline Maybe<T>& swap(Maybe<T>& other)
		{
			if (isEmpty() || !other.hasValue())
				throw new std::runtime_error("Maybe<T> is empty!");

			T* old = ptr_;
			ptr_ = std::addressof(other.get());
			other.ptr_ = old;
			return other;
		}

		inline T& swap(T& other)
		{
			if (isEmpty())
				throw new std::runtime_error("Maybe<T> is empty!");

			T* old = ptr_;
			ptr_ = std::addressof(other);
			return *old;
		}

	private:
		T* ptr_;
	};

	template<typename T>
	class Maybe<T*>
	{
	public:
		Maybe() : ptr_(nullptr) {}
		Maybe(T* ref) : ptr_(ref) {}
		~Maybe() {}

		inline bool hasValue() const
		{
			return ptr_ != nullptr;
		}

		inline bool isEmpty() const
		{
			return ptr_ == nullptr;
		}

		inline T* get()
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return ptr_;
		}

		template<typename A>
		inline A* getAs()
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return static_cast<A*>(ptr_);
		}

		inline const T* get() const
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return ptr_;
		}

		
		template<typename A>
		inline const A* getAs() const
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");
			return static_cast<A*>(ptr_);
		}

		inline void reset()
		{
			ptr_ = nullptr;
		}

		inline T* getOr(T* other) const
		{
			if (isEmpty())
				return other;
			return ptr_;
		}

		template<typename Callback>
		inline T* getOrElse(Callback callback) const
		{
			if (isEmpty())
				return callback();
			return ptr_;
		}

		inline T* swap(T* other)
		{
			if (isEmpty())
				throw std::runtime_error("Maybe<T> is empty!");

			T* old = ptr_;
			ptr_ = static_cast<T*>(other);
			return old;
		}

		inline T* set(T* other)
		{
			if(!isEmpty())
				throw std::runtime_error("Maybe<T> already has a value!");

			ptr_ = static_cast<T*>(other);
			return ptr_;
		}

	private:
		T* ptr_;
	};
}
