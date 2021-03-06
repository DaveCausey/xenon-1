#pragma once
//-- Copyright 2015 Intrig
//-- see https://github.com/intrig/xenon for license
#include <random>
#include <functional>
#include <ict/message.h>
#include <ict/spec_server.h>

namespace ict {
inline bitstring serialize(const message & m) {
    obitstream bs;
    recurse(m.root(), [&](message::const_cursor & self, message::const_cursor &) {
        if (self->consumes()) bs << self->bits;
    });
    return bs.bits();
}

inline ict::bitstring random_bitstring(size_t bit_len) {
    std::random_device engine;
    auto bytes = bit_len / 8 + 1;
    auto v = std::vector<unsigned char>(bytes);
    for (auto & b : v) b = engine();
    return ict::bitstring(v.begin(), bit_len);
}

template <typename Message>
inline void recombobulate(Message & a) {
    ict::recurse(a.root(), [&](ict::message::cursor c, ict::message::cursor) {
        if (c->is_pof()) c->bits = random_bitstring(c->bits.bit_size());
    });
}

// TODO: change this to header only
std::string to_text(const message & m, const std::string & format = "nlvhs",
    std::function<bool(message::const_cursor c)> filter=[](message::const_cursor){ return true; });
   
// TODO: change this to header only
std::string to_xml(const message & m, 
    std::function<bool(message::const_cursor c)> filter=[](message::const_cursor){ return true; });

namespace util {
    template <typename Stream, typename Cursor, typename Filter>
    void to_debug_text(Stream & os, Cursor parent, Filter filter, int level) {
        for (auto c = parent.begin(); c != parent.end(); ++c) if (filter(c)) {
            // os << ict::spaces(level * 2) << c->tag() << " " << c->mnemonic() << " " << c->name() << '\n';
            os << ict::spaces(level * 2);
            to_debug(os, *c);
            os << '\n';
            to_debug_text(os, c, filter, level + 1);
        }
    }
}
   
template <typename Filter>
inline std::string to_debug_text(const message & m, Filter filter) {
    std::ostringstream ss;
    util::to_debug_text(ss, m.root(), filter, 0);
    return ss.str();
}

inline message parse(spec::cursor start, ibitstream & bs) {
    message m;
    m.root().emplace_back(node::prop_node, start);
    parse(start, m.root(), bs);
    return m;
}

inline message parse(spec::cursor start, const bitstring & bits) {
    ibitstream bs(bits);
    return parse(start, bs);
}

inline message parse(spec_server & spec, const bitstring & bits) {
    if (spec.empty()) IT_THROW("empty spec");
    auto start = find(spec.base().ast.root(), "xddl", tag_of);
    return parse(start, bits);
}

spec::cursor get_record(spec_server &, const url & href);

spec::cursor get_type(spec_server &, const url & href);

inline std::string to_hex_string(const bitstring & bits) {
    return to_hex_string(bits.begin(), bits.end());
}

std::string to_html(const spec & s);

}

