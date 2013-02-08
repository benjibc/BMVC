al:
	g++ tester.cpp -o tester -std=c++0x -Wall -I ./module/ -I ./bmvc/boost_file/ -ggdb 
pic:
	g++ tester.cpp -o test -std=c++0x -fmax-errors=10 -ljpeg -lpng -ltiff
constexpr:
	g++ static_hash_map.cpp -o constexpr -std=c++0x -O2
clean:
	rm ./constexpr
