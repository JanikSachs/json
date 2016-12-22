# benchmarks
benchmarks: src/benchmarks.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -DNDEBUG -O3 -flto -I ../src -I src -I thirdparty $< $(LDFLAGS) -o $@	

prepare:
	cd data/numbers ; python generate.py
