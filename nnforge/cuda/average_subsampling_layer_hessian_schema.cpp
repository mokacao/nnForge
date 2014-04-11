/*
 *  Copyright 2011-2013 Maxim Milakov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "average_subsampling_layer_hessian_schema.h"

#include "../neural_network_exception.h"
#include "../average_subsampling_layer.h"
#include "average_subsampling_2d_layer_hessian_cuda.h"

#include <boost/format.hpp>

namespace nnforge
{
	namespace cuda
	{
		average_subsampling_layer_hessian_schema::average_subsampling_layer_hessian_schema()
		{
		}

		average_subsampling_layer_hessian_schema::~average_subsampling_layer_hessian_schema()
		{
		}

		const boost::uuids::uuid& average_subsampling_layer_hessian_schema::get_uuid() const
		{
			return average_subsampling_layer::layer_guid;
		}

		layer_hessian_schema_smart_ptr average_subsampling_layer_hessian_schema::create_specific() const
		{
			return layer_hessian_schema_smart_ptr(new average_subsampling_layer_hessian_schema());
		}

		layer_hessian_cuda_smart_ptr average_subsampling_layer_hessian_schema::create_hessian_specific(
			const layer_configuration_specific& input_configuration_specific,
			const layer_configuration_specific& output_configuration_specific) const
		{
			layer_hessian_cuda_smart_ptr res;

			switch (output_configuration_specific.dimension_sizes.size())
			{
			case 2:
				res = layer_hessian_cuda_smart_ptr(new average_subsampling_2d_layer_hessian_cuda());
				break;
			default:
				throw neural_network_exception((boost::format("No CUDA hessian for the average subsampling layer of %1% dimensions") % output_configuration_specific.dimension_sizes.size()).str());
				break;
			}

			return res;
		}
	}
}
