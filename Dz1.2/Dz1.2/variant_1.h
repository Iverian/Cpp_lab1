#pragma once

#include "search_struct_traits.h"

#define MAXLEN 100

struct Record {
    int code;
    char model[MAXLEN];
    char name[MAXLEN];
    char type[MAXLEN];
    int chast;
    int vol;
    int obem;
    int _vol;
    int cost;
    int col_vo;
};

enum class search_fields {
    type,
    vol,
    obem,
    _vol
};

struct Search_struct : search_struct_traits<Record> {
    void index_record(const id_type& pos, const Record& x) override;
    void delete_record(const Record& x) override;
    ~Search_struct();

    template <int Param>
    range<Param> find(const linked_val<Param>& x);

private:
    Search_cont<char*> type;
    Search_cont<int> vol;
    Search_cont<int> _vol;
    Search_cont<int> obem;
};

def_all(type, char*);
def_all(vol, int);
def_all(_vol, int);
def_all(obem, int);
