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

#pragma once

#include "network_tester.h"
#include "nn_types.h"

namespace nnforge
{
	class network_tester_factory
	{
	public:
		virtual ~network_tester_factory();

		virtual network_tester_smart_ptr create(network_schema_smart_ptr schema) const = 0;

	protected:
		network_tester_factory();
	};

	typedef nnforge_shared_ptr<network_tester_factory> network_tester_factory_smart_ptr;
}
