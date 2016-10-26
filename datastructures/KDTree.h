/*
 * KDTree.h
 *
 *  Created on: Mar 15, 2016
 *      Author: Madison
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Utilities.h"
#include <iomanip>
#include <Comparison.h>

namespace flabs
{
	template<class Type>
	class KDTree
	{
		private:
			uint32_t k;
			uint32_t depth;
			uint32_t axis;
			Type data;
			KDTree* left;
			KDTree* right;

		public:
			template<class RandomAccessIterator>
			static KDTree<Type>* build(const RandomAccessIterator& start,
			    const RandomAccessIterator& end, uint32_t k, uint32_t depth = 0)
			{
				// Select axis based on depth so that axis cycles through all valid values
				uint32_t axis = depth % k;

				// Sort list by the selected axis
				auto compareAxis = [&axis](const Type& t1, const Type& t2) -> bool
				{
					return t1[axis] < t2[axis];
				};
				std::sort(start, end, compareAxis);

				// Select the median as this node's data
				RandomAccessIterator median = start + (end - start) / 2;

				// Select the left most median value
				// TODO: NO LINEAR SEARCH!!!
				auto equals =
				    [&axis](const RandomAccessIterator& r1, const RandomAccessIterator& r2) -> bool
				    {
					    return !((*r1)[axis] < (*r2)[axis]) && !((*r2)[axis] < (*r1)[axis]);
				    };
				while (median != start && equals(median, median - 1))
					--median;

				KDTree<Type>* tree = new KDTree<Type>(*median, k, depth);

				// Create left sub-tree
				if (start != median)
					tree->left = build(start, median, k, depth + 1);
				else
					tree->left = NULL;

				// Create right sub-tree
				if (end != median && end != median + 1)
					tree->right = build(median + 1, end, k, depth + 1);
				else
					tree->right = NULL;

				return tree;
			}

			virtual ~KDTree()
			{
				if (left != NULL)
					delete left;

				if (right != NULL)
					delete right;
			}

			void insert(const Type& data)
			{
				if (data[axis] < this->data[axis])
					if (left != NULL)
						left->insert(data);
					else
						left = new KDTree(data, k, depth + 1);
				else if (right != NULL)
					right->insert(data);
				else
					right = new KDTree(data, k, depth + 1);
			}

			uint32_t count(const Type& key) const
			{
				if (key[axis] < data[axis])
				{
					if (left != NULL)
						return left->count(key);
					else
						return 0;
				}
				else
				{
					uint32_t count = equals(key, data) ? 1 : 0;
					if (right != NULL)
						return right->count(key) + count;
					else
						return count;
				}
			}

			const Type* get(const Type& key) const
			{
				if (key[axis] < data[axis])
				{
					if (left != NULL)
						return left->get(key);
					else
						return NULL;
				}
				else
				{
					if (equals(key, data))
						return &data;
					else if (right != NULL)
						return right->get(key);
					else
						return NULL;
				}
			}

			template<class OutputIterator>
			void get(const Type& key, OutputIterator& output) const
			{
				if (left != NULL && key[axis] < data[axis])
					left->get(key, output);
				else
				{
					if (equals(key, data))
					{
						*output = data;
						++output;
					}

					if (right != NULL)
						right->get(key, output);
				}
			}

			template<class OutputIterator>
			void get(const Type& min, const Type& max, OutputIterator& output) const
			{
				if (left != NULL && min[axis] < data[axis])
					left->get(min, max, output);

				bool inRange = true;
				for (uint32_t i = 0; i < k; ++i)
					if (!(min[i] <= data[i] && data[i] < max[i]))
					{
						inRange = false;
						break;
					}

				if (inRange)
				{
					*output = data;
					++output;
				}

				if (right != NULL && data[axis] < max[axis])
					right->get(min, max, output);
			}

			friend std::ostream& operator<<(std::ostream& out, const KDTree<Type>& tree)
			{
				return out << tree.data;
			}

			void postorder(KDTree<Type>* p, int indent = 0)
			{
				if (p != NULL)
				{
					if (p->right)
						postorder(p->right, indent + 4);

					if (indent)
						std::cout << std::setw(indent) << ' ';

					if (p->right)
						std::cout << "   /\n" << std::setw(indent) << ' ';

					std::cout << p->data << "\n";

					if (p->left)
					{
						std::cout << std::setw(indent) << ' ' << ' ' << ' ' << " \\\n";
						postorder(p->left, indent + 4);
					}
				}
			}

		private:
			KDTree(const Type& data, uint32_t k, uint32_t depth = 0) :
					k(k), depth(depth), data(data), left(NULL), right(NULL)
			{
				// Select axis based on depth so that axis cycles through all valid values
				axis = depth % k;
			}

			inline bool equals(const Type& t1, const Type& t2) const
			{
				for (uint32_t i = 0; i < k; ++i)
					if (t1[i] != t2[i])
						return false;
				return true;
			}
	};
}

#endif
