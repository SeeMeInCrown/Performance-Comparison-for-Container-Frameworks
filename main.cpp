#include"test.h"
using namespace std;
using namespace PerfTest;
int main(int argc, char** argv) {

	uint32_t max = 1200, min = 800;
	uint64_t vecSize = 1000000;
	const uint64_t quantity = 500;
	const uint64_t upd_quantity = 300;

	uint32_t price;
	uint64_t id;
	srand((uint32_t)time(NULL));

	for (uint64_t i = 0; i < vecSize; i++)
	{
		price = rand() % (max - min + 1) + min; //range of min to (max-min+1)

		InpData data1;
		data1.id = i;
		data1.price = price;
		data1.quantity = quantity;
		insertvec.push_back(data1);

		InpData data2;
		data2.id = i;
		data2.price = price;
		data2.quantity = upd_quantity;
		updatevec.push_back(data2);

		InpData data3;
		data3.id = i;
		data3.price = price;
		data3.quantity = 0;
		deletevec.push_back(data3);
	}

	auto start_time = chrono::system_clock::now(); //begin insert
	//inserting details table
	Level* master = new Level();
	//m_orders.set_empty_key(-1); // must done for dense
	for (uint64_t i = 0; i < insertvec.size(); i++)
	{
		Order* item = new Order();
		item->price = insertvec[i].price;
		item->quantity= insertvec[i].quantity;
		
		m_orders.insert(pair<uint64_t , Order*>(insertvec[i].id,item));

		auto master = m_levels.find(insertvec[i].price);

		if (master != m_levels.end())
    	{

            master->second->quantity += insertvec[i].quantity;
			
        }
        else
        {
            Level* master = new Level();
            master->quantity = insertvec[i].quantity;
            m_levels.insert(pair<uint32_t, Level*>(insertvec[i].price, master));
        }
	}
	
	auto end_time1 = chrono::system_clock::now(); //begin update

	//updating details table
	//m_orders.set_deleted_key(-2); //must for dense
	for (uint64_t i = 0; i < updatevec.size(); i++)
	{
		auto item = m_orders.find(updatevec[i].id);
		if (item !=m_orders.end())
		{
			item->second->quantity -= updatevec[i].quantity;
			if(0==item->second->quantity){
				
				m_orders.erase(item->first);
			}
		}
		else
		{
			cout << "UPDATE:no such item for ID: " << updatevec[i].id << endl;
		}

        auto master = m_levels.find(updatevec[i].price);

        if (master != m_levels.end()){

            master->second->quantity -= updatevec[i].quantity;
			if(0==master->second->quantity){
				m_levels.erase(master->first);
			}
        }
        else{
        cout << "UPDATE:no such item for Price: " << updatevec[i].price << endl;
        }
    }

	auto end_time2 = chrono::system_clock::now(); //begin delete

	//deleting details table
	//m_orders.set_deleted_key(-3); //must for dense
	for (uint64_t i = 0; i < deletevec.size(); i++) //
	{
		auto item = m_orders.find(deletevec[i].id);
		if (item != m_orders.end())
		{
			//m_orders.erase(deletevec[i].id);
			m_orders.erase(item->first);
		}
		else
		{
			cout << "DELETE:no such item for ID: "<<deletevec[i].id << endl;
		}

		auto master = m_levels.find(deletevec[i].price);
		if (master != m_levels.end())
		{
			master->second->quantity = 0;
			//m_levels.erase(master->first);
		}
		else
		{
			cout << "DELETE:no such item for Price: " << deletevec[i].price << endl;
		}
	}

	auto end_time3 = chrono::system_clock::now(); //end timer

	auto insDur= chrono::duration_cast<chrono::nanoseconds>(end_time1 - start_time).count();
	auto insAvg = insDur / vecSize;

	auto updDur = chrono::duration_cast<chrono::nanoseconds>(end_time2 - end_time1).count();
	auto updAvg = updDur / vecSize;

	auto delDur = chrono::duration_cast<chrono::nanoseconds>(end_time3 - end_time2).count();
	auto delAvg = delDur / vecSize;

	cout<<"Performance results for Details / Master table SKA_UNORDERED / BOOST"<<endl;
	cout <<"Operations done for "<<vecSize<<" variables" << endl;
	cout << "Time taken for inserting:" << insDur << " nanosecs.		Average :"<<insAvg <<" ns"<< endl;
	cout << "Time taken for updating :" << updDur << " nanosecs.		Average :"<<updAvg <<" ns"<< endl;
	cout << "Time taken for deleting :" << delDur << " nanosecs.		Average :"<<delAvg <<" ns"<< endl;


	return 0;
}

// #include"test.h"

// using namespace std;
// using namespace PerfTest;

// int main(int argc, char** argv) {

// 	uint32_t max = 1200, min = 800;
// 	uint64_t vecSize = 100000;
// 	const uint64_t quantity = 500;
// 	const uint64_t upd_quantity = 300;

// 	uint32_t price;
// 	uint64_t id;
// 	srand((uint32_t)time(NULL));

// 	for (uint64_t i = 0; i < vecSize; i++)
// 	{
// 		price = rand() % (max - min + 1) + min; //range of min to (max-min+1)

// 		InpData data1;
// 		data1.id = i;
// 		data1.price = price;
// 		data1.quantity = quantity;
// 		insertvec.push_back(data1);

// 		InpData data2;
// 		data2.id = i;
// 		data2.price = price;
// 		data2.quantity = upd_quantity;
// 		updatevec.push_back(data2);

// 		InpData data3;
// 		data3.id = i;
// 		data3.price = price;
// 		data3.quantity = 0;
// 		deletevec.push_back(data3);
// 	}

// 	auto start_time = chrono::system_clock::now(); //begin insert
// 	//inserting details table
	
// 	//m_orders.set_empty_key(-1); // must done for dense
// 	Level *master=new Level() ;
// 	for (uint64_t i = 0; i < insertvec.size(); i++)
// 	{
// 		Order item ;
// 		item.price = insertvec[i].price;
// 		item.quantity= insertvec[i].quantity;
		
// 		m_orders.insert(pair<uint64_t , Order>(insertvec[i].id,item));

		

// 		auto master = m_levels.find(insertvec[i].price);

// 		if (master != m_levels.end())
//     	{
			
//             master->second->quantity += insertvec[i].quantity;
			
//         }
//         else
//         {
//             Level* master=new Level() ;
//             master.quantity = insertvec[i].quantity;
//             m_levels.insert(pair<uint32_t, Level>(insertvec[i].price, master));
//         }
// 	}
	
// 	auto end_time1 = chrono::system_clock::now(); //begin update

// 	//updating details table
// 	//m_orders.set_deleted_key(-2); //must for dense
// 	for (uint64_t i = 0; i < updatevec.size(); i++)
// 	{
// 		auto item = m_orders.find(updatevec[i].id);
// 		if (item !=m_orders.end())
// 		{
// 			item->second.quantity -= updatevec[i].quantity;
// 			if(0==item->second.quantity){
				
// 				m_orders.erase(item->first);
// 			}
// 		}
// 		else
// 		{
// 			cout << "UPDATE:no such item for ID: " << updatevec[i].id << endl;
// 		}

//         auto master = m_levels.find(updatevec[i].price);

//         if (master != m_levels.end()){

//             master->second->quantity -= updatevec[i].quantity;
// 			if(0==master->second.quantity){
// 				m_levels.erase(master->first);
// 			}
//         }
//         else{
//         cout << "UPDATE:no such item for Price: " << updatevec[i].price << endl;
//         }
//     }

// 	auto end_time2 = chrono::system_clock::now(); //begin delete

// 	//deleting details table
// 	//m_orders.set_deleted_key(-3); //must for dense
// 	for (uint64_t i = 0; i < deletevec.size(); i++) //
// 	{
// 		auto item = m_orders.find(deletevec[i].id);
// 		if (item != m_orders.end())
// 		{
// 			//m_orders.erase(deletevec[i].id);
// 			m_orders.erase(item->first);
// 		}
// 		else
// 		{
// 			cout << "DELETE:no such item for ID: "<<deletevec[i].id << endl;
// 		}

// 		auto master = m_levels.find(deletevec[i].price);
// 		if (master != m_levels.end())
// 		{
// 			master->second->quantity = 0;
// 			//m_levels.erase(master->first);
// 		}
// 		else
// 		{
// 			cout << "DELETE:no such item for Price: " << deletevec[i].price << endl;
// 		}
// 	}

// 	auto end_time3 = chrono::system_clock::now(); //end timer

// 	auto insDur= chrono::duration_cast<chrono::nanoseconds>(end_time1 - start_time).count();
// 	auto insAvg = insDur / vecSize;

// 	auto updDur = chrono::duration_cast<chrono::nanoseconds>(end_time2 - end_time1).count();
// 	auto updAvg = updDur / vecSize;

// 	auto delDur = chrono::duration_cast<chrono::nanoseconds>(end_time3 - end_time2).count();
// 	auto delAvg = delDur / vecSize;

// 	cout<<"Performance results for Details / Master table BYTELL / POCO"<<endl;
// 	cout <<"Operations done for "<<vecSize<<" variables" << endl;
// 	cout << "Time taken for inserting:" << insDur << " nanosecs.		Average :"<<insAvg <<" ns"<< endl;
// 	cout << "Time taken for updating :" << updDur << " nanosecs.		Average :"<<updAvg <<" ns"<< endl;
// 	cout << "Time taken for deleting :" << delDur << " nanosecs.		Average :"<<delAvg <<" ns"<< endl;


// 	return 0;
// }


