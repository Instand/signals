#ifndef SIGNALS_H
#define SIGNALS_H

#include <functional>
#include <vector>

namespace es
{
#define signals
#define slots
#define emit

    class Connector;

    /*
        Base preudo signal
    */
    template<typename T>
    class Signal;

    /*
        Signal needed specialization
    */
    template <typename Return, typename... InArgs>
    class Signal<Return(InArgs...)>
    {
    public:
        using Argument = std::function<Return(InArgs...)>;
        using Signature = Return(InArgs...);
        using Slots = std::vector<Argument>;

        template<typename... Args>
        inline constexpr void operator() (Args&&... args)
        {
            for (auto& elem : mSlots)
                elem(std::forward<Args>(args)...);
        }

        // creation
        Signal() = default;
        Signal(const Signal&) = delete;
        Signal& operator=(const Signal&) = delete;

        Signal(Signal&& signal):
            mSlots(std::move(signal.mSlots))
        {
            signal.mSlots.clear();
        }

        Signal& operator=(Signal&& signal)
        {
            mSlots = std::move(signal.mSlots);
            signal.mSlots.clear();

            return *this;
        }

        ~Signal()
        {
            (*this) = nullptr;
        }

    private:

        // adds slot to signal
        template<typename T>
        constexpr decltype(auto) add(T&& s)
        {
            Argument arg = s;

            if (!arg)
                return *this;

            mSlots.push_back(arg);
            return *this;
        }

        // clears all signal slots
        constexpr decltype(auto) operator=(void* ptr)
        {
            if (ptr == nullptr)
                mSlots.clear();

            return *this;
        }

        // returns size of slots
        constexpr std::size_t size() const
        {
            return mSlots.size();
        }

        // all connected slots
        Slots mSlots;

        friend class Connector;
        friend class Signal;
    };

    /*
        Signal for function prototype
    */
    template<typename T>
    class Signal<std::function<T>>
    {
    public:
        using Argument = std::function<T>;
        using Signature = T;
        using Slots = std::vector<Argument>;

        template<typename... Args>
        inline constexpr void operator() (Args&&... args)
        {
            mSignal(std::forward<Args>(args)...);
        }

        // creation
        Signal() = default;
        Signal(const Signal&) = delete;
        Signal& operator=(const Signal&) = delete;

        Signal(Signal&& signal):
            mSignal(std::move(signal.mSignal))
        {
        }

        Signal& operator=(Signal&& signal)
        {
            mSignal = std::move(signal.mSignal);
            return *this;
        }

        ~Signal()
        {
            (*this) = nullptr;
        }

    private:

        // adds slot to signal
        template<typename T>
        inline constexpr decltype(auto) add(T&& s)
        {
            mSignal.add(std::forward<T>(s));
            return *this;
        }

        // clears all slots
        inline constexpr decltype(auto) operator=(void* ptr)
        {
            mSignal = ptr;
            return *this;
        }

        // returns size of signal slots
        inline constexpr std::size_t size() const noexcept
        {
            return mSignal.size();
        }

        Signal<Signature> mSignal;
        friend class Connector;
    };

    // helper namespace
    namespace Args
    {
        template <typename T>
        struct GetArguments : GetArguments<decltype(&T::operator())> {};

        template <typename T, typename... Args>
        struct GetArguments<T(*)(Args...)> : std::integral_constant<unsigned, sizeof...(Args)> {};

        template <typename T, typename C, typename... Args>
        struct GetArguments<T(C::*)(Args...)> : std::integral_constant<unsigned, sizeof...(Args)> {};

        template <typename T, typename C, typename... Args>
        struct GetArguments<T(C::*)(Args...) const> : std::integral_constant<unsigned, sizeof...(Args)> {};

        // bindings
        template<int>
        class CheckArgs
        {
        public:

            template<typename T, typename Slot>
            void connect(T& slotObj, Slot&& slot);
        };

        template<>
        class CheckArgs<0>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj);
            }
        };

        template<>
        class CheckArgs<1>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1);
            }
        };

        template<>
        class CheckArgs<2>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2);
            }
        };

        template<>
        class CheckArgs<3>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            }
        };

        template<>
        class CheckArgs<4>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4);
            }
        };

        template<>
        class CheckArgs<5>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5);
            }
        };

        template<>
        class CheckArgs<6>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6);
            }
        };

        template<>
        class CheckArgs<7>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7);
            }
        };

        template<>
        class CheckArgs<8>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7,
                    std::placeholders::_8);
            }
        };

        template<>
        class CheckArgs<9>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7,
                    std::placeholders::_8, std::placeholders::_9);
            }
        };

        template<>
        class CheckArgs<10>
        {
        public:

            template<typename T, typename Slot>
            auto connect(T& slotObj, Slot&& slot)
            {
                return std::bind(std::forward<Slot>(slot), slotObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7,
                    std::placeholders::_8, std::placeholders::_9, std::placeholders::_10);
            }
        };
    }

    /*
        Signal - slot connection entity
    */
    class Connector
    {
    public:

        // connects signal with callback
        template<typename Signal, typename T, typename Slot>
        inline static void connect(Signal& signal, const T& slotObj, Slot&& slot)
        {
            constexpr int size = Args::GetArguments<Slot>();
            signal.add(Args::CheckArgs<size>().connect(slotObj, std::forward<Slot>(slot)));
        }

        // connects signal with callback
        template<typename Signal, typename T, typename Slot>
        inline static void connect(const Signal& signal, const T& slotObj, Slot&& slot)
        {
            constexpr int size = Args::GetArguments<Slot>();
            const_cast<Signal&>(signal).add(Args::CheckArgs<size>().connect(slotObj, std::forward<Slot>(slot)));
        }

        // connects signal with callback
        template<typename Signal, typename Slot>
        inline static void connect(Signal& signal, Slot&& slot)
        {
            signal.add(std::forward<Slot>(slot));
        }

        // drops all signal connections
        template<typename Signal>
        inline static void disconnect(Signal& signal)
        {
            signal = nullptr;
        }

        // returns signal callbacks size
        template<typename Signal>
        inline static std::size_t callbacks(Signal& signal)
        {
            return signal.size();
        }

    private:
        explicit Connector() = delete;
        Connector(const Connector&) = delete;
    };
}

#endif // SIGNALS_H
