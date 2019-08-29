CXX		= g++

.PHONY all: 001 002 003 004 \
			005 006 007

001:
	$(CXX) -Wall -Wextra -std=c++11 001_main.cpp -lpthread -o 001_main

002:
	$(CXX) -Wall -Wextra -std=c++11 002_main.cpp -lpthread -o 002_main

003:
	$(CXX) -Wall -Wextra -std=c++11 003_main.cpp -lpthread -o 003_main

004:
	$(CXX) -Wall -Wextra -std=c++11 004_main.cpp -lpthread -o 004_main

005:
	$(CXX) -Wall -Wextra -std=c++11 005_main.cpp -lpthread -o 005_main

006:
	$(CXX) -Wall -Wextra -std=c++11 006_main.cpp -o 006_main

007:
	$(CXX) -Wall -Wextra -std=c++11 007_main.cpp -lpthread -o 007_main

.PHONY clean:
	$(RM) 001_main
	$(RM) 002_main
	$(RM) 003_main
	$(RM) 004_main
	$(RM) 005_main
	$(RM) 006_main
	$(RM) 007_main
