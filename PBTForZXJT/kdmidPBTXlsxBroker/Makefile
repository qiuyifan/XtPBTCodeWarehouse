PROGRAM = kdmidPBTXlsxStock.so
LIBS    = -L$(BUILD_OUT_DIR) $(BUILD_BROKER_BASE_LIBS) $(BUILD_BASE_LIBS) $(BUILD_SYS_LIBS)
SOURCE  = $(wildcard */*.cpp) $(wildcard *.cpp)
OBJS 	= $(patsubst %.cpp,%.o, $(SOURCE)) 
%.o: %.cpp
	$(CXX) -c $(BUILD_INCS) -I$(BUILD_HOME_DIR)/frame/base_broker/include -I$(BUILD_HOME_DIR)/frame $(FORCE_INCLUDE) -o $@ $?

$(PROGRAM):$(OBJS)
	#$(CXX) -shared $(BUILD_LIBS) -o $(BUILD_OUT_DIR)/$@ $(OBJS)
	g++ -fPIC -Wall  -g -DDEBUG -shared  -o $(BUILD_OUT_DIR)/$@ $^ $(LIBS) $(BUILD_LIBS)	

clean:
	rm -f $(OBJS) $(BUILD_OUT_DIR)/$(PROGRAM)
