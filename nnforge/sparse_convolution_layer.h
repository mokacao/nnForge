/*
 *  Copyright 2011-2014 Maxim Milakov
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

#pragma once

#include "layer.h"

#include <vector>

namespace nnforge
{
	class sparse_convolution_layer : public layer
	{
	public:
		sparse_convolution_layer(
			const std::vector<unsigned int>& window_sizes,
			unsigned int input_feature_map_count,
			unsigned int output_feature_map_count,
			unsigned int feature_map_connection_count,
			const std::vector<unsigned int>& left_zero_padding = std::vector<unsigned int>(),
			const std::vector<unsigned int>& right_zero_padding = std::vector<unsigned int>());

		sparse_convolution_layer(
			const std::vector<unsigned int>& window_sizes,
			unsigned int input_feature_map_count,
			unsigned int output_feature_map_count,
			float feature_map_connection_sparsity_ratio,
			const std::vector<unsigned int>& left_zero_padding = std::vector<unsigned int>(),
			const std::vector<unsigned int>& right_zero_padding = std::vector<unsigned int>());

		virtual layer_smart_ptr clone() const;

		virtual layer_configuration get_layer_configuration(const layer_configuration& input_configuration) const;

		virtual layer_configuration_specific get_output_layer_configuration_specific(const layer_configuration_specific& input_configuration_specific) const;

		virtual std::vector<std::pair<unsigned int, unsigned int> > get_input_rectangle_borders(const std::vector<std::pair<unsigned int, unsigned int> >& output_rectangle_borders) const;

		virtual layer_data_configuration_list get_layer_data_configuration_list() const;

		virtual float get_forward_flops(const layer_configuration_specific& input_configuration_specific) const;

		virtual float get_backward_flops(const layer_configuration_specific& input_configuration_specific) const;

		virtual float get_weights_update_flops(const layer_configuration_specific& input_configuration_specific) const;

		virtual const boost::uuids::uuid& get_uuid() const;

		virtual void write(std::ostream& binary_stream_to_write_to) const;

		virtual void read(
			std::istream& binary_stream_to_read_from,
			const boost::uuids::uuid& layer_read_guid);

		virtual void randomize_data(
			layer_data& data,
			layer_data_custom& data_custom,
			random_generator& generator) const;

		virtual std::set<unsigned int> get_weight_decay_part_id_set() const;

		static const boost::uuids::uuid layer_guid;

		static const boost::uuids::uuid layer_guid_v1;

	protected:
		virtual data_config get_data_config() const;

		virtual data_custom_config get_data_custom_config() const;

	private:
		void check_consistency();

		void randomize_custom_data(
			layer_data_custom& data_custom,
			random_generator& generator) const;

		void randomize_weights(
			layer_data& data,
			const layer_data_custom& data_custom,
			random_generator& generator) const;

	public:
		std::vector<unsigned int> window_sizes;
		unsigned int input_feature_map_count;
		unsigned int output_feature_map_count;
		unsigned int feature_map_connection_count;
		std::vector<unsigned int> left_zero_padding;
		std::vector<unsigned int> right_zero_padding;
	};
}
