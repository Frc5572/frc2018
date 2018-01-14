{
  "targets": [
    {
      "target_name": "mapper",
      "sources": [ "src/min.cpp", "src/drivetrain/motion.cpp" ],
      "include_dirs": [
	"-I/usr/local/include/"
      ],
      "libraries": [
	"-L/usr/local/lib/ ", "-l:libupscaledb.so " "-lcurlpp -Wl,-Bsymbolic-functions -Wl,-z,relro -lstdc++ -lcurl -L/home/watson/ -lmysqlcpp -lmysqlclient"
      ],
      "cflags": [ "-std=c++1z -g -fstack-protector-strong -fno-exceptions " ]
    }
  ]
}