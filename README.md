# asio_service_discovery

Components for service discovery via udp multicasting. It's using boost::asio for async networking. It's non-blocking and non-locking.

The best way to get started is having a [look at the tests](tests).
Basic functionality is derived from [boost::asios udp multicast example](http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/multicast/)
.

## requirements

- asio_service_discovery is using boost::asio, therefore you need the boost asio headers and you need to link agains boost_system.
- You also need a compiler that supports C++11
- If you want to run the tests, you also need to install cmake

## How it works

There are two components: service_announcer and service_discoverer.

### [The Announcer](include/betabugs/networking/service_announcer.hpp)

The announcer multicasts information about the service it's announcing in one second intervals.
The packet format is: service_name:computer_name:port
You have to pass service_name and service_port to the service_announcer. they can be freely chosen.

### [The Discoverer](include/betabugs/networking/service_discoverer.hpp)

The discoverer listens for incomming multicast packets that match the service_name it was configured with.
It hold a set of service_discoverer::service objects. Each time a packet comes in, it is parsed and if the
service name matches, a service_discoverer::service objects is constructed and added to the set. After that
the optional callback is called.

## a simple example

### The Announcer

```
  boost::asio::io_service io_service;
  betabugs::networking::service_announcer announcer(io_service, "my_service", 1337);
  io_service.run();
```

### The discoverer

```
  boost::asio::io_service io_service;
  betabugs::networking::service_discoverer discoverer(io_service, "my_service", 1337,
  [](const service_discoverer::services& services){
    std::clog << "my_service is available on the following machines:" << std::endl;
    for(const auto& service : services)
    {
      std::clog << "  " << service << std::endl;
    }
  });
  io_service.run();
```

## License

This library is Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt) .