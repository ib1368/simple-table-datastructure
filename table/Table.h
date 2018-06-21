#ifndef TABLE_H_
#define TABLE_H_

#include <map>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <iostream>
#include "TupleUtility.h"

/// Simple table data structure
template <typename Index, typename... EntriesTypes>
class Table
{
public:
	using IndexType = Index;
	using RecordType = std::tuple<EntriesTypes...>;
	using MapType = std::map<IndexType, RecordType>;
	using Iterator = typename MapType::iterator;

	Table()
	{
		for(size_t i = 0; i < NumberOfColumns; i++)
		{
			columns_names["C" + std::to_string(i)] = i;
		}
	}

	template <typename ColumnName>
	Table(const ColumnName& column_name)
	{
		const size_t column_id = NumberOfColumns - 1;
		columns_names[column_name] = column_id;
	}

	template <typename ColumnName, typename... ColumnsNames, typename std::enable_if<sizeof...(ColumnsNames) + 1 == sizeof...(EntriesTypes), int>::type = 0>
	Table(const ColumnName& column_name, const ColumnsNames&... rest_of_names):
	Table(rest_of_names...)
	{
		const size_t column_id = NumberOfColumns - sizeof...(rest_of_names) - 1;
		columns_names[column_name] = column_id;
	}

	// Inserts a record with specific index
	void insert(const IndexType& index, const RecordType& record)
	{
		records.insert(make_pair(index, record));
	}

	// Removes a record with specific index
	void erase(const IndexType& index)
	{
		records.erase(index);
	}

	Iterator begin()
	{
		return records.begin();
	}
	
	Iterator end()
	{
		return records.end();
	}

	Iterator find(const IndexType& index)
	{
		return records.find(index);
	}

	bool empty() const
	{
		return records.empty();
	}

	/// Updates the entry specified by record index and column name with the supplied value
	template<typename Value>
	Iterator update(const IndexType& index, const std::string& column_name, const Value& value)
	{
		Iterator record_it = find(index);
		if (record_it == records.end())
        		throw std::runtime_error("[Table::update] There is no record with index of '" + std::to_string(index) + "'!");

		std::map<std::string, int>::iterator column_id_it = columns_names.find(column_name);
		if (column_id_it == columns_names.end())
        		throw std::runtime_error("[Table::update] There is no column with the name '" + column_name + "'!");

		Value& entry = tuple_utility::get<Value>(record_it->second, column_id_it->second);
		entry = value;

		return record_it;
	}

	/// Finds the entry specified by record index and column name
	template<typename Value>
	const Value& find(const IndexType& index, const std::string& column_name)
	{
		Iterator record_it = find(index);
		if (record_it == records.end())
        		throw std::runtime_error("[Table::find] There is no record with index of '" + std::to_string(index) + "'!");

		std::map<std::string, int>::iterator column_id_it = columns_names.find(column_name);
		if (column_id_it == columns_names.end())
        		throw std::runtime_error("[Table::find] There is no column with the name '" + column_name + "'!");

		Value& entry = tuple_utility::get<Value>(record_it->second, column_id_it->second);

		return entry;
	}

protected:
	template <typename ColumnName, typename... ColumnsNames, typename std::enable_if<sizeof...(ColumnsNames) + 1 < sizeof...(EntriesTypes), int>::type = 0>
	Table(const ColumnName& column_name, const ColumnsNames&... rest_of_names):
	Table(rest_of_names...)
	{
		const size_t column_id = NumberOfColumns - sizeof...(rest_of_names) - 1;
		columns_names[column_name] = column_id;
	}

private:
	std::map<IndexType, RecordType> records;
	std::map<std::string, int> columns_names;
	const size_t NumberOfColumns = sizeof...(EntriesTypes);
};

#endif
