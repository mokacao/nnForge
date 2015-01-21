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

#include "supervised_data_reader.h"
#include "data_transformer.h"

#include <memory>

namespace nnforge
{
	class supervised_transformed_output_data_reader : public supervised_data_reader
	{
	public:
		supervised_transformed_output_data_reader(
			supervised_data_reader_smart_ptr original_reader,
			data_transformer_smart_ptr transformer);

		virtual ~supervised_transformed_output_data_reader();

		// The method should return true in case entry is read and false if there is no more entries available (and no entry is read in this case)
		// If any parameter is null the method should just discard corresponding data
		virtual bool read(
			void * input_elems,
			float * output_elems);

		virtual bool raw_read(std::vector<unsigned char>& all_elems);

		virtual void rewind(unsigned int entry_id);

		virtual void reset();

		virtual void next_epoch();

		virtual layer_configuration_specific get_input_configuration() const;

		virtual layer_configuration_specific get_output_configuration() const;

		virtual neuron_data_type::input_type get_input_type() const;

		virtual unsigned int get_entry_count() const;

		virtual unsigned int get_sample_count() const;

	protected:
		supervised_transformed_output_data_reader();

	protected:
		supervised_data_reader_smart_ptr original_reader;
		data_transformer_smart_ptr transformer;

		std::vector<float> buf;
		std::vector<unsigned char> input_buf;
		float * local_output_ptr;
		void * local_input_ptr;
		size_t input_buf_size;
		unsigned int current_sample_id;
		unsigned int transformer_sample_count;
	};
}
