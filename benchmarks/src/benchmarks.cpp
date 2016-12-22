/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (benchmarks)
|  |  |__   |  |  | | | |  version 2.0.9
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
*/

#define NONIUS_RUNNER
#include <nonius/nonius.h++>
#include <json.hpp>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

void parse_test(const std::string& filename, nonius::chronometer& meter)
{
    // read file into string stream
    std::stringstream istr;
    {
        std::ifstream input_file(filename);
        istr << input_file.rdbuf();
        input_file.close();
    }

    // the actual benchmark
    meter.measure([&](int i)
    {
        // clear flags and rewind
        istr.clear();
        istr.seekg(0);
        // parse input
        json j;
        j << istr;
    });
}

void dump_test(const std::string& filename, bool indent, nonius::chronometer& meter)
{
    json j;
    {
        std::ifstream input_file(filename);
        j << input_file;
    }

    // the acutal benchmark
    meter.measure([&](int i)
    {
        std::stringstream ostr;
        if (indent)
        {
            ostr << std::setw(4) << j;
        }
        else
        {
            ostr << j;
        }
    });
}

void dump_cbor_test(const std::string& filename, nonius::chronometer& meter)
{
    json j;
    {
        std::ifstream input_file(filename);
        j << input_file;
    }

    // the acutal benchmark
    meter.measure([&](int i)
    {
        auto v = json::to_cbor(j);
    });
}

void dump_msgpack_test(const std::string& filename, nonius::chronometer& meter)
{
    json j;
    {
        std::ifstream input_file(filename);
        j << input_file;
    }

    // the acutal benchmark
    meter.measure([&](int i)
    {
        auto v = json::to_msgpack(j);
    });
}

NONIUS_BENCHMARK("parse jeopardy.json", [](nonius::chronometer meter)
{
    parse_test("data/jeopardy/jeopardy.json", meter);
});

NONIUS_BENCHMARK("parse canada.json", [](nonius::chronometer meter)
{
    parse_test("data/nativejson-benchmark/canada.json", meter);
});

NONIUS_BENCHMARK("parse citm_catalog.json", [](nonius::chronometer meter)
{
    parse_test("data/nativejson-benchmark/citm_catalog.json", meter);
});

NONIUS_BENCHMARK("parse twitter.json", [](nonius::chronometer meter)
{
    parse_test("data/nativejson-benchmark/twitter.json", meter);
});

NONIUS_BENCHMARK("parse numbers/floats.json", [](nonius::chronometer meter)
{
    parse_test("data/numbers/floats.json", meter);
});

NONIUS_BENCHMARK("parse numbers/signed_ints.json", [](nonius::chronometer meter)
{
    parse_test("data/numbers/signed_ints.json", meter);
});

NONIUS_BENCHMARK("parse numbers/flounsigned_intsats.json", [](nonius::chronometer meter)
{
    parse_test("data/numbers/unsigned_ints.json", meter);
});


NONIUS_BENCHMARK("dump jeopardy.json", [](nonius::chronometer meter)
{
    dump_test("data/jeopardy/jeopardy.json", false, meter);
});

NONIUS_BENCHMARK("dump jeopardy.json with indent", [](nonius::chronometer meter)
{
    dump_test("data/jeopardy/jeopardy.json", true, meter);
});

NONIUS_BENCHMARK("dump numbers/floats.json", [](nonius::chronometer meter)
{
    dump_test("data/numbers/floats.json", false, meter);
});

NONIUS_BENCHMARK("dump numbers/signed_ints.json", [](nonius::chronometer meter)
{
    dump_test("data/numbers/signed_ints.json", false, meter);
});


NONIUS_BENCHMARK("dump jeopardy.json to CBOR", [](nonius::chronometer meter)
{
    dump_cbor_test("data/jeopardy/jeopardy.json", meter);
});

NONIUS_BENCHMARK("dump numbers/floats.json to CBOR", [](nonius::chronometer meter)
{
    dump_cbor_test("data/numbers/floats.json", meter);
});

NONIUS_BENCHMARK("dump numbers/signed_ints.json to CBOR", [](nonius::chronometer meter)
{
    dump_cbor_test("data/numbers/signed_ints.json", meter);
});


NONIUS_BENCHMARK("dump jeopardy.json to MessagePack", [](nonius::chronometer meter)
{
    dump_msgpack_test("data/jeopardy/jeopardy.json", meter);
});

NONIUS_BENCHMARK("dump numbers/floats.json to MessagePack", [](nonius::chronometer meter)
{
    dump_msgpack_test("data/numbers/floats.json", meter);
});

NONIUS_BENCHMARK("dump numbers/signed_ints.json to MessagePack", [](nonius::chronometer meter)
{
    dump_msgpack_test("data/numbers/signed_ints.json", meter);
});
