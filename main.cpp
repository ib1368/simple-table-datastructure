#include <iostream>

#include "Table.h"

using namespace std;

int main()
{
	using MyTable = Table<int, string, int, string>;
	using MyTableIterator = typename MyTable::Iterator;
	using MyTableRecord = typename MyTable::RecordType;
	using MyTableIndex = typename MyTable::IndexType;


	MyTable table1("column1", "column2", "column3");

	MyTableIndex index{2};
	MyTableRecord record{"data1", 5, "data2"};
	table1.insert(index, record);

	table1.insert(MyTableIndex{5}, MyTableRecord{"data3", 5, "data4"});
	table1.insert(MyTableIndex{6}, MyTableRecord{"data5", 5, "data6"});
	table1.insert(MyTableIndex{7}, MyTableRecord{"data7", 5, "data8"});
	table1.insert(MyTableIndex{8}, MyTableRecord{"data9", 5, "data10"});
	table1.insert(MyTableIndex{9}, MyTableRecord{"data11", 5, "data12"});

	table1.update<int>(2, "column2", 7);
	table1.update<string>(7, "column1", "changed data");

	cout << table1.find<int>(2,"column2") << endl;
	cout << table1.find<string>(7,"column1") << endl;

	return 0;
}
