

install:
	git submodule init
	git submodule update

modules:
	git submodule add https://github.com/Falldot/Corsac_STL.git ./test/packages/Corsac_STL
	git submodule add https://github.com/Lirik-Keltran/Corsac-Test.git ./test/packages/Corsac_Test