//
// Created by Falldot on 10.12.2021.
//

#ifndef CORSAC_ECS_ECS_H
#define CORSAC_ECS_ECS_H


#include "Corsac/type_traits.h"
#include "Corsac/vector.h"
#include "Corsac/fixed_vector.h"
#include "Corsac/tuple_vector.h"
#include "Corsac/fixed_tuple_vector.h"

namespace corsac
{

//    template <int First, int Last, typename Lambda>
//    inline void static_for(Lambda const& f)
//    {
//        if constexpr (First < Last)
//        {
//            f(std::integral_constant<int, First>{});
//            static_for<First + 1, Last>(f);
//        }
//    }


    using EntityType    = uint32_t;
    using Group         = corsac::vector<corsac::EntityType>;

    template<typename T>
    class sparse_set
    {
        static_assert(corsac::is_unsigned_v<T>,
                "sparse_set can only store integers numbers");

        using Packed = corsac::vector<T>;
        using Sparse = corsac::vector<T>;

        using pointer                   = T*;
        using const_pointer             = const T*;
        using reference                 = T&;
        using const_reference           = const T&;
        using iterator                  = T*;
        using const_iterator            = const T*;
        using reverse_iterator          = corsac::reverse_iterator<iterator>;
        using const_reverse_iterator    = corsac::reverse_iterator<const_iterator>;

    public:
        using size_type = typename corsac::vector<T>::size_type;

    protected:
        Packed packed;
        Sparse sparse;
    public:
        sparse_set() noexcept;

        iterator       begin() noexcept;
        const_iterator begin() const noexcept;

        iterator       end() noexcept;
        const_iterator end() const noexcept;

        reverse_iterator       rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;

        reverse_iterator       rend() noexcept;
        const_reverse_iterator rend() const noexcept;

        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;

        void resize(size_type n);
        void reserve(size_type n);

        void set_capacity(size_type n = Packed::npos);
        void shrink_to_fit();

        pointer       data() noexcept;
        const_pointer data() const noexcept;

        [[nodiscard]] bool      empty() const noexcept;
        [[nodiscard]] size_type size() const noexcept;
        [[nodiscard]] size_type capacity() const noexcept;

        [[nodiscard]] bool has(const EntityType& value) noexcept;
        [[nodiscard]] bool has(EntityType&& value) noexcept;

        void add(const EntityType& value) noexcept;
        void add(EntityType&& value) noexcept;

        void remove(const EntityType& value) noexcept;
        void remove(EntityType&& value) noexcept;

        void clear() noexcept;
        void reset_lose_memory() noexcept;
    };

    template<typename T>
    sparse_set<T>::sparse_set() noexcept : packed(), sparse() {}

    template<typename T>
    inline typename sparse_set<T>::iterator
    sparse_set<T>::begin() noexcept
    {
        return packed.mpBegin;
    }

    template<typename T>
    inline typename sparse_set<T>::const_iterator
    sparse_set<T>::begin() const noexcept
    {
        return packed.mpBegin;
    }

    template<typename T>
    inline typename sparse_set<T>::iterator
    sparse_set<T>::end() noexcept
    {
        return packed.mpEnd;
    }

    template<typename T>
    inline typename sparse_set<T>::const_iterator
    sparse_set<T>::end() const noexcept
    {
        return packed.mpEnd;
    }

    template<typename T>
    inline typename sparse_set<T>::reverse_iterator
    sparse_set<T>::rbegin() noexcept
    {
        return reverse_iterator(packed.mpEnd);
    }

    template<typename T>
    inline typename sparse_set<T>::const_reverse_iterator
    sparse_set<T>::rbegin() const noexcept
    {
        return const_reverse_iterator(packed.mpEnd);
    }

    template<typename T>
    inline typename sparse_set<T>::reverse_iterator
    sparse_set<T>::rend() noexcept
    {
        return reverse_iterator(packed.mpBegin);
    }

    template<typename T>
    inline typename sparse_set<T>::const_reverse_iterator
    sparse_set<T>::rend() const noexcept
    {
        return const_reverse_iterator(packed.mpBegin);
    }

    template<typename T>
    inline typename sparse_set<T>::reference
    sparse_set<T>::front()
    {
        return packed.front();
    }

    template<typename T>
    inline typename sparse_set<T>::const_reference
    sparse_set<T>::front() const
    {
        return packed.front();
    }

    template<typename T>
    inline typename sparse_set<T>::reference
    sparse_set<T>::back()
    {
        return packed.back();
    }

    template<typename T>
    inline typename sparse_set<T>::const_reference
    sparse_set<T>::back() const
    {
        return packed.mpEnd;
    }

    template<typename T>
    inline typename sparse_set<T>::reference
    sparse_set<T>::operator[](size_type n)
    {
        return packed[n];
    }

    template<typename T>
    inline typename sparse_set<T>::const_reference
    sparse_set<T>::operator[](size_type n) const
    {
        return packed[n];
    }

    template <typename T>
    inline void sparse_set<T>::resize(size_type n)
    {
        packed.resize(n);
        sparse.resize(n);
    }

    template <typename T>
    inline void sparse_set<T>::reserve(size_type n)
    {
        packed.reserve(n);
        sparse.reserve(n);
    }

    template <typename T>
    inline void sparse_set<T>::set_capacity(size_type n)
    {
        packed.set_capacity(n);
        sparse.set_capacity(n);
    }

    template <typename T>
    inline void sparse_set<T>::shrink_to_fit()
    {
        packed.shrink_to_fit();
        sparse.shrink_to_fit();
    }

    template <typename T>
    inline typename sparse_set<T>::pointer
    sparse_set<T>::data() noexcept
    {
        return packed.mpBegin;
    }

    template <typename T>
    inline typename sparse_set<T>::const_pointer
    sparse_set<T>::data() const noexcept
    {
        return packed.mpBegin;
    }

    template <typename T>
    inline bool sparse_set<T>::empty() const noexcept
    {
        return packed.empty();
    }

    template <typename T>
    inline typename sparse_set<T>::size_type
    sparse_set<T>::size() const noexcept
    {
        return packed.size();
    }

    template <typename T>
    inline typename sparse_set<T>::size_type
    sparse_set<T>::capacity() const noexcept
    {
        return packed.capacity();
    }

    template<typename T>
    inline bool sparse_set<T>::has(const EntityType& value) noexcept
    {
        return sparse[value] < packed.size() && packed[sparse[value]] == value;
    }

    template<typename T>
    inline bool sparse_set<T>::has(EntityType&& value) noexcept
    {
        return sparse[value] < packed.size() && packed[sparse[value]] == value;
    }

    template<typename T>
    inline void sparse_set<T>::add(const EntityType& value) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
    }

    template<typename T>
    inline void sparse_set<T>::add(EntityType&& value) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(corsac::move(value));
    }

    template<typename T>
    inline void sparse_set<T>::remove(const EntityType &value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
        }
    }

    template<typename T>
    inline void sparse_set<T>::remove(EntityType &&value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
        }
    }

    template<typename T>
    inline void sparse_set<T>::clear() noexcept
    {
        packed.clear();
        sparse.clear();
    }

    template<typename T>
    inline void sparse_set<T>::reset_lose_memory() noexcept
    {
        packed.reset_lose_memory();
    }

    template<typename T, size_t nodeCount = 0, bool bEnableOverflow = true>
    struct fixed_sparse_set : sparse_set<T>
    {
        static_assert(corsac::is_unsigned_v<T>, "sparse_set can only store integers numbers");
        using Packed = corsac::fixed_vector<T, nodeCount, bEnableOverflow>;
        using Sparse = corsac::fixed_vector<T, nodeCount, bEnableOverflow>;

        using sparse_set<T>::packed;
        using sparse_set<T>::sparse;
        using sparse_set<T>::has;

        template<bool over = bEnableOverflow> void add(const EntityType& value) noexcept;
        template<bool over = bEnableOverflow> void add(EntityType&& value) noexcept;
    };

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    template<bool over>
    void fixed_sparse_set<T, nodeCount, bEnableOverflow>::add(const EntityType &value) noexcept
    {
        if constexpr (over) {
            if (value >= sparse.size())
                sparse.resize(value * 2);
        }
        if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    template<bool over>
    void fixed_sparse_set<T, nodeCount, bEnableOverflow>::add(EntityType &&value) noexcept
    {
        if constexpr (over) {
            if (value >= sparse.size())
                sparse.resize(value * 2);
        }
        if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(corsac::move(value));
    }

    template<typename T, size_t nodeCount = 0, bool bEnableOverflow = true>
    class EntityStorage : public corsac::conditional_t<nodeCount == 0,
            corsac::sparse_set<T>,
            corsac::fixed_sparse_set<T, nodeCount, bEnableOverflow>
        >
    {
        using base_type = corsac::conditional_t<nodeCount == 0,
                corsac::sparse_set<T>,
                corsac::fixed_sparse_set<T, nodeCount, bEnableOverflow>
        >;
    };

    template<typename T, size_t nodeCount = 0, bool bEnableOverflow = true>
    class ComponentAoS : public EntityStorage<EntityType, nodeCount, bEnableOverflow>
    {
        static_assert(corsac::is_trivial_v<T>, "not the right type for the component");
        using Values = corsac::conditional_t<
                nodeCount == 0,
                corsac::vector<T>,
                corsac::fixed_vector<T, nodeCount, bEnableOverflow>
        >;
        using base_type                 = EntityStorage<EntityType, nodeCount, bEnableOverflow>;
        using size_type                 = typename base_type::size_type;
        using pointer                   = T*;
        using const_pointer             = const T*;
        using value_type                = T;
        using reference                 = T&;
        using const_reference           = const T&;
        using iterator                  = T*;
        using const_iterator            = const T*;
        using reverse_iterator          = corsac::reverse_iterator<iterator>;
        using const_reverse_iterator    = corsac::reverse_iterator<const_iterator>;

    public:
        using base_type::packed;
        using base_type::sparse;
        using base_type::has;

    protected:
        Values values;

    public:
        ComponentAoS() noexcept;

        iterator       begin() noexcept;
        const_iterator begin() const noexcept;

        iterator       end() noexcept;
        const_iterator end() const noexcept;

        reverse_iterator       rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;

        reverse_iterator       rend() noexcept;
        const_reverse_iterator rend() const noexcept;

        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        reference operator[](size_type n);
        const_reference operator[](size_type n) const;

        void resize(size_type n);
        void reserve(size_type n);

        void set_capacity(size_type n = Values::npos);
        void shrink_to_fit();

        pointer       data() noexcept;
        const_pointer data() const noexcept;

        reference       get(const EntityType& value);
        reference       get(EntityType&& value);
        const_reference get(const EntityType& value) const;
        const_reference get(EntityType&& value) const;

        void add(const EntityType& value, const value_type& data) noexcept;
        void add(EntityType&& value, value_type&& data) noexcept;

        void remove(const EntityType& value) noexcept;
        void remove(EntityType&& value) noexcept;

        void clear() noexcept;
        void reset_lose_memory() noexcept;
    };

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline ComponentAoS<T, nodeCount, bEnableOverflow>::ComponentAoS() noexcept
            : base_type(), values()
    {}

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::begin() noexcept
    {
        return values.begin();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::begin() const noexcept
    {
        return values.begin();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::end() noexcept
    {
        return values.end();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::end() const noexcept
    {
        return values.end();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reverse_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::rbegin() noexcept
    {
        return values.rbegin();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reverse_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::rbegin() const noexcept
    {
        return values.rbegin();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reverse_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::rend() noexcept
    {
        return values.rend();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reverse_iterator
    ComponentAoS<T, nodeCount, bEnableOverflow>::rend() const noexcept
    {
        return values.rend();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::front()
    {
        return values.front();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::front() const
    {
        return values.front();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::back()
    {
        return values.back();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::back() const
    {
        return values.back();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::operator[](size_type n)
    {
        return values[n];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::operator[](size_type n) const
    {
        return values[n];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::resize(size_type n)
    {
        packed.resize(n);
        sparse.resize(n);
        values.resize(n);
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::reserve(size_type n)
    {
        packed.reserve(n);
        sparse.reserve(n);
        values.reserve(n);
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::set_capacity(size_type n)
    {
        packed.set_capacity(n);
        sparse.set_capacity(n);
        values.set_capacity(n);
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::shrink_to_fit()
    {
        packed.shrink_to_fit();
        sparse.shrink_to_fit();
        values.shrink_to_fit();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::pointer
    ComponentAoS<T, nodeCount, bEnableOverflow>::data() noexcept
    {
        return values.data();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_pointer
    ComponentAoS<T, nodeCount, bEnableOverflow>::data() const noexcept
    {
        return values.data();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::get(const EntityType& value)
    {
        return values[sparse[value]];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::get(EntityType&& value)
    {
        return values[sparse[value]];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::get(const EntityType& value) const
    {
        return values[sparse[value]];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline typename ComponentAoS<T, nodeCount, bEnableOverflow>::const_reference
    ComponentAoS<T, nodeCount, bEnableOverflow>::get(EntityType&& value) const
    {
        return values[sparse[value]];
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::add(const EntityType &value, const value_type &data) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
        values.push_back(data);
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::add(EntityType &&value, value_type &&data) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
        values.push_back(corsac::move(data));
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::remove(const EntityType &value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            values[sparse[value]] = values[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
            values.pop_back();
        }
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::remove(EntityType &&value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            values[sparse[value]] = values[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
            values.pop_back();
        }
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::clear() noexcept
    {
        packed.clear();
        sparse.clear();
        values.clear();
    }

    template<typename T, size_t nodeCount, bool bEnableOverflow>
    inline void ComponentAoS<T, nodeCount, bEnableOverflow>::reset_lose_memory() noexcept
    {
        packed.reset_lose_memory();
        values.reset_lose_memory();
    }

    template<size_t nodeCount = 0, bool bEnableOverflow = true, typename... Ts>
    class ComponentSoA : public EntityStorage<EntityType, nodeCount, bEnableOverflow>
    {
        static_assert(corsac::conjunction_v<corsac::is_trivial<Ts>...>, "not the right type for the component");
        using Values = corsac::conditional_t<
                nodeCount == 0,
                corsac::tuple_vector<Ts...>,
                corsac::fixed_tuple_vector<nodeCount, bEnableOverflow, Ts...>
        >;
        using base_type                 = EntityStorage<EntityType, nodeCount, bEnableOverflow>;
        using size_type                 = typename base_type::size_type;

    public:
        using base_type::packed;
        using base_type::sparse;
        using base_type::has;

    protected:
        Values values;

    public:
        ComponentSoA() noexcept;

        auto front();
        auto front() const;

        auto back();
        auto back() const;

        template<size_t I>
        auto get();

        template<size_t I>
        auto get() const;

        template<size_t I>
        auto get(const EntityType& value);

        template<size_t I>
        auto get(EntityType&& value);

        template<size_t I>
        auto get(const EntityType& value) const;

        template<size_t I>
        auto get(EntityType&& value) const;

        auto operator[](size_type n);
        auto operator[](size_type n) const;

        void resize(size_type n);
        void reserve(size_type n);

        void set_capacity(size_type n = Values::npos);
        void shrink_to_fit();

        auto data() noexcept;
        auto data() const noexcept;

        template<typename ...Args>
        void add(const EntityType& value, Args&&... data) noexcept;

        template<typename ...Args>
        void add(EntityType&& value, Args&&... data) noexcept;

        void remove(const EntityType& value) noexcept;
        void remove(EntityType&& value) noexcept;

        void clear() noexcept;
        void reset_lose_memory() noexcept;
    };

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline ComponentSoA<nodeCount, bEnableOverflow, Ts...>::ComponentSoA() noexcept
            : base_type(), values()
    {}

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::front()
    {
        return values.front();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::front() const
    {
        return values.front();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::back()
    {
        return values.back();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::back() const
    {
        return values.back();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get()
    {
        return values.template get<I>();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get() const
    {
        return values.template get<I>();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get(const EntityType& value)
    {
        return values.template get<I>()[sparse[value]];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get(const EntityType& value) const
    {
        return values.template get<I>()[sparse[value]];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get(EntityType&& value)
    {
        return values.template get<I>()[sparse[value]];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    template<size_t I>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::get(EntityType&& value) const
    {
        return values.template get<I>()[sparse[value]];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::operator[](size_type n)
    {
        return values[n];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::operator[](size_type n) const
    {
        return values[n];
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::resize(size_type n)
    {
        packed.resize(n);
        sparse.resize(n);
        values.resize(n);
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::reserve(size_type n)
    {
        packed.reserve(n);
        sparse.reserve(n);
        values.reserve(n);
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::set_capacity(size_type n)
    {
        packed.set_capacity(n);
        sparse.set_capacity(n);
        values.set_capacity(n);
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::shrink_to_fit()
    {
        packed.shrink_to_fit();
        sparse.shrink_to_fit();
        values.shrink_to_fit();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::data() noexcept
    {
        return values.mpBegin;
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline auto ComponentSoA<nodeCount, bEnableOverflow, Ts...>::data() const noexcept
    {
        return values.mpBegin;
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    template<typename ...Args>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::add(const EntityType &value, Args&&... data) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
        values.push_back(data...);
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    template<typename ...Args>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::add(EntityType &&value, Args&&... data) noexcept
    {
        if (value >= sparse.size())
            sparse.resize(value * 2);
        else if (has(value))
            return;
        sparse[value] = static_cast<EntityType>(packed.size());
        packed.push_back(value);
        values.push_back(data...);
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::remove(const EntityType &value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            values[sparse[value]] = values[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
            values.pop_back();
        }
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::remove(EntityType &&value) noexcept
    {
        if (has(value))
        {
            packed[sparse[value]] = packed[packed.size() - 1];
            values[sparse[value]] = values[packed.size() - 1];
            sparse[packed[packed.size() - 1]] = sparse[value];
            packed.pop_back();
            values.pop_back();
        }
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::clear() noexcept
    {
        packed.clear();
        sparse.clear();
        values.clear();
    }

    template<size_t nodeCount, bool bEnableOverflow, typename ...Ts>
    inline void ComponentSoA<nodeCount, bEnableOverflow, Ts...>::reset_lose_memory() noexcept
    {
        packed.reset_lose_memory();
        values.reset_lose_memory();
    }

    template<size_t nodeCount = 0, bool bEnableOverflow = true>
    class ComponentTag : public EntityStorage<EntityType, nodeCount, bEnableOverflow>
    {};

    template<typename... Ts>
    struct Component : public ComponentSoA<0, true, Ts...> {};

    template<typename T>
    struct Component<T> : public ComponentAoS<T> {};

    template<>
    struct Component<> : public ComponentTag<> {};

    template<size_t nodeCount, bool bEnableOverflow, typename... Ts>
    struct ComponentMake : public ComponentSoA<nodeCount, bEnableOverflow, Ts...> {};

    template<size_t nodeCount, bool bEnableOverflow, typename T>
    struct ComponentMake<nodeCount, bEnableOverflow, T> : public ComponentAoS<T, nodeCount, bEnableOverflow> {};

    template<size_t nodeCount, bool bEnableOverflow>
    struct ComponentMake<nodeCount, bEnableOverflow> : public ComponentTag<nodeCount, bEnableOverflow> {};

    template<auto F, size_t nodeCount = 0, bool bEnableOverflow = true>
    struct System : public EntityStorage<EntityType, nodeCount, bEnableOverflow>
    {
        using EntityStorage<EntityType, nodeCount, bEnableOverflow>::packed;
        constexpr void call()
        {
            F(packed);
        }
    };

    namespace internal
    {
        inline EntityType getNewEntityTypeID() noexcept
        {
            static EntityType lastID = 1;
            return lastID++;
        }
    }

    class Entity {
        EntityType value;

    public:
        inline Entity() noexcept
        {
            value = corsac::internal::getNewEntityTypeID();
        }

        template<auto &comp>
        [[nodiscard]] inline bool has() const noexcept
        {
            return comp.has(value);
        }

        template<auto &comp>
        [[nodiscard]] inline decltype(auto) get() noexcept
        {
            return comp.get(value);
        }

        template<auto &comp, size_t I>
        [[nodiscard]] inline decltype(auto) get() noexcept
        {
            return comp.template get<I>(value);
        }

        template<auto &comp>
        inline void add() noexcept
        {
            comp.add(value);
        }

        template<auto &comp, typename data>
        inline void add(data&& arg) noexcept
        {
            comp.add(value, corsac::move(arg));
        }

        template<auto &comp, typename data>
        inline void add(const data& arg) noexcept
        {
            comp.add(value, arg);
        }

        template<auto &comp, typename... Args>
        inline void add(Args&&... args) noexcept
        {
            comp.add(value, args...);
        }

        template<auto &comp>
        inline void remove() noexcept
        {
            comp.remove(value);
        }
    };
}

#endif //CORSAC_ECS_ECS_H
