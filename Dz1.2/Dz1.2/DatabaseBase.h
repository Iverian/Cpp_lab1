#pragma once

#include "utility.h"

#include <fstream>
#include <map>

template <int Param>
struct link;

template <class T>
using Search_cont = std::multimap<T, id_type>;
template <int Param>
using Sc_iter = typename Search_cont<typename link<Param>::value>::iterator;

template <class Record>
struct search_struct_traits {
	template <int Param>
	using range = std::pair<Sc_iter<Param>, Sc_iter<Param>>;
	template <int Param>
	using linked_val = typename link<Param>::value;

    virtual ~search_struct_traits() {};
    virtual void index_record(const id_type& pos, const Record& x) = 0;
    virtual void delete_record(const Record& x) = 0;
    template <int Param>
    range<Param> find(const linked_val<Param>& x)
    {
        return make_pair(Sc_iter<Param>(), Sc_iter<Param>());
    }
};

template <class Record, class SearchStruct>
class DatabaseBase {
public:
    explicit DatabaseBase();
    explicit DatabaseBase(const std::string& file_name);
    virtual ~DatabaseBase() = 0;

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
DatabaseBase<Record, SearchStruct>::DatabaseBase()
    : _filename()
    , _search()
{
}

template <class Record, class SearchStruct>
DatabaseBase<Record, SearchStruct>::DatabaseBase(const std::string& file_name)
    : _filename(file_name)
    , _search()
{
}

template <class Record, class SearchStruct>
void DatabaseBase<Record, SearchStruct>::add_record(const Record& a)
{
    std::ofstream out(_filename, std::ios_base::binary | std::ios_base::app);
    out.write((char*)&a, sizeof(Record));
    id_type pos = out.tellp() / sizeof(Record) - 1;
    _search.index_record(pos, a);
}

template <class Record, class SearchStruct>
Record DatabaseBase<Record, SearchStruct>::get_record(const id_type& id)
{
    Record a;
    std::ifstream in(_filename, std::ios_base::binary);
    set_pos<Record>(id, std::ios_base::beg, in);
    in.read((char*)&a, sizeof(Record));
    return std::move(a);
}

template <class Record, class SearchStruct>
void DatabaseBase<Record, SearchStruct>::delete_record(const id_type& pos)
{
    char tmpname[L_tmpnam];
    tmpnam_s(tmpname);
    std::ofstream tmp(tmpname, std::ios_base::binary);
    std::ifstream in(_filename, std::ios_base::binary);

    set_pos<Record>(pos + 1, std::ios_base::beg, in);
    auto del_pos = in.tellg();
    set_pos<Record>(0, std::ios_base::beg, in);
    for (Record x; !in.read((char*)&x, sizeof(Record));)
        if (in.tellg() != del_pos)
            tmp.write((char*)&x, sizeof(Record));
        else
            _search.delete_record(x);
    tmp.close();
    in.close();
    std::remove(_filename.c_str());
    std::rename(tmpname, _filename.c_str());
}

template <class Record, class SearchStruct>
void DatabaseBase<Record, SearchStruct>::change_record(const id_type& pos, const Record& a)
{
    Record old = get_record(pos);
    std::ofstream out(_filename, std::ios_base::binary);
    set_pos<Record>(pos, std::ios_base::beg, out);
    out.write((char*)&a, sizeof(Record));
    _search.delete_record(old);
    _search.index_record(pos, a);
}

template <class Record, class SearchStruct>
template <int Param>
std::pair<Sc_iter<Param>, Sc_iter<Param>>
DatabaseBase<Record, SearchStruct>::find(const typename link<Param>::value& x)
{
    return _search.find<Param>(x);
}

template <class Record, class SearchStruct>
template <int Param>
std::pair<Sc_iter<Param>, Sc_iter<Param>>
DatabaseBase<Record, SearchStruct>::find(const typename link<Param>::value& x, const std::string& found_file_name)
{
    std::ofstream f(found_file_name);
    auto retval = find(x);
    for (auto i = retval.first; i != retval.second; ++i)
        f << *i << std::endl;
    return move(retval);
}
