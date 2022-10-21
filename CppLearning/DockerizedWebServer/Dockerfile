# Uncomment Section 1 to add minimum libraries 
# FROM gcc:7.3.0

# RUN apt-get -qq update
# RUN apt-get -qq upgrade
# RUN apt-get -qq install cmake

# RUN apt-get -qq install libboost-all-dev=1.62.0.1
# RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
#   ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
#
# Section 1 ends 

# Section 2 : to buide hello_crow app only
# FROM hello_crow
# WORKDIR /usr/src/cppweb/build
# CMD ["./hello_crow"]
# Section 2 Ends:

# Section 3 : created bbox with mongo-c and mongo-cxx drivers to use them

FROM bbox:latest

WORKDIR /usr/src/cppweb
COPY . .

WORKDIR /usr/src/cppweb/build
RUN cmake .
RUN make
CMD ["./hello_crow"]

# Section 3 : Ends
