#pragma once

#include <type_traits>
#include <algorithm>
#include <memory>

namespace arrow {
    namespace internal {
        /// Объект вызова со стиранием типа, который может быть вызван только один раз.
        /// Он может быть построен из любой лямбды, соответствующей предоставленной сигнатуре вызова.
        /// Его вызов приводит к уничтожению лямбды, освобождая все состояния/ссылки.
        /// немедленно. Вызов FnOnce, сконструированного по умолчанию, или того, который уже был вызван
        /// уже вызывался, приведет к segfault.

        template<typename Signature>
        class FnOnce;

        template<typename R, typename ...A>
        class FnOnce<R(A...)> {
        public: // Constructors
            FnOnce() = default;

            template<class Fn,
                    typename  = typename std::enable_if<std::is_convertible<
                            decltype(std::declval<Fn &&>()(std::declval<A>()...)), R>::value>::type>
            FnOnce(Fn fn) :
                    impl_(new FnImpl<Fn>(std::move(fn))) {

            }

            explicit operator bool() const {
                return impl_ != nullptr;
            }

            R operator()(A...a) &&{
                auto bye = std::move(impl_);
                return bye->Invoke(std::forward<A &&>(a)...);
            }

        private: //Fields
            struct Impl {
                virtual ~Impl() = default;

                virtual R Invoke(A &&... a) = 0;
            };

            template<class Fn>
            struct FnImpl {
                explicit FnImpl(Fn fn) : fn_(std::move(fn)) {}

                R invoke(A &&... a) override { return std::move(fn_)(std::forward<A &&>(a)...); }

                Fn fn_;
            };

            std::unique_ptr<Impl> impl_;
        };

    }
}