/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XTENSOR_FORWARD_HPP
#define XTENSOR_FORWARD_HPP

#include <memory>
#include <vector>

#include "xexpression.hpp"
#include "xlayout.hpp"
#include "xstorage.hpp"
#include "xtensor_config.hpp"
#include "xtensor_simd.hpp"

#include "xtl/xoptional_sequence.hpp"

namespace xt
{
    template <class C>
    struct xcontainer_inner_types;

    template <class EC,
              layout_type L = DEFAULT_LAYOUT,
              class SC = DEFAULT_SHAPE_CONTAINER(typename EC::value_type,
                                                 typename EC::allocator_type,
                                                 std::allocator<typename EC::size_type>),
              class Tag = xtensor_expression_tag>
    class xarray_container;

    /**
     * @typedef xarray
     * Alias template on xarray_container with default parameters for data container
     * type and shape / strides container type. This allows to write
     *
     * \code{.cpp}
     * xt::xarray<double> a = {{1., 2.}, {3., 4.}};
     * \endcode
     *
     * instead of the heavier syntax
     *
     * \code{.cpp}
     * xt::xarray_container<std::vector<double>, std::vector<std::size_t>> a = ...
     * \endcode
     * 
     * @tparam T The value type of the elements.
     * @tparam L The layout_type of the xarray_container (default: row_major).
     * @tparam A The allocator of the container holding the elements.
     * @tparam SA The allocator of the containers holding the shape and the strides.
     */
    template <class T,
              layout_type L = DEFAULT_LAYOUT,
              class A = std::allocator<T>,
              class SA = std::allocator<typename std::vector<T, A>::size_type>>
    using xarray = xarray_container<DEFAULT_DATA_CONTAINER(T, A), L, DEFAULT_SHAPE_CONTAINER(T, A, SA)>;

    template <class EC,
              layout_type L = DEFAULT_LAYOUT,
              class SC = std::vector<typename EC::size_type>,
              class Tag = xtensor_expression_tag>
    class xarray_adaptor;

    /**
     * @typedef xarray_optional
     * Alias template on xarray_container for handling missing values
     *
     * @tparam T The value type of the elements.
     * @tparam L The layout_type of the container (default: row_major).
     * @tparam A The allocator of the container holding the elements.
     * @tparam BA The allocator of the container holding the missing flags.
     * @tparam SA The allocator of the containers holding the shape and the strides.
     */
    template <class T,
              layout_type L = DEFAULT_LAYOUT,
              class A = std::allocator<T>,
              class BC = xtl::xdynamic_bitset<std::size_t>,
              class SA = std::allocator<typename std::vector<T, A>::size_type>>
    using xarray_optional = xarray_container<xtl::xoptional_vector<T, A, BC>, L, DEFAULT_SHAPE_CONTAINER(T, A, SA), xoptional_expression_tag>;

    template <class EC, std::size_t N, layout_type L = DEFAULT_LAYOUT, class Tag = xtensor_expression_tag>
    class xtensor_container;

    /**
     * @typedef xtensor
     * Alias template on xtensor_container with default parameters for data container
     * type. This allows to write
     *
     * \code{.cpp}
     * xt::xtensor<double, 2> a = {{1., 2.}, {3., 4.}};
     * \endcode
     *
     * instead of the heavier syntax
     *
     * \code{.cpp}
     * xt::xtensor_container<std::vector<double>, 2> a = ...
     * \endcode
     *
     * @tparam T The value type of the elements.
     * @tparam N The dimension of the tensor.
     * @tparam L The layout_type of the tensor (default: row_major).
     * @tparam A The allocator of the containers holding the elements.
     */
    template <class T, std::size_t N, layout_type L = DEFAULT_LAYOUT, class A = std::allocator<T>>
    using xtensor = xtensor_container<DEFAULT_DATA_CONTAINER(T, A), N, L>;

    template <class EC, std::size_t N, layout_type L = DEFAULT_LAYOUT, class Tag = xtensor_expression_tag>
    class xtensor_adaptor;

    /**
     * @typedef xtensor_optional
     * Alias template on xtensor_container for handling missing values
     *
     * @tparam T The value type of the elements.
     * @tparam N The dimension of the tensor.
     * @tparam L The layout_type of the container (default: row_major).
     * @tparam A The allocator of the containers holding the elements.
     * @tparam BA The allocator of the container holding the missing flags.
     */
    template <class T,
              std::size_t N,
              layout_type L = DEFAULT_LAYOUT,
              class A = std::allocator<T>,
              class BC = xtl::xdynamic_bitset<std::size_t>>
    using xtensor_optional = xtensor_container<xtl::xoptional_vector<T, A, BC>, N, L, xoptional_expression_tag>;

    template <class CT, class... S>
    class xview;

    namespace check_policy
    {
        struct none
        {
        };
        struct full
        {
        };
    }
}

#endif
