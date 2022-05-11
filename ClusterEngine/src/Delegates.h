#pragma once
#include <iostream>
#include <vector>
#include <memory>

namespace ClusterEngine
{
    class Converter
    {
    public:
        /**
         *
         * @param object object to convert
         * @return object's address
         */
        template<typename T>
        static void* ForceToVoid(T object) noexcept
        {
            return (void*&)object;
        }
    };


    template<typename R, typename... Params>
    class IDelegate
    {
    public:
        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual R Invoke(Params... args) = 0;
    };

    template <typename T, typename R, typename... Params>
    class BaseMemberDelegate : IDelegate<R, Params...>
    {
    public:
        typedef R(T::* func_type)(Params...);

        BaseMemberDelegate(func_type func, T& callee)
            : callee_(callee)
            , func_(func)
        {}

        bool operator ==(const BaseMemberDelegate& other) const;

        bool operator !=(const BaseMemberDelegate& other) const;

    protected:
        T& callee_;
        func_type func_;
    };

    template <typename T, typename R, typename... Params>
    class Delegate : public BaseMemberDelegate<T, R, Params...>
    {
    public:

        using rBaseMemberDelegate = BaseMemberDelegate<T, R, Params...>;
        using func_type = void(T::*)(Params...);

        Delegate(func_type func, T& callee) : rBaseMemberDelegate(func, callee) {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual R Invoke(Params... args) override;
    };

    template < typename T, typename... Params>
    class Delegate<T, void, Params...> : public BaseMemberDelegate<T, void, Params...>
    {
    public:
        using rBaseMemberDelegate = BaseMemberDelegate<T, void, Params...>;
        using func_type = void(T::*)(Params...);

        Delegate(func_type func, T& callee) : rBaseMemberDelegate(func, callee) {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual void Invoke(Params... args) override;
    };

    template <typename R, typename... Params>
    class BaseGlobalDelegate : public IDelegate<R, Params...>
    {
    public:
        using rIDelegate = IDelegate< R, Params...>;
        using func_type = R(*)(Params...);

        BaseGlobalDelegate(func_type func) : func_(func), rIDelegate() {}


        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual R Invoke(Params... args) = 0;

    protected:
        func_type func_;
    };

    template <typename R, typename... Params>
    class Delegate<void, R, Params...> : public BaseGlobalDelegate<R, Params...>
    {
    public:

        using rBaseGlobalDelegate = BaseGlobalDelegate< R, Params...>;
        using func_type = R(*)(Params...);

        Delegate(func_type func) : rBaseGlobalDelegate(func) {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual R Invoke(Params... args);
    };

    template <typename... Params>
    class Delegate<void, void, Params...> : public BaseGlobalDelegate<void, Params...>
    {
    public:
        using rBaseGlobalDelegate = BaseGlobalDelegate<void, Params...>;
        using func_type = void(*)(Params...);

        Delegate(func_type func) : rBaseGlobalDelegate(func) {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual void Invoke(Params... args);
    };

    //definitions

    template <typename T, typename R, typename... Params>
    bool BaseMemberDelegate<T, R, Params...>::operator !=(const BaseMemberDelegate& other) const
    {
        return !((&callee_ == &other.callee_) && (func_ == other.func_));
    }

    template <typename T, typename R, typename... Params>
    bool BaseMemberDelegate<T, R, Params...>::operator ==(const BaseMemberDelegate& other) const
    {
        return (&callee_ == &other.callee_) && (&func_ == &other.func_);
    }

    template <typename T, typename R, typename... Params>
    R Delegate<T, R, Params...>::Invoke(Params... args)
    {
        return (rBaseMemberDelegate::callee_.*rBaseMemberDelegate::func_)(args...);
    }

    template <typename T, typename... Params>
    void Delegate<T, void, Params...>::Invoke(Params... args)
    {
        (rBaseMemberDelegate::callee_.*rBaseMemberDelegate::func_)(args...);
    }

    template <typename R, typename... Params>
    R Delegate<void, R, Params...>::Invoke(Params... args)
    {
        return (*rBaseGlobalDelegate::func_)(args...);
    }

    template <typename... Params>
    void Delegate<void, void, Params...>::Invoke(Params... args)
    {
        (*rBaseGlobalDelegate::func_)(args...);
    }
}