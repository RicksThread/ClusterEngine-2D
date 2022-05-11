#pragma once
#include "Delegates.h"
#include <unordered_map>
#include <functional>

namespace ClusterEngine
{
    template <typename R, typename... Params>
    class MultiCastDelegate;

    template <typename R, typename... Params>
    class MultiCastDelegateBase : IDelegate<R, Params...>
    {
        using rIDelegate = IDelegate<R, Params...>;
        using GlobalFunc = R(*)(Params...);
    public:

        MultiCastDelegateBase();

        /**
         * Adds the pointer to the member function
         * @param func The function to add from the register
         */
        template<class T>
        void Add(R(T::* func)(Params...), T& caller);

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
        void Remove(R(T::* func)(Params...), T& caller);

        /**
         * Removes the given pointer to global function
         * @param func The function to remove from the register
         */
        void Remove(GlobalFunc func);

        virtual R Invoke(Params... args) = 0;

        void Clear();

        int GetSize() { return memberFuncs.size();  }

        virtual ~MultiCastDelegateBase() { initialized = false; }
    protected:

        /**
         * holds an array of functions of the same type
         */
        class MemberFunc
        {
        public:
            //address of function and array of functions of the same adress (example: same function registered multiple times)
            std::unordered_map<void*, std::vector<std::unique_ptr<rIDelegate>> > functions;
        };

        //global funcs (key 1: address of function, key 2: function)
        std::unordered_map< void*, std::vector<std::unique_ptr<rIDelegate>> > globalFuncs;
        //member funcs (key 1: address of callee; key 2: member function)
        std::unordered_map< void*, MemberFunc > memberFuncs;
        bool initialized = true;

        typedef std::function<void(rIDelegate*)> ForeachFunc;

        void ForEachFunc(ForeachFunc lambda);
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
    MultiCastDelegateBase<R, Params...>::MultiCastDelegateBase() : rIDelegate() {}

    template <typename R, typename... Params> template <class T>
    void MultiCastDelegateBase<R, Params...>::Add(R(T::* func)(Params...), T& caller)
    {
        if (!initialized) return;
        //for more readability
        using std::pair;
        using std::unique_ptr;
        using std::vector;

        using rDelegate = Delegate<T, R, Params...>;

        //takes the address of the caller and function
        void* addressCaller = &caller;
        void* addressFunc = Converter::ForceToVoid<R(T::*)(Params...)>(func);

        //create a delegate to hold the pointer and caller and convert it to a delegate interface
        //the multicast delegate doesn't have to remember the caller so it must be reinterpreted to an interface delegate so that the method call can still happen
        rDelegate* funcHolder = new rDelegate(func, caller);
        rIDelegate* iDelegate = reinterpret_cast<rIDelegate*>(funcHolder);


        if (memberFuncs.count(addressCaller))
        {
            //if the function is already present then add only the interface delegate
            if (memberFuncs[addressCaller].functions.count(addressFunc))
            {
                memberFuncs[addressCaller].functions[addressFunc].push_back(unique_ptr<rIDelegate>(iDelegate));
            }
            else
            {
                //insert the new function address
                memberFuncs[addressCaller].functions.insert(pair< void*, vector<unique_ptr<rIDelegate>>>(addressFunc, 0));
                memberFuncs[addressCaller].functions[addressFunc].push_back(unique_ptr<rIDelegate>(iDelegate));
            }
        }
        else
        {
            //insert the new caller address and new function address

            //insert caller
            memberFuncs.insert(pair<void*, MemberFunc>(addressCaller, MemberFunc()));

            //insert function address
            memberFuncs[addressCaller].functions.insert(pair< void*, vector<unique_ptr<rIDelegate>>>(addressFunc, 0));
            //insert function content (delegate interface)
            memberFuncs[addressCaller].functions[addressFunc].push_back(unique_ptr<rIDelegate>(iDelegate));
        }
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Add(GlobalFunc globalFunc)
    {
        if (!initialized) return;
        using std::pair;
        using std::unique_ptr;
        using std::vector;
        using DelegateGlobalFunc = Delegate<void, R, Params...>;

        void* adress = Converter::ForceToVoid(globalFunc);

        DelegateGlobalFunc* funcHolder = new DelegateGlobalFunc(globalFunc);
        rIDelegate* iDelegate = reinterpret_cast<rIDelegate*>(funcHolder);

        if (globalFuncs.count(adress))
        {
            globalFuncs[adress].push_back(move(unique_ptr <rIDelegate>(iDelegate)));
        }
        else
        {
            globalFuncs.insert(pair< void*, vector<unique_ptr<rIDelegate>> >(adress, 0));
            globalFuncs[adress].push_back(std::move(unique_ptr <rIDelegate>(iDelegate)));
        }
    }

    template<typename R, typename... Params> template<class T>
    void MultiCastDelegateBase<R, Params...>::Remove(R(T::* func)(Params...), T& caller)
    {
        if (!initialized) return;
        void* funcAdress = Converter::ForceToVoid<R(T::*)(Params...)>(func);
        void* callerAdress = &caller;

        std::cout << "nums of memberfuncs: " << memberFuncs.size() << "\n";
        if (!memberFuncs.count(callerAdress)) return;
        if (!memberFuncs[callerAdress].functions.count(funcAdress)) return;

        memberFuncs[callerAdress].functions[funcAdress].erase(memberFuncs[callerAdress].functions[funcAdress].begin());
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Remove(GlobalFunc func)
    {
        if (!initialized) return;
        void* funcAddress = Converter::ForceToVoid<R(*)(Params...)>(func);

        if (!globalFuncs.count(funcAddress)) return;

        globalFuncs[funcAddress].erase(globalFuncs[funcAddress].begin());
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::ForEachFunc(ForeachFunc lambda)
    {
        if (!initialized) return;
        for (const auto& i : globalFuncs)
        {
            for (const auto& j : i.second)
            {
                lambda(j.get());
            }
        }

        for (const auto& i : memberFuncs)
        {
            for (const auto& j : i.second.functions)
            {
                for (const auto& k : j.second)
                {
                    lambda(k.get());
                }
            }
        }
    }

    template<typename R, typename... Params>
    void MultiCastDelegateBase<R, Params...>::Clear()
    {
        if (!initialized) return;
        memberFuncs.clear();
        globalFuncs.clear();
    }

    template<typename R, typename... Params>
    R MultiCastDelegate<R, Params...>::Invoke(Params... args)
    {
        if (!MultiCastDelegateBase<R,Params>::initialized) return;
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
        if (!MultiCastDelegateBase<void, Params...>::initialized) return;
        rMultiCastDelegateBase::ForEachFunc
        (
            [&](rIDelegate* iDelegate)
            {
                iDelegate->Invoke(args...);
            }
        );
    }
}