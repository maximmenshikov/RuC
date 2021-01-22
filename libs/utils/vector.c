/*
 *	Copyright 2021 Andrey Terekhov, Victor Y. Fadeev, Dmitrii Davladov
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 */

#include "vector.h"
#include <stdlib.h>


vector vector_create(const size_t values)
{
	vector vec;

	vec.size = 0;
	vec.size_alloc = values != 0 ? values : 1;
	vec.array = malloc(vec.size_alloc * sizeof(int64_t));

	return vec;
}


size_t vector_add(vector *const vec, const int64_t value)
{
	if (!vector_is_correct(vec))
	{
		return SIZE_MAX;
	}

	if (vec->size == vec->size_alloc)
	{
		int64_t *array_new = realloc(vec->array, 2 * vec->size_alloc * sizeof(int64_t));
		if (array_new == NULL)
		{
			return SIZE_MAX;
		}

		vec->size_alloc *= 2;
		vec->array = array_new;
	}

	vec->array[vec->size] = value;
	return vec->size++;
}

int vector_set(vector *const vec, const size_t index, const int64_t value)
{
	if (!vector_is_correct(vec) || index >= vec->size)
	{
		return -1;
	}

	vec->array[index] = value;
	return 0;
}

int64_t vector_get(const vector *const vec, const size_t index)
{
	if (!vector_is_correct(vec) || index >= vec->size)
	{
		return LLONG_MAX;
	}

	return vec->array[index];
}


size_t vector_size(vector *const vec)
{
	return vector_is_correct(vec) ? vec->size : SIZE_MAX;
}

int vector_is_correct(const vector *const vec)
{
	return vec != NULL && vec->array != NULL;
}


int vector_clear(vector *const vec)
{
	if (!vector_is_correct(vec))
	{
		return -1;
	}

	free(vec->array);
	vec->array = NULL;

	return 0;
}