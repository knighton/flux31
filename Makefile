clang:
	@mkdir -p bin/
	clang++ -O3 -std=c++17 -Wpedantic -Wall -Weverything -Wextra -Werror -Wno-double-promotion -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Isrc/ src/*.cc src/main.cpp -o bin/sunyata

gcc:
	@mkdir -p bin/
	g++ -O3 -std=c++17 -Wpedantic -Wall -Wextra -Werror -Wno-double-promotion -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Isrc/ src/*.cc src/main.cpp -o bin/sunyata

clean:
	rm -rf bin/
