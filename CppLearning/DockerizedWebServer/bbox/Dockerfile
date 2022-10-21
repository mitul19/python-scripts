FROM gcc:7.3.0

RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake

RUN apt-get -qq install libboost-all-dev=1.62.0.1
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
  ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so

WORKDIR /usr/src

# Download mongo-c-driver latest version and make it
# At the time of installation mongo-c-driver-1.23.0 was there. 
# we faced issue with ValueError: No download for "crypt_shared" was found for the requested version+target+architecture+edition so
# we removed that via https://www.mongodb.com/community/forums/t/problem-downloading-crypt-shared-when-installing-the-mongodb-c-driver/189370 
# by skipping it cmake -DMONGOC_TEST_USE_CRYPT_SHARED=OFF 
# See below.
# root@366c32d9dd6c:~# tar xvf mongo-c-driver-1.23.1.tar.gz
# root@366c32d9dd6c:~# cd mongo-c-driver-1.23.1 && mkdir cmake-build && cd cmake-build
# root@366c32d9dd6c:~/mongo-c-driver-1.23.1/cmake-build# cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DMONGOC_TEST_USE_CRYPT_SHARED=OFF .. && make && make install && ldconfig /usr/local/lib 

RUN git clone https://github.com/mongodb/mongo-c-driver.git \
&& cd mongo-c-driver && git checkout 1.23.1 \
&& mkdir cmake-build && cd cmake-build \
&& cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DMONGOC_TEST_USE_CRYPT_SHARED=OFF .. \
&& make && make install && ldconfig /usr/local/lib

# Below snippet was supplied in training but we need to enhance it.
# 
#   RUN git clone https://github.com/mongodb/mongo-cxx-driver.git \
#   --branch releases/stable --depth 1 \
#   && cd mongo-cxx-driver/build && cmake \
#   -DBSONCXX_POLY_USE_MNMLSTC=1 \
#   -DCMAKE_BUILD_TYPE=Release \
#   -DCMAKE_INSTALL_PREFIX=/usr/local \
#   -DLIBMONGOC_DIR=/usr/lib/x86_64-linux-gnu \
#   -DLIBBSON_DIR=/usr/lib/x86_64-linux-gnu \
#   -DCMAKE_MODULE_PATH=/usr/src/mongo-cxx-driver-r3.0.3/cmake .. \
#   && make EP_mnmlstc_core && make && make install && ldconfig /usr/local/lib
#
# When we run it runs below commnad
#  > [9/9] RUN git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1 
# && cd mongo-cxx-driver/build && cmake -DBSONCXX_POLY_USE_MNMLSTC=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DLIBMONGOC_DIR=/usr/lib/x86_64-linux-gnu -DLIBBSON_DIR=/usr/lib/x86_64-linux-gnu -DCMAKE_MODULE_PATH=/usr/src/mongo-cxx-driver-r3.0.3/cmake .. 
# && make EP_mnmlstc_core && make && make install && ldconfig /usr/local/lib:                                                   
#
# install Doc https://mongocxx.org/mongocxx-v3/installation/linux/ 
# Our testest and enhanced way which select desired install locations like DCMAKE_MODULE_PATH  
#   root@366c32d9dd6c:~# git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1 && cd mongo-cxx-driver/build
#   root@366c32d9dd6c:~/mongo-cxx-driver/build# cmake -DBSONCXX_POLY_USE_MNMLSTC=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DLIBMONGOC_DIR=/usr/lib/x86_64-linux-gnu -DLIBBSON_DIR=/usr/lib/x86_64-linux-gnu -DCMAKE_MODULE_PATH=/root/mongo-cxx-driver/src/mongocxx/cmake .. && make EP_mnmlstc_core && make && make install && ldconfig /usr/local/lib

RUN git clone https://github.com/mongodb/mongo-cxx-driver.git \
--branch releases/stable --depth 1 \
&& cd mongo-cxx-driver/build && cmake \
-DBSONCXX_POLY_USE_MNMLSTC=1 \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DLIBMONGOC_DIR=/usr/lib/x86_64-linux-gnu \
-DLIBBSON_DIR=/usr/lib/x86_64-linux-gnu \
-DCMAKE_MODULE_PATH=/usr/src/mongocxx/cmake .. \
&& make EP_mnmlstc_core && make && make install && ldconfig /usr/local/lib