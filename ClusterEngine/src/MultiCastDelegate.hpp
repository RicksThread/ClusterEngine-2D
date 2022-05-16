#pragma once
#include "Delegates.hpp"
#include <map>
#include <functional>
#include <unordered_set>



namespace ClusterEngine
{
    template <typename R, typename... Params>
    class MultiCastDelegate;

    template <typename R, typename... Params>
    class MultiCastDelegateBase : IDelegate<R, Params...>
    {
        using rIDelegate = IDelegate<R, Params...>;
        using GlobalFunc = R(*)(Params...);
        template<typename T>
        using MemberFunc = R(T::*)(Params...);
    public:

        MultiCastDelegateBase();

        /**
         * Adds the pointer to the member function
         * @param func The function to add from the register
         */
        template<class T>
        void Add(MemberFunc<T> func, T& caller);

        /**
         * Adds the given pointer to member function
         * @param func The function to add to the register
         */
        void Add(GlobalFunc globalFunc);

        /**
         * Removes the given pointer to member function
         * @param func The function to remove from the register
         */
        template<class T>
        void Remove(MemberFunc<T> func, T& caller);

        /**
         * Removes the given pointer to global function
         * @param func The function to remove from the register
         */
        void Remove(GlobalFunc func);

        virtual R Invoke(Params... args) = 0;

        bool operator ==(const MultiCastDelegateBase<R, Params...>& other) const;

        bool operator !=(const MultiCastDelegateBase<R, Params...>& other) const;

        void Clear();

        int GetMethodsN() const;

        virtual ~MultiCastDelegateBase() {}
    protected:
        struct Func
        {
            //interface function pointer
            std::unique_ptr<rIDelegate> iDelegate;

            //number of times the same function has been registered
            int amount;

            Func() = default;
            Func(rIDelegate*& del) : iDelegate(std::unique_ptr<rIDelegate>(del)), amount(1) {}
        };

        std::vector<Func> funcs;

        std::map<std::pair<ADDRESS, ADDRESS>, int> funcsIndex;

        std::unordered_set<int> deletedFuncsIndex;

        typedef std::function<void(rIDelegate*)> ForeachFunc;

        void ForEachFunc(ForeachFunc lambda);
        void Add(std::pair<ADDRESS, ADDRESS>& fullAdress, rIDelegate*& del);
        void Remove(std::pair<ADDRESS, ADDRESS>& fullAdress);
    };

    template <typename R, typename... Params>
    class MultiCastDelegate : public MultiCastDelegateBase<R, Params...>
    {
    public:
        using rIDelegate = IDelegate<R, Params...>;
        using rMultiCastDelegateBase = MultiCastDelegateBase<R, Params...>;

        MultiCastDelegate() : rMultiCastDelegateBase() {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual R Invoke(Params... args) override;
    };

    template <typename... Params>
    class MultiCastDelegate<void, Params...> : public MultiCastDelegateBase<void, Params...>
    {
    public:
        using rIDelegate = IDelegate<void, Params...>;
        using rMultiCastDelegateBase = MultiCastDelegateBase<void, Params...>;

        MultiCastDelegate() : rMultiCastDelegateBase() {}

        /**
         * Calls the registered functions in the delegate
         * @param args parameters of the array of functions
         */
        virtual void Invoke(Params... args) override;
    };


    //defining base multicast delegate

    //constructor
    template <typename R, typename... Params>
    MultiCastDelegateBase<R, Params...>::MultiCastDelegateBase() : funcs(0), deletedFuncsIndex(0),  rIDelegate() {}

    template <typename R, typename... Params> template <class T>
    void MultiCastDelegateBase<R, Params...>::Add(MemberFunc<T> func, T& caller)
    {
        //for more readability
        using std::pair;
        using std::unique_ptr;
        using std::vector;

        using rDelegate = Delegate<T, R, Params...>;

        //takes the address of the caller and function
        ADDRESS addressCaller = &caller;
        ADDRESS addressFunc = Converter::ForceToVoid<R(T::*)(Params...)>(func);

        //create a delegate to hold the pointer and caller and convert it to a delegate interface
        //the multicast delegate doesn't have to remember the caller so it must be reinterpreted to an interface delegate so that the method call can still happen
        rDelegate* funcHolder = new rDelegate(func, caller);
        rIDelegate* iDelegate = reinterpret_cast<rIDelegate*>(funcHolder);

        std::pair<ADDRESS, ADDRESS> fullAdress(addressCaller, addressFunc);

        Add(fullAdress, iDelegate);
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Add(GlobalFunc globalFunc)
    {
        using std::pair;
        using std::unique_ptr;
        using std::vector;
        using DelegateGlobalFunc = Delegate<void, R, Params...>;

        ADDRESS address = Converter::ForceToVoid(globalFunc);

        DelegateGlobalFunc* funcHolder = new DelegateGlobalFunc(globalFunc);
        rIDelegate* iDelegate = reinterpret_cast<rIDelegate*>(funcHolder);

        std::pair<ADDRESS, ADDRESS> fullAdress(nullptr, address);

        Add(fullAdress, iDelegate);
    }

    template<typename R, typename... Params> template<class T>
    void MultiCastDelegateBase<R, Params...>::Remove(MemberFunc<T> func, T& caller)
    {
        ADDRESS funcAdress = Converter::ForceToVoid<R(T::*)(Params...)>(func);
        ADDRESS callerAdress = &caller;

        std::pair<ADDRESS, ADDRESS> fullAdress(callerAdress, funcAdress);

        Remove(fullAdress);
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Remove(GlobalFunc func)
    {
        ADDRESS funcAddress = Converter::ForceToVoid<R(*)(Params...)>(func);
        std::pair<ADDRESS, ADDRESS> fullAdress(nullptr, funcAddress);
        Remove(fullAdress);
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Add(std::pair<ADDRESS, ADDRESS>& fullAdress, rIDelegate*& del)
    {
        if (funcsIndex.count(fullAdress))
        {
            Func& func = funcs[funcsIndex[fullAdress]];
            func.amount++;
        }
        else
        {
            if (deletedFuncsIndex.size() > 0)
            {
                int indexToFull = *deletedFuncsIndex.begin();
                funcs[indexToFull] = Func(del);
                funcsIndex.emplace(fullAdress, indexToFull);
                deletedFuncsIndex.erase(indexToFull);
            }
            else
            {
                funcs.push_back(Func(del));
                funcsIndex.emplace(fullAdress, funcs.size() - 1);
            }
        }
    }
    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Remove(std::pair<ADDRESS, ADDRESS>& fullAdress)
    {
        if (!funcsIndex.count(fullAdress)) return;

        int i = funcsIndex.at(fullAdress);

        funcs[i].amount--;
        if (funcs[i].amount <= 0)
        {
            funcsIndex.erase(fullAdress);
            deletedFuncsIndex.insert(i);
        }
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::ForEachFunc(ForeachFunc lambda)
    {
        for (int i = 0; i < funcs.size(); ++i)
        {
            if (deletedFuncsIndex.count(i)) continue;
            for (int k = 0; k < funcs[i].amount; ++k)
            {
                lambda(funcs[i].iDelegate.get());
            }
        }
    }

    template<typename R, typename... Params>
    bool MultiCastDelegateBase<R, Params...>::operator ==(const MultiCastDelegateBase<R, Params...>& other) const
    {
        if (funcs.size() != other.funcs.size()) return;

        for (const auto& func : funcsIndex)
        {
            if (!other.funcsIndex.count(func.first)) return false;
            if (!other.funcs.at(other.funcsIndex.at(func.first)).amount == funcs.at(func.second).amount) return false;
        }

        return true;
    }

    template<typename R, typename... Params>
    bool MultiCastDelegateBase<R, Params...>::operator !=(const MultiCastDelegateBase<R, Params...>& other) const
    {
        return !(*this == other);
    }


    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Clear()
    {
        funcs.clear();
        funcsIndex.clear();
        deletedFuncsIndex.clear();
    }

    template<typename R, typename... Params>
    int MultiCastDelegateBase<R, Params...>::GetMethodsN() const
    {
        return funcs.size();
    }

    template<typename R, typename... Params>
    R MultiCastDelegate<R, Params...>::Invoke(Params... args)
    {
        R result;
        rMultiCastDelegateBase::ForEachFunc
        (
            [&](rIDelegate* iDelegate)
            {
                result = iDelegate->Invoke(args...);
            }
        );
        return result;
    }

    template<typename... Params>
    void MultiCastDelegate<void, Params...>::Invoke(Params... args)
    {
        rMultiCastDelegateBase::ForEachFunc
        (
            [&](rIDelegate* iDelegate)
            {
                iDelegate->Invoke(args...);
            }
        );
    }
}