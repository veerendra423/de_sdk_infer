all: build

# Clean up
clean:
	rm obj_detector/object_detection_app
	rm config-parser/bin/item_test
	rm config-parser/bin/parser_test

# Build only
build:
	g++ -Wall -Wno-unused-variable -I config-parser/config/ -I target_platform/inc -I target_platform/src -I obj_detector/inc -I obj_detector/src -std=c++11 obj_detector/object_detection_main.cpp config-parser/config/handler.cpp config-parser/config/item.cpp config-parser/config/parser.cpp obj_detector/src/detector.cpp obj_detector/src/yolov3.cpp target_platform/src/intel.cpp -o object_detection_app

# Build and run
run: build
	./obj_detector/object_detection_app

# There will be no output from the executable if all tests pass.
test:
	@echo "\n> 1 of 2: Running item_test.cpp..."
	g++ -Wall -Wno-unused-variable -Wno-missing-braces -std=c++11 config-parser/config/item.cpp config-parser/config/item_test.cpp -o config-parser/bin/item_test
	./config-parser/bin/item_test
	@echo "Done!"
	@echo "\n> 2 of 2: Running parser_test.cpp..."
	g++ -Wall -Wno-unused-variable -Wno-missing-braces -std=c++11 config-parser/config/parser.cpp config-parser/config/parser_test.cpp config-parser/config/item.cpp -o config-parser/bin/parser_test
	./config-parser/bin/parser_test
	@echo "Done!"
