# benchmarks
all: benchmarks_dump_json benchmarks_dump_cbor benchmarks_dump_msgpack benchmarks_parse_json

benchmarks_dump_json: src/benchmarks.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -DNDEBUG -DJSON_BENCHMARK_DUMP_JSON -O3 -flto -I ../src -I src -I thirdparty $< $(LDFLAGS) -o $@	

benchmarks_dump_cbor: src/benchmarks.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -DNDEBUG -DJSON_BENCHMARK_DUMP_CBOR -O3 -flto -I ../src -I src -I thirdparty $< $(LDFLAGS) -o $@	

benchmarks_dump_msgpack: src/benchmarks.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -DNDEBUG -DJSON_BENCHMARK_DUMP_MSGPACK -O3 -flto -I ../src -I src -I thirdparty $< $(LDFLAGS) -o $@	

benchmarks_parse_json: src/benchmarks.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -DNDEBUG -DJSON_BENCHMARK_PARSE_JSON -O3 -flto -I ../src -I src -I thirdparty $< $(LDFLAGS) -o $@	

prepare:
	cd data/numbers ; python generate.py
