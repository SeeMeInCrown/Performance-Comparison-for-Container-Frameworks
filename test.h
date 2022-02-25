#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <vector>
#include<map>
#include<random>
#include<ctime>
#include <chrono>	
#include <boost/container/flat_map.hpp>
#include <google/dense_hash_map>

#include "bytell_hash_map.hpp"
#include "flat_hash_map.hpp"
#include <Poco/HashSet.h>
#include <Poco/HashMap.h>
#include "robin_growth_policy.h"
#include "robin_hash.h"
#include "robin_map.h"
#include "robin_set.h"
#include "parallel-hashmap/parallel_hashmap/phmap.h"
#include "hashmap/include/hackmap.hpp"
#include "unordered_map.hpp"

using namespace std;

namespace PerfTest {


	struct InpData		// Details Table (current framework google::dense_hash_map)(unordered)
	{
		uint64_t  id;
		uint32_t  price;
		uint64_t  quantity;

		InpData() {
			id = 0;
			price = 0;
			quantity = 0;
		}
	};

	struct Order		// Details Table (current framework google::dense_hash_map)(unordered)
	{
		uint32_t  price;
		uint64_t  quantity;

		Order() {
			price = 0;
			quantity = 0;
		}
	};

	struct Level		// Master Table (current framework boost::container::flat_map)(ordered)
	{
		uint64_t  quantity;

		Level() = default;

		~Level() = default;
	};

	vector<InpData> insertvec, updatevec, deletevec;

	//hackmap::unordered_map<uint64_t, Order*>      m_orders;
	//google::dense_hash_map<uint64_t, Order*>      m_orders;
	//ska::bytell_hash_map<uint64_t, Order*> m_orders;
	//ska::flat_hash_map<uint64_t, Order*> m_orders;
	//Poco::HashMap<uint64_t, Order*>      m_orders;
	//tsl::robin_map<uint64_t, Order*>      m_orders;
	//tsl::robin_set<uint64_t, Order*>      m_orders;
	//phmap::flat_hash_map<uint64_t, Order*>      m_orders;
	ska::unordered_map<uint64_t, Order*>      m_orders;

	boost::container::flat_map<uint32_t, Level *>  m_levels;	// m_levels.first: price (uint32_t),   m_orders.second: quantity (uint64_t)
	//phmap::node_hash_set<uint64_t, Order*> m_levels;
	//Poco::HashSet<uint32_t, Level* >  m_levels;
}
#endif   
