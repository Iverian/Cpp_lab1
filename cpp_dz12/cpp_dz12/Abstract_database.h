#pragma once

#include "search_struct_traits.h"
#include "utility.h"

#include <fstream>
#include <map>
#include <vector>

#define template_                                                                                           \
    template <class Record, template <class> class SearchStruct, template <class> class BinToText>
#define basic_database_ basic_database<Record, SearchStruct, BinToText>

template_ class basic_database {
public:
    explicit basic_database();
    explicit basic_database(const std::string& file_name);
    virtual ~basic_database();

    const std::string& filename() const;
    id_type size() const;
    void add_record(const Record& a);
    Record get_record(const id_type& id) const;
    void delete_record(const id_type& pos);
    void change_record(const id_type& pos, const Record& a);
    void bin_to_txt(const std::string& txtfile_name) const;

    template <int id>
    std::vector<id_type> find(const linked_type<id>& x) const;
    template <int id>
    std::vector<id_type> find(const linked_type<id>& x, const std::string& found_file_name) const;

private:
    std::string _filename;
    SearchStruct<Record> _search;
};

template_ void basic_database_::bin_to_txt(const std::string& txtfile_name) const
{
	BinToText<Record>()(txtfile_name);
}

template_ basic_database_::basic_database()
    : _filename()
    , _search()
{
}

template_ basic_database_::basic_database(const std::string& file_name)
    : _filename(file_name)
    , _search()
{
}

template_ basic_database_::~basic_database()
{
}

template_ void basic_database_::add_record(const Record& a)
{
    std::ofstream out(_filename, std::ios_base::binary | std::ios_base::app);
    out.write(reinterpret_cast<char*>(&a), sizeof(Record));
    id_type pos = out.tellp() / sizeof(Record) - 1;
    _search.index_record(pos, a);
}

template_ Record basic_database_::get_record(const id_type& id) const
{
    Record a;
    std::ifstream in(_filename, std::ios_base::binary);
    set_pos<Record>(id, std::ios_base::beg, in);
    in.read(reinterpret_cast<char*>(&a), sizeof(Record));
    return a;
}

template_ void basic_database_::delete_record(const id_type& pos)
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

template_ void basic_database_::change_record(const id_type& pos, const Record& a)
{
    Record old = get_record(pos);
    std::ofstream out(_filename, std::ios_base::binary);
    set_pos<Record>(pos, std::ios_base::beg, out);
    out.write(reinterpret_cast<char*>(&a), sizeof(Record));
    _search.delete_record(old);
    _search.index_record(pos, a);
}

template_ const std::string& basic_database_::filename() const
{
    return _filename;
}

template_ id_type basic_database_::size() const
{
    return std::ofstream(_filename, std::ios_base::binary | std::ios_base::app).tellp() / sizeof(Record);
}

template_ template <int id>
std::vector<id_type> basic_database_::find(const linked_type<id>& x) const
{
    return _search.find<id>(x);
}

template_ template <int id>
std::vector<id_type> basic_database_::find(
    const linked_type<id>& x, const std::string& found_file_name) const
{
    std::ofstream f(found_file_name);
    auto retval = find<id>(x);
    for (const auto& i : retval)
        f << i << std::endl;
    return retval;
}

#undef template_
#undef basic_database_