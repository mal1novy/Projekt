CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = app

OBJS = main.o Platform.o Content.o Movie.o Game.o Series.o User.o Rental.o Subscription.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
