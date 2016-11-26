#pragma once

#include "utility.h"
#include "search_struct_traits.h"

#include <fstream>
#include <map>

template <class Record, class SearchStruct>
class Abstract_database {
public:
    explicit Abstract_database();
    explicit Abstract_database(const std::string& file_name);
	virtual ~Abstract_database();;

    void add_record(const Record& a);
    Record get_record(const id_type& id);
    void delete_record(const id_type& pos);
    void change_record(const id_type& pos, const Record& a);

    virtual void bin_to_txt(const std::string& txtfile_name) = 0;

    template <int Param>
    std::pair<Sc_iter<Param>, Sc_iter<Param>> find(const typename link<Param>::value& x);
    template <int Param>
    std::pair<Sc_iter<Param>, Sc_iter<Param>> find(const typename link<Param>::value& x, const std::string& found_file_name);

private:
    std::string _filename;
    SearchStruct _search;
};

template <class Record, class SearchStruct>
Abstract_database<Record, SearchStruct>::Abstract_database()
    : _filename()
    , _search()
{
}

template <class Record, class SearchStruct>
Abstract_database<Record, SearchStruct>::Abstract_database(const std::string& file_name)
    : _filename(file_name)
    , _search()
{
}

template <class Record, class SearchStruct>
Abstract_database<Record, SearchStruct>::~Abstract_database()
{
}

template <class Record, class SearchStruct>
void Abstract_database<Record, SearchStruct>::add_record(const Record& a)
{
    std::ofstream out(_filename, std::ios_base::binary | std::ios_base::app);
    out.write(reinterpret_cast<char*>(&a), sizeof(Record));
    id_type pos = out.tellp() / sizeof(Record) - 1;
    _search.index_record(pos, a);
}

template <class Record, class SearchStruct>
Record Abstract_database<Record, SearchStruct>::get_record(const id_type& id)
{
    Record a;
    std::ifstream in(_filename, std::ios_base::binary);
    set_pos<Record>(id, std::ios_base::beg, in);
    in.read(reinterpret_cast<char*>(&a), sizeof(Record));
    return std::move(a);
}

template <class Record, class SearchStruct>
void Abstract_database<Record, SearchStruct>::delete_record(const id_type& pos)
{
    char tmpname[L_tmpnam];
    tmpnam_s(tmpname);
    std::ofstream tmp(tmpname, std::ios_base::binary);
    std::ifstream in(_filename, std::ios_base::binary);

    set_pos<Record>(pos + 1, std::ios_base::beg, in);
    auto del_pos = in.tellg();
    set_pos<Record>(0, std::ios_base::beg, in);
    for (Record x; !in.read(reinterpret_cast<char*>(&x), sizeof(Record));)
        if (in.tellg() != del_pos)
            tmp.write(reinterpret_cast<char*>(&x), sizeof(Record));
        else
            _search.delete_record(x);
    tmp.close();
    in.close();
    std::remove(_filename.c_str());
    std::rename(tmpname, _filename.c_str());
}

template <class Record, class SearchStruct>
void Abstract_database<Record, SearchStruct>::change_record(const id_type& pos, const Record& a)
{
    Record old = get_record(pos);
    std::ofstream out(_filename, std::ios_base::binary);
    set_pos<Record>(pos, std::ios_base::beg, out);
    out.write(reinterpret_cast<char*>(&a), sizeof(Record));
    _search.delete_record(old);
    _search.index_record(pos, a);
}

template <class Record, class SearchStruct>
template <int Param>
std::pair<Sc_iter<Param>, Sc_iter<Param>>
Abstract_database<Record, SearchStruct>::find(const typename link<Param>::value& x)
{
    return _search.find<Param>(x);
}

template <class Record, class SearchStruct>
template <int Param>
std::pair<Sc_iter<Param>, Sc_iter<Param>>
Abstract_database<Record, SearchStruct>::find(const typename link<Param>::value& x, const std::string& found_file_name)
{
    std::ofstream f(found_file_name);
    auto retval = find<Param>(x);
    for (auto i = retval.first; i != retval.second; ++i)
        f << *i << std::endl;
    return move(retval);
}
