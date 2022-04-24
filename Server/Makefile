BUILD_DIR = build

TARGET = build/server.out

.PHONY: all build clean run

all: build clean

build: clean $(BUILD_DIR)

$(BUILD_DIR): $(TARGET)

$(TARGET):
	./scripts/build.sh

clean:
	rm -rf $(BUILD_DIR)

run-server: clean $(TARGET)
	./$(TARGET)
