OUTPUT = mapper

all :
	-@rm -rf build
	-@rm $(OUTPUT).node
	node-gyp configure
	node-gyp build
	mv build/Release/$(OUTPUT).node .
